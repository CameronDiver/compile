cmake_minimum_required (VERSION 2.6)

set (CMAKE_C_COMPILER		"clang")
set (CMAKE_CXX_COMPILER 	"clang++")
set (CMAKE_CXX_FLAGS 		"-Wall -std=c++11 -DDEBUG -g")

project (compile CXX)


add_executable(compile main.cpp token.cpp builtins.cpp)