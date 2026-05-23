////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq::expr {
    
    /*! \brief Symbol category
    */
    enum class SymCategory {
        None	= 0,
        Error,
        Operator,
        Space,
        Text,
        Value,
        Open,
        Close,
        Special
    };
}

