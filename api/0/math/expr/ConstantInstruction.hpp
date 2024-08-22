////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Stack.hpp>
#include <0/math/expr/Instruction.hpp>
#include <0/math/expr/Repo.hpp>

namespace yq::expr {
    class ConstantInstruction : public Instruction {
    public:
        ConstantInstruction(const string_t& s) : Instruction(s)
        {
        }
        
        ~ConstantInstruction()
        {
        }

        virtual std::error_code     execute(any_stack_t&values, Context&) const override
        {
            static const Repo& _repo    = repo();
            auto x  = _repo.constant(m_text);
            if(!x)
                return x.error();
            values << *x;
            return {};
        }

        uint16_t    pop_count() const override { return 0; }
        uint16_t    push_count() const override { return 1; }
    };
}
