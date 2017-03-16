cmake_minimum_required (VERSION 2.6)
project (memtool)
add_executable(test  test.c )
add_library(wxtool wxslab.c)

add_executable(wxslab_test wxslab_test.c)
target_link_libraries(wxslab_test wxtool)
