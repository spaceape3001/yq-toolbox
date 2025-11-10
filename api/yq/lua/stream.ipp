////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/lualua.hpp>
#include <yq/lua/stream.hpp>

namespace yq::lua {
    Streamer::Streamer(lua_State* l)
    {
        m_error     = stream(l, ERROR);
        m_warning   = stream(l, WARNING);
        m_output    = stream(l, OUTPUT);
    }
}
