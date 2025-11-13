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
    
        const std::string&  brief() const { return m_brief; }
        const std::string&  key() const { return m_key; }
        const std::string&  help() const { return m_help; }
    
        //! Sets the brief
        //! \note Provided pointer must *LIVE* throughout the program lifetime (ie, it's not copied)
        void            brief(const std::string&);
        
        //! Sets the text
        //! \note Provided pointer must *LIVE* throughout the program lifetime (ie, it's not copied)
        void            help(const std::string&);
        
        virtual bool    is_argument() const { return false; }
        virtual bool    is_function() const { return false; }
        
        //  true for the global module
        virtual bool    is_global() const { return false; }
        virtual bool    is_module() const { return false; }
        virtual bool    is_object() const { return false; }
        virtual bool    is_type() const { return false; }
        virtual bool    is_value() const { return false; }
    
        // Installs ourself, appropriately (Global/top level scope)
        virtual bool    install(InstallInfoAPI&) const { return false; }
    
        const Info*     parent() const { return m_parent; }
        
        //! Pushs the value/function onto the stack (ready for installation, wherever)
        virtual bool    push_it(InstallInfoAPI&) const { return false; }
    
    protected:
        friend class ModuleInfo;
        friend class Repo;
        
        Info(const std::string& k={});
        virtual ~Info();
    
    private:
        
        std::string m_key;
        std::string m_brief;
        std::string m_help;
        Info*       m_parent    = nullptr;
    };
}
