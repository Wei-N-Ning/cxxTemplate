
add_executable(nested_collection_depend_on_t collection_depend_on_t.cpp)
target_link_libraries(nested_collection_depend_on_t PRIVATE doctest)
add_test(NAME "nested::ContainerT-depend-on-T" COMMAND nested_collection_depend_on_t)
