add_executable(singletonInheritanceTest inheritance.cpp)
set_target_properties(singletonInheritanceTest
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "class-template::singleton" COMMAND singletonInheritanceTest)