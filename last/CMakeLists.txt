cmake_minimum_required (VERSION 2.6)

set (CMAKE_C_COMPILER		"clang")
set (CMAKE_CXX_COMPILER 	"clang++")
set (CMAKE_CXX_FLAGS 		"-Wall -std=c++11 -DDEBUG -g")

project (lang)

# Version Number
set (Lang_VERSION_MAJOR 0)
set (Lang_VERSION_MINOR 1)

# configure a header file to pass information to the build
configure_file (
	"${PROJECT_SOURCE_DIR}/langconf.h.in"
	"${PROJECT_BINARY_DIR}/langconf.h"
)

# Add the binary tree to the search path for the config file include
include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/")
