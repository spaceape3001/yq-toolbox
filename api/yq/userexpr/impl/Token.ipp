////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Token.hpp"

#include <yq/core/Logging.hpp>
#include <yq/core/Enumeration.hpp>

namespace yq::expr {
    template <typename S> void stream_out(S&out, const Token& tok)
    {
        out << "{" << key_of(tok.category) << "/" << key_of(tok.kind) << ": " << tok.length << "}";
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
