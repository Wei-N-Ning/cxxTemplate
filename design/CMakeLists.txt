add_subdirectory(containers)
add_subdirectory(tags)
add_subdirectory(forwarding)

add_executable(typing_phantom_types phantom_types.cpp)
target_link_libraries(typing_phantom_types PRIVATE doctest)
add_test(NAME "typing::phantom-types" COMMAND typing_phantom_types)

add_executable(compute_align_size align_size.cpp)
target_link_libraries(compute_align_size PRIVATE doctest)
add_test(NAME "compute::align-struct-size" COMMAND compute_align_size)

add_executable(class_template_base template_base_class.cpp)
target_link_libraries(class_template_base PRIVATE doctest)
add_test(NAME "class::template-base-class" COMMAND class_template_base)

add_executable(class_recursive_template recur_class_template.cpp)
target_link_libraries(class_recursive_template PRIVATE doctest)
add_test(NAME "class::recursive-class-template" COMMAND class_recursive_template)

add_executable(class_inherit_singleton singleton_template.cpp)
target_link_libraries(class_inherit_singleton PRIVATE doctest)
add_test(NAME "class::inherit-singleton-base-class" COMMAND class_inherit_singleton)

add_executable(class_friend_function_template friend_function_template.cpp)
target_link_libraries(class_friend_function_template PRIVATE doctest)
add_test(NAME "class::friend-function-template" COMMAND class_friend_function_template)
