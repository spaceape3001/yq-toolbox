////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Object.hpp"
#include <yq/meta/ObjectInfoWriter.hpp>

namespace yq {
    const ObjectInfo&    Object::metaInfo() const 
    {
        return staticMetaInfo();
    }
    
    const ObjectInfo&    Object::staticMetaInfo()
    {
        static ObjectInfo   *s_info = new ObjectInfo("Object");
        return *s_info;
    }

    void Object::init_meta()
    {
        auto w = writer<Object>();
        w.description("Abstract object class (root of all objects)");
    }
}
