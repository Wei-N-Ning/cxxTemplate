
add_executable(functionOverloading functions.cpp)
set_target_properties(functionOverloading
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "overloading::functions" COMMAND functionOverloading)
