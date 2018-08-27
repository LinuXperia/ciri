//
// Created by John Cottrell on 27/8/18.
//

#ifndef CIRI_DB_H
#define CIRI_DB_H

#include <lmdb.h>
#include <utils/errors.h>
#include <utils/logger_helper.h>

#define DB_LOGGER_ID "db"

MDB_env *env;
MDB_dbi dbi;
MDB_val key;
MDB_val data;
MDB_txn *txn;
MDB_cursor *cursor;

retcode_t db_load();

#endif //CIRI_DB_H
