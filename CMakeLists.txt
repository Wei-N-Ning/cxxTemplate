cmake_minimum_required(VERSION 3.8)
project(cxxTemplate)

#add_executable(methodTemplateInClassTemplate methodTemplateInClassTemplate.cpp)
#set_target_properties(methodTemplateInClassTemplate
#    PROPERTIES
#    CXX_STANDARD 98)

add_subdirectory(compute)
add_subdirectory(parameters)
add_subdirectory(policy)
add_subdirectory(singleton)
add_subdirectory(tags)
add_subdirectory(traits)
add_subdirectory(typeDeduction)
