# Set the project name
set(project_name "cpp-golang-channel-exe")
project(${project_name} C CXX)

file(GLOB_RECURSE src ${CMAKE_CURRENT_LIST_DIR}/*.h
     ${CMAKE_CURRENT_LIST_DIR}/*.c ${CMAKE_CURRENT_LIST_DIR}/*.cc
     ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

# Add an executable for testing purpose
add_executable(${project_name} ${src})

target_link_libraries(${project_name} PUBLIC cpp::golang::channel)
