add_executable(typeTAndParamTest typeTAndParam.cpp)
set_target_properties(typeTAndParamTest
    PROPERTIES
    CXX_STANDARD 17)

add_executable(declTypeTest declType.cpp)
set_target_properties(declTypeTest
    PROPERTIES
    CXX_STANDARD 14)

add_executable(viewDeducedTypesTest viewDeducedTypes.cpp)
set_target_properties(viewDeducedTypesTest
    PROPERTIES
    CXX_STANDARD 14)
