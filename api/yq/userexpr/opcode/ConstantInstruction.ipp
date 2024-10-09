////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ConstantInstruction.hpp"
#include <yq-toolbox/container/Stack.hpp>
#include <yq/userexpr/impl/Repo.hpp>

namespace yq::expr {
    ConstantInstruction::ConstantInstruction(const string_t& s) : Instruction(s)
    {
    }
    

    std::error_code     ConstantInstruction::execute(any_stack_t&values, Context&) const
    {
        static const Repo& _repo    = repo();
        auto x  = _repo.constant(m_text);
        if(!x)
            return x.error();
        values << *x;
        return {};
    }
    
    Instruction::result_t    ConstantInstruction::result() const
    {
        static const Repo& _repo    = repo();
        const TypeInfo* type = _repo.constant_type(m_text);
        if(type)
            return type;
        return {};
    }
}
