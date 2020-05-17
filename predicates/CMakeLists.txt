add_executable(predicates_enable_if enable_if.cpp)
target_link_libraries(predicates_enable_if PRIVATE doctest)
add_test(NAME "predicates::enable-if" COMMAND predicates_enable_if)

add_executable(predicates_is_convertible is_convertible.cpp)
target_link_libraries(predicates_is_convertible PRIVATE doctest)
add_test(NAME "predicates::is-convertible" COMMAND predicates_is_convertible)

add_executable(predicates_is_constructible is_constructible.cpp)
target_link_libraries(predicates_is_constructible PRIVATE doctest)
add_test(NAME "predicates::is-constructible" COMMAND predicates_is_constructible)

add_executable(predicates_constexpr_if constexpr_if.cpp)
target_link_libraries(predicates_constexpr_if PRIVATE doctest)
add_test(NAME "predicates::constexpr-if" COMMAND predicates_constexpr_if)

add_executable(predicates_template conditional_t.cpp)
target_link_libraries(predicates_template PRIVATE doctest)
add_test(NAME "predicates::template" COMMAND predicates_template)

add_executable(predicates_is_base_of is_base_of.cpp)
target_link_libraries(predicates_is_base_of PRIVATE doctest)
add_test(NAME "predicates::is-base-of" COMMAND predicates_is_base_of)

add_executable(predicates_sfinae_if_not sfinae_if_not.cpp)
target_link_libraries(predicates_sfinae_if_not PRIVATE doctest)
add_test(NAME "predicates::sfinae-if-not" COMMAND predicates_sfinae_if_not)

add_executable(predicates_has_member has_member.cpp)
target_link_libraries(predicates_has_member PRIVATE doctest)
add_test(NAME "predicates::has-member" COMMAND predicates_has_member)

add_executable(predicates_is_legit_expression is_legit_expression.cpp)
target_link_libraries(predicates_is_legit_expression PRIVATE doctest)
add_test(NAME "predicates::is-legit-expression" COMMAND predicates_is_legit_expression)
