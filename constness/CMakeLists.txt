
add_executable(const_is_const is_const.cpp)
target_link_libraries(const_is_const PRIVATE doctest)
add_test(NAME "const::is-const" COMMAND const_is_const)
