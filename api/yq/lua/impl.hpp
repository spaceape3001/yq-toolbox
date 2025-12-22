////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/types.hpp>

namespace yq::lua {


    //////////////////////////////////////////////////////////////////////////////
    //  Micro helpers, these *ASSUME* things (like valid pointers, in range, etc)
    //  Technically more "impl" than external, simply going to be reused so exposed.

    //! Converts lua error code into a std::error_code
    std::error_code     _error(int);
    

    XFlags              _flags(lua_State *l, int n);
    
    //! Set flags to the top item (table)
    void    _flags_set(lua_State*, XFlags);

    std::error_code     _gc(lua_State*, int, object_k);
    std::error_code     _gc(lua_State*, int, type_k);
    
    //! ID from the specified value (returns 0 if errors)
    uint64_t            _id(lua_State*l, int);
    
    int                 _enum(lua_State*l, int);

    //! Assumes the pointer of the meta field on the given table is a valid meta thing
    
    /*! Assumes the given stack value is a table representing a complex thing (ie, object, any), 
        and extracts the meta pointer from it.  
    */
    const Meta*         _meta(lua_State*l, int n);
    
    /*! Assumes the given stack item is a table representing a complex thing (ie, object), 
        and extracts the meta pointer from it.  
    */
    const ObjectMeta*   _meta(lua_State*l, int n, object_k);

    /*! Assumes the given stack item is a table representing a complex thing (ie, any), 
        and extracts the meta pointer from it.  
    */
    const TypeMeta*     _meta(lua_State*l, int n, type_k);

    //! Adds meta to the top item (so long as it's a table)
    void                _meta_add(lua_State*l, const TypeMeta&);
    
    //! Creates a table, primed with meta, ready for caller to add the data
    std::error_code    _prime(lua_State*l, const TypeMeta&, XFlags);

    void        _metamake(lua_State* l, meta_k, const Meta& m);
    void        _metamake(lua_State* l, const ObjectMeta& m);
    void        _metamake(lua_State* l, const TypeMeta& m);
    void        _metamake_nogc(lua_State* l, const TypeMeta& tm);
    
    std::vector<const ModuleInfo*>  _modules(const ObjectMeta&om);
    std::vector<const ModuleInfo*>  _modules(const TypeMeta&om);
    std::vector<const ModuleInfo*>  _modules(meta_k, const Meta&om);
    
    Object*             _object(lua_State *l, int n);
    
    //! Assumes the given stack item is a table representing a complex thing,
    //! Extracts the pointer from it
    void*               _pointer(lua_State* l, int n);
    
    void                _pop(lua_State* l);

    std::error_code     _push(lua_State*l, const Meta*, XFlags);

    std::error_code     _push(lua_State* l, Object* obj, XFlags flags);
    std::error_code     _push(lua_State* l, const value_t& val, unsigned n=0);
    std::error_code     _push(lua_State* l, const TypeMeta& type, const void* ptr, XFlags flags);
    
    std::error_code     _push_enum(lua_State*l, int);
    
    //  pushed as an ID to the lua stack
    std::error_code     _push_id(lua_State*l, uint64_t);
    


    //! Type for the object (uses meta)
    const Meta*         _metatype(lua_State*l, int n);

    //! Generic type string to a lua type ID (don't use with the meta)
    std::string_view    _typename(int);
    
}
