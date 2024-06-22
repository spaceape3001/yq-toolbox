////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Enum.hpp>
#include <0/basic/Flags.hpp>

namespace yq {
    YQ_ENUM(Operator, , 
        None   = 0,
        Add,
        //! Positive operator
        Affirm,
        And,
        Cross,
        Divide,
        Dot,
        Equal,
        Greater,
        GreaterEqual,
        Inner,
        Intersection,
        Less,
        LessEqual,
        Multiply,
        Negate,
        Not,
        NotEqual,
        Or,
        Outer,
        Power,
        Subtract,
        Union,
        Xor
    );
    using OperatorFlags = Flags<Operator>;
}
