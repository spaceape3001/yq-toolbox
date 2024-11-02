# Units

This toolbox contains units, which are compile time annotations to values.  These units are generally defined in the `yq::unit` namespace.  Currently MKS and scaled units are supported.  The easiest way to use units is a single include.

```
#include <yq/units.hpp>
```

## Dimensions

A dimension is a grouping of similarly related units, with the full listing found `yq/unit/dims.hpp`.

Currently, this toolbox defines eight basic/fundamental dimensions to work against; while some already have equivalency, we keep the dimension to help thwart rookie coding errors in formulas and usage (Angle is one such dimension)

Some common dimensions:

| Dimension     | Defined       | Some Units                                    |
|---------------|---------------|-----------------------------------------------|
| Acceleration  | `L/T²`        | Meter per Second², Feet per Second²           |
| Angle         | `A`           | Degrees, Radians, Gradians                    |
| Area          | `L²`          | Meter², Feet²                                 |
| Charge        | `C*T`         | Coulomb                                       |
| Current       | `C`           | Ampere                                        |
| Density       | `M/L³`        | Kilogram per Meter³, Gram per cubic Centimeter|
| Energy        | `M*L²/T²`     | Joule, Calorie                                |
| Force         | `M*L/T²`      | Newton, Pound‡                                |
| Frequency     | `1/T`         | Hertz                                         |
| Intensity     | `I`           | Candela                                       |
| Length        | `L`           | Meter, Miles, Feet                            |
| Mass          | `M`           | Kilogram, Pound‡, Ounce                       |
| Matter        | `Q`           | Mole                                          |
| Power         | `M*L²/T³`     | Watt, Horsepower                              |
| Speed         | `L/T`         | Meters per Second, Miles Per Hour, Light Speed|
| Temperature   | `K`           | Kelvin, Rankine                               |
| Time          | `T`           | Second                                        |
| Voltage       | `M*L²/(C*T³)` | Volt                                          |
| Volume        | `L³`          | Meter³, Inch³, Gallon, Pint                   |

*‡ A distinction is made in the code between pounds of mass and pounds of force, use `PoundMass` or `PoundForce` to clarify.

## Literals

Defined in `yq/unit/literals.hpp` are some user-defined literals with symbols the compiler lets us use.  (ie, some won't be there, like m/s)  To use this in code.

```
    using namespace yq;
    using namespace yq::unit;
    
    Meter m = 0.3048_m;
    if(Feet(m) == 1._ft){
        yInfo() << "I feel excited!";
    }
```

## Usage

(TODO)



