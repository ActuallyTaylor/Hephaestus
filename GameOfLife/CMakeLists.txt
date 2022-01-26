cmake_minimum_required(VERSION 3.20)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
#set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(GameOfLife main.cpp mainLevelScene.cpp mainLevelScene.hpp)

add_library(hephaestus STATIC IMPORTED)
set_property(TARGET hephaestus PROPERTY IMPORTED_LOCATION "/${CMAKE_SOURCE_DIR}/lib/hephaestus/lib/libHephaestus.a")

target_link_libraries(GameOfLife hephaestus)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(GameOfLife glfw)

find_package(GLEW REQUIRED)
target_link_libraries(GameOfLife GLEW::GLEW)

find_package(Freetype REQUIRED)
target_link_libraries(GameOfLife Freetype::Freetype)

target_link_libraries(GameOfLife ${CMAKE_SOURCE_DIR}/lib/hephaestus/include/Library/irrKlang/lib/libirrklang.dylib)

add_custom_command(TARGET GameOfLife PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:GameOfLife>)

