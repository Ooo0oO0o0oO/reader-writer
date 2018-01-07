cmake_minimum_required(VERSION 3.9)
project(finalpro C)

set(CMAKE_C_STANDARD 99)

add_executable(finalpro writer.c semaphore.h semaphore.c reader.c lock.h lock.c go.c)