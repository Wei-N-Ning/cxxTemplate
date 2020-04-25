
add_executable(traits_is_type test_isType.cpp)
target_link_libraries(traits_is_type PRIVATE doctest)
add_test(NAME "traits::is-type" COMMAND traits_is_type)

add_executable(traits_has_method has_method_trait.cpp)
target_link_libraries(traits_has_method PRIVATE doctest)
add_test(NAME "traits::has-method" COMMAND traits_has_method)

add_executable(traits_iterator_category iteratorCategory.cpp)
target_link_libraries(traits_iterator_category PRIVATE doctest)
add_test(NAME "traits::iterator-category" COMMAND traits_iterator_category)

add_executable(traits_method_template_in_class_template methodTemplateInClassTemplate.cpp)
target_link_libraries(traits_method_template_in_class_template PRIVATE doctest)
add_test(NAME "traits::method-template-in-class-template" COMMAND traits_method_template_in_class_template)
