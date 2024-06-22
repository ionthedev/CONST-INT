# Create project from directory
project_from_path(${CMAKE_CURRENT_SOURCE_DIR})

# Setup source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.[hc]"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.[hc]pp")

include_directories(
"${CMAKE_CURRENT_SOURCE_DIR}"
)

# Setup project as dynamic library with source code
add_library("${PROJECT_NAME}" SHARED "${SOURCES}"
        Actors/Player.cpp
        Core/InputHandler.h)

# Add godot cpp to the library
target_link_libraries(${PROJECT_NAME} PRIVATE "godot-cpp" ${TARGET_LINK_LIBRARIES_OPTIONS})

# Enable hot reload in godot
target_compile_definitions(${PROJECT_NAME} PUBLIC HOT_RELOAD_ENABLED)

# Set output variables
set(PROJECT_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/${GODOT_PROJECT_PATH}/${GD_EXTENSIONS_PATH}/${PROJECT_NAME}")

# Create a symlink of the dynamic library to the godot project folder
create_symlink_project_output(${PROJECT_OUTPUT_PATH} "${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}")

# Alternatively you can copy the dynamic library to the folder godot project instead of creating a symlink
# copy_project_output(${PROJECT_OUTPUT_PATH} "${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}")

# Copy configured .gdextension to output folder
configure_gd_extension("${CMAKE_SOURCE_DIR}/template.gdextension" ${PROJECT_OUTPUT_PATH} ${PROJECT_NAME})