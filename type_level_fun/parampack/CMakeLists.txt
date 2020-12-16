add_executable(tlf_parampack_variadic_test variadic.cpp)
target_link_libraries(tlf_parampack_variadic_test PRIVATE doctest)
add_test(NAME "tlf::parampack::variadic-param" COMMAND tlf_parampack_variadic_test)

add_executable(tlf_parampack_variadic_fold variadic_fold.cpp)
target_link_libraries(tlf_parampack_variadic_fold PRIVATE doctest)
add_test(NAME "tlf::parampack::variadic-fold" COMMAND tlf_parampack_variadic_fold)

add_executable(tlf_parampack_variadic_mapfilteracc variadic_map_filter_acc.cpp)
target_link_libraries(tlf_parampack_variadic_mapfilteracc PRIVATE doctest)
add_test(NAME "tlf::parampack::variadic_map_filter_acc" COMMAND tlf_parampack_variadic_mapfilteracc)

add_executable(tlf_parampack_variadic_match_many variadic_match_many.cpp)
target_link_libraries(tlf_parampack_variadic_match_many PRIVATE doctest)
add_test(NAME "tlf::parampack::variadic-match-many" COMMAND tlf_parampack_variadic_match_many)

add_executable(tlf_parampack_variadic_insert_many variadic_insert_many.cpp)
target_link_libraries(tlf_parampack_variadic_insert_many PRIVATE doctest)
add_test(NAME "tlf::parampack::variadic-insert-many" COMMAND tlf_parampack_variadic_insert_many)

add_executable(tlf_parampack_variadic_in_range variadic_in_range.cpp)
target_link_libraries(tlf_parampack_variadic_in_range PRIVATE doctest)
add_test(NAME "tlf::parampack::variadic-in-range" COMMAND tlf_parampack_variadic_in_range)

add_executable(tlf_parampack_variadic_istream_tuple variadic_istream_tuple.cpp)
target_link_libraries(tlf_parampack_variadic_istream_tuple PRIVATE doctest)
add_test(NAME "tlf::parampack::variadic-istream-for-tuple" COMMAND tlf_parampack_variadic_istream_tuple)