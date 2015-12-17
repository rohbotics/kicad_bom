cmake_minimum_required (VERSION 2.8)
project(kicad_bom_tests)

add_subdirectory (lib/gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})