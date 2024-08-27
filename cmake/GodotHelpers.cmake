# Download and make available godot-cpp from git
function(download_godot_cpp VERSION)
    include(FetchContent)

    FetchContent_Declare(
        "godot-cpp"
        GIT_REPOSITORY "https://github.com/godotengine/godot-cpp.git"
        GIT_TAG "godot-${VERSION}-stable"
    )

    FetchContent_MakeAvailable("godot-cpp")
endfunction()

# Copy the .gdextension for the current project to the specified folder
function(configure_gd_extension TEMPLATE_PATH OUTPUT_PATH LIBRARY_NAME)
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(DEBUG_POSTFIX ".debug")
    endif ()

    add_custom_target(
        "${PROJECT_NAME}_configure_gd_extension"
        COMMAND
        ${CMAKE_COMMAND}
        "-DINPUT=${TEMPLATE_PATH}"
        "-DOUTPUT=${OUTPUT_PATH}/${PROJECT_NAME}.gdextension"
        "-DDEBUG_POSTFIX=${DEBUG_POSTFIX}"
        "-DLIBRARY_NAME=${LIBRARY_NAME}"
        "-P" "${CMAKE_SOURCE_DIR}/cmake/ConfigureFile.cmake"
    )

    add_dependencies(${PROJECT_NAME} "${PROJECT_NAME}_configure_gd_extension")
endfunction()