cmake_minimum_required(VERSION 3.5)
project(thread_registrar)

set(CMAKE_CXX_STANDARD 11)

option(THREAD_REGISTRAR_BUILD_EXAMPLES "Build examples" OFF)

add_library(${PROJECT_NAME} src/thread_registrar.c)
target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
target_include_directories(${PROJECT_NAME} PUBLIC include)

if (THREAD_REGISTRAR_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()
