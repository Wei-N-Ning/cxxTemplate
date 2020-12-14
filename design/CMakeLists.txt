add_subdirectory(containers)
add_subdirectory(tags)

add_executable(typing_phantom_types phantom_types.cpp)
target_link_libraries(typing_phantom_types PRIVATE doctest)
add_test(NAME "typing::phantom-types" COMMAND typing_phantom_types)