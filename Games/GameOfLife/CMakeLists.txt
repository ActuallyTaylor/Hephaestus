cmake_minimum_required(VERSION 3.13)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)

add_executable(GameOfLife main.cpp mainLevelScene.cpp mainLevelScene.hpp)

add_custom_command(TARGET GameOfLife PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:GameOfLife>)

add_subdirectory(../../Hephaestus ./Hephaestus/)
target_link_libraries(GameOfLife Hephaestus)

