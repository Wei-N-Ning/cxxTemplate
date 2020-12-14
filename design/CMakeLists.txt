add_subdirectory(containers)
add_subdirectory(tags)
add_subdirectory(forwarding)

add_executable(typing_phantom_types phantom_types.cpp)
target_link_libraries(typing_phantom_types PRIVATE doctest)
add_test(NAME "typing::phantom-types" COMMAND typing_phantom_types)

add_executable(compute_align_size alignSize.cpp)
target_link_libraries(compute_align_size PRIVATE doctest)
add_test(NAME "compute::align-struct-size" COMMAND compute_align_size)
