cmake_minimum_required (VERSION 3.0.0) 
 
set (PROJECT CMake-Test) 
 
project (${PROJECT} VERSION 0.1.0)

add_subdirectory(./client)
add_subdirectory(./server)

add_custom_target(${PROJECT})
add_dependencies(${PROJECT} client server)