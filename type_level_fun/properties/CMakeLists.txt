add_executable(tlf_properties_has_member has_member.cpp)
target_link_libraries(tlf_properties_has_member PRIVATE doctest)
add_test(NAME "tlf::properties::has-member" COMMAND tlf_properties_has_member)

add_executable(tlf_properties_has_all_methods has_all_methods.cpp)
target_link_libraries(tlf_properties_has_all_methods PRIVATE doctest)
add_test(NAME "tlf::properties::has-all-methods" COMMAND tlf_properties_has_all_methods)

add_executable(tlf_properties_has_method_pattern has_method_pattern.cpp)
target_link_libraries(tlf_properties_has_method_pattern PRIVATE doctest)
add_test(NAME "tlf::properties::has-method-pattern" COMMAND tlf_properties_has_method_pattern)

add_executable(tlf_properties_has_method has_method_trait.cpp)
target_link_libraries(tlf_properties_has_method PRIVATE doctest)
add_test(NAME "tlf::properties::has-method" COMMAND tlf_properties_has_method)

add_executable(tlf_properties_container_value_type container_value_type.cpp)
target_link_libraries(tlf_properties_container_value_type PRIVATE doctest)
add_test(NAME "tlf::properties::container_value_type" COMMAND tlf_properties_container_value_type)

add_executable(typing_type_probing type_probing.cpp)
target_link_libraries(typing_type_probing PRIVATE doctest)
add_test(NAME "typing::type_probing" COMMAND typing_type_probing)

add_executable(nested_collection_depend_on_t collection_depend_on_t.cpp)
target_link_libraries(nested_collection_depend_on_t PRIVATE doctest)
add_test(NAME "nested::ContainerT-depend-on-T" COMMAND nested_collection_depend_on_t)

add_executable(nested_typename_keyword typename_keyword.cpp)
target_link_libraries(nested_typename_keyword PRIVATE doctest)
add_test(NAME "nested::typename-keyword" COMMAND nested_typename_keyword)
