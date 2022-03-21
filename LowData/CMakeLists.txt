cmake_minimum_required(VERSION 3.21)
project(LowData)

set(CMAKE_CXX_STANDARD 14)

add_executable(LowData main.cpp Scenes/MenuScene.cpp Scenes/MenuScene.hpp LowDataGame.cpp LowDataGame.hpp Scenes/GameScene.cpp Scenes/GameScene.hpp)

add_subdirectory(../Olympus/Hephaestus ./Hephaestus/)
target_link_libraries(LowData Hephaestus)

add_custom_command(TARGET LowData PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:LowData>)