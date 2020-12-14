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