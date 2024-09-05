////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/userexpr/impl/Symbol.hpp>

namespace yq::expr {
    struct SymData : public Symbol {
        bool            has_value   = false;
		uint16_t        priority	= 0;
        uint16_t        argcnt      = 0;
        int             sstack      = 0;
        
        SymData() {}
        SymData(const Symbol& sym) : Symbol(sym) {}
    };
}
