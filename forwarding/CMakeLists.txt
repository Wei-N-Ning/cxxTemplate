
add_executable(eli_perfect_forwarding eli_perfect_forwarding.cpp)
add_test(NAME "forwarding::eli-perfect-forwarding" COMMAND eli_perfect_forwarding)

add_executable(wrap_function wrap_function.cpp)
target_link_libraries(wrap_function PRIVATE doctest)
add_test(NAME "forwarding::wrap-function" COMMAND wrap_function)
