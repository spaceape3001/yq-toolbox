////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/userexpr/impl/Instruction.hpp>

namespace yq::expr {
    class NullInstruction : public Instruction {
    public:
        NullInstruction(const string_t&s) : Instruction(s) 
        {
        }
        
        ~NullInstruction(){}
        
        std::error_code     execute(any_stack_t&, Context&) const override
        {
            return {};
        }

        result_t   result() const override 
        { 
            return {}; 
        }
    };
}
