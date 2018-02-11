cmake_minimum_required(VERSION 3.9)
project(cli)

set(CMAKE_CXX_STANDARD 11)

include_directories(/home/parallels/course/api)
link_directories(/home/parallels/course/api)

add_executable(cli main.cpp)
target_link_libraries(cli PUBLIC libapi.so)