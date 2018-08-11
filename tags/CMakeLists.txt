add_executable(timerPolicy timerPolicy.cpp)
set_target_properties(timerPolicy
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "tag::timer-policy" COMMAND iteratorTagTest)