add_executable(timerPolicyTest timerPolicy.cpp)
set_target_properties(timerPolicyTest
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "tag::policy" COMMAND timerPolicyTest)