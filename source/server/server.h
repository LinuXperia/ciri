
#ifndef CIRI_SERVER_H
#define CIRI_SERVER_H

#include <uv.h>
#include <utils/errors.h>

#define SERVER_LOGGER_ID "server"

#define CHECK(r, msg)                                       \
    if (r<0) {                                              \
        fprintf(stderr, "%s: %s\n", msg, uv_strerror(r));   \
        return E_FAIL;                                      \
    }

static uv_loop_t *uv_loop;
static uv_udp_t   server;

retcode_t server_create();

#endif  // CIRI_SERVER_H