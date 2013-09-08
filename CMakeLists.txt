cmake_minimum_required(VERSION 2.8)
project(ATLeagueUtility)
set(CMAKE_BINARY_DIR build/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

if(CMAKE_GENERATOR STREQUAL Xcode)
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
	set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif(CMAKE_GENERATOR STREQUAL Xcode)

find_package(Boost 1.54.0 COMPONENTS iostreams REQUIRED) 

if (Boost_FOUND)
	add_executable(ATLeagueUtility src/main.cpp)
	include_directories(${Boost_INCLUDE_DIRS}) 
	target_link_libraries (ATLeagueUtility ${Boost_LIBRARIES})
endif (Boost_FOUND)
