////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "VirtualMachine.hpp"
#include <0/math/expr/Instruction.hpp>

namespace yq::expr {
    VirtualMachine::VirtualMachine() 
    {
    }

    VirtualMachine::~VirtualMachine()
    {
    }

    std::error_code     VirtualMachine::execute(any_stack_t& values, Context& ctx) const 
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
}
