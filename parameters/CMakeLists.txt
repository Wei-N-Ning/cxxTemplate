add_executable(param_variadic_test variadic.cpp)
target_link_libraries(param_variadic_test PRIVATE doctest)
add_test(NAME "param::variadic-param" COMMAND param_variadic_test)

add_executable(param_non_type_parameter nonTypeParam.cpp)
target_link_libraries(param_non_type_parameter PRIVATE doctest)
add_test(NAME "param::non-type-param" COMMAND param_non_type_parameter)

add_executable(param_default_parameter default_parameter.cpp)
target_link_libraries(param_default_parameter PRIVATE doctest)
add_test(NAME "param::default-parameters" COMMAND param_default_parameter)

add_executable(param_fixed_size_stack fixed_size_stack.cpp)
target_link_libraries(param_fixed_size_stack PRIVATE doctest)
add_test(NAME "param::fixed-size-stack" COMMAND param_fixed_size_stack)

add_executable(param_nested_variadic nested_variadic.cpp)
target_link_libraries(param_nested_variadic PRIVATE doctest)
add_test(NAME "param::nested-variadic" COMMAND param_nested_variadic)

add_executable(param_variadic_fold variadic_fold.cpp)
target_link_libraries(param_variadic_fold PRIVATE doctest)
add_test(NAME "param::variadic-fold" COMMAND param_variadic_fold)

add_executable(param_variadic_match_many variadic_match_many.cpp)
target_link_libraries(param_variadic_match_many PRIVATE doctest)
add_test(NAME "param::variadic-match-many" COMMAND param_variadic_match_many)

add_executable(param_variadic_insert_many variadic_insert_many.cpp)
target_link_libraries(param_variadic_insert_many PRIVATE doctest)
add_test(NAME "param::variadic-insert-many" COMMAND param_variadic_insert_many)

add_executable(param_variadic_in_range variadic_in_range.cpp)
target_link_libraries(param_variadic_in_range PRIVATE doctest)
add_test(NAME "param::variadic-in-range" COMMAND param_variadic_in_range)
