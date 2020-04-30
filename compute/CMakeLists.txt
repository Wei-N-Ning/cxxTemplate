add_executable(compute_align_size alignSize.cpp)
target_link_libraries(compute_align_size PRIVATE doctest)
add_test(NAME "compute::align-struct-size" COMMAND compute_align_size)

add_executable(compute_is_prime is_prime.cpp)
target_link_libraries(compute_is_prime PRIVATE doctest)
add_test(NAME "compute::is-prime" COMMAND compute_is_prime)

add_executable(compute_sfinae sfinae.cpp)
target_link_libraries(compute_sfinae PRIVATE doctest)
add_test(NAME "compute::sfinae" COMMAND compute_sfinae)

