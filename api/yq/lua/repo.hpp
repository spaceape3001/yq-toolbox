////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/lua/types.hpp>
#include <yq/meta/Meta.hpp>

namespace yq::lua {
    template <typename> class TypedTypeInfo;
    template <typename> class TypedObjectInfo;

    class Repo : public Meta {
    public:
    
        static Repo&    instance();
        
        const module_info_map_t&        modules() const { return m_modules; }
        const object_info_map_t&        objects() const { return m_objects; }
        const type_info_map_t&          types() const { return m_types; }
        const meta_module_map_t&        metas() const { return m_metas; }

        const ModuleInfo*               info(global_k) const;
        const ModuleInfo*               info(module_k, const std::string&) const;
        const ObjectInfo*               info(const ObjectMeta&) const;
        const TypeInfo*                 info(const TypeMeta&) const;
        const ModuleInfo*               info(meta_k, const Meta&) const;
        const ModuleInfo*               info(meta_k, uint32_t) const;
        
        std::pair<ModuleInfo*,bool>     edit(global_k);
        std::pair<ModuleInfo*,bool>     edit(module_k, const std::string&);
        std::pair<ObjectInfo*,bool>     edit(const ObjectMeta&);
        std::pair<TypeInfo*,bool>       edit(const TypeMeta&);
        std::pair<ModuleInfo*,bool>     edit(meta_k, const Meta&);
        std::pair<ModuleInfo*,bool>     edit(meta_k, uint32_t);

        template <typename T>
        std::pair<TypedTypeInfo<T>*,bool>       edit(type_k);
        template <typename T>
        std::pair<TypedObjectInfo<T>*,bool>     edit(object_k);

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
        meta_module_map_t   m_metas;
    };
}
