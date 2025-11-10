////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/stream/StdOutput.hpp>
#include <yq/stream/StdError.hpp>

struct lua_State;

namespace yq {
    class Stream;
}

namespace yq::lua {
    class Streamer {
    public:
    
        Streamer(lua_State*);
    
        bool    operator()(error_k) const { return static_cast<bool>(m_error); }
        bool    operator()(warning_k) const { return static_cast<bool>(m_warning); }
        bool    operator()(output_k) const { return static_cast<bool>(m_output); }
        
        bool        can_error() const { return static_cast<bool>(m_error); }
        bool        can_warning() const { return static_cast<bool>(m_warning); }
        bool        can_output() const { return static_cast<bool>(m_output); }
        
        Stream&     error() const { return *m_error; }
        Stream&     warning() const { return *m_warning; }
        Stream&     output() const { return *m_output; }
        operator Stream& () const { return *m_output; }
        
    private:
        Stream*     m_error     = nullptr;
        Stream*     m_output    = nullptr;
        Stream*     m_warning   = nullptr;
        
        stream::StdError    m_stderr;
        stream::StdOutput   m_stdout;
    };
}
