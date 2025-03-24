cmake_minimum_required(VERSION 3.28)

make_interface_lib(math math.hpp)

make_main_test(math "math_test.cpp" "interface::math")