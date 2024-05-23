cmake_minimum_required(VERSION 3.28)
project(CONST_INT)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(
        godot-cpp/gdextension
        godot-cpp/gen/include
        godot-cpp/gen/include/godot_cpp
        godot-cpp/gen/include/godot_cpp/classes
        godot-cpp/gen/include/godot_cpp/core
        godot-cpp/gen/include/godot_cpp/variant
        godot-cpp/gen/src/classes
        godot-cpp/gen/src/variant
        godot-cpp/include
        godot-cpp/include/godot_cpp
        godot-cpp/include/godot_cpp/classes
        godot-cpp/include/godot_cpp/core
        godot-cpp/include/godot_cpp/templates
        godot-cpp/include/godot_cpp/variant
        godot-cpp/test/src
        src
)

# Add executable
add_executable(
        CONST_INT
        src/register_types.cpp
        src/register_types.h
        src/gdexample.cpp
        src/gdexample.h
        src/ActorBase.cpp
        src/ActorBase.h
        src/ActorSettings.h
        src/ActorSettings.cpp
)