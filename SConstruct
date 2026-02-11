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
env.Append(CPPPATH=["include"])
sources = Glob("src/*.cpp")

project_name = "squash_the_creeps"
libname = "game"

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "{}/bin/lib{}.{}.{}.framework/libgdexample.{}.{}".format(
            libname, env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "{}/bin/lib{}.{}.{}.simulator.a".format(project_name, libname, env["platform"], env["target"]),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "{}/bin/lib{}.{}.{}.a".format(project_name, libname, env["platform"], env["target"]),
            source=sources,
        )
else:
    library = env.SharedLibrary(
        "{}/bin/lib{}{}{}".format(project_name, libname, env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
