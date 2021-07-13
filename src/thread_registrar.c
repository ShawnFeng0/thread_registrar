//
// Created by shawnfeng on 2021-07-12.
//

#include "thread_registrar/thread_registrar.h"

#include <pthread.h>

static void *thread_entry_wrapper(void *function) {
  ((tr_thread_entry_function_t)function)();
  return NULL;
}

void tr_thread_init_all() {
  extern struct tr_thread_entry *TR_SECTION_BEGIN(TR_SECTION_NAME);
  extern struct tr_thread_entry *TR_SECTION_END(TR_SECTION_NAME);

  pthread_t thread_id;
  for (struct tr_thread_entry **i = &TR_SECTION_BEGIN(TR_SECTION_NAME);
       i < &TR_SECTION_END(TR_SECTION_NAME); i++) {
    pthread_create(&thread_id, NULL, thread_entry_wrapper, (*i)->function);
    pthread_detach(thread_id);
  }
}
