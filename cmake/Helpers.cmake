# Call add_subdirectory for every sub directory with a CMakeLists.txt
function(add_all_subdirectories PATH)
    file(GLOB SUB_DIRECTORIES LIST_DIRECTORIES true ${PATH}/*)

    foreach (SUB_DIRECTORY ${SUB_DIRECTORIES})
        if (EXISTS ${SUB_DIRECTORY}/CMakeLists.txt)
            add_subdirectory("${SUB_DIRECTORY}")
        endif ()
    endforeach ()
endfunction()

# Create a project named after the path provided
macro(project_from_path PATH)
    get_filename_component(PROJECT_ID ${PATH} NAME)
    string(REPLACE " " "_" ${PROJECT_ID} ${PROJECT_ID})
    project(${PROJECT_ID})
endmacro()

# Create a symlink from the output of the project to a given path and file name
function(create_symlink_project_output PATH FILE_NAME)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PATH}
        COMMAND ${CMAKE_COMMAND} -E create_symlink $<TARGET_FILE:${PROJECT_NAME}> ${PATH}/${FILE_NAME})
endfunction()

# Copy the output to a given path and file name
function(copy_project_output PATH FILE_NAME)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> "${PATH}/${FILE_NAME}"
    )
endfunction()