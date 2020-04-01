cmake_minimum_required(VERSION 3.15)
project(chip8 C)

set(CMAKE_C_STANDARD 99)

add_executable(chip8 main.c)

target_link_libraries(chip8 mingw32 SDL2main SDL2)