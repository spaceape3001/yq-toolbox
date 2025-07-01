////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/MetaObject.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>

namespace yq {

    /*! \brief Writer of meta object's meta
    
        This is using during initialization by the methods writing to meta, presenting a writable
        API to modify/set the meta properties, methods, etc.
    */
    template <typename C>
    class MetaObjectMeta::Writer : public ObjectMeta::Writer<C> {
    public:
        Writer(MetaObjectMeta* metaObjInfo) : ObjectMeta::Writer<C>(metaObjInfo)
        {
        }
        
        Writer(MetaObjectMeta& metaObjInfo) : Writer(&metaObjInfo)
        {
        }
    };
}
