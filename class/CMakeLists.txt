add_executable(class_inherit_singleton inheritance.cpp)
target_link_libraries(class_inherit_singleton PRIVATE doctest)
add_test(NAME "class::inherit-singleton-base-class" COMMAND class_inherit_singleton)

add_executable(class_friend_function_template friend_function_template.cpp)
target_link_libraries(class_friend_function_template PRIVATE doctest)
add_test(NAME "class::friend-function-template" COMMAND class_friend_function_template)

add_executable(class_pod pod.cpp)
target_link_libraries(class_pod PRIVATE doctest)
add_test(NAME "class::pod/aggregate" COMMAND class_pod)

add_executable(class_template_base template_base_class.cpp)
target_link_libraries(class_template_base PRIVATE doctest)
add_test(NAME "class::template-base-class" COMMAND class_template_base)

add_executable(class_data_member_template data_member_template.cpp)
target_link_libraries(class_data_member_template PRIVATE doctest)
add_test(NAME "class::data-member-template" COMMAND class_data_member_template)

add_executable(class_recursive_template recur_class_template.cpp)
target_link_libraries(class_recursive_template PRIVATE doctest)
add_test(NAME "class::recursive-class-template" COMMAND class_recursive_template)

add_executable(class_empty_class empty_class.cpp)
target_link_libraries(class_empty_class PRIVATE doctest)
add_test(NAME "class::empty-class" COMMAND class_empty_class)
