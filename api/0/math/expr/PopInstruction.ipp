////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "PopInstruction.hpp"
#include <0/basic/Any.hpp>
#include <yq/basic/errors.hpp>
#include <yq/basic/Stack.hpp>

namespace yq::expr {
    PopInstruction::PopInstruction(const string_t&s) : Instruction(s) 
    {
    }
        
    std::error_code     PopInstruction::execute(any_stack_t& values, Context&) const 
    {
        if(values.empty())
            return errors::empty_stack();
        values.pop();
        return {};
    }
}
