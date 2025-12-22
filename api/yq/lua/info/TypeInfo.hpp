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
        
        /*
            Pushers push the value onto the stack, expect the caller to configure the 
            meta information (for tables).
            
            Divertors do *NOT* expect the caller to configure the meta information (ie, 
            it might be pushed on as a different meta type where the restriction makes
            sense).   (ie.... string views to strings)
        */
        
    
        virtual bool   is_type() const override { return true; }

        FNLuaPush       pusher() const { return m_pusher; }
        FNLuaExtract    extractor() const { return m_extractor; }
        FNLuaDivertor   divertor() const { return m_divertor; }
        
        const TypeMeta* attached() const { return m_attach; }
        
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
        FNLuaDivertor       m_divertor  = nullptr;
        const TypeMeta*     m_attach    = nullptr;
    };

}
