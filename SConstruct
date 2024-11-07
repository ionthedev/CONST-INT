#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")  # Get cpp files in src directory
sources.extend(Glob("src/*/*.cpp"))  # Get cpp files in immediate subdirectories
# Or for completely recursive behavior:
# sources = Glob("src/**/*.cpp", recursive=True)  # Get all cpp files in src and all subdirectories


if env["platform"] == "macos":
    library = env.SharedLibrary(
        "project/addons/CONST-INT/bin/libCONST-INT.{}.{}.framework/libCONST-INT.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "project/addons/CONST-INT/bin/libCONST-INT.{}.{}.simulator.a".format(env["platform"], env["target"]),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "project/addons/CONST-INT/bin/libCONST-INT.{}.{}.a".format(env["platform"], env["target"]),
            source=sources,
        )
else:
    library = env.SharedLibrary(
        "project/addons/CONST-INT/bin/libCONST-INT{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
