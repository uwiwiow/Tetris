cmake_minimum_required(VERSION 3.25)
project(Tetris C)

set(CMAKE_C_STANDARD 11)

add_executable(Tetris main.c)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)

target_link_libraries(${PROJECT_NAME} SDL2::Main)
