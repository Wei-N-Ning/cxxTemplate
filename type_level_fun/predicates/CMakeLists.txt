
add_executable(tlf_predicates_roll_my_own_predicate roll_my_own_predicate.cpp)
target_link_libraries(tlf_predicates_roll_my_own_predicate PRIVATE doctest)
add_test(NAME "tlf::predicates::roll_my_own_predicate" COMMAND tlf_predicates_roll_my_own_predicate)

add_executable(tlf_predicates_is_convertible is_convertible.cpp)
target_link_libraries(tlf_predicates_is_convertible PRIVATE doctest)
add_test(NAME "tlf::predicates::is-convertible" COMMAND tlf_predicates_is_convertible)

add_executable(tlf_predicates_is_constructible is_constructible.cpp)
target_link_libraries(tlf_predicates_is_constructible PRIVATE doctest)
add_test(NAME "tlf::predicates::is-constructible" COMMAND tlf_predicates_is_constructible)

add_executable(tlf_predicates_is_base_of is_base_of.cpp)
target_link_libraries(tlf_predicates_is_base_of PRIVATE doctest)
add_test(NAME "tlf::predicates::is-base-of" COMMAND tlf_predicates_is_base_of)

add_executable(tlf_predicates_is_legit_expression is_legit_expression.cpp)
target_link_libraries(tlf_predicates_is_legit_expression PRIVATE doctest)
add_test(NAME "tlf::predicates::is-legit-expression" COMMAND tlf_predicates_is_legit_expression)

add_executable(tlf_predicates_is_nonthrowing is_nonthrowing.cpp)
target_link_libraries(tlf_predicates_is_nonthrowing PRIVATE doctest)
add_test(NAME "tlf::predicates::is-nonthrowing" COMMAND tlf_predicates_is_nonthrowing)

add_executable(tlf_predicates_is_primitive_type is_primitive_type.cpp)
target_link_libraries(tlf_predicates_is_primitive_type PRIVATE doctest)
add_test(NAME "tlf::predicates::is-primitive-type" COMMAND tlf_predicates_is_primitive_type)

add_executable(const_is_const is_const.cpp)
target_link_libraries(const_is_const PRIVATE doctest)
add_test(NAME "const::is-const" COMMAND const_is_const)
