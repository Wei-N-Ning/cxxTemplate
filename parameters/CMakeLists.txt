add_executable(variadicTest variadic.cpp)
set_target_properties(variadicTest
    PROPERTIES
    CXX_STANDARD 14)

add_executable(nonTypeParameter nonTypeParam.cpp)
set_target_properties(nonTypeParameter
    PROPERTIES
    CXX_STANDARD 14)
