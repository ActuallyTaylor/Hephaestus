cmake_minimum_required(VERSION 3.0.0)
project(Hephaestus VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(GLEW REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})


find_package(glfw3 REQUIRED)

link_libraries(${GLEW_LIBRARIES} glfw)

add_library(Hephaestus SHARED
            Hephaestus.hpp
            Hephaestus.cpp
            )



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
