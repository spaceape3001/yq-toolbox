////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/preamble.hpp>


#if 0

#include <0/math/expr/preamble.hpp>
#include <0/math/expr/InsCode.hpp>
#include <0/basic/Any.hpp>

namespace yq::expr {
    struct Instruction {
        InsCode             code        = InsCode::None;
        std::u32string      key;
        Any                 data;
        uint16_t            args        = 0;
        int8_t              priority    = 0;
    };

    Expect<InsVector>   compile(const SymVector&);
    Expect<InsVector>   compile(std::string_view);
    Expect<InsVector>   compile(std::u32string_view);
    Expect<Any>         evaluate(const InsVector&, VarMap&);
    Expect<Any>         evaluate(const InsVector&);
}

#endif
