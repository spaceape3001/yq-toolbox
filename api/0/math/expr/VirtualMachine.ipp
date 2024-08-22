////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "VirtualMachine.hpp"

namespace yq::expr {
    VirtualMachine::VirtualMachine() : Instruction({})
    {
    }

    std::error_code     VirtualMachine::execute(any_stack_t&values, Context&ctx) const 
    {
        for(auto& ins : m_instructions){
            if(!ins)
                continue;
            std::error_code ec = ins->execute(values, ctx);
            if(ec)
                return ec;
        }
        return {};
    }
    
    Instruction::result_t    VirtualMachine::result() const 
    { 
        return m_result; 
    }
}
