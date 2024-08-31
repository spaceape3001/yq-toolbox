////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AssignInstruction.hpp"

#include <yq/basic/Stack.hpp>
#include <0/math/expr/Context.hpp>

namespace yq::expr {
    AssignInstruction::AssignInstruction(const string_t& s) : Instruction(s)
    {
    }
    
    std::error_code     AssignInstruction::execute(any_stack_t&values, Context& ctx) const
    {
        if(values.empty()){
            return errors::empty_stack();
        }
        
        ctx.variables[m_text]  = values.pop();
        return {};
    }

}
