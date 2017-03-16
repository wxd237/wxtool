cmake_minimum_required (VERSION 2.6)
project (mp)

add_library(mp mp_alloc.c)

add_executable(test mp_test.c)
target_link_libraries(test mp)
