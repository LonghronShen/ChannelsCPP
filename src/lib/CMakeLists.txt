cmake_minimum_required(VERSION 3.16)

# Set the project name
set(project_name "cpp-golang-channel-lib")

project(${project_name} C CXX)

file(
  GLOB_RECURSE
  src
  ${CMAKE_CURRENT_LIST_DIR}/*.def
  ${CMAKE_CURRENT_LIST_DIR}/*.h
  ${CMAKE_CURRENT_LIST_DIR}/*.hpp
  ${CMAKE_CURRENT_LIST_DIR}/*.c
  ${CMAKE_CURRENT_LIST_DIR}/*.cc
  ${CMAKE_CURRENT_LIST_DIR}/*.cxx
  ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

file(GLOB_RECURSE public_headers ${CMAKE_CURRENT_LIST_DIR}/include/public/*.h
     ${CMAKE_CURRENT_LIST_DIR}/include/public/*.hpp)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include
                    ${CMAKE_CURRENT_BINARY_DIR}/include)

# ------------------------------------------------------------------
add_library(${project_name}-static STATIC ${src})

target_link_libraries(
  ${project_name}-static
  PUBLIC ${CMAKE_THREAD_LIBS_INIT}
  PUBLIC ${DL_LIBRARY})

target_include_directories(
  ${project_name}-static
  PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include/public"
  PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include/private"
  PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include")

target_link_options(${project_name}-static PRIVATE
                    "-fsanitize=address,undefined")

add_library(cpp::golang::channel ALIAS cpp-golang-channel-lib-static)
