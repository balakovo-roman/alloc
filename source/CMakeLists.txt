cmake_minimum_required(VERSION 3.28)

include(${CMAKE_SOURCE_DIR}/cmake/make-interface.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/make-static.cmake)

add_subdirectory(logger)
add_subdirectory(version)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE static::logger)

install_binary(${PROJECT_NAME})
