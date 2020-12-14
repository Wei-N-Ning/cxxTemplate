add_executable(design_containers_stack stack.cpp)
target_link_libraries(design_containers_stack PRIVATE doctest)
add_test(NAME "design::containers::stack-example" COMMAND design_containers_stack)

add_executable(design_containers_fixed_size_stack fixed_size_stack.cpp)
target_link_libraries(design_containers_fixed_size_stack PRIVATE doctest)
add_test(NAME "design::containers::fixed-size-stack" COMMAND design_containers_fixed_size_stack)

add_executable(design_containers_curious_recurring_template curious_recurring_template.cpp)
target_link_libraries(design_containers_curious_recurring_template PRIVATE doctest)
add_test(NAME "design::containers::curious-recurring-template" COMMAND design_containers_curious_recurring_template)

add_executable(traits_iterator_category iterator_category.cpp)
target_link_libraries(traits_iterator_category PRIVATE doctest)
add_test(NAME "traits::iterator-category" COMMAND traits_iterator_category)

add_executable(nested_method_template nested_method_template.cpp)
target_link_libraries(nested_method_template PRIVATE doctest)
add_test(NAME "nested::method-template-in-class-template" COMMAND nested_method_template)
