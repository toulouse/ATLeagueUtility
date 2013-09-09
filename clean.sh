#!/bin/bash

NAME=ATLeagueUtility

[ -d "build" ] && rm -r "build"

[ -d "$NAME.build" ] && rm -r "$NAME.build"
[ -d "$NAME.xcodeproj" ] && rm -r "$NAME.xcodeproj"
[ -f ".cproject" ] && rm ".cproject"
[ -f ".project" ] && rm ".project"
[ -f "Makefile" ] && rm "Makefile"

[ -d "CMakeFiles" ] && rm -r "CMakeFiles"
[ -d "CMakeScripts" ] && rm -r "CMakeScripts"
[ -f "CMakeCache.txt" ] && rm "CMakeCache.txt"
[ -f "cmake_install.cmake" ] && rm "cmake_install.cmake"
