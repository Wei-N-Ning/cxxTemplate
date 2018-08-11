add_executable(computeAlignmentSize alignSize.cpp)
set_target_properties(computeAlignmentSize
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "compute::struct-size"
    COMMAND computeAlignmentSize)