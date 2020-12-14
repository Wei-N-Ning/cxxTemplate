add_executable(tlf_conslist_variadic_test variadic.cpp)
target_link_libraries(tlf_conslist_variadic_test PRIVATE doctest)
add_test(NAME "tlf::conslist::variadic-param" COMMAND tlf_conslist_variadic_test)

add_executable(tlf_conslist_variadic_fold variadic_fold.cpp)
target_link_libraries(tlf_conslist_variadic_fold PRIVATE doctest)
add_test(NAME "tlf::conslist::variadic-fold" COMMAND tlf_conslist_variadic_fold)

add_executable(tlf_conslist_variadic_match_many variadic_match_many.cpp)
target_link_libraries(tlf_conslist_variadic_match_many PRIVATE doctest)
add_test(NAME "tlf::conslist::variadic-match-many" COMMAND tlf_conslist_variadic_match_many)

add_executable(tlf_conslist_variadic_insert_many variadic_insert_many.cpp)
target_link_libraries(tlf_conslist_variadic_insert_many PRIVATE doctest)
add_test(NAME "tlf::conslist::variadic-insert-many" COMMAND tlf_conslist_variadic_insert_many)

add_executable(tlf_conslist_variadic_in_range variadic_in_range.cpp)
target_link_libraries(tlf_conslist_variadic_in_range PRIVATE doctest)
add_test(NAME "tlf::conslist::variadic-in-range" COMMAND tlf_conslist_variadic_in_range)

add_executable(tlf_conslist_variadic_istream_tuple variadic_istream_tuple.cpp)
target_link_libraries(tlf_conslist_variadic_istream_tuple PRIVATE doctest)
add_test(NAME "tlf::conslist::variadic-istream-for-tuple" COMMAND tlf_conslist_variadic_istream_tuple)