
add_executable(forwarding_eli_perfect_forwarding eli_perfect_forwarding.cpp)
target_link_libraries(forwarding_eli_perfect_forwarding PRIVATE doctest)
add_test(NAME "forwarding::eli-perfect-forwarding" COMMAND forwarding_eli_perfect_forwarding)

add_executable(forwarding_wrap_function wrap_function.cpp)
target_link_libraries(forwarding_wrap_function PRIVATE doctest)
add_test(NAME "forwarding::wrap-function" COMMAND forwarding_wrap_function)

add_executable(forwarding_motivation forward_motivation.cpp)
target_link_libraries(forwarding_motivation PRIVATE doctest)
add_test(NAME "forwarding::motivation_of_forwarding" COMMAND forwarding_motivation)

add_executable(forwarding_variadic variadic.cpp)
target_link_libraries(forwarding_variadic PRIVATE doctest)
add_test(NAME "forwarding::variadic-template" COMMAND forwarding_variadic)
