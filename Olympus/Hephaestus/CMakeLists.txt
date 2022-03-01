cmake_minimum_required(VERSION 3.13)
project(Hephaestus)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_MACOSX_RPATH 1)
#set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/Hephaestus/Library")

add_library(Hephaestus Hephaestus.cpp Hephaestus.cpp Hephaestus.hpp Shader/Shader.cpp Shader/Shader.hpp Sprite/Sprite.cpp Sprite/Sprite.hpp Library/stb_image.hpp Controls/ControlManager.cpp Controls/ControlManager.hpp Controls/Keybind/Keybind.cpp Controls/Keybind/Keybind.hpp Camera/Camera.cpp Camera/Camera.hpp Sprite/PhysicsSprite/PhysicsSprite.cpp Sprite/PhysicsSprite/PhysicsSprite.hpp Collision/Collision.cpp Collision/Collision.hpp Text/TextManager.cpp Text/TextManager.hpp Text/Text.cpp Text/Text.hpp UI/Button/Button.cpp UI/Button/Button.hpp UI/UIElement.cpp UI/UIElement.hpp Scene/Scene.cpp Scene/Scene.hpp Function.hpp AudioEngine/AudioEngine.cpp AudioEngine/AudioEngine.hpp AudioEngine/AudioSnippet.cpp AudioEngine/AudioSnippet.hpp)

if(UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
    target_link_libraries(Hephaestus PUBLIC OpenGL)
endif()

add_subdirectory(Library/openal-soft/)
target_link_libraries(Hephaestus PUBLIC OpenAL)

find_package(glfw3 REQUIRED)
target_link_libraries(Hephaestus PUBLIC glfw)

find_package(GLEW REQUIRED)
target_link_libraries(Hephaestus PUBLIC GLEW::GLEW)

find_package(Freetype REQUIRED)
target_link_libraries(Hephaestus PUBLIC Freetype::Freetype)

add_custom_command(TARGET Hephaestus PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Hephaestus/Resources/ $<TARGET_FILE_DIR:Hephaestus>)