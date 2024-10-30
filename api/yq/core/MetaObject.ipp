////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "MetaObject.hpp"
#include <yq/core/DelayInit.hpp>

namespace yq {
    MetaObjectInfo::MetaObjectInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl) : 
        ObjectInfo(zName, base, sl)
    {
    }

    MetaObject::MetaObject()
    {
    }
    
    MetaObject::MetaObject(const MetaObject&) : MetaObject()
    {
    }

    MetaObject::~MetaObject()
    {
    }

    YQ_INVOKE(
        auto mo = writer<MetaObject>();
        mo.property("id",       &MetaObject::id).description("ID");
        mo.property("revision", &MetaObject::revision).description("Revision Number");
    )
}

YQ_OBJECT_IMPLEMENT(yq::MetaObject)

