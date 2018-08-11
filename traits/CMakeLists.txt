
add_executable(isTypeTest test_isType.cpp)
set_target_properties(isTypeTest
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "type-traits::is-type" COMMAND isTypeTest)

add_executable(hasMethodTrait has_method_trait.cpp)
set_target_properties(hasMethodTrait
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "type-traits::has-method" COMMAND hasMethodTrait)

add_executable(iteratorCategory iteratorCategory.cpp)
set_target_properties(iteratorCategory
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "type-traits::iterator-category" COMMAND iteratorCategory)

add_executable(isSameType methodTemplateInClassTemplate.cpp)
set_target_properties(isSameType
    PROPERTIES
    CXX_STANDARD 14)
add_test(NAME "type-traits::is-same-type" COMMAND isSameType)
