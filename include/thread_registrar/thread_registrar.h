//
// Created by shawnfeng on 2021-07-12.
//

#pragma once

typedef void (*tr_thread_entry_function_t)();

struct tr_thread_entry {
  tr_thread_entry_function_t function;
};

#define TR_SECTION_NAME tr_thread_entry_section

#define TR_SECTION_(section) \
  __attribute((__section__(#section))) __attribute((__used__))
#define TR_SECTION(section) TR_SECTION_(section)

#define TR_CAT(a, b) a##b
#define TR_SECTION_BEGIN(section) TR_CAT(__start_, section)
#define TR_SECTION_END(section) TR_CAT(__stop_, section)

// __attribute((__used__)) Prevent being optimized
#define TR_REGISTER_THREAD_ENTRY(func)                            \
  static struct tr_thread_entry __default_init_##func TR_SECTION( \
      TR_SECTION_NAME) = {                                        \
      .function = (func),                                         \
  }

#ifdef __cplusplus
extern "C" {
#endif

void tr_thread_init_all();

#ifdef __cplusplus
}
#endif
