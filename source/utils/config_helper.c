//
// Created by John Cottrell on 20/8/18.
//

#include <argtable3.h>
#include <json.h>

#include "file_helper.h"
#include "logger_helper.h"
#include "config_helper.h"

#define CONFIG_HELPER_LOGGER_ID "config_helper"

void set_config(struct arg_file *config) {

    logger_helper_init(CONFIG_HELPER_LOGGER_ID, debug_level, true);

    if (config->count > 0) {
        log_info(CONFIG_HELPER_LOGGER_ID, "Config file: %s\n", config->filename[0]);

        binary_data_t *config_file = read_file(config->filename[0]);

        struct json_object *jobj2;
        if (config_file->size > 0) {
            ciri_config = json_tokener_parse(config_file->data);
            free(config_file);
            //log_info(CONFIG_HELPER_LOGGER_ID,"%s", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
            json_pointer_get(ciri_config, "/node/port", &jobj2);
            int port = json_object_get_int(jobj2);
            log_info(CONFIG_HELPER_LOGGER_ID, "Node port: %d\n", port);
        }
    }
}