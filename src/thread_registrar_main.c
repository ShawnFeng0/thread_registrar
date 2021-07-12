//
// Created by shawnfeng on 2021-07-12.
//

#include <pthread.h>

#include "thread_registrar/thread_registrar.h"

int main() __attribute__((weak));
int main() {
  tr_thread_init_all();
  pthread_exit(NULL);
}
