cmake_minimum_required(VERSION 3.13)
project(LowData)

set(CMAKE_CXX_STANDARD 14)

add_executable(LowData main.cpp Scenes/MenuScene.cpp Scenes/MenuScene.hpp LowDataGame.cpp LowDataGame.hpp Scenes/GameScene.cpp Scenes/GameScene.hpp Characters/Merchant.cpp Characters/Merchant.hpp Characters/MainCharacter.cpp Characters/MainCharacter.hpp Characters/AnimationFlipbook.cpp Characters/AnimationFlipbook.hpp Items/Item.cpp Items/Item.hpp Items/DroppedItem.cpp Items/DroppedItem.hpp Environment/EncounterSpace.cpp Environment/EncounterSpace.hpp)

add_subdirectory(../../Hephaestus ./Hephaestus/)
target_link_libraries(LowData Hephaestus)

add_custom_command(TARGET LowData PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:LowData>)