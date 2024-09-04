////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/basic/Enum.hpp>

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
