cmake_minimum_required(VERSION 3.28)
project(tamagotchi C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "-lncurses")
find_package(Curses REQUIRED)
include_directories(./opt/homebrew/Cellar/ncurses/6.5/include)
add_executable(server src/server.c)
add_executable(tamagotchi src/main.c
        src/display_tamagotchi.c
        include/display_tamagotchi.h
        include/welcome_screen.h
        src/welcome_screen.c
        src/load_stats.c
        include/load_stats.h
        src/eat_animation.c
        animation/eat_animation.h
        src/food_opt.c
        include/food_opt.h
        src/load_stats.c
        include/load_stats.h
        src/play_opt.c
        include/play_opt.h
        src/poop_opt.c
        include/poop_opt.h
        src/save_opt.c
        include/save_opt.h
        src/save_stats.c
        include/save_stats.h
        src/sick_opt.c
        include/sick_opt.h
        include/stats_def.h
        src/stats_opt.c
        include/stats_opt.h
        src/select_menu.c
        include/select_menu.h
        src/change_stats.c
        include/change_stats.h
        src/change_stats.c
        include/change_stats.h
        include/character_profile.h
        src/pass_away.c
        include/pass_away.h
        animation/tamagotchi_frames.h
        animation/menu_frames.h
        animation/status_frames.h
        src/intialise_tamagotchi.c
        include/initialise_tamagotchi.h
        "src/send_chat.c"
        "include/send_chat.h"
        src/happy_emote.c
        include/happy_emote.h)
target_link_libraries(tamagotchi ncurses)
