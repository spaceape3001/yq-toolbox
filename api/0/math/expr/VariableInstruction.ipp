////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "VariableInstruction.hpp"
#include <yq/container/Stack.hpp>
#include <0/math/expr/Context.hpp>

namespace yq::expr {
    VariableInstruction::VariableInstruction(const string_t& s) : Instruction(s)
    {
    }
    
    std::error_code     VariableInstruction::execute(any_stack_t&values, Context&ctx) const
    {
        auto i = ctx.variables.find(m_text);
        if(i == ctx.variables.end())
            return errors::bad_variable();
        values << i->second;
        return {};
    }
}
