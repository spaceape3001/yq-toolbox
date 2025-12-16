////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keyv/KV.hpp>
#include <filesystem>
#include <yq/file/SizeTimestamp.hpp>
#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/string_sets.hpp>
#include <yq/text/IgCase.hpp>

namespace yq {
    struct IgCase;
    
    /*! \brief Standard INI settings file (READER)
        
        This is a reader for INI setting files.  
        \note Lookups are case INSENSITIVE
        \note On name collisions, last one takes
    */
    class Settings {
    public:
    
        //! Constructs using a filepath to the INI file
        Settings(const std::filesystem::path&);
        ~Settings();
        
        //! Re-reads from file
        void                        sync();
        bool                        has(std::string_view key, std::string_view section={}) const;
        std::string_view            value(std::string_view key, std::string_view section={}) const;
        const string_view_set_t&    sections() const;
        const string_view_set_t&    keys(std::string_view section={}) const;
        
    private:
        struct Section;
        
        //! Note the empty string is the default....
        using section_map_t = std::map<std::string_view, Section, IgCase>;
        
        std::string             m_text;
        std::filesystem::path   m_filepath;
        section_map_t           m_sections;
        string_view_set_t       m_sectionKeys;
        SizeTimestamp           m_timestamp = {};
        
        const Section*          section(std::string_view) const;

        Settings(const Settings&) = delete;
        Settings(Settings&&) = delete;
        Settings& operator=(const Settings&) = delete;
        Settings& operator=(Settings&&) = delete;
    };
}


