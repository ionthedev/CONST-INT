cmake_minimum_required(VERSION 3.28)
project(CONST_INT)

set(CMAKE_CXX_STANDARD 17)
include_directories(godot-cpp/gdextension)
include_directories(godot-cpp/gen/include)
include_directories(godot-cpp/gen/include/godot_cpp)
include_directories(godot-cpp/gen/include/godot_cpp/classes)
include_directories(godot-cpp/gen/include/godot_cpp/core)
include_directories(godot-cpp/gen/include/godot_cpp/variant)
include_directories(godot-cpp/gen/src/classes)
include_directories(godot-cpp/gen/src/variant)
include_directories(godot-cpp/include)
include_directories(godot-cpp/include/godot_cpp)
include_directories(godot-cpp/include/godot_cpp/classes)
include_directories(godot-cpp/include/godot_cpp/core)
include_directories(godot-cpp/include/godot_cpp/templates)
include_directories(godot-cpp/include/godot_cpp/variant)
include_directories(godot-cpp/test/src)
include_directories(src)

add_executable(CONST_INT
        src/register_types.cpp
        src/register_types.h
        src/gdexample.cpp
        src/gdexample.h
        src/ActorBase.cpp
        src/ActorBase.h
)