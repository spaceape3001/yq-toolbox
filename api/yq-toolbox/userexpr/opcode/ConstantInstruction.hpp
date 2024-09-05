////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/userexpr/impl/Instruction.hpp>

namespace yq::expr {
    class ConstantInstruction : public Instruction {
    public:
        ConstantInstruction(const string_t& s);
        ~ConstantInstruction(){}

        virtual std::error_code     execute(any_stack_t&values, Context&) const override;

        uint16_t    pop_count() const override { return 0; }
        uint16_t    push_count() const override { return 1; }
        
        virtual result_t    result() const override;
    };
}
