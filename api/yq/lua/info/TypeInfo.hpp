////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/info/ModuleInfo.hpp>

namespace yq::lua {
    class TypeInfo : public ModuleInfo {
    public:
    
        virtual bool   is_type() const override { return true; }

        FNLuaPush       pusher() const { return m_pusher; }
        FNLuaExtract    extractor() const { return m_extractor; }
    
    protected:
        friend class Repo;

        TypeInfo(const TypeMeta&);
        virtual ~TypeInfo();
    
        // printer helpers go in here
    
    private:
        const TypeMeta&     m_meta;
    protected:
        FNLuaPush           m_pusher    = nullptr;
        FNLuaExtract        m_extractor = nullptr;
    };

}
