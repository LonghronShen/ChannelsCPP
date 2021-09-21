cmake_minimum_required(VERSION 3.13)

if(TARGET cpp::golang::channel)
  return()
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(project_name "cpp-golang-channel")

project(${project_name} C CXX)

set(CMAKE_CXX_EXTENSIONS
    OFF
    CACHE STRING "CMAKE_CXX_EXTENSIONS" FORCE)
set(CMAKE_CXX_STANDARD
    14
    CACHE
      STRING
      "Set to 11 or 14 to enable C++11, C++14 or C++17 builds, respectively."
      FORCE)
set(CMAKE_C_STANDARD
    11
    CACHE STRING "Set to 99 or 11 to enable C99 or C11 builds, respectively."
          FORCE)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)

add_compile_definitions("__STDC_WANT_LIB_EXT1__=1")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_BINARY_DIR})

include(external/InitializeExternalComponents.cmake)

add_subdirectory(src)
