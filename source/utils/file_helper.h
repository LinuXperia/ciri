//
// Created by John Cottrell on 20/8/18.
//
#ifndef CIRI_FILE_HELPER_H
#define CIRI_FILE_HELPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct binary_data_t binary_data_t;
struct binary_data_t {
    long size;
    void *data;
};

binary_data_t * read_file(const char *filename);

#ifdef __cplusplus
}
#endif

#endif //CIRI_FILE_HELPER_H