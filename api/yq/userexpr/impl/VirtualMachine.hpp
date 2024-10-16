////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Ref.hpp>
#include <yq/userexpr/forward.hpp>
#include <yq/typedef/any.hpp>

namespace yq::expr {
    class VirtualMachine : public RefCount {
    public:
        std::vector<InstructionCPtr>    m_instructions;
    
        VirtualMachine();
        ~VirtualMachine();

        std::error_code     execute(any_stack_t&values, Context&ctx) const;
    };
}
