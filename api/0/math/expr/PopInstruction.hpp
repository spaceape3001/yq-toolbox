////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/math/expr/Instruction.hpp>

namespace yq::expr {
    class PopInstruction : public Instruction {
    public:
        PopInstruction(const string_t&s);
        
        ~PopInstruction(){}

        std::error_code     execute(any_stack_t& values, Context&) const override;

        uint16_t            pop_count() const override { return 1; }
        uint16_t            push_count() const override { return 0; }
    };
}
