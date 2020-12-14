# Constness & Const-Correction

## Const reference bites too

inspired by: Complete guide L4392

read the cache invalidation theory and why I should prefer
inline function template that uses const ref

> the bad news is moderated by inlining: if the compiler can expand the call inline,
> it can reason about the caller and the callee together and in many cases "see"
> that the address is not used for anything but passing the underlying value

## Mutable Reference

complete guide L4422

not allowed for prvalue(temporaries) or xvalue (std::move)
