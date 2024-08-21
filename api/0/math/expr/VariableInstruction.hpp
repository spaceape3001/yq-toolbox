////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Stack.hpp>
#include <0/math/expr/Context.hpp>
#include <0/math/expr/Instruction.hpp>

namespace yq::expr {
    class VariableInstruction : public Instruction {
    public:
        VariableInstruction(const string_t& s) : Instruction(s)
        {
        }
        
        ~VariableInstruction(){}

        std::error_code     execute(any_stack_t&values, Context&ctx) const override
        {
            auto i = ctx.variables.find(m_text);
            if(i == ctx.variables.end())
                return errors::bad_variable();
            values << i->second;
            return {};
        }
    };
}
