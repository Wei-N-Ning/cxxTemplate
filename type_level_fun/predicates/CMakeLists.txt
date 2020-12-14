
add_executable(predicates_is_convertible is_convertible.cpp)
target_link_libraries(predicates_is_convertible PRIVATE doctest)
add_test(NAME "predicates::is-convertible" COMMAND predicates_is_convertible)

add_executable(predicates_is_constructible is_constructible.cpp)
target_link_libraries(predicates_is_constructible PRIVATE doctest)
add_test(NAME "predicates::is-constructible" COMMAND predicates_is_constructible)

add_executable(predicates_is_base_of is_base_of.cpp)
target_link_libraries(predicates_is_base_of PRIVATE doctest)
add_test(NAME "predicates::is-base-of" COMMAND predicates_is_base_of)

add_executable(predicates_has_member has_member.cpp)
target_link_libraries(predicates_has_member PRIVATE doctest)
add_test(NAME "predicates::has-member" COMMAND predicates_has_member)

add_executable(predicates_is_legit_expression is_legit_expression.cpp)
target_link_libraries(predicates_is_legit_expression PRIVATE doctest)
add_test(NAME "predicates::is-legit-expression" COMMAND predicates_is_legit_expression)

add_executable(predicates_has_all_methods has_all_methods.cpp)
target_link_libraries(predicates_has_all_methods PRIVATE doctest)
add_test(NAME "predicates::has-all-methods" COMMAND predicates_has_all_methods)

add_executable(predicates_is_nonthrowing is_nonthrowing.cpp)
target_link_libraries(predicates_is_nonthrowing PRIVATE doctest)
add_test(NAME "predicates::is-nonthrowing" COMMAND predicates_is_nonthrowing)

add_executable(predicates_is_primitive_type is_primitive_type.cpp)
target_link_libraries(predicates_is_primitive_type PRIVATE doctest)
add_test(NAME "predicates::is-primitive-type" COMMAND predicates_is_primitive_type)

