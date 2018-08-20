/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef CIRI_LOGGER_HELPER_H
#define CIRI_LOGGER_HELPER_H

#include <logger.h>
#include <stdbool.h>

typedef struct logger_t logger_t;

logger_level_t debug_level;

#define LOG_LEVEL_ALL "ALL"
#define LOG_LEVEL_DEBUG "DEBUG"
#define LOG_LEVEL_INFO "INFO"
#define LOG_LEVEL_ERROR "ERROR"

#define log_debug(id, ...) logger_helper_print(id, LOGGER_DEBUG, __VA_ARGS__)
#define log_info(id, ...) logger_helper_print(id, LOGGER_INFO, __VA_ARGS__)
#define log_notice(id, ...) logger_helper_print(id, LOGGER_NOTICE, __VA_ARGS__)
#define log_warning(id, ...) \
  logger_helper_print(id, LOGGER_WARNING, __VA_ARGS__)
#define log_error(id, ...) logger_helper_print(id, LOGGER_ERR, __VA_ARGS__)
#define log_critical(id, ...) logger_helper_print(id, LOGGER_CRIT, __VA_ARGS__)
#define log_alert(id, ...) logger_helper_print(id, LOGGER_ALERT, __VA_ARGS__)
#define log_emergency(id, ...) \
  logger_helper_print(id, LOGGER_EMERG, __VA_ARGS__)

extern void logger_helper_init(const char* const logger_id,
                               logger_level_t level, bool enable_color);
extern void logger_helper_destroy(const char* const logger_id);
extern void logger_helper_print(const char* const logger_id,
                                logger_level_t level, const char* format, ...);
extern void logger_helper_printer(const char* const string);


#endif  // CIRI_LOGGER_HELPER_H