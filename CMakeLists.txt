cmake_minimum_required(VERSION 3.7)
project(chip8 C)

set(CMAKE_C_STANDARD 99)

add_executable(chip8 main.c memory.c memory.h cpu.c cpu.h display.c display.h sprite.c sprite.h chip8.c chip8.h utils.c utils.h libs/KBQueue.c libs/KBQueue.h)

find_package(OpenSSL REQUIRED)

if (WIN32)
    target_link_libraries(chip8 mingw32 SDL2main SDL2 OpenSSL::SSL)
elseif (UNIX)
    target_link_libraries(chip8 SDL2main SDL2 OpenSSL::SSL)
endif ()