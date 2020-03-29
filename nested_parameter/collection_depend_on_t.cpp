// nested template parameter, see:
// https://stackoverflow.com/questions/20373466/nested-c-template-parameters-for-functions
// cpp reference:
// https://en.cppreference.com/w/cpp/language/template_parameters
// template and class keywords, since C++17 are interchangeable
// https://stackoverflow.com/questions/2023977/difference-of-keywords-typename-and-class-in-templates
template <typename T, template <typename> typename CollectionType>
T doSum(const CollectionType<T> &input, const T &init = 0) {
    return std::accumulate(input.cbegin(), input.cend(), init);
}


