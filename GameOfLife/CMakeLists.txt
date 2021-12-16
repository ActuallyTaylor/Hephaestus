cmake_minimum_required(VERSION 3.20)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)

add_executable(GameOfLife main.cpp)

add_library(hephaestus STATIC IMPORTED)
set_property(TARGET hephaestus PROPERTY IMPORTED_LOCATION "/${CMAKE_SOURCE_DIR}/lib/hephaestus/lib/libHephaestus.a")

target_link_libraries(GameOfLife hephaestus)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(GameOfLife glfw)

find_package(GLEW REQUIRED)
target_link_libraries(GameOfLife GLEW::GLEW)

find_package(Freetype REQUIRED)
target_link_libraries(GameOfLife Freetype::Freetype)

