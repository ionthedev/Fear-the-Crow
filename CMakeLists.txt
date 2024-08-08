cmake_minimum_required(VERSION 3.16)
project(FearTheCrow)

# Set the PhantomEngine root directory
set(PHANTOM_ENGINE_DIR ../PhantomEngine)

# Add PhantomEngine subdirectory with a specified binary directory
#add_subdirectory(${PHANTOM_ENGINE_DIR} ${CMAKE_BINARY_DIR}/PhantomEngine)

add_subdirectory(${PHANTOM_ENGINE_DIR} ${CMAKE_BINARY_DIR}/PhantomEngine)
# Include directories
include_directories(${PHANTOM_ENGINE_DIR}/src)

# Add FearTheCrow executable
add_executable(FearTheCrow
        src/FearTheCrow.cpp
        # Add other game source files
)

# Link PhantomEngine
target_link_libraries(FearTheCrow
        PRIVATE
        PhantomEngine
        imgui
        rlimgui
        raylib_cpp
        raylib
        Bullet3Common
        EnTT::EnTT
)
