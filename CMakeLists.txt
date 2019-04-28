cmake_minimum_required(VERSION 3.13)
project(TSP)

set(CMAKE_CXX_STANDARD 14)

add_executable(TSP main.cpp DSU.cpp DSU.h MatrixGraph.cpp MatrixGraph.h ListGraph.cpp ListGraph.h)