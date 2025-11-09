////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/types.hpp>

namespace yq::lua {

    struct InstallInfoAPI {
        lua_State*      lvm     = nullptr;
        // up value resolve
    };

    class Info {
    public:
    
        const char*     brief() const { return m_brief; }
        const char*     key() const { return m_key; }
        const char*     help() const { return m_help; }
    
        //! Sets the brief
        //! \note Provided pointer must *LIVE* throughout the program lifetime (ie, it's not copied)
        void            brief(const char*);
        
        //! Sets the text
        //! \note Provided pointer must *LIVE* throughout the program lifetime (ie, it's not copied)
        void            help(const char*);
        
        virtual bool    is_argument() const { return false; }
        virtual bool    is_function() const { return false; }
        
        //  true for the global module
        virtual bool    is_global() const { return false; }
        virtual bool    is_module() const { return false; }
        virtual bool    is_object() const { return false; }
        virtual bool    is_type() const { return false; }
        virtual bool    is_value() const { return false; }
    
        // Installs ourself to the given table (using our key)
        virtual void    install(InstallInfoAPI&) const {}
    
        const Info*     parent() const { return m_parent; }
    
    protected:
        friend class ModuleInfo;
        friend class Repo;
        
        Info(const char*z=nullptr);
        virtual ~Info();
    
    private:
        
        const char* m_key       = nullptr;
        const char* m_brief     = nullptr;
        const char* m_help      = nullptr;
        Info*       m_parent    = nullptr;
    };
}
