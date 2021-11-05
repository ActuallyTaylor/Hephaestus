cmake_minimum_required(VERSION 3.20)
project(Hephaestus)

set(CMAKE_CXX_STANDARD 17)

add_library(Hephaestus
        Hephaestus.cpp Hephaestus.hpp
        Library/stb_image.hpp
        Classes/Window/WindowDelegate/WindowDelegate.cpp Classes/Window/WindowDelegate/WindowDelegate.hpp
        Classes/Window/Window.cpp Classes/Window/Window.hpp
        Classes/Shader/Shader.cpp  Classes/Shader/Shader.hpp
        Classes/Geometry\ Manager/GeometryManager.cpp Classes/Geometry\ Manager/GeometryManager.hpp
        Classes/Geometry\ Manager/Compressed\ Data/CompressedData.cpp Classes/Geometry\ Manager/Compressed\ Data/CompressedData.hpp
        Classes/Geometry\ Manager/Sprite/Sprite.cpp Classes/Geometry\ Manager/Sprite/Sprite.hpp
        Classes/Geometry\ Manager/Vertex/Vertex.cpp Classes/Geometry\ Manager/Vertex/Vertex.hpp
        Classes/Controls/Controls.cpp Classes/Controls/Controls.hpp Classes/Controls/Keybind/Keybind.cpp Classes/Controls/Keybind/Keybind.hpp
        )

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(Hephaestus glfw)

find_package(GLEW REQUIRED)
target_link_libraries(Hephaestus GLEW::GLEW)