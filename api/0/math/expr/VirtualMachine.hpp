////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Stack.hpp>
#include <0/math/expr/Instruction.hpp>

namespace yq::expr {
    class VirtualMachine : public Instruction {
    public:
        std::vector<InstructionCPtr>    m_instructions;
        result_t                        m_result;
    
        VirtualMachine();

        std::error_code     execute(any_stack_t&values, Context&ctx) const override;
        
        result_t    result() const override ;
    };
}
