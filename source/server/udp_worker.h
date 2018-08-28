//
// Created by John Cottrell on 28/8/18.
//

#ifndef UDP_WORKER_H
#define UDP_WORKER_H

#include <utils/logger_helper.h>

#include "defs.h"

#define UDP_WORKER_LOGGER_ID "udp_worker"

typedef struct {
    unsigned int id;
    udp_server_t* server;
} udp_worker_config_t;


int udp_worker_start(udp_worker_t* worker, udp_worker_config_t* config);

void udp_worker_stop(udp_worker_t* worker);

int udp_worker_join(udp_worker_t* worker);

#endif //UDP_WORKER_H
