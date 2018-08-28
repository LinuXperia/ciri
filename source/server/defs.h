//
// Created by John Cottrell on 28/8/18.
//

#ifndef DEFS_H
#define DEFS_H

#include "uv.h"
#include "queue.h"

#define container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) - offsetof(type, member)))

#define ASSERT(x)                                                           \
    do {                                                                    \
        if (!(x)) {                                                         \
            fprintf(stderr, "%s:%u: Assertion `" #x "' failed.\n",          \
                            __FILE__, __LINE__);                            \
            abort();                                                        \
        }                                                                   \
    } while(0)                                                              \

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))


typedef struct udp_server_s udp_server_t;
typedef struct udp_worker_s udp_worker_t;

struct udp_server_s {
    uv_loop_t* loop;
    unsigned int own_loop:1;
    struct sockaddr_storage address;
    uv_signal_t sigint_h;
    uv_signal_t sigterm_h;
    uv_barrier_t start_barrier;
    udp_worker_t* workers;
};

struct udp_worker_s {
    char name[32];
    uv_loop_t loop;
    uv_async_t stop_async;
    uv_thread_t thread;
    udp_server_t* server;
    uv_udp_t udp_listener;
    QUEUE conn_queue;
    struct {
        unsigned int connections;
    } statistics;
};


typedef struct {
    uv_udp_t udp_handle;
    QUEUE queue;
    udp_worker_t* worker;
} udp_conn_t;

#endif //DEFS_H
