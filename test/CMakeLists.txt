cmake_minimum_required(VERSION 3.0.2)

set(sources
  main.cpp
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/..)
add_executable(${PROJECT_NAME}-test ${sources})
target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME}-lib stdc++fs)
