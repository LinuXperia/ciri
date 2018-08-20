//
// Created by John Cottrell on 20/8/18.
//
#include "lock.h"

/* Call when holding |mutex|. */
static void synchronize_nowait(void) {
    step += 1;
    uv_cond_signal(&condvar);
}


/* Call when holding |mutex|. */
static void synchronize(void) {
    int current;

    synchronize_nowait();
    /* Wait for the other thread.  Guard against spurious wakeups. */
    for (current = step; current == step; uv_cond_wait(&condvar, &mutex));
    ASSERT(step == current + 1);
}