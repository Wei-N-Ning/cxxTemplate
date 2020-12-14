# Type Traits

## Has XX Method

**ultimate workaround**: see complete guide L15295 for a macro-based solution
that works for any data/function member

Note there is an older example pieced together from web findings; 
see has_method_trait.cpp

Complete guide L5157 introduces a **pattern**, using the "has size() member function"
as a demonstration.
see has_method_pattern.cpp

## Infer result type

what is the result type of Container<T1> op Container<T2> ?

in haskell this is determined by the type signature of the operator:

```haskell
f: a -> b -> b
-- or
f: a -> a -> a
```

