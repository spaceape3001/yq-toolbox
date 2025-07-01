////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Object.hpp"
#include <yq/meta/ObjectMetaWriter.hpp>

namespace yq {
    const ObjectMeta&    Object::metaInfo() const 
    {
        return staticMetaInfo();
    }
    
    const ObjectMeta&    Object::staticMetaInfo()
    {
        static ObjectMeta   *s_info = new ObjectMeta("Object");
        return *s_info;
    }

    void Object::init_meta()
    {
        auto w = writer<Object>();
        w.description("Abstract object class (root of all objects)");
    }
}
