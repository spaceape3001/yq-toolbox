////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ConstructorInfo.hpp"
#include <yq-toolbox/meta/TypeInfo.hpp>
#include <cassert>

namespace yq {
    ConstructorInfo::ConstructorInfo(const std::source_location&sl, Meta*parentMeta) : 
        MethodInfo("(constructor)", sl, parentMeta)
    {
        assert(parentMeta);
        set(Flag::CONSTRUCTOR);
        
        if(TypeInfo* type = to_type(parentMeta))
            type->m_constructors.push_back(this);
    }
}
