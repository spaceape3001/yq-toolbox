////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Any.hpp>
#include <0/basic/errors.hpp>
#include <0/basic/Stack.hpp>
#include <0/math/expr/Instruction.hpp>

namespace yq::expr {
    class PopInstruction : public Instruction {
    public:
        PopInstruction(const string_t&s) : Instruction(s) 
        {
        }
        
        ~PopInstruction(){}

        std::error_code     execute(any_stack_t& values, Context&) const override
        {
            if(values.empty())
                return errors::empty_stack();
            values.pop();
            return {};
        }

        result_t   result() const override 
        { 
            return -1; 
        }
    };
}
