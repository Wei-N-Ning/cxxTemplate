add_executable(compute_align_size alignSize.cpp)
target_link_libraries(compute_align_size PRIVATE doctest)
add_test(NAME "compute::align-struct-size" COMMAND compute_align_size)