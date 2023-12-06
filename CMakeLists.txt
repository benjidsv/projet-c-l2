cmake_minimum_required(VERSION 3.24)
project(projet_c_L2 C)

set(CMAKE_C_STANDARD 23)

add_executable(projet_c_L2 main.c al_cell.h al_list.h timer/timer.h al_cell.c al_list.c timer/timer.c agenda.c agenda.h)
