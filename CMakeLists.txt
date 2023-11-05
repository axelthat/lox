cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(lox)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_FILES})