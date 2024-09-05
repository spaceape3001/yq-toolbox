////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OperatorInfo.hpp"
#include <yq-toolbox/meta/TypeInfo.hpp>
#include <cassert>

namespace yq {
    OperatorInfo::OperatorInfo(Operator codeId, const std::source_location&sl, Meta*parentMeta) : 
        MethodInfo("(operator)", sl, parentMeta), m_code(codeId)
    {
        assert(parentMeta);
        set(Flag::OPERATOR);
        
        if(TypeInfo* type = to_type(parentMeta))
            type->m_operators << this;
    }
}
