# Tags

## Tag-dispatch

tag type can be used to implement a Haskell-like pattern matching mechanism:

```text
template
R implementation(args, Tags::Case1) { ... }
R implementation(args, Tags::Case2) { ... }
... more cases ...
R entry_point(args...) {
    implementation(args, generate_tag(args))
    -> dispatch to the corresponding case or compilation error
}
```

note, C++17's variant type (ported from boost) also offers a neat way to write
pattern-matching code, and guarantees type safety.