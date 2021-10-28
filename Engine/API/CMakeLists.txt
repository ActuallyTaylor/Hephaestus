cmake_minimum_required(VERSION 3.0.0)
project(Hephaestus VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(Hephaestus SHARED
            Hephaestus.hpp
            Hephaestus.cpp
            )

# OpenGL
# find_package(OpenGL REQUIRED)

# GLM
# find_package(GLM REQUIRED)
# message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# GLFW
# find_package(GLFW3 REQUIRED)
# message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

# set(LIBS glfw3)

# target_link_libraries(Hephaestus ${LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
