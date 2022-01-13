cmake_minimum_required(VERSION 3.20)
project(Hephaestus)

set(CMAKE_CXX_STANDARD 17)

add_library(Hephaestus Hephaestus.cpp Hephaestus.cpp Hephaestus.hpp Shader/Shader.cpp Shader/Shader.hpp Sprite/Sprite.cpp Sprite/Sprite.hpp Library/stb_image.hpp Controls/ControlManager.cpp Controls/ControlManager.hpp Controls/Keybind/Keybind.cpp Controls/Keybind/Keybind.hpp Camera/Camera.cpp Camera/Camera.hpp Sprite/PhysicsSprite/PhysicsSprite.cpp Sprite/PhysicsSprite/PhysicsSprite.hpp Collision/Collision.cpp Collision/Collision.hpp Text/TextManager.cpp Text/TextManager.hpp Text/Text.cpp Text/Text.hpp UI/Button/Button.cpp UI/Button/Button.hpp UI/UIElement.cpp UI/UIElement.hpp Scene/Scene.cpp Scene/Scene.hpp Function.hpp)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(Hephaestus PRIVATE glfw)

find_package(GLEW REQUIRED)
target_link_libraries(Hephaestus PRIVATE GLEW::GLEW)

find_package(Freetype REQUIRED)
target_link_libraries(Hephaestus PUBLIC Freetype::Freetype)

add_custom_command(TARGET Hephaestus PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Hephaestus/Resources/ $<TARGET_FILE_DIR:Hephaestus>)