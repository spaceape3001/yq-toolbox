////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/expr/Instruction.hpp>

namespace yq::expr {
    class VariableInstruction : public Instruction {
    public:
        VariableInstruction(const string_t& s);
        
        ~VariableInstruction(){}

        std::error_code     execute(any_stack_t&values, Context&ctx) const override;
        uint16_t    pop_count() const override { return 0; }
        uint16_t    push_count() const override { return 1; }
    };
}
