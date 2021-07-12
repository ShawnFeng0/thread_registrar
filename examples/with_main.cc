//
// Created by shawnfeng on 2021-07-12.
//
#include <unistd.h>

#include <iostream>

#include "thread_registrar/thread_registrar.h"

#define LOGGER_MARK() printf("%s:%d\r\n", __PRETTY_FUNCTION__, __LINE__)

void thread_1() {
  int i = 2;
  while (i--) {
    LOGGER_MARK();
    sleep(1);
  }
}
TR_REGISTER_THREAD_ENTRY(thread_1);

void thread_2() {
  int i = 3;
  while (i--) {
    LOGGER_MARK();
    sleep(1);
  }
}
TR_REGISTER_THREAD_ENTRY(thread_2);

int main() {
  printf("%s\n", "Start from main.");
  tr_thread_init_all();
  pthread_exit(nullptr);
}
