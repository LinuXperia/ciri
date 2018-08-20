//
// Created by John Cottrell on 20/8/18.
//

#ifndef CIRI_TRIT_BYTE_H
#define CIRI_TRIT_BYTE_H

#include "bytes.h"
#include "trits.h"

size_t min_bytes(size_t);
byte_t trits_to_byte(trit_t const *const trits, byte_t const cum,
                     size_t const i);
void trits_to_bytes(trit_t *, byte_t *, size_t);
void byte_to_trits(byte_t byte, trit_t *const trit, size_t const i);
void bytes_to_trits(byte_t const *const byte, size_t const n_bytes,
                    trit_t *const trit, size_t const n_trits);

#endif //CIRI_TRIT_BYTE_H



