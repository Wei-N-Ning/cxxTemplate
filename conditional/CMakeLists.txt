add_executable(conditional_enable_if enable_if.cpp)
target_link_libraries(conditional_enable_if PRIVATE doctest)
add_test(NAME "compute::conditional-enable-if" COMMAND conditional_enable_if)
