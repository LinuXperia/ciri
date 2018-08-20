//
// Created by John Cottrell on 20/8/18.
//

#include <uv.h>

#ifndef LOCK_H_
#define LOCK_H_

static uv_cond_t condvar;
static uv_mutex_t mutex;
static uv_rwlock_t rwlock;
static int step;

static void synchronize_nowait(void);
static void synchronize(void);

#endif  // LOCK_H_