//
// Created by John Cottrell on 28/8/18.
//

#include <utils/config_helper.h>
#include "test_server.h"

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

retcode_t server_create() {

    logger_helper_init(TEST_SERVER_LOGGER_ID, debug_level, true);

    int r;
    struct sockaddr_in addr;
    uv_loop = uv_default_loop();

    r = uv_udp_init(uv_loop, &server);
    CHECK(r, "init");

    json_pointer_get(obj_cfg, "/node/port", &get_cfg);
    int port = json_object_get_int(get_cfg);
    log_info(TEST_SERVER_LOGGER_ID, "Node port: %d\n", port);

    uv_ip4_addr("0.0.0.0", port, &addr);

    r = uv_udp_bind(&server, (const struct sockaddr *) &addr, 0);
    CHECK(r, "bind");

    r = uv_udp_recv_start(&server, on_alloc, on_recv);
    CHECK(r, "recv");

    r = uv_run(uv_loop, UV_RUN_DEFAULT);

    return E_SUCCESS;
}