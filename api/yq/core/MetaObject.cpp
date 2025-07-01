////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "MetaObject.hpp"
#include <yq/meta/MetaObjectMetaWriter.hpp>

namespace yq {
    MetaObjectMeta::MetaObjectMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) : 
        ObjectMeta(zName, base, sl)
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

    void MetaObject::init_meta()
    {
        auto mo = writer<MetaObject>();
        mo.property("id",       &MetaObject::id).description("ID");
        mo.property("revision", &MetaObject::revision).description("Revision Number");
    }
}

YQ_OBJECT_IMPLEMENT(yq::MetaObject)

