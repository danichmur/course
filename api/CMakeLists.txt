cmake_minimum_required(VERSION 3.9)
project(api)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp server.c client.c server.h client.h api.h)

add_library(api SHARED ${SOURCE_FILES})
