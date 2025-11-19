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

    std::error_code     _gc(lua_State*, int, object_k);
    std::error_code     _gc(lua_State*, int, type_k);
    
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

    //! Type for the object (uses meta)
    const Meta*         _metatype(lua_State*l, int n);

    //! Generic type string to a lua type ID (don't use with the meta)
    std::string_view    _typename(int);
    
}
