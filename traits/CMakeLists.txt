
add_executable(isTypeTest test_isType.cpp)
set_target_properties(isTypeTest
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "type-traits::is-type" COMMAND isTypeTest)