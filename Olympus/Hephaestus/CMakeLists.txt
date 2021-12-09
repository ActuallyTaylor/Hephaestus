cmake_minimum_required(VERSION 3.20)
project(Hephaestus)

set(CMAKE_CXX_STANDARD 17)

add_library(Hephaestus Hephaestus.cpp Hephaestus.cpp Hephaestus.hpp Window/Window.cpp Window/Window.hpp Shader/Shader.cpp Shader/Shader.hpp Window/Sprite/Sprite.cpp Window/Sprite/Sprite.hpp Library/stb_image.hpp Window/Controls/ControlManager.cpp Window/Controls/ControlManager.hpp Window/Controls/Keybind/Keybind.cpp Window/Controls/Keybind/Keybind.hpp Window/Camera/Camera.cpp Window/Camera/Camera.hpp Window/Sprite/PhysicsSprite/PhysicsSprite.cpp Window/Sprite/PhysicsSprite/PhysicsSprite.hpp Window/Collision/Collision.cpp Window/Collision/Collision.hpp Window/Text/TextManager.cpp Window/Text/TextManager.hpp Window/Text/Text.cpp Window/Text/Text.hpp Window/UI/Button/Button.cpp Window/UI/Button/Button.hpp Window/UI/UIElement.cpp Window/UI/UIElement.hpp)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(Hephaestus glfw)

find_package(GLEW REQUIRED)
target_link_libraries(Hephaestus GLEW::GLEW)

find_package(Freetype REQUIRED)
target_link_libraries(Hephaestus Freetype::Freetype)

add_custom_command(TARGET Hephaestus PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Hephaestus/Resources/ $<TARGET_FILE_DIR:Hephaestus>)