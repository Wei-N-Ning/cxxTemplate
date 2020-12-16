add_executable(tlf_conslist cons_list.cpp)
target_link_libraries(tlf_conslist PRIVATE doctest)
add_test(NAME "tlf::conslist" COMMAND tlf_conslist)

add_executable(typing_typelist_algorithms typelist_algorithms.cpp)
target_link_libraries(typing_typelist_algorithms PRIVATE doctest)
add_test(NAME "typing::typelist-algorithms" COMMAND typing_typelist_algorithms)

add_executable(typing_typelist_transform typelist_transform.cpp)
target_link_libraries(typing_typelist_transform PRIVATE doctest)
add_test(NAME "typing::typelist-transform" COMMAND typing_typelist_transform)

add_executable(typing_typelist_accumulate typelist_accumulate.cpp)
target_link_libraries(typing_typelist_accumulate PRIVATE doctest)
add_test(NAME "typing::typelist-accumulate" COMMAND typing_typelist_accumulate)

add_executable(typing_typelist_insertion_sort typelist_insertion_sort.cpp)
target_link_libraries(typing_typelist_insertion_sort PRIVATE doctest)
add_test(NAME "typing::typelist-insertion-sort" COMMAND typing_typelist_insertion_sort)

add_executable(typing_typelist_creation typelist_creation.cpp)
target_link_libraries(typing_typelist_creation PRIVATE doctest)
add_test(NAME "typing::typelist_creation" COMMAND typing_typelist_creation)