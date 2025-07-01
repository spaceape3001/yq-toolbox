////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ConstructorMeta.hpp"
#include <yq/meta/TypeMeta.hpp>
#include <cassert>

namespace yq {
    ConstructorMeta::ConstructorMeta(const std::source_location&sl, Meta*parentMeta) : 
        MethodMeta("(constructor)", sl, parentMeta)
    {
        assert(parentMeta);
        set(Flag::CONSTRUCTOR);
        
        if(TypeMeta* type = to_type(parentMeta))
            type->m_constructors.push_back(this);
    }
}
