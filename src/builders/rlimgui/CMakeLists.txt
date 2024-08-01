cmake_minimum_required(VERSION 3.14)
project(rlimgui)

# Specify the library
add_library(rlimgui STATIC

        ${CMAKE_BINARY_DIR}/_deps/rlimgui-src/rlImGui.cpp

        ${CMAKE_BINARY_DIR}/_deps/rlimgui-src/rlImGui.h
)

# Include directories
target_include_directories(rlimgui PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link libraries (ensure these libraries are properly defined in your main CMakeLists.txt)
target_link_libraries(rlimgui PUBLIC
        imgui
        raylib_static
)
