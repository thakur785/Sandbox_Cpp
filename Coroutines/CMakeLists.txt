cmake_minimum_required(VERSION 3.15)

project(StateDesignPattern)

set(SOURCES Simplecoroutines.cpp)

#include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)
add_executable(${PROJECT_NAME} ${SOURCES})


target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)