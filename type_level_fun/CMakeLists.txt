add_subdirectory(conditional)
add_subdirectory(predicates)
add_subdirectory(parampack)
add_subdirectory(conslist)
add_subdirectory(properties)

add_executable(tlf_declval declval.cpp)
target_link_libraries(tlf_declval PRIVATE doctest)
add_test(NAME "tlf::declval" COMMAND tlf_declval)

add_executable(tlf_decltype decltype.cpp)
target_link_libraries(tlf_decltype PRIVATE doctest)
add_test(NAME "tlf::decltype" COMMAND tlf_decltype)

add_executable(tlf_decltype_instances decltype_instances.cpp)
target_link_libraries(tlf_decltype_instances PRIVATE doctest)
add_test(NAME "tlf::decltype_on_instances" COMMAND tlf_decltype_instances)

add_executable(tlf_decltype_expr_type decltype_expr_type.cpp)
target_link_libraries(tlf_decltype_expr_type PRIVATE doctest)
add_test(NAME "tlf::decltype::expression-type" COMMAND tlf_decltype_expr_type)

add_executable(typing_ctvalue ctvalue.cpp)
target_link_libraries(typing_ctvalue PRIVATE doctest)
add_test(NAME "typing::ctvalue" COMMAND typing_ctvalue)

add_executable(typing_ctvalue_auto ctvalue_auto.cpp)
target_link_libraries(typing_ctvalue_auto PRIVATE doctest)
add_test(NAME "typing::ctvalue-auto-deducible" COMMAND typing_ctvalue_auto)
