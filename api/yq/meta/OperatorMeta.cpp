////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OperatorMeta.hpp"
#include <yq/meta/TypeMeta.hpp>
#include <cassert>

namespace yq {
    OperatorMeta::OperatorMeta(Operator codeId, const std::source_location&sl, Meta*parentMeta) : 
        MethodMeta("(operator)", sl, parentMeta), m_code(codeId)
    {
        assert(parentMeta);
        set(Flag::OPERATOR);
        
        if(TypeMeta* type = to_type(parentMeta))
            type->m_operators << this;
    }
}
