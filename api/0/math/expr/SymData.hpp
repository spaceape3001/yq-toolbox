////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/expr/Symbol.hpp>

namespace yq::expr {
    struct SymData : public Symbol {
        bool            has_value   = false;
		uint16_t        priority	= 0;
        uint16_t        argcnt      = 0;
        
        SymData() {}
        SymData(const Symbol& sym) : Symbol(sym) {}
    };
}
