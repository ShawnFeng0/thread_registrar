# thread_registrar

使用C语言和GCC编译器的特性写成的线程注册库, 使嵌入式软件中守护线程(不必销毁)的创建更加方便.

原理: 在编译期间使用函数宏注册线程函数, 并自动在`main`函数中使用`pthread_create`启动各个注册的函数.

## 依赖

编译器: gcc

库: `pthread`

## 怎么使用

代码库使用cmake构建, 包含两个代码库`thread_registrar`和`thread_registrar_main`, 其中`thread_registrar_main`附带一个被gcc的`weak`属性修饰的`main`函数.

下载源码后使用cmake脚本集成到项目中:

```cmake
add_subdirectory(thread_registrar)
target_link_libraries(xxx PUBLIC thread_registrar) # or thread_registrar_main
```

创建一个线程仅需要包含头文件然后使用`TR_REGISTER_THREAD_ENTRY`函数宏注册:

```C
// example.c:
#include "thread_registrar/thread_registrar.h"

void some_thread_entry() {
    while (true) {
        // do_something()...
    }
}
TR_REGISTER_THREAD_ENTRY(some_thread_entry);
```

创建的线程的方式有两种, 类似gtest测试框架. 

1. `thread_registrar_main`库自带一个被`__attribute__((weak))`属性修饰的main()函数, 会在其中启动所有被注册的线程入口.

或者

2. 在自定义的`main()`函数中显式调用 `tr_thread_init_all()`构造所有线程.

具体可参考[examples](examples)文件夹中的例子.

## 相关技术

1. 借助gcc的`__attribute((__section__(section_name))) __attribute((__used__))`属性, 把函数指针放到同一个section名中.
2. 借助gcc编译源文件后会给section添加`__start_section`和`__stop_section`两个符号的特性, 获取函数数组的起始位置和结束位置.
3. 借助gcc的`__attribute__((weak))`属性修饰内部`main`函数, 在外部没有定义`main`函数时自动使用内部`main`函数.
