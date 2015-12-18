cmake_minimum_required (VERSION 2.8)
project(kicad_bom_tests)

add_subdirectory (lib/gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(component_test component_test.cc)
target_link_libraries(component_test gtest gtest_main)
target_link_libraries(component_test kicad_bom_lib)