cmake_minimum_required(VERSION 4.3)
project(RPG)

set(CMAKE_CXX_STANDARD 26)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(raylib)

add_executable(RPG main.cpp)

target_link_libraries(RPG PRIVATE raylib)