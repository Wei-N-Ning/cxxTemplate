add_executable(typeTAndParamTest typeTAndParam.cpp)
set_target_properties(typeTAndParamTest
    PROPERTIES
    CXX_STANDARD 17)
add_test(NAME "type-deduction::T-and-param" COMMAND typeTAndParamTest)

add_executable(declTypeTest declType.cpp)
set_target_properties(declTypeTest
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "type-deduction::decltype" COMMAND declTypeTest)

add_executable(viewDeducedTypesTest viewDeducedTypes.cpp)
set_target_properties(viewDeducedTypesTest
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "type-deduction::view-type" COMMAND viewDeducedTypesTest)

add_tinytest_executable(containerValueType containerValueType.cpp)
set_target_properties(containerValueType
    PROPERTIES
    CXX_STANDARD 14)
add_test(
    NAME
    "type-deduction::universal-reference-and-value-type"
    COMMAND
    containerValueType
    )
