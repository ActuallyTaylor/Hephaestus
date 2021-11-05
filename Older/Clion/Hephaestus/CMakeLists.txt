cmake_minimum_required(VERSION 3.20)
project(Hephaestus)

set(CMAKE_CXX_STANDARD 14)

add_executable(Hephaestus main.cpp API/Hephaestus.cpp API/Hephaestus.hpp)
