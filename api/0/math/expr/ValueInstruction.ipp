////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ValueInstruction.hpp"
#include <0/basic/Stack.hpp>
#include <0/basic/Any.hpp>

namespace yq::expr {
    ValueInstruction::ValueInstruction(const string_t& s, Any&& value) : 
        Instruction(s), m_value(std::move(value))
    {
    }
    
    std::error_code     ValueInstruction::execute(any_stack_t&values, Context&) const 
    {
        values << m_value;
        return {};
    }

    Instruction::result_t    ValueInstruction::result() const 
    { 
        return &m_value.type(); 
    }

}
