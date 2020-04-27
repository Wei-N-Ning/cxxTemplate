
add_executable(decay_raw_array_no_decay no_decay_array.cpp)
target_link_libraries(decay_raw_array_no_decay PRIVATE doctest)
add_test(NAME "decay::raw-array-no-decay" COMMAND decay_raw_array_no_decay)
