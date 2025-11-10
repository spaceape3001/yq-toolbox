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
        m_output        = yq::lua::stream(l, OUTPUT);
        if(!m_output){
luaInfo << "Output stream not found, defaulting to standard output";        
        
            m_output    = &m_stdout;
        }

        m_error         = yq::lua::stream(l, ERROR);
        if(!m_error){
luaInfo << "Error stream not found, defaulting to standard output";        
            m_error     = &m_stderr;
        }
            
        m_warning       = yq::lua::stream(l, WARNING);
        if(!m_warning){
luaInfo << "Warning stream not found, defaulting to selected output";        
            m_warning   = m_output;
        }
    }
}
