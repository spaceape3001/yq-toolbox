////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "SStringMap.hpp"

namespace yq::spatial {
    SStringMap::SStringMap() = default;
    SStringMap::SStringMap(const SStringMap&) = default;
    SStringMap::~SStringMap() = default;

    bool                SStringMap::contains(const std::string& k) const
    {
        return m_data.contains(k);
    }

    void                SStringMap::erase(const std::string& k)
    {
        m_data.erase(k);
    }
    
    std::string_view    SStringMap::get(const std::string& k) const
    {
        auto i = m_data.find(k);
        if(i != m_data.end())
            return i->second;
        return {};
    }

    std::string_view    SStringMap::get(const std::initializer_list<std::string>& ks) const
    {
        for(auto& k : ks){
            auto i = m_data.find(k);
            if(i != m_data.end())
                return i->second;
        }
        return {};
    }

    std::string_view    SStringMap::get(const std::span<const std::string>& ks) const
    {
        for(auto& k : ks){
            auto i = m_data.find(k);
            if(i != m_data.end())
                return i->second;
        }
        return {};
    }
    
    string_set_t        SStringMap::keys() const
    {
        string_set_t    ret;
        for(auto& i : m_data)
            ret.insert(i.first);
        return ret;
    }
    
    void                SStringMap::set(const std::string& key, const std::string& value)
    {
        m_data[key]   = value;
    }

    void                SStringMap::set(const std::string& key, std::string&& value)
    {
        m_data[key]   = std::move(value);
    }
}
