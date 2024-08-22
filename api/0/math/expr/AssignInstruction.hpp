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
    class AssignInstruction : public Instruction {
    public:
        AssignInstruction(const string_t& s) : Instruction(s)
        {
        }
        
        ~AssignInstruction(){}
        
        std::error_code     execute(any_stack_t&values, Context& ctx) const override
        {
            if(values.empty()){
                return errors::empty_stack();
            }
            
            ctx.variables[m_text]  = values.pop();
            return {};
        }

        uint16_t            pop_count() const override { return 1; }
        uint16_t            push_count() const override { return 0; }

        result_t    result() const override
        {
            return -1;
        }
    };
}
