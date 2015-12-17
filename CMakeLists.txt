cmake_minimum_required (VERSION 2.8)
project (kicad_bom)
add_definitions(-std=c++11)

add_subdirectory(test)

set(LIB_HEADER_FILES
        Component.h)
set(LIB_SOURCE_FILES
        Component.cc)
add_library(kicad_bom_lib STATIC ${LIB_HEADER_FILES} ${LIB_SOURCE_FILES})


add_executable(kicad_bom kicad_bom.cc)
target_link_libraries(kicad_bom kicad_bom_lib)