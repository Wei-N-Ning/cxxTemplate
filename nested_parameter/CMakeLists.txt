
add_executable(nested_collection_depend_on_t collection_depend_on_t.cpp)
target_link_libraries(nested_collection_depend_on_t PRIVATE doctest)
add_test(NAME "nested::ContainerT-depend-on-T" COMMAND nested_collection_depend_on_t)

add_executable(nested_typename_keyword typename_keyword.cpp)
target_link_libraries(nested_typename_keyword PRIVATE doctest)
add_test(NAME "nested::typename-keyword" COMMAND nested_typename_keyword)
