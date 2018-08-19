#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uv.h"
#include "lmdb.h"
#include <json.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "utils/logger_helper.h"

#define MAIN_LOGGER_ID "main"

#define CHECK(r, msg)                                       \
    if (r<0) {                                              \
        fprintf(stderr, "%s: %s\n", msg, uv_strerror(r));   \
        exit(1);                                            \
    }

static uv_loop_t *uv_loop;
static uv_udp_t   server;

static void on_recv(uv_udp_t* handle, ssize_t nread, const uv_buf_t* rcvbuf, const struct sockaddr* addr, unsigned flags) {
    if (nread > 0) {
        printf("%lu\n",nread);
        printf("%s",rcvbuf->base);
    }
    printf("free  :%lu %p\n",rcvbuf->len,rcvbuf->base);
    free(rcvbuf->base);
}

static void on_alloc(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf) {
    buf->base = malloc(suggested_size);
    buf->len = suggested_size;
    printf("malloc:%lu %p\n",buf->len,buf->base);
}

int main(int argc,char *argv[]) {



    /*
    struct json_object *jobj;
    char *str = "{ \"msg-type\": [ \"0xdeadbeef\", \"irc log\" ], \
		\"msg-from\": { \"class\": \"soldier\", \"name\": \"Wixilav\" }, \
		\"msg-to\": { \"class\": \"supreme-commander\", \"name\": \"[Redacted]\" }, \
		\"msg-log\": [ \
			\"soldier: Boss there is a slight problem with the piece offering to humans\", \
			\"supreme-commander: Explain yourself soldier!\", \
			\"soldier: Well they don't seem to move anymore...\", \
			\"supreme-commander: Oh snap, I came here to see them twerk!\" \
			] \
		}";

    printf("str:\n---\n%s\n---\n\n", str);

    jobj = json_tokener_parse(str);
    printf("jobj from str:\n---\n%s\n---\n", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
    */

    if (LOGGER_VERSION != logger_version()) {
        return EXIT_FAILURE;
    }
    logger_init();
    logger_output_register(stdout);
    logger_output_level_set(stdout, LOGGER_DEBUG);
    logger_helper_init(MAIN_LOGGER_ID, LOGGER_DEBUG, true);

    log_info(MAIN_LOGGER_ID, "Initializing cIRI core\n");

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
        printf("key: %p %.*s, data: %p %.*s\n",
               key.mv_data,  (int) key.mv_size,  (char *) key.mv_data,
               data.mv_data, (int) data.mv_size, (char *) data.mv_data);
    }
    mdb_cursor_close(cursor);
    mdb_txn_abort(txn);
    leave:
    mdb_dbi_close(env, dbi);
    mdb_env_close(env);
    return 0;

    int status;
    struct sockaddr_in addr;
    uv_loop = uv_default_loop();

    status = uv_udp_init(uv_loop,&server);
    CHECK(status,"init");

    uv_ip4_addr("0.0.0.0", 14600, &addr);

    status = uv_udp_bind(&server, (const struct sockaddr*)&addr,0);
    CHECK(status,"bind");

    status = uv_udp_recv_start(&server, on_alloc, on_recv);
    CHECK(status,"recv");

    return uv_run(uv_loop, UV_RUN_DEFAULT);
}