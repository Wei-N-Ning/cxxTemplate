cmake_minimum_required(VERSION 3.8)
project(C++Template)

enable_testing()

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