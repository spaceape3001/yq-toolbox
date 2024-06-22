////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/expr/preamble.hpp>
#include <0/math/expr/InsCode.hpp>
#include <0/basic/Any.hpp>

namespace yq::expr {
    struct Instruction {
        InsCode             code    = InsCode::None;
        std::u32string      key;
        void*               exec    = nullptr;
        Any                 data;
    };

    Expect<InsVector>   compile(const SymVector&);
    Expect<InsVector>   compile(std::string_view);
    Expect<InsVector>   compile(std::u32string_view);
    Expect<Any>         evaluate(const InsVector&, VarMap&);
    Expect<Any>         evaluate(const InsVector&);
}
