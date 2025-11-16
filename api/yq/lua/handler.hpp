////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

struct lua_State;

namespace yq::lua {

    //////////////////////////////////////////////////////////////////////////////
    //  Lua Handlers (can use these....)
    //
    //  NOTE: Upvalue parameters (ie pointers) are expected to remain VALID throughout
    //  the usage of the specific Lua VM.  
    
    //! Deletes the items in the stack
    int lh_gc_object(lua_State*);

    int lh_gc_type(lua_State*);
    
    //! Writes to the specified stream
    //! \tparam stream Pointer to stream
    //! \param vaargs things to write
    int lh_write_stream(lua_State*);  
    
    int lh_write_cerr(lua_State*);
    int lh_write_cout(lua_State*);
}
