////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/meta/MethodInfo.hpp>
#include <basic/meta/Global.hpp>
#include <basic/meta/ObjectInfo.hpp>
#include <basic/meta/TypeInfo.hpp>

#include <basic/Logging.hpp>

namespace yq {
    MethodInfo::MethodInfo(std::string_view zName, const std::source_location& sl, Meta* parentMeta, options_t opts) : Meta(zName, parentMeta, sl)
    {
        assert(parentMeta);

        m_flags |= METHOD | opts;

        if(GlobalInfo* g = to_global(parentMeta)){
            assert(g == &meta<Global>());
            if(g->m_methods.keys.has(zName))
                yCritical() << "Duplicate method on GLOBAL: " << zName;
            g->m_methods << this;
        }
        
        if(ObjectInfo* obj = to_object(parentMeta)){
            if(obj->m_local.methods.keys.has(zName))
                yCritical() << "Duplicate method on object (" << obj -> name() << "): " << zName;
            obj->m_local.methods << this;
        }
        
        if(TypeInfo* type = to_type(parentMeta)){
            if(type -> m_methods.keys.has(zName))
                yCritical() << "Duplicate method on type (" << type -> name() << "): " << zName;
            type->m_methods << this;
        }
    }
}


