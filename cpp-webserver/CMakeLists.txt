cmake_minimum_required(VERSION 3.25)
project(CppWebserver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

option(BUILD_STD_UNORDERED_MAP "build with std::unordered_map" Off)
option(BUILD_DENSE_MAP "build with ankerl::unordered_dense::map" Off)

add_subdirectory(src/webapp)
