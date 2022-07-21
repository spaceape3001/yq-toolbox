////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/meta/PropSetter.hpp>
#include <basic/meta/PropertyInfo.hpp>
#include <cassert>

namespace yq {
    PropSetter::PropSetter(PropertyInfo* propInfo, const std::source_location& sl) : Meta("set", propInfo, sl) 
    {
        assert("no duplicate setters!" && !propInfo->m_setter);    //  duplicate property is an ERROR
        propInfo->m_setter     = this;
    }

    const PropertyInfo* PropSetter::property() const
    {
        return static_cast<const PropertyInfo*>(parent());
    }
}
