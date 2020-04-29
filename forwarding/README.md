# Forwarding

## Forwarding without using template

source: c++ templates: the complete guide L/3786

see: forwarding_notemplate.cpp

this is to demonstrate the concept only, also to show
why using template is a good idea (to remove redundant
code)

## Function Wrapper

stuck on how to handle the return type, without using explicit template instantiation, e.g.

`wrap<(int)(int, int)>(...)`

### Eli Bendersky's tutorial on perfect forwarding

### modern C++ challenge's timer function

this is closer to my goal of creating a drop-in replacement wrapper function,

`prof(fib, 38, nullptr)` vs `fib(38, nullptr)`

**BEWARE** that even though the original function `fib` has default value for the `cache` argument,
the forwarded version **DOES NOT ALLOW THAT**, I have to always pass in a value for the cache argument.
