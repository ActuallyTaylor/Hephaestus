cmake_minimum_required(VERSION 3.20)
project(Hephaestus)

set(CMAKE_CXX_STANDARD 17)

add_library(Hephaestus Hephaestus.cpp Hephaestus.cpp Hephaestus.hpp Window/Window.cpp Window/Window.hpp Shader/Shader.cpp Shader/Shader.hpp)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(Hephaestus glfw)

find_package(GLEW REQUIRED)
target_link_libraries(Hephaestus GLEW::GLEW)