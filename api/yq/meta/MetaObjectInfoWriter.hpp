////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/MetaObject.hpp>
#include <yq/meta/ObjectInfoWriter.hpp>

namespace yq {

    /*! \brief Writer of meta object's meta
    
        This is using during initialization by the methods writing to meta, presenting a writable
        API to modify/set the meta properties, methods, etc.
    */
    template <typename C>
    class MetaObjectInfo::Writer : public ObjectInfo::Writer<C> {
    public:
        Writer(MetaObjectInfo* metaObjInfo) : ObjectInfo::Writer<C>(metaObjInfo)
        {
        }
        
        Writer(MetaObjectInfo& metaObjInfo) : Writer(&metaObjInfo)
        {
        }
    };
}
