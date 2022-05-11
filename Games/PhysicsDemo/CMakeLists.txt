cmake_minimum_required(VERSION 3.22)
project(PhysicsDemo)

set(CMAKE_CXX_STANDARD 14)

add_executable(PhysicsDemo main.cpp)

add_subdirectory(../../Hephaestus ./Hephaestus/)
target_link_libraries(PhysicsDemo Hephaestus)

add_custom_command(TARGET PhysicsDemo PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:PhysicsDemo>)
