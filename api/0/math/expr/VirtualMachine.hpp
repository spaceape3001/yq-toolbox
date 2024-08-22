////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/Ref.hpp>
#include <0/math/expr/preamble.hpp>

namespace yq::expr {
    class VirtualMachine : public RefCount {
    public:
        std::vector<InstructionCPtr>    m_instructions;
    
        VirtualMachine();
        ~VirtualMachine();

        std::error_code     execute(any_stack_t&values, Context&ctx) const;
    };
}
