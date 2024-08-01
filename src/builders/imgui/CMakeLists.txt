cmake_minimum_required(VERSION 3.14)
project(imgui)

# Specify the library
add_library(imgui STATIC
        ${CMAKE_BINARY_DIR}/_deps/imgui-src/imgui.cpp
        ${CMAKE_BINARY_DIR}/_deps/imgui-src/imgui_demo.cpp
        ${CMAKE_BINARY_DIR}/_deps/imgui-src/imgui_draw.cpp
        ${CMAKE_BINARY_DIR}/_deps/imgui-src/imgui_tables.cpp
        ${CMAKE_BINARY_DIR}/_deps/imgui-src/imgui_widgets.cpp
        ${CMAKE_BINARY_DIR}/_deps/imgui-src/backends/imgui_impl_glfw.cpp
        ${CMAKE_BINARY_DIR}/_deps/imgui-src/backends/imgui_impl_opengl3.cpp
)

# Include directories
target_include_directories(imgui PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link libraries (ensure these libraries are properly defined in your main CMakeLists.txt)
target_link_libraries(imgui PUBLIC
        raylib_static
        glfw
)
