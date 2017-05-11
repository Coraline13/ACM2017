cmake_minimum_required (VERSION 3.1)

project (ACM-2017-TM)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions(-D__LOCAL)

add_executable(labyrinth a-labyrinth.cpp)
add_executable(jollo c-jollo.cpp)
add_executable(war d-war.cpp)
add_executable(frog e-frog.cpp)
add_executable(bits g-bits.cpp)
add_executable(critical i-critical.cpp)
