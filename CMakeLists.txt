cmake_minimum_required(VERSION 3.17.5)
project(supersolver)

set(CMAKE_CXX_STANDARD 20)

add_executable(linearequation linearequation/main.cpp)
add_executable(rootmod root_by_mod/rootmod.cpp)
add_executable(poleq poleq/poleq.cpp)