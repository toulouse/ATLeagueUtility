cmake_minimum_required(VERSION 2.8)
project(ATLeagueClient)
set(CMAKE_BINARY_DIR build/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include(FindPkgConfig)
if(PKG_CONFIG_FOUND)
	message(STATUS "PkgConfig Found.")
else(PKG_CONFIG_FOUND)
	message(STATUS "PkgConfig Not Found.")
endif(PKG_CONFIG_FOUND)
message(STATUS "PkgConfig Executable: ${PKG_CONFIG_EXECUTABLE}")

pkg_check_modules(librtmp REQUIRED librtmp)

find_package(Boost 1.54.0 COMPONENTS serialization REQUIRED) 

if (librtmp_FOUND AND Boost_FOUND)
	add_executable(ATLeagueClient src/main.cpp)
	include_directories(${librtmp_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS}) 
	target_link_libraries (ATLeagueClient ${librtmp_LDFLAGS} ${Boost_LIBRARIES})
endif (librtmp_FOUND AND Boost_FOUND)
