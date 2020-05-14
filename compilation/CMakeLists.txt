
add_executable(compilation_attributes attributes.cpp)
target_link_libraries(compilation_attributes PRIVATE doctest)
add_test(NAME "compilation::attributes" COMMAND compilation_attributes)
if(MSVC)
    target_compile_options(compilation_attributes PRIVATE /W4 /WX)
else()
    target_compile_options(compilation_attributes PRIVATE -Wall -Wextra -pedantic -Werror)
endif()