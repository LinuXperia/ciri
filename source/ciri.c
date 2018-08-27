#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <argtable3.h>

#include <utils/logger_helper.h>
#include <utils/config_helper.h>
#include <db/db.h>
#include <server/server.h>


#define MAIN_LOGGER_ID "main"

int main(int argc,char *argv[]) {

    int exitcode = 0;
    char progname[] = "ciri";

    struct arg_lit *help = arg_lit0(NULL, "help", "display this help and exit");
    struct arg_lit *version = arg_lit0(NULL, "version", "display version info and exit");
    struct arg_file *config = arg_file0("c", "config", "config.json", "ciri configuration");
    struct arg_str *dlvl = arg_strn("d", "debug", NULL, 0, argc+2, "debug level");
    struct arg_end *end = arg_end(20);

    void *argtable[] = { help, version, config, dlvl, end };

    int nerrors = arg_parse(argc,argv,argtable);

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

    set_config(config);

    retcode_t db = db_load();
    retcode_t svr = server_create();
    //int status = server_create();


exit:
    /* deallocate each non-null entry in argtable[] */
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));

    return exitcode;
}