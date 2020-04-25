
add_executable(specialization_explicit explicit.cpp)
add_test(NAME "specialization::explicit" COMMAND specialization_explicit)

add_executable(specialization_partial partial.cpp)
add_test(NAME "specialization::partial" COMMAND specialization_partial)

