cmake_minimum_required(VERSION 3.5)
project(thread_registrar)

set(CMAKE_CXX_STANDARD 11)

option(THREAD_REGISTRAR_BUILD_EXAMPLES "Build examples" OFF)

add_library(${PROJECT_NAME} src/thread_registrar.c)
target_link_options(${PROJECT_NAME} PUBLIC -pthread)
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_library(${PROJECT_NAME}_main src/thread_registrar_main.c)
target_link_libraries(${PROJECT_NAME}_main PUBLIC ${PROJECT_NAME})

if (THREAD_REGISTRAR_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()
