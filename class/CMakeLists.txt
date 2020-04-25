add_executable(class_inherit_singleton inheritance.cpp)
target_link_libraries(class_inherit_singleton PRIVATE doctest)
add_test(NAME "class::inherit-singleton-base-class" COMMAND class_inherit_singleton)

add_executable(class_friend_function_template friend_function_template.cpp)
target_link_libraries(class_friend_function_template PRIVATE doctest)
add_test(NAME "class::friend-function-template" COMMAND class_friend_function_template)

add_executable(class_stack stack.cpp)
target_link_libraries(class_stack PRIVATE doctest)
add_test(NAME "class::stack-example" COMMAND class_stack)

add_executable(class_pod pod.cpp)
target_link_libraries(class_pod PRIVATE doctest)
add_test(NAME "class::pod/aggregate" COMMAND class_pod)
