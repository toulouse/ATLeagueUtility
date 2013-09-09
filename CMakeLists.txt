cmake_minimum_required(VERSION 2.8)
project(ATLeagueUtility)
set(CMAKE_BINARY_DIR build/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

if(CMAKE_GENERATOR STREQUAL Xcode)
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif(CMAKE_GENERATOR STREQUAL Xcode)

add_executable(ATLeagueUtility src/main.cpp src/parse.hpp src/parse.cpp)
include_directories(src) 
target_link_libraries (ATLeagueUtility)
