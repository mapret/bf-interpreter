cmake_minimum_required(VERSION 3.0.2)

project(bf)
set(CMAKE_CXX_STANDARD 17)

set(sources
  Interpreter.cpp
  Tape.cpp
)
set(headers
  Interpreter.hpp
  Tape.hpp
)
add_library(${PROJECT_NAME}-lib STATIC ${sources} ${headers})

add_subdirectory(test)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib stdc++fs)
