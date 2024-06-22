////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Enum.hpp>

namespace yq::expr {
    YQ_ENUM(InsCode,,
        //! No operation (no-op)
        None        = 0,
        
        //! Assign top item in stack to key in instruction data
        Assign,
        //! Loads up constant
        Constant,

        //! Duplicates top item of stack
        Duplicate,        
        
        //! Loads up its value
        Value,
        
        //! Loads up the assigned variable
        Variable,
        
        Operator,
        
        Function
    )
}
