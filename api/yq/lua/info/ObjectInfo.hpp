////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/info/ModuleInfo.hpp>

namespace yq::lua {
    class ObjectInfo : public ModuleInfo {
    public:
    
        const ObjectMeta&   meta() const { return m_meta; }
        virtual bool        is_object() const override { return true; }

    protected:
        friend class Repo;

        ObjectInfo(const ObjectMeta&);
        virtual ~ObjectInfo();
        
        //  printer goes in here....
    
    private:
        const ObjectMeta&   m_meta;
    };

}
