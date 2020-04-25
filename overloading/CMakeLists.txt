
add_executable(overload_resolution_order resolution_order.cpp)
target_link_libraries(overload_resolution_order PRIVATE doctest)
add_test(NAME "overloading::resolution-order" COMMAND overload_resolution_order)
