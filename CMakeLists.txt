cmake_minimum_required(VERSION 3.0.2)

project(bf)
set(CMAKE_CXX_STANDARD 17)

file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

add_executable(${PROJECT_NAME} ${sources} ${headers})
