////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Enum.hpp>
#include <yq/math/Operator.hpp>

namespace yq::expr {
    YQ_ENUM(SymKind,, 
        None		= 0,
        
            // OPERATORS (at front to match the operators enumeration)
        YQ_OPERATORS,

            // VALUES
        Integer,
        Octal,
        Hexadecimal,
        Float,

            // TEXTS
        Variable,
        Function,
        Constant,
        Constructor,
        
            // SPECIALS
        Assign,
        Duplicate,
        Comma,
        
            // OPEN/CLOSE
        Generic,
        Array,
        Tuple,
        Guard
    );

}
