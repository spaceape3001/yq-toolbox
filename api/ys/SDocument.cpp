////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "SDocument.hpp"
#include <ys/bit/ID.hpp>

namespace yq::spatial {
    SDocument::SDocument()
    {
        m_objects.push_back(nullptr);
    }
    
    SDocument::~SDocument()
    {
    }


    std::string_view        SDocument::attribute(const std::string&k) const
    {
        return m_attributes.get(k);
    }

    void                    SDocument::attribute_erase(const std::string&k)
    {
        m_attributes.erase(k);
    }
    
    string_set_t            SDocument::attribute_keys() const
    {
        return m_attributes.keys();
    }
    
    void                    SDocument::attribute_set(const std::string& k, const std::string& v)
    {
        m_attributes.set(k,v);
    }
    
    void                    SDocument::attribute_set(const std::string& k, std::string&&v)
    {
        m_attributes.set(k, std::move(v));
    }

    const string_map_t&     SDocument::attributes() const
    {
        return m_attributes.data();
    }

    void                    SDocument::bump()
    {
        ++m_revision;
    }

    ID  SDocument::insert(SObject* obj)
    {
        if(!obj)
            return {};
        ID  ret{ (ID::id_t) m_objects.size() };
        m_objects.push_back(obj);
        return ret;
    }

    bool                    SDocument::is_attribute(const std::string&k) const
    {
        return m_attributes.contains(k);
    }
    
    bool                    SDocument::is_variable(const std::string&k) const
    {
        return m_attributes.contains(k);
    }

    SObject*                SDocument::object(ID i)
    {
        if(i >= (ID::id_t) m_objects.size())
            return m_objects[i];
        return m_objects[i];
    }
    
    const SObject*          SDocument::object(ID i) const
    {
        if(i >= (ID::id_t) m_objects.size())
            return m_objects[i];
        return m_objects[i];
    }

    std::string_view        SDocument::variable(const std::string&k) const
    {
        return m_variables.get(k);
    }

    void                    SDocument::variable_erase(const std::string&k)
    {
        m_variables.erase(k);
    }
    
    string_set_t            SDocument::variable_keys() const
    {
        return m_variables.keys();
    }
    
    void                    SDocument::variable_set(const std::string&k, const std::string&v)
    {
        m_variables.set(k, v);
    }
    
    void                    SDocument::variable_set(const std::string&k, std::string&&v)
    {
        m_variables.set(k, std::move(v));
    }
    
    const string_map_t&     SDocument::variables() const
    {
        return m_variables.data();
    }

}
