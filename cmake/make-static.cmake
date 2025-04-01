function(make_static_lib target_name)
    add_library(${target_name} STATIC)
    target_sources(${target_name} PRIVATE ${ARGN})
    add_library(static::${target_name} ALIAS ${target_name})
    target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()