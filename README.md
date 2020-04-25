# Template Lang

## History

source: c++ templates: the complete guide

L791

> for historical reasons you can also use the keyword class instead of
> typename to define a type parameter
> the keyword typename came relatively late in the evolution of C++98
> prior to that the keyword class was the only way to introduce a type

L801

> you should prefer the use of typename

source: exception c++

exceptional P94

it was known that templates were a Turing-complete metalanguage allowing 
programs of arbitrary complexity to be written that could execute entirely 
at compile time, 

exceptional P95

(on export)

the world's only implementers of expert, EDG, report that in their 
experience, export is by far the most difficult C++ feature to implement, 
as much work as any three major C++ language features they have done 
(such as namespaces or member templates). The export feature alone took 
more than three person-years to code and test, not counting design work; 
by comparison, implementing the entire Java language took the same three 
people only two person-years.

## Template Source Code

### source inclusion model

source: exceptional P80

, is widely used (actively supported by all compilers)

, "inline"

, template's full source code must be visible to any code that uses
the template

, definition can be placed in a separate file, but must appear (via 
`#include` statement) in the compilation unit that uses it

### source separation model

, almost unsupported

, definitions do not need to be visible to callers

, does not change the way template is instantiated

### problem in inclusion model

, source exposure for the definitions: the whole world can see the 
perhaps-proprietary definitions.

, source dependencies: all callers depend on the internal details, and 
have recompile; also if the template definition uses other types not 
already mentioned, then all their callers will need to see those types' 
full definitions too

## Class template

see /class

## Template, Container and Iterator
