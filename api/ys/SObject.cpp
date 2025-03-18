////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "SObject.hpp"
#include "SObjectInfoWriter.hpp"

#include <ys/SDocument.hpp>

namespace yq::spatial {
    struct SObject::Repo {
        MetaLookup<SObjectInfo>     objects;
    };

////////////////////////////////////////////////////////////////////////////////

    SObjectInfo::SObjectInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl) :
        ObjectInfo(zName, base, sl)
    {
        SObject::repo().objects << this;
    }

    bool    SObjectInfo::is_0d() const
    {
        return has(Flag::D0);
    }
    
    bool    SObjectInfo::is_1d() const
    {
        return has(Flag::D1);
    }
    
    bool    SObjectInfo::is_2d() const
    {
        return has(Flag::D2);
    }
    
    bool    SObjectInfo::is_3d() const
    {
        return has(Flag::D3);
    }
    
    bool    SObjectInfo::is_4d() const
    {
        return has(Flag::D4);
    }
    
    bool    SObjectInfo::is_5d() const
    {
        return has(Flag::D5);
    }
    
    bool    SObjectInfo::is_6d() const
    {
        return has(Flag::D6);
    }
    
    
////////////////////////////////////////////////////////////////////////////////

    SObject::Repo& SObject::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

    void SObject::init_info()
    {
        auto w = writer<SObject>();
        w.description("Spatial Object");
        w.property("description", &SObject::description).setter(&SObject::set_description);
        w.property("uid", &SObject::uid).setter(&SObject::set_uid);
        w.property("notes", &SObject::notes).setter(&SObject::set_notes);
        w.property("title", &SObject::title).setter(&SObject::set_title);
        w.property("id", &SObject::get_id);
        w.property("revision", &SObject::get_revision);
    }

    SObject::SObject(SDocument& doc) : m_doc(doc), m_id(doc.insert(this))
    {
    }
    
    SObject::SObject(SDocument& doc, const SObject& cp) : 
        m_doc(doc), m_id(doc.insert(this)), m_attributes(cp.m_attributes)
    {
        m_parent    = cp.m_parent;
        m_children  = cp.m_children;
        m_title     = cp.m_title;
        m_notes     = cp.m_notes;
    }
    
    SObject::~SObject()
    {
        m_children.clear();
        m_parent    = {};
    }

    std::string_view        SObject::attribute(const std::string& k) const
    {
        return m_attributes.get(k);
    }

    std::string_view        SObject::attribute(const std::string& k, all_k) const
    {
        auto& map   = m_attributes.data();
        auto i = map.find(k);
        if(i != map.end())
            return i->second;
        
        if(const SObject*p = m_doc.object(m_parent)){
            return p->attribute(k);
        } else {
            return m_doc.attribute(k);
        }
    }
    
    void                    SObject::attribute_erase(const std::string& k)
    {
        m_attributes.erase(k);
    }
    
    string_set_t            SObject::attribute_keys() const
    {
        return m_attributes.keys();
    }
    
    void                    SObject::attribute_set(const std::string&k, const std::string&v)
    {
        m_attributes.set(k, v);
    }
    
    void                    SObject::attribute_set(const std::string&k, std::string&&v)
    {
        m_attributes.set(k, std::move(v));
    }
    
    const string_map_t&     SObject::attributes() const
    {
        return m_attributes.data();
    }
    
    void    SObject::bump()
    {
        ++m_revision.local;
        ++m_revision.all;
        
        for(ID i = m_parent; i;){
            SObject*p   = m_doc.object(i);
            if(!p)
                break;
            ++(p->m_revision.all);
            i   = p->m_parent;
        }
        
        m_doc.bump();
    }

    SObject*    SObject::create(child_k, const SObjectInfo& sinfo)
    {
        SObject* obj = sinfo.create(m_doc);
        if(!obj)
            return nullptr;
        
        obj->m_parent   = id();
        m_children.push_back(obj->id());
        bump();
        return obj;
    }
    
    bool                SObject::is_attribute(const std::string& k) const
    {
        return m_attributes.contains(k);
    }

    const SObject*      SObject::parent(pointer_k) const
    {
        return m_doc.object(m_parent);
    }
    
    SObject*            SObject::parent(pointer_k)
    {
        return m_doc.object(m_parent);
    }

    void     SObject::remap(const Remapper& theMap)
    {
        m_parent    = theMap(m_parent);
        
        for(ID& i : m_children){
            i   = theMap(i);
            SObject*    dob = m_doc.object(i);
            if(dob)
                dob -> remap(theMap);
        }
    }

    void    SObject::set_description(const std::string&v)
    {
        m_description   = v;
        bump();
    }
    
    void    SObject::set_notes(const std::string&v)
    {
        m_notes     = v;
        bump();
    }
    
    void    SObject::set_uid(const std::string&v)
    {
        m_uid       = v;
        bump();
    }
    
    void    SObject::set_title(const std::string&v)
    {
        m_title     = v;
        bump();
    }


    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    
    ID Remapper::operator()(ID i) const
    {
        auto j = data.find(i.id);
        if(j != data.end())
            return { j->second };
        return i;
    }
}

YQ_OBJECT_IMPLEMENT(yq::spatial::SObject)
