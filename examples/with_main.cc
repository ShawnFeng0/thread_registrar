//
// Created by shawnfeng on 2021-07-12.
//
#include <unistd.h>

#include <iostream>

#include "thread_registrar/thread_registrar.h"

#define LOGGER_TOKEN(token) \
  std::cout << __FUNCTION__ << ": " << #token << " -> " << token << std::endl

void thread_1() {
  int i = 1;
  while (i--) {
    LOGGER_TOKEN(i);
    sleep(1);
  }
}
TR_REGISTER_THREAD_ENTRY(thread_1);

void thread_2() {
  int i = 2;
  while (i--) {
    LOGGER_TOKEN(i);
    sleep(1);
  }
}
TR_REGISTER_THREAD_ENTRY(thread_2);

void thread_3() {
  int i = 3;
  while (i--) {
    LOGGER_TOKEN(i);
    sleep(1);
  }
}
TR_REGISTER_THREAD_ENTRY(thread_3);

int main() {
  printf("%s\n", "Start from main.");
  tr_thread_init_all();
  pthread_exit(nullptr);
}
