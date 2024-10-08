////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/basic/Enum.hpp>
#include <yq-toolbox/math/Operator.hpp>

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
