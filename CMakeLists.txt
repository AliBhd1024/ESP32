cmake_minimum_required(VERSION 3.23)
project(ESP32 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ESP32
        src/diffieHellman.c
        src/header1.h)
