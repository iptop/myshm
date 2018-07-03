cmake_minimum_required(VERSION 3.8)
project(myshm)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c shm_queue.c shm_queue.h opt_time.h)
add_executable(myshm ${SOURCE_FILES})