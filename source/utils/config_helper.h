//
// Created by John Cottrell on 20/8/18.
//
#include <argtable3.h>
#include <json.h>

#ifndef CONFIG_HELPER_H
#define CONFIG_HELPER_H

static struct json_object *cfg;

extern void set_config(struct arg_file *config);

#endif //CONFIG_HELPER_H
