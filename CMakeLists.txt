cmake_minimum_required(VERSION 3.14)
project(Fear-The-Crow)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/FearTheCrow.cpp
)

# Create an executable target for the game
add_executable(Fear-The-Crow ${SOURCES})

# Link against the phantom-engine library
target_link_libraries(Fear-The-Crow PhantomEngine raylib_cpp imgui rlimgui)

# Include directories from the phantom-engine
target_include_directories(Fear-The-Crow PRIVATE
        ${CMAKE_SOURCE_DIR}/PhantomEngine/src
        # Add other include directories if needed
)
