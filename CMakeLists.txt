cmake_minimum_required(VERSION 3.5.1)
project(daemon.out)
include_directories(include)
file(GLOB SOURCES "src/*.c")
add_executable(${PROJECT_NAME} main.c ${SOURCES})
SET(CMAKE_C_FLAGS "")

target_link_libraries(${PROJECT_NAME} check m rt pthread pcap)
