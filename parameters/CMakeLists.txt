
add_executable(param_non_type_parameter nonTypeParam.cpp)
target_link_libraries(param_non_type_parameter PRIVATE doctest)
add_test(NAME "param::non-type-param" COMMAND param_non_type_parameter)

add_executable(param_default_parameter default_parameter.cpp)
target_link_libraries(param_default_parameter PRIVATE doctest)
add_test(NAME "param::default-parameters" COMMAND param_default_parameter)

add_executable(param_nested_variadic nested_variadic.cpp)
target_link_libraries(param_nested_variadic PRIVATE doctest)
add_test(NAME "param::nested-variadic" COMMAND param_nested_variadic)
