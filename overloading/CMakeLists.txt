
add_executable(overload_resolution_order resolution_order.cpp)
target_link_libraries(overload_resolution_order PRIVATE doctest)
add_test(NAME "overloading::resolution-order" COMMAND overload_resolution_order)

add_executable(overload_specialized_swap specialized_swap.cpp)
target_link_libraries(overload_specialized_swap PRIVATE doctest)
add_test(NAME "overloading::specialized-swap" COMMAND overload_specialized_swap)


