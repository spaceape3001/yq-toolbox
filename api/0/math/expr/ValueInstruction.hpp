////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Stack.hpp>
#include <0/basic/Any.hpp>
#include <0/math/expr/Instruction.hpp>

namespace yq::expr {
    class ValueInstruction : public Instruction {
    public:
        ValueInstruction(const string_t& s, Any&& value) : Instruction(s), m_value(std::move(value))
        {
        }
        
        ~ValueInstruction(){}
        
        std::error_code     execute(any_stack_t&values, Context&) const override
        {
            values << m_value;
            return {};
        }

        uint16_t            pop_count() const override { return 0; }
        uint16_t            push_count() const override { return 1; }

        result_t    result() const override 
        { 
            return &m_value.type(); 
        }

    private:
        Any m_value;
    };
}
