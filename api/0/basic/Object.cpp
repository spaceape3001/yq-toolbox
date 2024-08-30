////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Object.hpp"

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
}
