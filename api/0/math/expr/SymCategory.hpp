////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Enum.hpp>

namespace yq::expr {
    
    /*! \brief Symbol category
    */
    YQ_ENUM(SymCategory,,
        None	= 0,
        Error,
        Operator,
        Space,
        Text,
        Value,
        Open,
        Close,
        Special
    );
}

