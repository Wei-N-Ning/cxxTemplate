cmake_minimum_required(VERSION 3.8)
project(C++Template)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(vendor/doctest)
include(vendor/tinyCUnit/tinyCUnit.cmake)

#add_executable(methodTemplateInClassTemplate
#    methodTemplateInClassTemplate.cpp)
#set_target_properties(methodTemplateInClassTemplate
#    PROPERTIES
#    CXX_STANDARD 98)

add_subdirectory(compute)
add_subdirectory(overloading)
add_subdirectory(parameters)
add_subdirectory(singleton)
add_subdirectory(specialization)
add_subdirectory(tags)
add_subdirectory(traits)
add_subdirectory(typeDeduction)
add_subdirectory(forwarding)

