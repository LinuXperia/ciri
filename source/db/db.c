//
// Created by John Cottrell on 27/8/18.
//

#include <sys/stat.h>
#include <string.h>
#include "db.h"

retcode_t db_load() {
    int rc;

    char* mykey;
    char* myvalue;

    logger_helper_init(DB_LOGGER_ID, debug_level, true);

    /* Note: Most error checking omitted for simplicity */

    rc = mdb_env_create(&env);
    if (rc) {
        log_info(DB_LOGGER_ID,"mdb_env_create: (%d) %s\n", rc, mdb_strerror(rc));
        goto leave;
    }

    struct stat st = {0};

    if (stat("./testdb", &st) == -1) {
        mkdir("./testdb", 0700);
    }

    rc = mdb_env_open(env, "./testdb", 0, 0664);
    if (rc) {
        log_info(DB_LOGGER_ID,"mdb_env_open: (%d) %s\n", rc, mdb_strerror(rc));
        goto leave;
    }
    rc = mdb_txn_begin(env, NULL, 0, &txn);
    if (rc) {
        log_info(DB_LOGGER_ID,"mdb_txn_begin: (%d) %s\n", rc, mdb_strerror(rc));
        goto leave;
    }
    rc = mdb_dbi_open(txn, NULL, 0, &dbi);
    if (rc) {
        log_info(DB_LOGGER_ID,"mdb_dbi_open: (%d) %s\n", rc, mdb_strerror(rc));
        goto leave;
    }

    mykey = "hello";
    myvalue = "world";

    key.mv_size = strlen(mykey);
    key.mv_data = mykey;
    data.mv_size = strlen(myvalue);
    data.mv_data = myvalue;

    //sprintf(sval, "%03x %d foo bar", 32, 3141592);
    rc = mdb_put(txn, dbi, &key, &data, 0);
    if (rc) {
        log_info(DB_LOGGER_ID,"mdb_txn_put: (%d) %s\n", rc, mdb_strerror(rc));
        goto leave;
    }

    rc = mdb_txn_commit(txn);
    if (rc) {
        log_info(DB_LOGGER_ID,"mdb_txn_commit: (%d) %s\n", rc, mdb_strerror(rc));
        goto leave;
    }
    rc = mdb_txn_begin(env, NULL, MDB_RDONLY, &txn);
    rc = mdb_cursor_open(txn, dbi, &cursor);
    while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
        char *keyn = (char *) malloc(key.mv_size + 1);
        memcpy(keyn, key.mv_data, key.mv_size);
        keyn[key.mv_size] = 0;

        char *valuen = (char *) malloc(data.mv_size + 1);
        memcpy(valuen, data.mv_data, data.mv_size);
        valuen[data.mv_size] = 0;

        log_info(DB_LOGGER_ID,"key: %s\n", keyn);
        log_info(DB_LOGGER_ID,"data: %s\n", valuen);

        free(valuen);
        free(keyn);

    }
    mdb_cursor_close(cursor);
    mdb_txn_abort(txn);

leave:
    mdb_dbi_close(env, dbi);
    mdb_env_close(env);

    return E_SUCCESS;

}