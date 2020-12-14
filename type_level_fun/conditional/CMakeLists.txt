add_executable(tlf_conditional_constexpr_if constexpr_if.cpp)
target_link_libraries(tlf_conditional_constexpr_if PRIVATE doctest)
add_test(NAME "tlf::conditional::constexpr-if" COMMAND tlf_conditional_constexpr_if)

add_executable(tlf_conditional_conditional_t conditional_t.cpp)
target_link_libraries(tlf_conditional_conditional_t PRIVATE doctest)
add_test(NAME "tlf::conditional::conditional-t" COMMAND tlf_conditional_conditional_t)

add_executable(tlf_conditional_enable_if enable_if.cpp)
target_link_libraries(tlf_conditional_enable_if PRIVATE doctest)
add_test(NAME "tlf::conditional::enable-if" COMMAND tlf_conditional_enable_if)

add_executable(tlf_conditional_sfinae_if_not sfinae_if_not.cpp)
target_link_libraries(tlf_conditional_sfinae_if_not PRIVATE doctest)
add_test(NAME "tlf::conditional::sfinae-if-not" COMMAND tlf_conditional_sfinae_if_not)