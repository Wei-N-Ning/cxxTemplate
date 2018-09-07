
source:
exceptional P80

### source inclusion model

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






