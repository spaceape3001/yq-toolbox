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
    
        const Info*         info(const char*) const;
        const ValueInfo*    info(value_k, const char*) const;
        const FunctionInfo* info(function_k, const char*) const;
        
        std::pair<FunctionInfo*,bool>   edit(function_k, const char*);
        std::pair<ValueInfo*,bool>      edit(value_k, const char*);
    
        virtual bool        is_module() const override { return true; }

        //! Adds an abstract function
        //! \note This is generic, means it'll be set by the VM
        FunctionInfo*       add(const char*, function_k);

        //! Adds an abstract value
        //! \note This is generic, means it'll be set by the VM
        ValueInfo*          add(const char*, value_k);

        //! Adds a function/method
        FunctionInfo*       add(const char*, FNLuaCallback);

        //! Adds a boolean value
        ValueInfo*          add(const char*, bool);

        //! Adds a double value
        ValueInfo*          add(const char*, double);

        //! Adds a integer value
        ValueInfo*          add(const char*, int);

        //! Adds a string value
        ValueInfo*          add(const char*, std::string_view);

        //! Adds an object
        ValueInfo*          add(const char*, const Object*);

        //! Adds an object
        ValueInfo*          add(const char*, Object*);

        //! Adds an raw pointer
        ValueInfo*          add(const char*, raw_k, void*);

    protected:
        friend class Repo;
    
        ModuleInfo(const char*);
        virtual ~ModuleInfo();
    
    private:
        info_map_t          m_components;
    };

    class GlobalModuleInfo : public ModuleInfo {
    public:
        GlobalModuleInfo();
        virtual ~GlobalModuleInfo();

        virtual bool    is_global() const { return true; }
    };

}
