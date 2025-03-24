cmake_minimum_required(VERSION 3.28)

make_interface_lib(allocator allocator.hpp)

set(TEST_SOURCES allocator_test.cpp)

make_main_test(allocator "${TEST_SOURCES}" "interface::allocator")