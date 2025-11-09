////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

struct lua_State;
namespace yq { class Stream; }

namespace yq::lua {
    struct WriteOptions {
        //! Writes out the full table (if there)
        bool        table   = false;
    };
    
    //! Writes the specified value to the stream
    void                write(Stream&, lua_State*, int, const WriteOptions& options={});

    void                write(Stream&, lua_State*, all_k, const WriteOptions& options={});
}
