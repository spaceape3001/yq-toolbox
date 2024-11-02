# Meta

Meta is runtime reflection, by employing registration requirements on individual components, aspects of the codebase is exposed in an abstract fashion.  This permits for dynamic definition of behavior (ie, scripts, user inputs, etc).

*NOTE* Meta is expected to be defined at application initialization (see [Initialization](initialization.md) ) in the main thread, using the delayed initialization mechanism.

## Meta Meta

Class `Meta` is the generic base to all meta information.  It's got a name, description, flags, id, source, and a tree.

| function    | description                                                    |
|-------------|----------------------------------------------------------------|
| aliases     | Set of aliases this is also known for.                         |
| description | Brief description of the item                                  |
| children    | All children meta (ie, properties for a type/object)           |
| flags       | All flags for this meta                                        |
| generic     | What this meta is a generic for                                |
| has         | Tests for specific flag(s)                                     |
| id          | Meta id (unique to this meta)                                  |
| is_*        | Tests for known flag(s) patterns                               |
| name        | Name of the meta                                               |
| name32      | Name of the meta as a 32-bit unicode string                    |
| parent      | Meta parent (ie, the type/object for a property)               |
| source      | Source location of its definition                              |
| stem        | Name without namespace, so `yq::post::PBX` would be `PBX`      |
| stem32      | Stem (above) in 32-bit unicode                                 |
| tag         | Gets a tag                                                     |
| tagged      | Tests for a tag                                                |

### Strings

Meta holds onto string *views* which means the actual string must reside in the caller.  As most of this is being done with `"name"` syntax, that data is in the program strings-table, and is thus, fine.  Dynamic generation of a name is where this can be trouble, thus, if *dynamic* generation is required, allocation without free would be acceptable, and you can use `Meta::allocate_copy(std::ttring_view)` for this purpose.

*Standard encoding is UTF-8.*

### ID

A meta ID's identifier is unique, to it.

### Name

This is the name for the meta, its origin depends on what the meta is.  For objects/types, this is the C++ name for it, as stringified by the implement macro.  For properties/methods, it's the name provided in the declaration.

This name will remove the `yq::` namespace, if found (basically by advancing the `char*` pointer past it).  It's last bit beyond any namespace, is considered the "stem", which can be useful in situations.  Both of these are encoded into 32-bit unicode strings, with that accessible by the above API.

### Description


## Getting Meta

Getting the meta for a specific type/object is the same.

```
    #include <yq/meta/InfoBinder.hpp>  //< Has the `meta()` routine in it
    #include "MyType.hpp"
    #include "MyObject.hpp"
    
    const auto& typeInfo    = meta<MyType>();
    const auto& objectInfo  = meta<MyObject>();
```

For a specific object, it's

```
    #include "MyObject.hpp"
    MyObject*   obj        = new MyObject;
    const auto& objectInfo = obj -> metaInfo();  //< Function defined before I settled on convention
```

## Writing Meta

**MAIN THREAD/STARTUP ONLY**

For writing meta, it follows the generally same signature.

```
    #include "MyObject.hpp"
    #include <yq/meta/TypeInfoWriter.hpp>
    #include <yq/core/DelayInit.hpp>
    #include "MyType.hpp"
    
    static void reg_my_type()
    {
        auto w = writer<MyType>();
        w.description("It's my type");
        w.property("party", &MyType::party).description("Partying happening?");
    }
    
    YQ_INVOKE(reg_my_type();)
```

```
    #include "MyObject.hpp"
    #include <yq/meta/ObjectInfoWriter.hpp>
    #include <yq/core/DelayInit.hpp>
    
    void MyObject::init_info()
    {
        auto w = writer<MyObject>();
        w.description("It's my object");
        w.property("party", &MyObject::party).description("Partying happening?");
    }
    
    YQ_INVOKE(MyObject::init_info();)
```
 
Meta uses the notion of writers to differentiate between runtime and startup-initialization.  To alter meta requires a writer.  That writer has the mechanisms to define description, properties, methods, etc.




