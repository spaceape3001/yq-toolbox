////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AssignInstruction.hpp"

#include <yq-toolbox/container/Stack.hpp>
#include <yq-toolbox/userexpr/Context.hpp>

namespace yq::expr {
    AssignInstruction::AssignInstruction(const string_t& s) : Instruction(s)
    {
    }
    
    std::error_code     AssignInstruction::execute(any_stack_t&values, Context& ctx) const
    {
        if(values.empty()){
            return errors::empty_stack();
        }
        
        ctx.variables[m_text]  = values.pop();
        return {};
    }

}
