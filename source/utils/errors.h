//
// Created by John Cottrell on 27/8/18.
//

#ifndef CIRI_ERRORS_H
#define CIRI_ERRORS_H

#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ERROR_CODES(X)                                        \
    X(0,    E_SUCCESS,            "No error at all!")         \
    X(-1,   E_FAIL,               "An error occurred")        \

#define ERROR_ENUM(ID, NAME, TEXT) NAME = ID,
#define ERROR_TEXT(ID, NAME, TEXT) case ID: return TEXT;

enum retcode_t {
    ERROR_CODES(ERROR_ENUM)
};

    /*
const char *get_error(int code)
{
    switch (code) {
        ERROR_CODES(ERROR_TEXT)
    }

    return "Unknown error";
}
     */

typedef enum retcode_t retcode_t;

#ifdef __cplusplus
}
#endif

#endif //CIRI_ERRORS_H
