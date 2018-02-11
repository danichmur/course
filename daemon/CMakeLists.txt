cmake_minimum_required(VERSION 3.9)
project(daemon)

set(CMAKE_CXX_STANDARD 11)

set(LIB_API_PATH /home/parallels/course/api)
set(LIB_RRD_PATH /home/parallels/course/rddtool)

include_directories(${LIB_API_PATH} ${LIB_RRD_PATH} ${LIB_RRD_PATH}/iniparser)
link_directories(${LIB_API_PATH} ${LIB_RRD_PATH} ${LIB_RRD_PATH}/iniparser)

add_executable(daemon main.cpp)
target_link_libraries(daemon PUBLIC libapi.so)
target_link_libraries(daemon PUBLIC librrdtool.a)

