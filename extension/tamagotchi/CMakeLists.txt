cmake_minimum_required(VERSION 3.28)
project(tamagotchi C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "-lncurses")
find_package(Curses REQUIRED)
include_directories(/opt/homebrew/Cellar/ncurses/6.5/include)
add_executable(tamagotchi main.c
        display_tamagotchi.c
        display_tamagotchi.h
        welcome_screen.h
        welcome_screen.c)
target_link_libraries(tamagotchi ncurses)
