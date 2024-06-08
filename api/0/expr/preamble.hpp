////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <set>
#include <string>

/*! \brief User defined expressions

    This is a mechanism to evaluate user submitted expressions (without LUA/python/etc).
    It's a low-speed design, sure others can soup it up (please do).
    
    Symbol is the text the user defined, minimal interpretation.
    
    OpCode is the execution.
*/
namespace yq::expr {

    struct Context;
    class Grammar;
    
    struct Execution;
    struct Expression;

    class OpCode;
    struct Symbol;
    
    using u32string_set_t   = std::set<std::u32string>;
    
    enum class SymType {
        //! Not a symbol
        None            = 0,
        
        //! Error occured
        Error,
        
        //! White space
        Space,
        
        //! Operator
        Operator,
        
        //! Text
        Text,
        
        //! Variable
        Variable,
        
        //! Function
        Function,
        
        //! Value
        Value,
        
        //! Open (ie push)
        Open,
        
        //! Close (ie pop)
        Close
    };
}
