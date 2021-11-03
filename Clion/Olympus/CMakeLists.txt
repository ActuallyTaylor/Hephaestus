cmake_minimum_required(VERSION 3.20)
project(Olympus)

set(CMAKE_CXX_STANDARD 17)

add_executable(Olympus main.cpp)

add_subdirectory(Hephaestus)

target_link_libraries(Olympus Hephaestus)