add_executable(functional_lambda lambda.cpp)
target_link_libraries(functional_lambda PRIVATE doctest)
add_test(NAME "functional::lambda" COMMAND functional_lambda)

add_executable(functional_invoke invoke.cpp)
target_link_libraries(functional_invoke PRIVATE doctest)
add_test(NAME "functional::invoke" COMMAND functional_invoke)
