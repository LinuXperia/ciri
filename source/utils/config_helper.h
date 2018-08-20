//
// Created by John Cottrell on 20/8/18.
//

#ifndef CIRI_CONFIG_HELPER_H
#define CIRI_CONFIG_HELPER_H

#include <argtable3.h>
#include <json.h>

json_object *ciri_config;

extern void set_config(struct arg_file *config);

#endif //CIRI_CONFIG_HELPER_H
