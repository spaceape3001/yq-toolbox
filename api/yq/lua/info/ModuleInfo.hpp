////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/info/Info.hpp>

namespace yq::lua {
    class ModuleInfo : public Info {
    public:
    
        const info_map_t&   components() const { return m_components; }
    
        const Info*         info(const std::string&) const;
        const ValueInfo*    info(value_k, const std::string&) const;
        const FunctionInfo* info(function_k, const std::string&) const;
        
        std::pair<FunctionInfo*,bool>   edit(function_k, const std::string&);
        std::pair<ValueInfo*,bool>      edit(value_k, const std::string&);
    
        virtual bool        is_module() const override { return true; }

        //! Adds an abstract function
        //! \note This is generic, means it'll be set by the VM
        FunctionInfo*       add(const std::string&, function_k);

        //! Adds an abstract value
        //! \note This is generic, means it'll be set by the VM
        ValueInfo*          add(const std::string&, value_k);

        //! Adds a function/method
        FunctionInfo*       add(const std::string&, FNLuaCallback);

        //! Adds a boolean value
        ValueInfo*          add(const std::string&, bool);

        //! Adds a double value
        ValueInfo*          add(const std::string&, double);

        //! Adds a integer value
        ValueInfo*          add(const std::string&, int);

        //! Adds a string value
        ValueInfo*          add(const std::string&, std::string_view);

        //! Adds an object
        ValueInfo*          add(const std::string&, const Object*);

        //! Adds an object
        ValueInfo*          add(const std::string&, Object*);

        //! Adds an raw pointer
        ValueInfo*          add(const std::string&, raw_k, void*);

        virtual bool        install(InstallInfoAPI&) const override;

    protected:
        friend class Repo;
    
        ModuleInfo(const std::string&);
        virtual ~ModuleInfo();
    
        info_map_t          m_components;
    };

    class GlobalModuleInfo : public ModuleInfo {
    public:
        GlobalModuleInfo();
        virtual ~GlobalModuleInfo();

        virtual bool    is_global() const { return true; }

        virtual bool    install(InstallInfoAPI&) const override;
    };

}
