add_executable(references_mutable mut_references.cpp)
target_link_libraries(references_mutable PRIVATE doctest)
add_test(NAME "references::mutable" COMMAND references_mutable)

add_executable(references_immutable immutable_ref.cpp)
target_link_libraries(references_immutable PRIVATE doctest)
add_test(NAME "references::immutable" COMMAND references_immutable)

add_executable(references_removal remove_reference.cpp)
target_link_libraries(references_removal PRIVATE doctest)
add_test(NAME "references::remove-reference" COMMAND references_removal)