#!/bin/bash

NAME=ATLeagueClient

[ -d "CMakeFiles" ] && rm -r "CMakeFiles"
[ -d "CMakeScripts" ] && rm -r "CMakeScripts"
[ -d "$NAME.build" ] && rm -r "$NAME.build"
[ -d "$NAME.xcodeproj" ] && rm -r "$NAME.xcodeproj"
[ -d "build" ] && rm -r "build"

[ -f "CMakeCache.txt" ] && rm "CMakeCache.txt"
[ -f "cmake_install.cmake" ] && rm "cmake_install.cmake"
[ -f "Makefile" ] && rm "Makefile"
