add_executable(typing_typeTAndParamTest typeTAndParam.cpp)
target_link_libraries(typing_typeTAndParamTest PRIVATE doctest)
add_test(NAME "typing::T-and-param" COMMAND typing_typeTAndParamTest)

add_executable(typing_declTypeTest declType.cpp)
target_link_libraries(typing_declTypeTest PRIVATE doctest)
add_test(NAME "typing::decltype" COMMAND typing_declTypeTest)

add_executable(typing_viewDeducedTypesTest viewDeducedTypes.cpp)
target_link_libraries(typing_viewDeducedTypesTest PRIVATE doctest)
add_test(NAME "typing::view-type" COMMAND typing_viewDeducedTypesTest)

add_executable(typing_containerValueType containerValueType.cpp)
target_link_libraries(typing_containerValueType PRIVATE doctest)
add_test(NAME "typing::universal-reference-and-value-type" COMMAND typing_containerValueType)

add_executable(typing_from_constructor_args deduce_from_ctor.cpp)
target_link_libraries(typing_from_constructor_args PRIVATE doctest)
add_test(NAME "typing::deduce-type-param-from-ctor" COMMAND typing_from_constructor_args)

add_executable(typing_typeid typeid.cpp)
target_link_libraries(typing_typeid PRIVATE doctest)
add_test(NAME "typing::typeid-and-typeinfo" COMMAND typing_typeid)

add_executable(typing_phantom_types phantom_types.cpp)
target_link_libraries(typing_phantom_types PRIVATE doctest)
add_test(NAME "typing::phantom-types" COMMAND typing_phantom_types)

add_executable(typing_deduce_from_func_arg deduce_from_func_arg.cpp)
target_link_libraries(typing_deduce_from_func_arg PRIVATE doctest)
add_test(NAME "typing::deduce-from-func-arg" COMMAND typing_deduce_from_func_arg)

add_executable(typing_type_function type_function.cpp)
target_link_libraries(typing_type_function PRIVATE doctest)
add_test(NAME "typing::type-function" COMMAND typing_type_function)

add_executable(typing_typelist typelist.cpp)
target_link_libraries(typing_typelist PRIVATE doctest)
add_test(NAME "typing::typelist" COMMAND typing_typelist)

