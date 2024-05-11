#!/usr/bin/env python
import os
import sys

libname = "CONST_INT"
env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
#env.Append(CPPPATH=["src/"])
#sources = Glob("src/*.cpp")

def find_directories(directory):
    directories = ["src/"]
    for root, dirs, files in os.walk(directory):
        directories.extend(["src/" + os.path.relpath(os.path.join(root, d), directory).replace("\\", "/") + "/" for d in dirs])
    return directories

source_dirs = find_directories("/home/brandon/Documents/GitHub/CONST-INT/src")
env.Append(CPPPATH=source_dirs)

sources = []
for d in source_dirs:
    sources.append(Glob(d + "*.cpp"))

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "CI_DEMO/bin/{}.{}.{}.framework/{}.{}.{}".format(libname,
            env["platform"], env["target"], libname, env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "CI_DEMO/bin/{}{}{}".format(libname, env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)