////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PropSetter.hpp"
#include <yq/meta/PropertyMeta.hpp>
#include <cassert>

namespace yq {
    PropSetter::PropSetter(PropertyMeta* propInfo, const std::source_location& sl) : Meta("set", propInfo, sl) 
    {
        assert(propInfo);
        assert("no duplicate setters!" && !propInfo->m_setter);    //  duplicate property is an ERROR
        propInfo->m_setter     = this;
    }

    const PropertyMeta* PropSetter::property() const
    {
        return static_cast<const PropertyMeta*>(parent());
    }
}
