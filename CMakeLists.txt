cmake_minimum_required(VERSION 3.8)
project(cxxTemplate)

enable_testing()

add_executable(isTypeTest traits/test_isType.cpp)
set_target_properties(isTypeTest
    PROPERTIES
    CXX_STANDARD 14)

add_executable(iteratorTagTest tagDispatch/iteratorTag.cpp)
set_target_properties(iteratorTagTest
    PROPERTIES
    CXX_STANDARD 14)

add_executable(singletonInheritanceTest singleton/inheritance.cpp)
set_target_properties(singletonInheritanceTest
    PROPERTIES
    CXX_STANDARD 14)

add_executable(timerPolicyTest policy/timerPolicy.cpp)
set_target_properties(timerPolicyTest
    PROPERTIES
    CXX_STANDARD 14)

add_executable(computeAlignmentSize compute/alignSize.cpp)
set_target_properties(computeAlignmentSize
    PROPERTIES
    CXX_STANDARD 14)

add_executable(typeTAndParamTest typeDeduction/typeTAndParam.cpp)
set_target_properties(typeTAndParamTest
    PROPERTIES
    CXX_STANDARD 17)

add_executable(declTypeTest typeDeduction/declType.cpp)
set_target_properties(declTypeTest
    PROPERTIES
    CXX_STANDARD 14)

add_executable(viewDeducedTypesTest typeDeduction/viewDeducedTypes.cpp)
set_target_properties(viewDeducedTypesTest
    PROPERTIES
    CXX_STANDARD 14)

add_executable(variadicTest variadic.cpp)
set_target_properties(variadicTest
    PROPERTIES
    CXX_STANDARD 14)

add_executable(methodTemplateInClassTemplate methodTemplateInClassTemplate.cpp)
set_target_properties(methodTemplateInClassTemplate
    PROPERTIES
    CXX_STANDARD 98)

