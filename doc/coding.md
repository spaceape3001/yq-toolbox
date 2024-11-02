# Coding Standards

## Language Standard

`C++23` or LATER is the language standard to be used.

## File Extensions

| Extension | Usage              |
|-----------|--------------------|
| `*.cpp`   | C++ source files   |
| `*.hpp`   | C++ header files   |
| `*.hxx`   | C++ implementation header files |
| `*.ipp`   | C++ implementation source files |

## Leaner Header Files

Lean toward more granular header files, separating forward declarations (in `preamble.hpp`) to declarations (`class Thing`) and the inline-implementations (`*.hxx`).

## Unity Style Builds

Lean toward unity style builds, this is where a particular `*.cpp` file includes multiple source implementation files `*.ipp`.

## Namespace

Primary root namespace is `yq`.  This is from the originations of this toolbox/project in the "YourQuill" project/repository, and the namespace is maintained.

## Modules

Once C++ modules mature, this library will most likely be converted over to them.  However, in the meanwhile, expect the current segregation of declarations and implementations to continue while the `#include` mechanism is the predominant way of using these libraries.  For math, this segregation is becoming rigourous, so expect the following general usage pattern.

```
#include <Thing1.hpp>
#include <Thing2.hpp>
...
#include <ThingN.hpp>

#include <Thing1.hxx>
#include <Thing2.hxx>
...
#include <ThingN.hxx>
```

This allows decoupling so that including one implementation doesn't automatically include ALL of the library.  The flip side is this means that all the `*.hpp` need to be included *FIRST* before the `*.hxx` are included, this is because the `*.hxx` will be using `#ifdef/#endif` macros to exclude unwanted features and cross-coupling.

