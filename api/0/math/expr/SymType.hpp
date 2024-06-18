////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Enum.hpp>

namespace yq::expr {
    /*! \brief Symbol Type
    
        Used at various stages
    */
    YQ_ENUM(SymType,,
        //! Not a symbol
        None    = 0,
        
            //  THESE come off the base parser

        //! An error occured
        Error,

        //! White space
        Space,

        //! Operator
        Operator,
        
        //! Text (variable, constant, function, etc)
        Text,
        
        //! Hexadecimal constant
        Hex,
        
        //! Octal constant
        Octal,
        
        //! Integer constant
        Int,
        
        //! Floating point constant
        Float,
        
            // THESE are subsequently interpretted from the above
        
        //! Variable being referred to
        Variable,
        
        //! Constant being referred to
        Constant,
        
        //! Function to be called
        Function,
        
        //! Opening type of punctuation (like parenthesis, brackets, etc)
        Open,
        
        //! Closing type of punctuation (ie parenthesis, brackets, etc)
        Close
    );
}
