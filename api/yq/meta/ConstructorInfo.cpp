////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ConstructorInfo.hpp"
#include <yq/meta/TypeMeta.hpp>
#include <cassert>

namespace yq {
    ConstructorInfo::ConstructorInfo(const std::source_location&sl, Meta*parentMeta) : 
        MethodInfo("(constructor)", sl, parentMeta)
    {
        assert(parentMeta);
        set(Flag::CONSTRUCTOR);
        
        if(TypeMeta* type = to_type(parentMeta))
            type->m_constructors.push_back(this);
    }
}
