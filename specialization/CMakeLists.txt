
add_executable(specialization_explicit explicit.cpp)
target_link_libraries(specialization_explicit PRIVATE doctest)
add_test(NAME "specialization::explicit" COMMAND specialization_explicit)

add_executable(specialization_overload overload.cpp)
target_link_libraries(specialization_overload PRIVATE doctest)
add_test(NAME "specialization::overload" COMMAND specialization_overload)

add_executable(specialization_partial partial.cpp)
target_link_libraries(specialization_partial PRIVATE doctest)
add_test(NAME "specialization::partial" COMMAND specialization_partial)

