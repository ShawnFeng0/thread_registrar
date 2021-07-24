//
// Created by shawnfeng on 2021-07-12.
//

#pragma once

#include <pthread.h>

typedef void (*tr_thread_entry_function_t)();

struct tr_thread_entry {
  tr_thread_entry_function_t function;
};

#define TR_SECTION_NAME .tr_threads

// __attribute((__used__)) Prevent being optimized
#define TR_SECTION_(section) __attribute((used, __section__(#section)))
#define TR_SECTION(section) TR_SECTION_(section)

#define TR_REGISTER_THREAD_ENTRY(func)                              \
  static struct tr_thread_entry tr_register_##func = {              \
      .function = (func),                                           \
  };                                                                \
  static struct tr_thread_entry *tr_register_##func##_p TR_SECTION( \
      TR_SECTION_NAME) = &tr_register_##func

#define TR_CAT(a, b) a##b
#define TR_SECTION_BEGIN(section) TR_CAT(__start_, section)
#define TR_SECTION_END(section) TR_CAT(__stop_, section)

extern struct tr_thread_entry *_tr_start;
extern struct tr_thread_entry *_tr_stop;

#ifdef __cplusplus
extern "C" {
#endif

static inline void *thread_entry_wrapper(void *function) {
  ((tr_thread_entry_function_t)function)();
  return NULL;
}

static inline void tr_thread_init_all() {
  pthread_t thread_id;
  for (struct tr_thread_entry **i = &_tr_start; i < &_tr_stop; i++) {
    pthread_create(&thread_id, NULL, thread_entry_wrapper,
                   (void *)((*i)->function));
    pthread_detach(thread_id);
  }
}

#ifdef __cplusplus
}
#endif
