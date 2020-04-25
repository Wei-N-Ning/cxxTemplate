add_executable(functional_lambda lambda.cpp)
target_link_libraries(functional_lambda PRIVATE doctest)
add_test(NAME "functional::lambda" COMMAND functional_lambda)
