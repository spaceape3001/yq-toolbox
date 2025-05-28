////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Settings.hpp"
#include <yq/file/FileUtils.hpp>
#include <yq/text/chars.hpp>
#include <yq/text/transform.hpp>
#include <yq/text/split.hpp>
#include <yq/text/vsplit.hpp>

namespace yq {
    struct Settings::Section {
        string_view_map_t   values;
        string_view_set_t   keys;
    };
    
    Settings::Settings(const std::filesystem::path& fp) : m_filepath(fp)
    {
        sync();
    }
    
    Settings::~Settings()
    {
    }

    bool  Settings::has(std::string_view k, std::string_view sk) const
    {
        const Section *s  = section(sk);
        if(!s)
            return false;
        return s->keys.contains(k);
    }

    const string_view_set_t& Settings::keys(std::string_view sk) const
    {
        static const string_view_set_t s_empty;
        const Section *s  = section(sk);
        if(!s)
            return s_empty;
        return s->keys;
    }

    const Settings::Section* Settings::section(std::string_view k) const
    {
        auto i = m_sections.find(k);
        if(i != m_sections.end())
            return &i->second;
        return nullptr;
    }

    const string_view_set_t&    Settings::sections() const
    {
        return m_sectionKeys;
    }

    void        Settings::sync()
    {
        SizeTimestamp   info = file_size_and_timestamp(m_filepath);
        if(!info.exists)
            return ;
        if(info == m_timestamp)
            return ;
        
        m_text      = file_string(m_filepath);
        m_timestamp = info;
        
        //  And...rebuild
        m_sections.clear();
        std::string_view    sectionKey;
        
        vsplit(m_text, '\n', [&](std::string_view line){
            line    = trimmed(line);
            if(line.empty())
                return;
            if(line[0] == ';')  // comments
                return ;
                
            if(line[0] == '['){  // section header
                auto end = line.find_last_of(']');
                if(end == std::string_view::npos)   // rejecting
                    return ;
                sectionKey  = trimmed(line.substr(1, end-1));
                return ;
            }
            
            if(is_alpha(!line[0]))
                return ;
                
            auto end = line.find_first_of('=');
            if(end == std::string_view::npos)   // rejecting
                return ;
            
            std::string_view    key     = trimmed(line.substr(0, end));
            std::string_view    value   = trimmed(line.substr(end+1));
            
            m_sections[sectionKey].values[key]  = value;
        });
        
        for(auto& i : m_sections){
            if(!i.first.empty())
                m_sectionKeys.insert(i.first);
            for(auto& j : i.second.values)
                i.second.keys.insert(j.first);
        }
    }

    std::string_view            Settings::value(std::string_view k, std::string_view sk) const
    {
        const Section* s = section(sk);
        if(!s)
            return {};
        auto i = s->values.find(k);
        if(i == s->values.end())
            return {};
        return i->second;
    }
}


