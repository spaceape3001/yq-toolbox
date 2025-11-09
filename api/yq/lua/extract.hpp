////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/lua/keywords.hpp>
#include <yq/lua/types.hpp>
#include <yq/typedef/expected.hpp>

namespace yq::lua {
    //////////////////////////////////////////////////////////////////////////////
    //  Extracting
    //
    //  Usage
    //      (type/item) (luaState*, int)  
    //
    //          Gets the item from the stack with negatives used to get the last (n) 
    //          item pushed.   (ie, -1 to get top of stack).
    //
    //      (type/item) (luaState*, GLOBAL, const char*)
    //
    //          Gets the specified global using the specified key
    //
    //      (type/item) (luaState*, UPVALUE, int)
    //
    //          Gets the specified upvalue (ie, bound at registration), where 1 <= n <= 255
    
 
    boolean_x               boolean(lua_State*, int);
    boolean_x               boolean(lua_State*, global_k, const char*);
    boolean_x               boolean(lua_State*, upvalue_k, int);
    
    double_x                double_(lua_State*, int);
    double_x                double_(lua_State*, global_k, const char*);
    double_x                double_(lua_State*, upvalue_k, int);
    
    integer_x               integer(lua_State*, int);
    integer_x               integer(lua_State*, global_k, const char*);
    integer_x               integer(lua_State*, upvalue_k, int);
    
    object_ptr_x            object(lua_State*, int);
    object_cptr_x           object(lua_State*, int, const_k);
    object_ptr_x            object(lua_State*, int, const ObjectMeta&);
    object_cptr_x           object(lua_State*, int, const ObjectMeta&, const_k);

    object_ptr_x            object(lua_State*, global_k, const char*);
    object_cptr_x           object(lua_State*, global_k, const char*, const_k);
    object_ptr_x            object(lua_State*, global_k, const char*, const ObjectMeta&);
    object_cptr_x           object(lua_State*, global_k, const char*, const ObjectMeta&, const_k);

    object_ptr_x            object(lua_State*, upvalue_k, int);
    object_cptr_x           object(lua_State*, upvalue_k, int, const_k);
    object_ptr_x            object(lua_State*, upvalue_k, int, const ObjectMeta&);
    object_cptr_x           object(lua_State*, upvalue_k, int, const ObjectMeta&, const_k);
    
    // defined in lualua.hxx
    template <class Obj>
    Expect<Obj*>            object_as(lua_State*, int);

    // defined in lualua.hxx
    template <class Obj>
    Expect<const Obj*>      object_as(lua_State*, int, const_k);

    // defined in lualua.hxx
    template <class Obj>
    Expect<Obj*>            object_as(lua_State*, global_k, const char*);

    // defined in lualua.hxx
    template <class Obj>
    Expect<const Obj*>      object_as(lua_State*, global_k, const char*, const_k);
    
    // defined in lualua.hxx
    template <class Obj>
    Expect<Obj*>            object_as(lua_State*, upvalue_k, int);

    // defined in lualua.hxx
    template <class Obj>
    Expect<const Obj*>      object_as(lua_State*, upvalue_k, int, const_k);

    //! Returns user data as a pointer (may or may not be lightweight)
    void_ptr_x              pointer(lua_State*, int);

    //! Returns user data as a pointer (may or may not be lightweight)
    void_ptr_x              pointer(lua_State*, global_k, const char*);

    //! Returns user data as a pointer (may or may not be lightweight)
    void_ptr_x              pointer(lua_State*, upvalue_k, int);
    


    //! Stack value as a string... 
    //! \note This will convert said value to a STRING
    string_view_x           string(lua_State*,  int);

    //! Global as a string... 
    string_x                string(lua_State*, global_k, const char*);

    //! Stack value as a string... 
    //! \note This will convert said value to a STRING
    string_view_x           string(lua_State*,  upvalue_k, int);

    any_x                   value(lua_State*, int);
    any_x                   value(lua_State*, upvalue_k, int);


    //! Returns LIGHTWEIGHT user data (only)
    void_ptr_x              voidptr(lua_State*, int);

    //! Returns LIGHTWEIGHT user data (only)
    void_ptr_x              voidptr(lua_State*, global_k, const char*);

    //! Returns LIGHTWEIGHT user data (only)
    void_ptr_x              voidptr(lua_State*, upvalue_k, int);
}
