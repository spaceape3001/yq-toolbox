////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Enum.hpp>
#include <0/math/Operator.hpp>

namespace yq::expr {
    YQ_ENUM(InsCode,,
        //! No operation (no-op)
        None        = 0,
        
        YQ_OPERATORS,


        //! Assign top item in stack to key in instruction data
        Assign,
        //! Loads up constant
        Constant,

        //! Duplicates top item of stack
        Duplicate,        

        //! Invokes function
        Function,
        
        //! Loads up its value
        Value,
        
        //! Loads up the assigned variable
        Variable
    )
}
