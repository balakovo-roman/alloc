cmake_minimum_required(VERSION 3.28)

make_static_lib(logger
    console_logger.cpp
    console_logger.hpp
    logger.hpp
)