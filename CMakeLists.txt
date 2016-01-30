cmake_minimum_required (VERSION 2.8)
project (kicad_bom)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pthread")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_subdirectory(test)

set(LIB_HEADER_FILES
        Component.h)
set(LIB_SOURCE_FILES
        Component.cc)
add_library(kicad_bom_lib STATIC ${LIB_HEADER_FILES} ${LIB_SOURCE_FILES})


add_executable(kicad_bom kicad_bom.cc)
target_link_libraries(kicad_bom kicad_bom_lib pugixml)