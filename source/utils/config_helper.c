//
// Created by John Cottrell on 20/8/18.
//

#include <argtable3.h>
#include <json.h>

#include "file_helper.h"
#include "logger_helper.h"
#include "config_helper.h"

void set_config(struct arg_file *config) {

    logger_helper_init(CONFIG_HELPER_LOGGER_ID, debug_level, true);

    if (config->count > 0) {
        log_info(CONFIG_HELPER_LOGGER_ID, "Config file: %s\n", config->filename[0]);

        binary_data_t *config_file = read_file(config->filename[0]);

        if (config_file->size > 0) {
            obj_cfg = json_tokener_parse(config_file->data);
            free(config_file);
            //log_info(CONFIG_HELPER_LOGGER_ID,"%s", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
        }
    }
}