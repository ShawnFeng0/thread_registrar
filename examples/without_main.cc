#include <unistd.h>

#include <cstdio>

#include "thread_registrar/thread_registrar.h"

#define LOGGER_MARK() printf("%s:%d\r\n", __PRETTY_FUNCTION__, __LINE__)

static void thread_1() {
  int i = 2;
  while (i--) {
    LOGGER_MARK();
    sleep(1);
  }
}
TR_REGISTER_THREAD_ENTRY(thread_1);

static void thread_2() {
  int i = 3;
  while (i--) {
    LOGGER_MARK();
    sleep(1);
  }
}
TR_REGISTER_THREAD_ENTRY(thread_2);
