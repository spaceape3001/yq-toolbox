////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/info/Info.hpp>

namespace yq::lua {
    class ValueInfo : public Info {
    public:
    
        const type_t&   type() const { return m_type; }
        const value_t&  value() const { return m_value; }
        
        virtual bool    is_value() const override { return true; }
        virtual bool    is_global() const override;
        void            type(const type_t&);
        virtual void    install(InstallInfoAPI&) const;

    protected:
        friend class ModuleInfo;
        friend class FunctionInfo;
        friend class Repo;
        
        ValueInfo(const char*);
        virtual ~ValueInfo();
        
    private:
        bool    push_it(InstallInfoAPI&) const;
    
        type_t      m_type;
        value_t     m_value;
    };
}
