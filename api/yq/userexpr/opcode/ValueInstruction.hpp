////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/basic/Any.hpp>
#include <yq/userexpr/impl/Instruction.hpp>

namespace yq::expr {
    class ValueInstruction : public Instruction {
    public:
        ValueInstruction(const string_t& s, Any&& value);
        
        ~ValueInstruction(){}
        
        std::error_code     execute(any_stack_t&values, Context&) const override;

        uint16_t    pop_count() const override { return 0; }
        uint16_t    push_count() const override { return 1; }

        result_t    result() const override;

    private:
        Any m_value;
    };
}
