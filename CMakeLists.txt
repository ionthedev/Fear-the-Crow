# FearTheCrow/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(FearTheCrow)

set(CMAKE_CXX_STANDARD 17)
set(PHANTOM_ENGINE_DIR ../PhantomEngine)
# Add PhantomEngine as an external project or a subdirectory
add_subdirectory(${PHANTOM_ENGINE_DIR} ${CMAKE_BINARY_DIR}/PhantomEngine)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)


# Add the FearTheCrow executable
add_executable(FearTheCrow src/FearTheCrow.cpp)

# Link against PhantomEngine
target_link_libraries(FearTheCrow PRIVATE PhantomEngine)

# Include directories
target_include_directories(FearTheCrow
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../PhantomEngine/src
)
