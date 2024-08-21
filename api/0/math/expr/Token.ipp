////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Token.hpp"

#include <0/basic/Logging.hpp>

namespace yq::expr {
    template <typename S> void stream_out(S&out, const Token& tok)
    {
        out << "{" << key(tok.category) << "/" << key(tok.kind) << ": " << tok.length << "}";
    }

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream& out, const Token& tok)
    {
        stream_out(out, tok);
        return out;
    }

    std::ostream&    operator<<(std::ostream&out, const Token&tok)
    {
        stream_out(out, tok);
        return out;
    }
}
