#cmake_minimum_required(VERSION 2.2)
project(Labs)

set(CMAKE_C_STANDARD 11)
link_libraries(m)                #for math.h
add_executable(${PROJECT_NAME}
        1.2.c)
        #libraries/mystring.c)