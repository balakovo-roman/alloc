cmake_minimum_required(VERSION 3.28)

make_interface_lib(containers forward_list.hpp)

target_link_libraries(allocator INTERFACE static::logger)