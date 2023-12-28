////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/meta/CompoundInfo.hpp>

namespace yq {
    CompoundInfo::CompoundInfo(std::string_view zName, const std::source_location& sl, Meta* par, id_t i) : Meta(zName, par, sl, i)
    {
        set(Flag::COMPOUND);
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
            if(m && m->has(Flag::METHOD))
                res << static_cast<const MethodInfo*>(m);
        }
    }
    
    void        CompoundInfo::gather(LUC<PropertyInfo>& res)
    {
        res     = {};
        for(const Meta* m : children()){
            if(m && m->has(Flag::PROPERTY))
                res << static_cast<const PropertyInfo*>(m);
        }
    }

}
