add_executable(deduction_typeTAndParamTest typeTAndParam.cpp)
target_link_libraries(deduction_typeTAndParamTest PRIVATE doctest)
add_test(NAME "deduction::T-and-param" COMMAND deduction_typeTAndParamTest)

add_executable(deduction_declTypeTest declType.cpp)
target_link_libraries(deduction_declTypeTest PRIVATE doctest)
add_test(NAME "deduction::decltype" COMMAND deduction_declTypeTest)

add_executable(deduction_viewDeducedTypesTest viewDeducedTypes.cpp)
target_link_libraries(deduction_viewDeducedTypesTest PRIVATE doctest)
add_test(NAME "deduction::view-type" COMMAND deduction_viewDeducedTypesTest)

add_executable(deduction_containerValueType containerValueType.cpp)
target_link_libraries(deduction_containerValueType PRIVATE doctest)
add_test(NAME "deduction::universal-reference-and-value-type" COMMAND deduction_containerValueType)
