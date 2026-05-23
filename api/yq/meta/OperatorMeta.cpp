////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "OperatorMeta.hpp"
#include <yq/meta/TypeMeta.hpp>
#include <cassert>

#include <yq/core/Enumeration.hxx>

YQ_ENUM_IMPLEMENT(yq::Operator)
YQ_ENUM_IMPLEMENT(yq::OperatorType)

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
