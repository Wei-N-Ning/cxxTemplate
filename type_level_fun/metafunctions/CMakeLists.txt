
add_executable(tlf_metafunctions_roll_my_own_predicate roll_my_own_predicate.cpp)
target_link_libraries(tlf_metafunctions_roll_my_own_predicate PRIVATE doctest)
add_test(NAME "tlf::metafunctions::roll_my_own_predicate" COMMAND tlf_metafunctions_roll_my_own_predicate)

add_executable(tlf_metafunctions_is_convertible is_convertible.cpp)
target_link_libraries(tlf_metafunctions_is_convertible PRIVATE doctest)
add_test(NAME "tlf::metafunctions::is-convertible" COMMAND tlf_metafunctions_is_convertible)

add_executable(tlf_metafunctions_is_constructible is_constructible.cpp)
target_link_libraries(tlf_metafunctions_is_constructible PRIVATE doctest)
add_test(NAME "tlf::metafunctions::is-constructible" COMMAND tlf_metafunctions_is_constructible)

add_executable(tlf_metafunctions_is_base_of is_base_of.cpp)
target_link_libraries(tlf_metafunctions_is_base_of PRIVATE doctest)
add_test(NAME "tlf::metafunctions::is-base-of" COMMAND tlf_metafunctions_is_base_of)

add_executable(tlf_metafunctions_is_legit_expression is_legit_expression.cpp)
target_link_libraries(tlf_metafunctions_is_legit_expression PRIVATE doctest)
add_test(NAME "tlf::metafunctions::is-legit-expression" COMMAND tlf_metafunctions_is_legit_expression)

add_executable(tlf_metafunctions_is_nonthrowing is_nonthrowing.cpp)
target_link_libraries(tlf_metafunctions_is_nonthrowing PRIVATE doctest)
add_test(NAME "tlf::metafunctions::is-nonthrowing" COMMAND tlf_metafunctions_is_nonthrowing)

add_executable(tlf_metafunctions_is_primitive_type is_primitive_type.cpp)
target_link_libraries(tlf_metafunctions_is_primitive_type PRIVATE doctest)
add_test(NAME "tlf::metafunctions::is-primitive-type" COMMAND tlf_metafunctions_is_primitive_type)

add_executable(tlf_metafunctions_const_is_const is_const.cpp)
target_link_libraries(tlf_metafunctions_const_is_const PRIVATE doctest)
add_test(NAME "tlf::metafunctions::const::is-const" COMMAND tlf_metafunctions_const_is_const)

add_executable(tlf_metafunctions_logical_operator logical_operator_func.cpp)
target_link_libraries(tlf_metafunctions_logical_operator PRIVATE doctest)
add_test(NAME "tlf::metafunctions::const::logical_operator" COMMAND tlf_metafunctions_logical_operator)