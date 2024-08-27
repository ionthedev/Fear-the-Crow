cmake_minimum_required(VERSION 3.28)

# Setup Root Project
project("root")

# Setup paths
set(GODOT_PROJECT_PATH "godot_project") # Path to godot project
set(GD_EXTENSIONS_PATH "bin") # Path to output gd extensions relative to godot project

# Setup C++
set(CMAKE_CXX_STANDARD 23)

# Include helper functions
include("cmake/Helpers.cmake")
include("cmake/GodotHelpers.cmake")

# Download GDExtension
download_godot_cpp(4.3)

# Setup platform architecture
set(ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "")
    set(ARCHITECTURE "universal")
endif ()

# Setup compiler dependant options
if (MINGW)
    set(TARGET_LINK_LIBRARIES_OPTIONS "-static")
endif ()

# Dynamically add all sub directories with a CMakeLists.txt
add_all_subdirectories(${CMAKE_SOURCE_DIR})