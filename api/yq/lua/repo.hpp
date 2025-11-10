////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/types.hpp>
#include <yq/meta/Meta.hpp>

namespace yq::lua {
    class Repo : public Meta {
    public:
    
        static Repo&    instance();
        
        const module_info_map_t& modules() const { return m_modules; }
        const object_info_map_t& objects() const { return m_objects; }
        const type_info_map_t& types() const { return m_types; }

        const ModuleInfo*   info(global_k) const;
        const ModuleInfo*   info(module_k, const std::string&) const;
        const ObjectInfo*   info(const ObjectMeta&) const;
        const TypeInfo*     info(const TypeMeta&) const;
        
        std::pair<ModuleInfo*,bool>         edit(global_k);
        std::pair<ModuleInfo*,bool>         edit(module_k, const std::string&);
        std::pair<ObjectInfo*,bool>         edit(const ObjectMeta&);
        std::pair<TypeInfo*,bool>           edit(const TypeMeta&);

    private:
        Repo(const std::source_location& sl = std::source_location::current());
        ~Repo();
        
        Repo(const Repo&) = delete;
        Repo(Repo&&) = delete;
        Repo& operator=(const Repo&) = delete;
        Repo& operator=(Repo&&) = delete;
      
        ModuleInfo*         m_global  = nullptr;
        module_info_map_t   m_modules;
        object_info_map_t   m_objects;
        type_info_map_t     m_types;
    };
}
