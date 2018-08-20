//
// Created by John Cottrell on 20/8/18.
//

#ifndef CIRI_DIGEST_H
#define CIRI_DIGEST_H

#include "curl-p.h"

#ifdef __cplusplus
extern "C" {
#endif

void curl_digest(trit_t const* const trits, size_t const len, trit_t* const out,
                 Curl* const curl);

#ifdef __cplusplus
}
#endif

#endif //CIRI_DIGEST_H
