cmake_minimum_required(VERSION 3.0.0)
project(dsalgo VERSION 0.1.0)

add_subdirectory(${PROJECT_SOURCE_DIR}/graph)
add_subdirectory(${PROJECT_SOURCE_DIR}/linklist)
add_subdirectory(${PROJECT_SOURCE_DIR}/tree)


set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 11)


add_executable(main main.cpp)
