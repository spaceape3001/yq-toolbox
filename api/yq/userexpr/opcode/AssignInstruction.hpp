////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/userexpr/impl/Instruction.hpp>

namespace yq::expr {
    class AssignInstruction : public Instruction {
    public:
        AssignInstruction(const string_t& s);
        ~AssignInstruction(){}
        std::error_code     execute(any_stack_t&, Context&) const override;
        uint16_t            pop_count() const override { return 1; }
        uint16_t            push_count() const override { return 0; }
    };
}
