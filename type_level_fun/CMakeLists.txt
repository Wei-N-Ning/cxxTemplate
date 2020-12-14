add_subdirectory(conditional)
add_subdirectory(predicates)

add_executable(tlf_declval declval.cpp)
target_link_libraries(tlf_declval PRIVATE doctest)
add_test(NAME "tlf::declval" COMMAND tlf_declval)

add_executable(tlf_decltype_expr_type decltype_expr_type.cpp)
target_link_libraries(tlf_decltype_expr_type PRIVATE doctest)
add_test(NAME "tlf::decltype::expression-type" COMMAND tlf_decltype_expr_type)