cmake_minimum_required(VERSION 3.29)

add_executable(FearTheCrow
        src/DemoScene.cpp
        src/DemoScene.h
        FearTheCrow.cpp
)



add_executable(PH::FTC ALIAS FearTheCrow)

target_include_directories(
        FearTheCrow
        PRIVATE
        "src"
)

set_target_properties(
        FearTheCrow
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED TRUE
)

# Link against PhantomEngine
target_link_libraries(
        FearTheCrow
        PUBLIC
        PhantomEngine
)

# Set the resource directory relative to the CMakeLists.txt directory
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/Fear-the-Crow/resources")

# Copy the resources folder to the build directory
add_custom_command(
        TARGET FearTheCrow POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCE_DIR}"
        "$<TARGET_FILE_DIR:FearTheCrow>/resources"
        COMMENT "Copying resources folder to build directory"
)
