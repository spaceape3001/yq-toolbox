////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Instruction.hpp"

namespace yq::expr {
    Instruction::Instruction(const string_t& _text) : m_text(_text)
    {
    }
    
    Instruction::~Instruction()
    {
    }

    Instruction::result_t    Instruction::result() const
    {
        return {};
    }
    
        
    Instruction::result_t    Instruction::result(std::span<const TypeMeta*>) const
    {
        return result();
    }
}
