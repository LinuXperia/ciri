//
// Created by John Cottrell on 28/8/18.
//

#ifndef TEST_SERVER_H
#define TEST_SERVER_H

#include <uv.h>
#include <utils/errors.h>
#include <utils/logger_helper.h>

#define TEST_SERVER_LOGGER_ID "test_server"

#define CHECK(r, msg)                                       \
    if (r<0) {                                              \
        fprintf(stderr, "%s: %s\n", msg, uv_strerror(r));   \
        return E_FAIL;                                      \
    }

static uv_loop_t *uv_loop;
static uv_udp_t   server;

retcode_t server_create();

#endif //TEST_SERVER_H
