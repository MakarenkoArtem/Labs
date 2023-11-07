cmake_minimum_required(VERSION 2.2)
project(Labs)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME}
        8.1.c
        libraries/mystring.c)