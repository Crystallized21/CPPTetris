cmake_minimum_required(VERSION 3.29)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

set(MY_SOURCES main.cpp)

add_executable(my_game ${MY_SOURCES})
target_link_libraries(my_game PRIVATE SDL2::SDL2)

add_executable(Tetris main.cpp)
target_link_libraries(Tetris PRIVATE SDL2::SDL2)