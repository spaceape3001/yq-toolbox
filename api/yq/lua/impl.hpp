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

    //

    bool                _gc(lua_State*, int, object_k);
    
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

    // Creates a meta table
    void                _metamake(lua_State*, const ObjectMeta&);
    
    Object*             _object(lua_State *l, int n);
    
    void                _pop(lua_State* l);

    std::error_code     _push(lua_State* l, Object* obj, XFlags flags);
    bool                _push(lua_State* l, const value_t& val, unsigned n=0);

    //! Generic type string to a lua type ID (don't use with the meta)
    std::string_view    _type(int);
    
}
