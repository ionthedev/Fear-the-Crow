cmake_minimum_required(VERSION 3.29)
add_executable(FearTheCrow)
add_executable(PH::FTC ALIAS FearTheCrow)

target_sources(
        FearTheCrow
        PRIVATE
        "src/FearTheCrow.cpp"
)

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
        PhantomEngine)
