////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "DuplicateInstruction.hpp"

#include <0/basic/errors.hpp>
#include <0/basic/Stack.hpp>

namespace yq::expr {
    DuplicateInstruction::DuplicateInstruction(const string_t s) : Instruction(s)
    {
    }
    
    std::error_code     DuplicateInstruction::execute(any_stack_t&values, Context&) const
    {
        if(values.empty()){
            return errors::empty_stack();
        }
        
        values << values.top();
        return {};
    }

    Instruction::result_t   DuplicateInstruction::result() const 
    { 
        return errors::insufficient_information(); 
    }

    Instruction::result_t    DuplicateInstruction::result(std::span<const TypeInfo*>types) const
    {
        if(types.size() != 1){
            if(types.size()){
                return errors::too_many_arguments();
            } else {
                return errors::insufficient_arguments();
            }
        }
        
        if(!types[0])
            return errors::null_pointer();
        return types[0];
    }
}
