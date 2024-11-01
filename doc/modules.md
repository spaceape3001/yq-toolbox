# Modules

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
