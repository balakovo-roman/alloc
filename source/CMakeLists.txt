cmake_minimum_required(VERSION 3.28)

include(${CMAKE_SOURCE_DIR}/cmake/make-interface.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/make-static.cmake)

add_subdirectory(version)
add_subdirectory(logger)

add_executable(${PROJECT_NAME} main.cpp)

install_binary(${PROJECT_NAME})
