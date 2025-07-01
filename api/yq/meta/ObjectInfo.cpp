////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/meta/MetaRepo.hpp>
#include <yq/meta/ObjectInfo.hpp>
#include <yq/core/Logging.hpp>
#include <yq/core/Object.hpp>

namespace yq {
    const Vector<const ObjectInfo*>&   ObjectInfo::all()
    {
        return repo().objects.all;
    }

    const ObjectInfo*        ObjectInfo::find(std::string_view k)
    {
        return repo().objects.find(k);
    }

    const ObjectInfo*        ObjectInfo::find(id_t i)
    {
        const Meta* m   = repo().all.value(i, nullptr);
        return (m && m->is_object()) ? static_cast<const ObjectInfo*>(m) : nullptr;
    }

    ObjectInfo::ObjectInfo(std::string_view zName, const std::source_location& sl) : ObjectInfo(zName, nullptr, sl)
    {
    }
    
    ObjectInfo::ObjectInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl) :
        ObjectInfo(zName, &base, sl)
    {
    }

    ObjectInfo::ObjectInfo(std::string_view zName, ObjectInfo* myBase, const std::source_location& sl) : 
        CompoundMeta(zName, sl), m_base(myBase)
    {
        set(Flag::OBJECT);
        Repo& r    = repo();
        if(r.objects.lut.has(zName))
            yCritical() << "Duplicate object registration: " << zName;
        r.objects << this;
    }

    /* TODO
    Object* ObjectInfo::create(std::span<const Any>) const
    {
        return nullptr;
    }
    */

    const MetaLookup<ObjectInfo>&    ObjectInfo::bases(bool all) const
    {
        return def(all).bases;
    }

    const MetaLookup<ObjectInfo>&    ObjectInfo::deriveds(bool all) const
    {
        return def(all).derived;
    }
    

    int     ObjectInfo::hops_to_base(const ObjectInfo& presumedBase) const
    {
        if(this == &presumedBase)
            return 0;
        int cnt = 0;
        for(const ObjectInfo* b = m_base; b; b = b -> m_base){
            ++cnt;
            if(&presumedBase == b)
                return cnt;
        }
        return -1;
    }

    int     ObjectInfo::hops_to_derived(const ObjectInfo& presumedDerived) const
    {
        if(this == &presumedDerived)
            return 0;
        int cnt = 0;
        for(const ObjectInfo* b = presumedDerived.m_base; b; b = b -> m_base){
            ++cnt;
            if(b == this)
                return cnt;
        }
        return -1;
    }
    
    bool    ObjectInfo::is_base(const ObjectInfo&oi) const
    {
        for(const ObjectInfo* b = m_base; b; b = b -> m_base){
            if(&oi == b)
                return true;
        }
        return false;
    }
    
    bool    ObjectInfo::is_base_or_this(const ObjectInfo& oi) const
    {
        for(const ObjectInfo* b = this; b; b = b -> m_base){
            if(&oi == b)
                return true;
        }
        return false;
    }

    bool    ObjectInfo::is_derived(const ObjectInfo& oi) const
    {
        for(const ObjectInfo* b = oi.m_base; b; b = b -> m_base){
            if(b == this)
                return true;
        }
        return false;
    }

    bool    ObjectInfo::is_derived_or_this(const ObjectInfo& oi) const
    {
        for(const ObjectInfo* b = &oi; b; b = b -> m_base){
            if(b == this)
                return true;
        }
        return false;
    }

    bool    ObjectInfo::is_this(const ObjectInfo& presumedBase) const
    {
        return (this == &presumedBase) || is_base(presumedBase);
    }

    const MetaLookup<MethodInfo>&    ObjectInfo::methods(bool all) const
    {
        return def(all).methods;
    }

    const PropertyInfo*             ObjectInfo::property(std::string_view k) const
    {
        return m_all.properties.find(k);
    }
    
    const MetaLookup<PropertyInfo>&  ObjectInfo::properties(bool all) const
    {
        return def(all).properties;
    }
    
    size_t  ObjectInfo::size() const
    {
        return sizeof(Object);
    }

    void    ObjectInfo::sweep_impl() 
    {
        CompoundMeta::sweep_impl();
        
        m_all.clear();
        m_local.clear();
        
        gather(m_local.properties);
        gather(m_local.methods);
        
        m_all.methods     += m_local.methods;
        m_all.properties  += m_local.properties;

        if(m_base){
            for(auto& i : m_base->m_icons)
                m_icons.insert(i);
        
            m_local.bases << m_base;
            m_base -> sweep();
            m_base -> m_local.derived << this;

            for(ObjectInfo* b = m_base; b; b = b -> m_base){
                b->m_all.derived << this;
                m_all.bases << b;
            }
            
            m_all.methods += m_base -> m_all.methods;
            m_all.properties += m_base -> m_all.properties;
        }
    }


    const ObjectInfo* to_object(const Meta* m)
    {
        return (m && m->is_object()) ? static_cast<const ObjectInfo*>(m) : nullptr;
    }
    
    ObjectInfo* to_object(Meta* m)
    {
        return (m && m->is_object()) ? static_cast<ObjectInfo*>(m) : nullptr;
    }

}
