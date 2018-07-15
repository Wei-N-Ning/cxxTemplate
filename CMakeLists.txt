cmake_minimum_required(VERSION 3.8)
project(cxxTemplate)

add_executable(variadicTest variadic.cpp)
set_target_properties(variadicTest
    PROPERTIES
    CXX_STANDARD 14)

add_executable(methodTemplateInClassTemplate methodTemplateInClassTemplate.cpp)
set_target_properties(methodTemplateInClassTemplate
    PROPERTIES
    CXX_STANDARD 98)

add_subdirectory(compute)
add_subdirectory(policy)
add_subdirectory(singleton)
add_subdirectory(tagDispatch)
add_subdirectory(traits)
add_subdirectory(typeDeduction)
