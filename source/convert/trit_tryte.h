//
// Created by John Cottrell on 20/8/18.
//

#ifndef CIRI_TRIT_TRYTE_H
#define CIRI_TRIT_TRYTE_H

#include "utils/stdint.h"
#include "trits.h"
#include "tryte.h"

#define RADIX 3

size_t num_trytes_for_trits(size_t num_trits);
trit_t get_trit_at(tryte_t *const trytes, size_t const length, size_t index);
uint8_t set_trit_at(tryte_t *const trytes, size_t const length, size_t index,
                    trit_t trit);
void trits_to_trytes(trit_t const *const trits, tryte_t *const trytes,
                     size_t const length);
void trytes_to_trits(tryte_t const *const tryte, trit_t *const trits,
                     size_t const length);

#endif //CIRI_TRIT_TRYTE_H
