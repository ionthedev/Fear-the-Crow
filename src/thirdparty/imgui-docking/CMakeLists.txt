cmake_minimum_required(VERSION 3.1)
project(imgui)

add_library(imgui)
target_sources(imgui PRIVATE 
"${imgui_SOURCE_DIR}/imgui/imgui.cpp"
"${imgui_SOURCE_DIR}/imgui/imgui_demo.cpp"
"${imgui_SOURCE_DIR}/imgui/imgui_draw.cpp"
"${imgui_SOURCE_DIR}/imgui/imgui_tables.cpp"
"${imgui_SOURCE_DIR}/imgui/imgui_widgets.cpp"
"${imgui_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp"
"${imgui_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp"
)

target_include_directories(imgui PUBLIC "${imgui_SOURCE_DIR}/imgui")


target_link_libraries(imgui PUBLIC raylib_static glfw)

