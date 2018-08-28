//
// Created by John Cottrell on 28/8/18.
//

#include "udp_worker.h"

static void udp_worker_stop_async(uv_async_t* handle) {
    uv_stop(handle->loop);
}

static void udp_worker_close(udp_worker_t* worker) {
    int r;
    QUEUE* q;

    uv_close((uv_handle_t*) &worker->udp_listener, NULL);
    uv_close((uv_handle_t*) &worker->stop_async, NULL);

    /*
    uttp_conn_t* conn;
    while (!QUEUE_EMPTY(&worker->conn_queue)) {
        q = QUEUE_HEAD(&worker->conn_queue);
        conn = QUEUE_DATA(q, udp_conn_t, queue);
        udp_conn_destroy(conn);
    }
    ASSERT(QUEUE_EMPTY(&worker->conn_queue));
    */

    r = uv_run(&worker->loop, UV_RUN_DEFAULT);
    ASSERT(r == 0);

    r = uv_loop_close(&worker->loop);
    ASSERT(r == 0);
}

static void udp_alloc_cb(uv_handle_t* client, size_t suggested_size, uv_buf_t* buf) {
    buf->base = malloc(suggested_size);
    ASSERT(buf->base != NULL);
    buf->len = suggested_size;
}


static void udp_read_cb(uv_udp_t *req, ssize_t nread, uv_buf_t *buf, struct sockaddr *addr, unsigned flags) {

    if (nread < 0) {
        log_warning(UDP_WORKER_LOGGER_ID, "UDP read error: %s - %s", uv_err_name(nread), uv_strerror(nread));
        goto end;
    }

    log_debug(UDP_WORKER_LOGGER_ID, "%.*s", (int) nread, buf->base);

    end:
    if (buf->base != NULL) {
        free(buf->base);
    }
}

static void udp_worker_run(void* arg) {
    int r;
    udp_worker_t* worker = arg;
    udp_server_t* server = worker->server;

    r = uv_udp_recv_start(server, udp_alloc_cb, udp_read_cb);
    ASSERT(r == 0);

    /* synchronize the start */
    uv_barrier_wait(&server->start_barrier);

    log_info("[%s] started", worker->name);
    uv_run(&worker->loop, UV_RUN_DEFAULT);
    log_info("[%s] stopped", worker->name);

    udp_worker_close(worker);
}

int udp_worker_start(udp_worker_t* worker, udp_worker_config_t* config) {
    int r;
    int on;
    int fd;
    udp_server_t* server = config->server;

    memset(worker, 0, sizeof(*worker));

    snprintf(worker->name, sizeof(worker->name), "Worker #%d", config->id);
    worker->server = server;
    QUEUE_INIT(&worker->conn_queue);

    r = uv_loop_init(&worker->loop);
    ASSERT(r == 0);

    r = uv_async_init(&worker->loop, &worker->stop_async, udp_worker_stop_async);
    ASSERT(r == 0);

    r = uv_udp_init_ex(&worker->loop, &worker->udp_listener, server->address.ss_family);
    ASSERT(r == 0);

    r = uv_fileno((uv_handle_t*) &worker->udp_listener, &fd);
    ASSERT(r == 0);
    ASSERT(fd != -1);

    on = 1;
    r = setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
    ASSERT(r == 0);

    r = uv_udp_bind(&worker->udp_listener, (const struct sockaddr*) &server->address, 0);
    ASSERT(r == 0);

    r = uv_thread_create(&worker->thread, udp_worker_run, worker);
    ASSERT(r == 0);

    return 0;
}


void udp_worker_stop(udp_worker_t* worker) {
    int r;
    r = uv_async_send(&worker->stop_async);
    ASSERT(r == 0);
}


int udp_worker_join(udp_worker_t* worker) {
    return uv_thread_join(&worker->thread);
}