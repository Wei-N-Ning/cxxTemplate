add_executable(conditional_enable_if enable_if.cpp)
target_link_libraries(conditional_enable_if PRIVATE doctest)
add_test(NAME "conditional::enable-if" COMMAND conditional_enable_if)

add_executable(conditional_is_convertible is_convertible.cpp)
target_link_libraries(conditional_is_convertible PRIVATE doctest)
add_test(NAME "conditional::is-convertible" COMMAND conditional_is_convertible)

add_executable(conditional_is_constructible is_constructible.cpp)
target_link_libraries(conditional_is_constructible PRIVATE doctest)
add_test(NAME "conditional::is-constructible" COMMAND conditional_is_constructible)

add_executable(conditional_constexpr_if constexpr_if.cpp)
target_link_libraries(conditional_constexpr_if PRIVATE doctest)
add_test(NAME "conditional::constexpr-if" COMMAND conditional_constexpr_if)

add_executable(conditional_template conditional_t.cpp)
target_link_libraries(conditional_template PRIVATE doctest)
add_test(NAME "conditional::template" COMMAND conditional_template)