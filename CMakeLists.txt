cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER gcc-9)
set(CMAKE_CXX_COMPILER g++-9)

project(C++Template)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(vendor/doctest)

add_subdirectory(overloading)
add_subdirectory(parameters)
add_subdirectory(class)
add_subdirectory(specialization)
add_subdirectory(functional)
add_subdirectory(deduction)
add_subdirectory(references)
add_subdirectory(concept)
add_subdirectory(compilation)
add_subdirectory(type_level_fun)
add_subdirectory(design)
