# Mut, Immut References

## Reference Wrapper and Mutability

see: <https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper>


## Use value-semantic with reference

see: cxxConcurrency/stdthread/pass_arguments.cpp

thread ctor takes function argument by value, how can I execute a function
that expects pass-by-reference? use `std::ref` (or `std::cref` if immutable)

## Reference Wrapper and Optional

## std::ref

see: <https://en.cppreference.com/w/cpp/utility/functional/ref>

> ref and cref are helper functions that generate an object of type 
> std::reference_wrapper, using template argument deduction to determine the 
> template argument of the result.

see: cxxAlgorithm/random/mt19937_state.cpp for a use case;

prefer std::ref() to legacy `&` style.

