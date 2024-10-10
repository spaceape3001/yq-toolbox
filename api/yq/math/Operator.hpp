////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/basic/Enum.hpp>
#include <yq-toolbox/basic/Flags.hpp>

namespace yq {

    #define YQ_OPERATORS    \
        Add,                \
        Affirm,             \
        And,                \
        Cross,              \
        CubeRoot,           \
        Divide,             \
        Dot,                \
        Equal,              \
        FourthRoot,         \
        Greater,            \
        GreaterEqual,       \
        Inner,              \
        Intersection,       \
        Less,               \
        LessEqual,          \
        Multiply,           \
        Negate,             \
        Not,                \
        NotEqual,           \
        Or,                 \
        Outer,              \
        Power,              \
        SquareRoot,         \
        Subtract,           \
        TensorProduct,      \
        Union,              \
        Xor

    YQ_ENUM(Operator, , 
        None   = 0,
        YQ_OPERATORS
    );
    using OperatorFlags = Flags<Operator>;
    
    YQ_ENUM(OperatorType, ,
        None    = 0,
        //! Setter
        Set,
        //! Unary with operator on left side
        Left,
        //! Unary with operator on right side
        Right,
        //! Standard binary (a+b)
        Binary,
        //! First Trinary operator (a?b:c)
        Trinary1,
        //! Second Trinary operator (a?b:c)
        Trinary2,
        //! Comma
        Comma,
        //! Open-mark
        Open,
        //! Close-mark
        Close
    );
}
