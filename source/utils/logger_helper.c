/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://gitlab.com/iota-foundation/software/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#include <stdio.h>
#include <time.h>
#include <uv.h>
#include <assert.h>

#include "logger_helper.h"

//See: https://github.com/trevnorris/libuv-examples

static uv_mutex_t mutex;

void logger_helper_init(const char* const logger_id, logger_level_t level,
                        bool enable_color) {
    logger_id_t id;
    uv_mutex_init(&mutex);
    /* get a logging id, enable it and set log level */
    id = logger_id_request(logger_id);
    logger_id_enable(id);
    logger_id_level_set(id, level);
    logger_id_prefix_set(id, (LOGGER_PFX_DATE | LOGGER_PFX_NAME | LOGGER_PFX_LEVEL));
    if (enable_color) {
        logger_color_prefix_enable();
        logger_color_message_enable();
        logger_id_color_console_set(id, LOGGER_FG_MAGENTA, LOGGER_BG_UNCHANGED,
                                    LOGGER_ATTR_BRIGHT | LOGGER_ATTR_UNDERLINE);
    }
}

void logger_helper_destroy(const char* const logger_id) {
    logger_id_t id;
    uv_mutex_lock(&mutex);
    id = logger_id_request(logger_id);
    logger_id_release(id);
    uv_mutex_unlock(&mutex);
    uv_mutex_destroy(&mutex);
}

void logger_helper_print(const char* const logger_id, logger_level_t level,
                         const char* format, ...) {
    logger_id_t id;
    va_list argp;

    va_start(argp, format);
    uv_mutex_lock(&mutex);
    id = logger_id_request(logger_id);
    logger_va(id, level, format, argp);
    uv_mutex_unlock(&mutex);
    va_end(argp);
}