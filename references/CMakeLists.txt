add_executable(references_mutable mut_references.cpp)
target_link_libraries(references_mutable PRIVATE doctest)
add_test(NAME "references::mutable" COMMAND references_mutable)