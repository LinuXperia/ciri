//
// Created by John Cottrell on 20/8/18.
//

#ifndef CIRI_CURL_P_H
#define CIRI_CURL_P_H

#include "const.h"
#include "utils/stdint.h"
#include "convert/trits.h"

typedef struct {
    trit_t state[STATE_LENGTH];
    CurlType type;
} Curl;

void init_curl(Curl* ctx);

void curl_absorb(Curl* const ctx, trit_t const* const trits, size_t length);
void curl_squeeze(Curl* const ctx, trit_t* const trits, size_t length);
void curl_reset(Curl* const ctx);

#endif //CIRI_CURL_P_H
