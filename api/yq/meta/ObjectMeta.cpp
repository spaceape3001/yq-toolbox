////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/meta/MetaRepo.hpp>
#include <yq/meta/ObjectMeta.hpp>
#include <yq/core/Logging.hpp>
#include <yq/core/Object.hpp>

namespace yq {
    const Vector<const ObjectMeta*>&   ObjectMeta::all()
    {
        return repo().objects.all;
    }

    const ObjectMeta*        ObjectMeta::find(std::string_view k)
    {
        return repo().objects.find(k);
    }

    const ObjectMeta*        ObjectMeta::find(id_t i)
    {
        const Meta* m   = repo().all.value(i, nullptr);
        return (m && m->is_object()) ? static_cast<const ObjectMeta*>(m) : nullptr;
    }

    ObjectMeta::ObjectMeta(std::string_view zName, const std::source_location& sl) : ObjectMeta(zName, nullptr, sl)
    {
    }
    
    ObjectMeta::ObjectMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) :
        ObjectMeta(zName, &base, sl)
    {
    }

    ObjectMeta::ObjectMeta(std::string_view zName, ObjectMeta* myBase, const std::source_location& sl) : 
        CompoundMeta(zName, sl), m_base(myBase)
    {
        set(Flag::OBJECT);
        Repo& r    = repo();
        if(r.objects.lut.has(zName))
            yCritical() << "Duplicate object registration: " << zName;
        r.objects << this;
    }


    void            ObjectMeta::add_alias(std::string_view sz)
    {
        Meta::add_alias(sz);
        repo().objects.add_mapping(sz, this);
    }

    /* TODO
    Object* ObjectMeta::create(std::span<const Any>) const
    {
        return nullptr;
    }
    */

    const MetaLookup<ObjectMeta>&    ObjectMeta::bases(bool all) const
    {
        return def(all).bases;
    }

    const MetaLookup<ObjectMeta>&    ObjectMeta::deriveds(bool all) const
    {
        return def(all).derived;
    }
    

    int     ObjectMeta::hops_to_base(const ObjectMeta& presumedBase) const
    {
        if(this == &presumedBase)
            return 0;
        int cnt = 0;
        for(const ObjectMeta* b = m_base; b; b = b -> m_base){
            ++cnt;
            if(&presumedBase == b)
                return cnt;
        }
        return -1;
    }

    int     ObjectMeta::hops_to_derived(const ObjectMeta& presumedDerived) const
    {
        if(this == &presumedDerived)
            return 0;
        int cnt = 0;
        for(const ObjectMeta* b = presumedDerived.m_base; b; b = b -> m_base){
            ++cnt;
            if(b == this)
                return cnt;
        }
        return -1;
    }
    
    bool    ObjectMeta::is_base(const ObjectMeta&oi) const
    {
        for(const ObjectMeta* b = m_base; b; b = b -> m_base){
            if(&oi == b)
                return true;
        }
        return false;
    }
    
    bool    ObjectMeta::is_base_or_this(const ObjectMeta& oi) const
    {
        for(const ObjectMeta* b = this; b; b = b -> m_base){
            if(&oi == b)
                return true;
        }
        return false;
    }

    bool    ObjectMeta::is_derived(const ObjectMeta& oi) const
    {
        for(const ObjectMeta* b = oi.m_base; b; b = b -> m_base){
            if(b == this)
                return true;
        }
        return false;
    }

    bool    ObjectMeta::is_derived_or_this(const ObjectMeta& oi) const
    {
        for(const ObjectMeta* b = &oi; b; b = b -> m_base){
            if(b == this)
                return true;
        }
        return false;
    }

    bool    ObjectMeta::is_this(const ObjectMeta& presumedBase) const
    {
        return (this == &presumedBase) || is_base(presumedBase);
    }

    const MetaLookup<MethodMeta>&    ObjectMeta::methods(bool all) const
    {
        return def(all).methods;
    }

    const PropertyMeta*             ObjectMeta::property(std::string_view k) const
    {
        return m_all.properties.find(k);
    }
    
    const MetaLookup<PropertyMeta>&  ObjectMeta::properties(bool all) const
    {
        return def(all).properties;
    }
    
    size_t  ObjectMeta::size() const
    {
        return sizeof(Object);
    }

    void    ObjectMeta::sweep_impl() 
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

            for(ObjectMeta* b = m_base; b; b = b -> m_base){
                b->m_all.derived << this;
                m_all.bases << b;
            }
            
            m_all.methods += m_base -> m_all.methods;
            m_all.properties += m_base -> m_all.properties;
        }
    }


    const ObjectMeta* to_object(const Meta* m)
    {
        return (m && m->is_object()) ? static_cast<const ObjectMeta*>(m) : nullptr;
    }
    
    ObjectMeta* to_object(Meta* m)
    {
        return (m && m->is_object()) ? static_cast<ObjectMeta*>(m) : nullptr;
    }

}
