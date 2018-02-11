cmake_minimum_required(VERSION 2.8.9)

project (a.out)
include_directories(include)
file(GLOB SOURCES "src/*.c")
add_executable(${PROJECT_NAME} main.c ${SOURCES})
target_link_libraries(${PROJECT_NAME} progbase)