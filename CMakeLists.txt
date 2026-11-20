cmake_minimum_required(VERSION 4.3)
project(RPG)

set(CMAKE_CXX_STANDARD 26)

find_package(nlohmann_json 3.11.2 REQUIRED)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(PLATFORM SDL CACHE STRING "raylib backend" FORCE) # for joystick vibration
add_subdirectory(raylib)

add_executable(RPG main.cpp)

target_link_libraries(RPG PRIVATE raylib)

target_link_libraries(RPG PRIVATE nlohmann_json::nlohmann_json)