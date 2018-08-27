//
// Created by John Cottrell on 20/8/18.
//

#ifndef CIRI_CONFIG_HELPER_H
#define CIRI_CONFIG_HELPER_H

#define CONFIG_HELPER_LOGGER_ID "config_helper"

#include <argtable3.h>
#include <json.h>

json_object *obj_cfg, *get_cfg;

void set_config(struct arg_file *config);

#endif //CIRI_CONFIG_HELPER_H
