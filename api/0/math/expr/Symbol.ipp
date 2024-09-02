////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Symbol.hpp"

#include <yq/basic/Logging.hpp>
#include <yq/text/ios32.hpp>
#include <ostream>

namespace yq::expr {
    template <typename S>   void stream_out(S& out, const Symbol& sym)
    {
        out << "{" << key(sym.category) << "/" << key(sym.kind) << ": " << sym.text << "}";
    }

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&out, const Symbol&sym)
    {
        stream_out(out, sym);
        return out;
    }
    
    std::ostream&    operator<<(std::ostream& out, const Symbol& sym)
    {
        stream_out(out, sym);
        return out;
    }

    template <typename S>   void stream_out(S& out, const SymVector& syms)
    {
        out << "[";
        bool    f   = true;
        for(const Symbol& s : syms){
            if(f){
                f   = false;
            } else
                out << ", ";
            out << s;
        }
        out << "]";
    }

    log4cpp::CategoryStream&    operator<<(log4cpp::CategoryStream&out, const SymVector&syms)
    {
        stream_out(out, syms);
        return out;
    }
    

    std::ostream&    operator<<(std::ostream&out, const SymVector&syms)
    {
        stream_out(out, syms);
        return out;
    }
}
