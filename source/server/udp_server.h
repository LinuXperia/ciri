
#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <uv.h>
#include <utils/errors.h>
#include <utils/logger_helper.h>

#define UDP_SERVER_LOGGER_ID "udp_server"

#include "defs.h"


typedef struct {
    char* interface;
    unsigned short port;
    unsigned int nworkers;
} udp_server_config_t;


int udp_server_run(udp_server_t* server, udp_server_config_t* config, uv_loop_t* loop);

void udp_server_close(udp_server_t* server);

#endif  // UDP_SERVER_H