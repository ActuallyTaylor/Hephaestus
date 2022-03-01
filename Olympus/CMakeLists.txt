cmake_minimum_required(VERSION 3.13)
project(Olympus)

set(CMAKE_CXX_STANDARD 17)

add_executable(Olympus main.cpp ${someResources})

add_subdirectory(Hephaestus)
target_link_libraries(Olympus Hephaestus)

add_custom_command(TARGET Olympus PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:Olympus>)
