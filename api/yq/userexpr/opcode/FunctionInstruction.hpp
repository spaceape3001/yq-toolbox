////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/userexpr/forward.hpp>
#include <yq/userexpr/impl/Instruction.hpp>

namespace yq::expr {
    class FunctionInstruction : public Instruction {
    public:
        const std::string       m_text8;
        const uint16_t          m_argcnt;
        const TypeMeta* const   m_type;
        
        FunctionInstruction(const SymData& sd);
        std::error_code     execute(any_stack_t&values, Context&) const override;

        uint16_t            pop_count() const override { return m_argcnt; }
        uint16_t            push_count() const override { return 1; }
    };
}
