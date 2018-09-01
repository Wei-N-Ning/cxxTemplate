
add_executable(eli_perfect_forwarding eli_perfect_forwarding.cpp)
set_target_properties(eli_perfect_forwarding
    PROPERTIES
    CXX_STANDARD 14)
add_test(
    NAME
    "perfect-forwarding"
    COMMAND
    eli_perfect_forwarding
    )