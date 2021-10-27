cmake_minimum_required(VERSION 3.0.0)
project(Olympus VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(API)

add_executable(Olympus main.cpp)

target_link_libraries(Olympus Hephaestus)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
