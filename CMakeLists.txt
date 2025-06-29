cmake_minimum_required(VERSION 3.16)
project(langparse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(include)
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(langparse ${SOURCES})
