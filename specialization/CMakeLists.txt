
add_executable(explicitSpecialization explicit.cpp)
set_target_properties(explicitSpecialization
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "specialization::explicit"
    COMMAND explicitSpecialization)

add_executable(partialSpecialization partial.cpp)
set_target_properties(partialSpecialization
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "specialization::partial"
    COMMAND partialSpecialization)

