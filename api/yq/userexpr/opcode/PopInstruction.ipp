////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PopInstruction.hpp"
#include <yq-toolbox/basic/Any.hpp>
#include <yq-toolbox/errors.hpp>
#include <yq-toolbox/container/Stack.hpp>

namespace yq::expr {
    PopInstruction::PopInstruction(const string_t&s) : Instruction(s) 
    {
    }
        
    std::error_code     PopInstruction::execute(any_stack_t& values, Context&) const 
    {
        if(values.empty())
            return errors::empty_stack();
        values.pop();
        return {};
    }
}
