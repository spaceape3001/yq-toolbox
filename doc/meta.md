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
| stem32      | Stem (above) in 32-bit unicode strings                         |
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



### Writers

## Types

## Objects

## Properties

## Methods

## Globals



