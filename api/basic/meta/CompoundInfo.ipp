////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <basic/meta/CompoundInfo.hpp>

namespace yq {
    CompoundInfo::CompoundInfo(std::string_view zName, const std::source_location& sl, Meta* par, id_t i) : Meta(zName, par, sl, i)
    {
        m_flags |= COMPOUND;
    }
    
    CompoundInfo::~CompoundInfo()
    {
    }

    void        CompoundInfo::sweep_impl() 
    {
        Meta::sweep_impl();
    }

    void        CompoundInfo::gather(LUC<MethodInfo>& res)
    {
        res     = {};
        for(const Meta* m : children()){
            if(m && (m->flags() & METHOD))
                res << static_cast<const MethodInfo*>(m);
        }
    }
    
    void        CompoundInfo::gather(LUC<PropertyInfo>& res)
    {
        res     = {};
        for(const Meta* m : children()){
            if(m && (m->flags() & PROPERTY))
                res << static_cast<const PropertyInfo*>(m);
        }
    }
}
