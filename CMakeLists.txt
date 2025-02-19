cmake_minimum_required(VERSION 3.15...3.28)

project(
    DataBuffer
    VERSION 0.0.1
    DESCRIPTION "Circular buffer library."
    LANGUAGES C
)

include(CheckSymbolExists)
include(CheckIncludeFile)
include(cmake/CPM.cmake)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

CHECK_INCLUDE_FILE(stdatomic.h HAS_STDATOMIC_H)

#check_symbol_exists(timespec_get time.h HAS_TIMESPEC_GET)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CCMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CCMAKE_CUDA_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

CPMAddPackage(
  NAME Unity
  VERSION 2.6.1
  GITHUB_REPOSITORY ThrowTheSwitch/Unity
  OPTIONS
    "UNITY_EXTENSION_FIXTURE ON"
    "UNITY_EXTENSION_MEMORY OFF"
)

configure_file(configure.h.cmake configure.h @ONLY)

add_subdirectory(data_buffer)

