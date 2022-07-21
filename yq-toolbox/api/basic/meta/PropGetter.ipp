////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/meta/PropGetter.hpp>
#include <basic/meta/PropertyInfo.hpp>
#include <cassert>

namespace yq {
    PropGetter::PropGetter(PropertyInfo* propInfo, const std::source_location& sl) : Meta("get", propInfo, sl) 
    {
        assert("no duplicate getters!" && !propInfo->m_getter);    //  duplicate property is an ERROR
        propInfo->m_getter     = this;
    }

    const PropertyInfo* PropGetter::property() const
    {
        return static_cast<const PropertyInfo*>(parent());
    }
}
