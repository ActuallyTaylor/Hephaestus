cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

set(HEPHAESTUS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(CMakeDependentOption)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/install_and_expose.cmake)

file(STRINGS version.txt HEPHAESTUS_VERSION)

project(Hephaestus VERSION ${HEPHAESTUS_VERSION} LANGUAGES CXX C)

add_library(${PROJECT_NAME} STATIC)

# Add sources
target_sources(${PROJECT_NAME} PRIVATE  src/Hephaestus.cpp src/Hephaestus.cpp include/Hephaestus/Hephaestus.hpp src/Shader/Shader.cpp include/Hephaestus/Shader/Shader.hpp src/Sprite/Sprite.cpp include/Hephaestus/Sprite/Sprite.hpp src/Controls/ControlManager.cpp include/Hephaestus/Controls/ControlManager.hpp src/Controls/Keybind/Keybind.cpp include/Hephaestus/Controls/Keybind/Keybind.hpp src/Camera/Camera.cpp include/Hephaestus/Camera/Camera.hpp src/Sprite/PhysicsSprite.cpp include/Hephaestus/Sprite/PhysicsSprite.hpp src/Collision/PhysicsCollision.cpp include/Hephaestus/Collision/PhysicsCollision.hpp src/Text/TextManager.cpp include/Hephaestus/Text/TextManager.hpp src/Text/Text.cpp include/Hephaestus/Text/Text.hpp src/UI/Button/Button.cpp include/Hephaestus/UI/Button/Button.hpp src/UI/UIElement.cpp include/Hephaestus/UI/UIElement.hpp src/Scene/Scene.cpp include/Hephaestus/Scene/Scene.hpp include/Hephaestus/Function.hpp src/AudioEngine/AudioEngine.cpp include/Hephaestus/AudioEngine/AudioEngine.hpp src/AudioEngine/AudioSnippet.cpp include/Hephaestus/AudioEngine/AudioSnippet.hpp src/UI/Image/Image.cpp include/Hephaestus/UI/Image/Image.hpp include/Hephaestus/HephaestusUtility.hpp src/Collision/CollisionArea.cpp include/Hephaestus/Collision/CollisionArea.hpp include/Hephaestus/libs/stb_image.hpp include/Hephaestus/libs/json.hpp)

# Handle Dependencies
if(UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
    find_package(OpenAl REQUIRED)
    find_package(ALUT REQUIRED)

    target_link_libraries(${PROJECT_NAME}
            PUBLIC OpenGL
            PUBLIC OpenAL
            PUBLIC ALUT
            )
endif()

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)

target_link_libraries(${PROJECT_NAME}
        PUBLIC glfw
        PUBLIC GLEW::GLEW
        PUBLIC Freetype::Freetype
        PUBLIC glm::glm
        )

add_custom_command(TARGET Hephaestus PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Resources/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)

install_and_expose(${PROJECT_NAME})
