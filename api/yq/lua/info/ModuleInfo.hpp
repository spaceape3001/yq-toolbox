////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/info/Info.hpp>
#include <functional>

namespace yq::lua {
    
    enum class Phase : uint8_t {
        //  Yeah, could restructure slightly, mixing "module" with "meta table" here....
    
        General,    //!< General creation, so top item is the meta table
        Index,      //!< Method/Index table creation
        NewIndex,   //!< For New Index table creation 
        Call        //!< Method/Call table creation
    };
    class ModuleInfo : public Info {
    public:

        using FNAugment         = std::function<void(InstallInfoAPI&)>;
        using augment_pair_t    = std::pair<Phase,FNAugment>;
        using augment_vector_t  = std::vector<augment_pair_t>;
    
        //! What can get called during meta table creation
        const augment_vector_t& augments() const { return m_augments; }
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
        void                add(Phase, FNAugment&&);

        virtual bool        install(InstallInfoAPI&) const override;

        void                augment(InstallInfoAPI&, Phase) const;
        bool                augment(has_k, Phase) const;

        // not quite... need methods, properties, operators....
    protected:
        friend class Repo;
    
        ModuleInfo(const std::string&);
        virtual ~ModuleInfo();
    
        augment_vector_t    m_augments;
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
