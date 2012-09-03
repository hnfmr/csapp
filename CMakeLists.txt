cmake_minimum_required(VERSION 2.8)
project(csapp)

set(cmake_cxx_flags "-Wall -Werror -std=c99")

set(library_output_path ${CMAKE_SOURCE_DIR}/lib)
set(executable_output_path ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(src)
