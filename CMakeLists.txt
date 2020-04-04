cmake_minimum_required(VERSION 3.15)
project(chip8 C)

set(CMAKE_C_STANDARD 99)

add_executable(chip8 main.c memory.c memory.h cpu.c cpu.h display.c display.h sprite.c sprite.h chip8.c chip8.h eventsHandler.c eventsHandler.h)

if (WIN32)
    target_link_libraries(chip8 mingw32 SDL2main SDL2)
elseif (UNIX)
    target_link_libraries(chip8 SDL2main SDL2)
endif ()