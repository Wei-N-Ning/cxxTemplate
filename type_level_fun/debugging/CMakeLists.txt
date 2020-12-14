add_executable(typing_viewDeducedTypesTest viewDeducedTypes.cpp)
target_link_libraries(typing_viewDeducedTypesTest PRIVATE doctest)
add_test(NAME "typing::view-type" COMMAND typing_viewDeducedTypesTest)

add_executable(typing_typeid typeid.cpp)
target_link_libraries(typing_typeid PRIVATE doctest)
add_test(NAME "typing::typeid-and-typeinfo" COMMAND typing_typeid)