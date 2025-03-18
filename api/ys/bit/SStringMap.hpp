////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/string_sets.hpp>
#include <yq/text/IgCase.hpp>
#include <initializer_list>
#include <span>

namespace yq::spatial {
    class SStringMap {
    public:

        const string_map_t& data() const { return m_data; }
        void                set(const std::string& key, const std::string& value);
        void                set(const std::string& key, std::string&& value);
        void                erase(const std::string&);
        std::string_view    get(const std::string&) const;
        std::string_view    get(const std::initializer_list<std::string>&) const;
        std::string_view    get(const std::span<const std::string>&) const;
        string_set_t        keys() const;
        bool                contains(const std::string&) const;
    
        SStringMap();
        SStringMap(const SStringMap&);
        ~SStringMap();
        
    private:
        
        string_map_t        m_data;
        
        SStringMap(SStringMap&&) = delete;
        SStringMap& operator=(const SStringMap&) = delete;
        SStringMap& operator=(SStringMap&&) = delete;
    };
}
