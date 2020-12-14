add_subdirectory(decay)

add_executable(traits_method_template_in_class_template methodTemplateInClassTemplate.cpp)
target_link_libraries(traits_method_template_in_class_template PRIVATE doctest)
add_test(NAME "traits::method-template-in-class-template" COMMAND traits_method_template_in_class_template)

add_executable(typing_deduce_from_func_arg deduce_from_func_arg.cpp)
target_link_libraries(typing_deduce_from_func_arg PRIVATE doctest)
add_test(NAME "typing::deduce-from-func-arg" COMMAND typing_deduce_from_func_arg)

add_executable(typing_typeTAndParamTest typeTAndParam.cpp)
target_link_libraries(typing_typeTAndParamTest PRIVATE doctest)
add_test(NAME "typing::T-and-param" COMMAND typing_typeTAndParamTest)