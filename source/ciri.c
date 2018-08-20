#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lmdb.h>
#include <json.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <argtable3.h>

#include "utils/logger_helper.h"
#include "utils/file_helper.h"
#include "server/server.h"

#define MAIN_LOGGER_ID "main"

struct arg_lit *help, *version;
struct arg_file *config;
struct arg_str *dlvl;
struct arg_end *end;

int main(int argc,char *argv[]) {

    void *argtable[] = {
            help    = arg_lit0(NULL, "help", "display this help and exit"),
            version = arg_lit0(NULL, "version", "display version info and exit"),
            config  = arg_file0("c", "config", "config.json", "ciri configuration"),
            dlvl    = arg_strn("d", "debug", NULL, 0, argc+2, "debug level"),
            end     = arg_end(20),
    };

    int exitcode = 0;
    char progname[] = "ciri";

    int nerrors;
    nerrors = arg_parse(argc,argv,argtable);

    /* special case: '--help' takes precedence over error reporting */
    if (help->count > 0) {
        printf("Usage: %s", progname);
        arg_print_syntax(stdout, argtable, "\n");
        printf("List information about the FILE(s) "
               "(the current directory by default).\n\n");
        arg_print_glossary(stdout, argtable, "  %-25s %s\n");
        exitcode = EXIT_SUCCESS;
        goto exit;
    }

    /* If the parser returned any errors then display them and exit */
    if (nerrors > 0)
    {
        /* Display the error details contained in the arg_end struct.*/
        arg_print_errors(stdout, end, progname);
        printf("Try '%s --help' for more information.\n", progname);
        exitcode = EXIT_FAILURE;
        goto exit;
    }

    if (LOGGER_VERSION != logger_version()) {
        return EXIT_FAILURE;
    }
    logger_init();
    logger_output_register(stdout);

    if (dlvl->count > 0) {
        printf("Logging set to %s\n", *dlvl->sval);
    }

    logger_level_t debug_level;
    if (strcasecmp(*dlvl->sval, LOG_LEVEL_ALL) == 0) {
        debug_level = LOGGER_ALL;
    } else if (strcasecmp(*dlvl->sval, LOG_LEVEL_INFO) == 0) {
        debug_level = LOGGER_INFO;
    } else if (strcasecmp(*dlvl->sval, LOG_LEVEL_ERROR) == 0) {
            debug_level = LOGGER_ERR;
    } else {
        debug_level = LOGGER_DEBUG;
    }

    logger_output_level_set(stdout, debug_level);
    logger_helper_init(MAIN_LOGGER_ID, debug_level, true);

    log_info(MAIN_LOGGER_ID, "Initializing %s\n", progname);

    if (config->count > 0) {
        log_info(MAIN_LOGGER_ID, "Config file: %s\n", config->filename[0]);

        binary_data_t *config_file = read_file(config->filename[0]);

        struct json_object *jobj, *jobj2;
        if (config_file->size > 0) {
            jobj = json_tokener_parse(config_file->data);
            free(config_file);
            //log_info(MAIN_LOGGER_ID,"%s", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
            json_pointer_get(jobj, "/node/port", &jobj2);
            int port = json_object_get_int(jobj2);
            log_info(MAIN_LOGGER_ID, "Node port: %d\n", port);
        }
    }

    int rc;
    MDB_env *env;
    MDB_dbi dbi;
    MDB_val key, data;
    MDB_txn *txn;
    MDB_cursor *cursor;
    char sval[32];

    /* Note: Most error checking omitted for simplicity */

    rc = mdb_env_create(&env);
    if (rc) {
        fprintf(stderr, "mdb_env_create: (%d) %s\n", rc, mdb_strerror(rc));
        goto leave;
    }

    struct stat st = {0};

    if (stat("./testdb", &st) == -1) {
        mkdir("./testdb", 0700);
    }

    rc = mdb_env_open(env, "./testdb", 0, 0664);
    if (rc) {
        fprintf(stderr, "mdb_env_open: (%d) %s\n", rc, mdb_strerror(rc));
        goto leave;
    }
    rc = mdb_txn_begin(env, NULL, 0, &txn);
    if (rc) {
        fprintf(stderr, "mdb_txn_begin: (%d) %s\n", rc, mdb_strerror(rc));
        goto leave;
    }
    rc = mdb_dbi_open(txn, NULL, 0, &dbi);
    if (rc) {
        fprintf(stderr, "mdb_dbi_open: (%d) %s\n", rc, mdb_strerror(rc));
        goto leave;
    }

    key.mv_size = sizeof(int);
    key.mv_data = sval;
    data.mv_size = sizeof(sval);
    data.mv_data = sval;

    sprintf(sval, "%03x %d foo bar", 32, 3141592);
    rc = mdb_put(txn, dbi, &key, &data, 0);
    rc = mdb_txn_commit(txn);
    if (rc) {
        fprintf(stderr, "mdb_txn_commit: (%d) %s\n", rc, mdb_strerror(rc));
        goto leave;
    }
    rc = mdb_txn_begin(env, NULL, MDB_RDONLY, &txn);
    rc = mdb_cursor_open(txn, dbi, &cursor);
    while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
        log_info(MAIN_LOGGER_ID,"key: %p %.*s, data: %p %.*s\n",
               key.mv_data,  (int) key.mv_size,  (char *) key.mv_data,
               data.mv_data, (int) data.mv_size, (char *) data.mv_data);
    }
    mdb_cursor_close(cursor);
    mdb_txn_abort(txn);
    leave:
    mdb_dbi_close(env, dbi);
    mdb_env_close(env);

    //int status = server_create();


exit:
    /* deallocate each non-null entry in argtable[] */
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));

    return exitcode;
}