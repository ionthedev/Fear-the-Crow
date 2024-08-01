cmake_minimum_required(VERSION 3.14)
project(Fear-The-Crow)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent module
include(FetchContent)

# Fetch and build Raylib
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(raylib)

# Fetch and build Raylib-cpp
FetchContent_Declare(
        raylib-cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(raylib-cpp)

# Fetch and build Bullet3
FetchContent_Declare(
        bullet3
        GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(bullet3)

# Add source files
file(GLOB_RECURSE ENGINE_SOURCES "src/engine/*.cpp")
file(GLOB_RECURSE GAME_SOURCES "src/game/*.cpp")
file(GLOB_RECURSE EDITOR_SOURCES "src/editor/*.cpp")


add_subdirectory(src/thirdparty/imgui-docking)
add_subdirectory(src/thirdparty/rlImGui)

# Create the executable
add_executable(${PROJECT_NAME}
        src/main.cpp
        ${ENGINE_SOURCES}
        ${GAME_SOURCES}
        ${EDITOR_SOURCES}
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
        ${raylib_SOURCE_DIR}/src
        ${raylib-cpp_SOURCE_DIR}/include
        ${raylib-cpp_SOURCE_DIR}/examples
        ${raylib-cpp_SOURCE_DIR}/tests
        ${bullet3_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/include
        ${PROJECT_SOURCE_DIR}/src/engine
        ${PROJECT_SOURCE_DIR}/src/game
        ${PROJECT_SOURCE_DIR}/src/editor
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
        raylib
        raylib_cpp
        BulletDynamics
        BulletCollision
        LinearMath
        imgui
        rlimgui
)
