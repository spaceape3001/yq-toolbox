////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ys/keywords.hpp>
#include <ys/bit/SStringMap.hpp>
#include <ys/bit/SFormat.hpp>
#include <ys/typedef/sdocument.hpp>
#include <ys/typedef/sobject.hpp>
#include <ys/typedef/revision.hpp>
#include <filesystem>
#include <vector>
#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/string_sets.hpp>
#include <yq/text/IgCase.hpp>

namespace yq::spatial {
    class SObject;
    struct ID;

    struct Census {
        std::string     title;
    };
    
    class SDocument  {
    public:

        SDocument();
        ~SDocument();
    
        SObject*            object(ID);
        const SObject*      object(ID) const;
        
        static constexpr const char*    szExtB3     = "b3";
        static constexpr const char*    szExtXML    = "b3x";
        
        static SDocumentSPtr    load(shared_k, const std::filesystem::path&, SFormat sf=SFormat::AUTO);
        static SDocumentUPtr    load(unique_k, const std::filesystem::path&, SFormat sf=SFormat::AUTO);
        static SDocument*       load(raw_k, const std::filesystem::path&, SFormat sf=SFormat::AUTO);
    
        std::error_code         save(const std::filesystem::path&, SFormat sf=SFormat::AUTO) const;
        
        std::string_view        attribute(const std::string&) const;
        void                    attribute_erase(const std::string&);
        string_set_t            attribute_keys() const;
        void                    attribute_set(const std::string&, const std::string&);
        void                    attribute_set(const std::string&, std::string&&);
        const string_map_t&     attributes() const;
        
        bool                    is_attribute(const std::string&) const;
        bool                    is_variable(const std::string&) const;

        std::string_view        variable(const std::string&) const;
        void                    variable_erase(const std::string&);
        string_set_t            variable_keys() const;
        void                    variable_set(const std::string&, const std::string&);
        void                    variable_set(const std::string&, std::string&&);
        const string_map_t&     variables() const;
    
        revision_t              revision() const { return m_revision; }
        
        void                    bump();
    
    private:
        friend class SObject;
        SDocument(SDocument&&) = delete;
        SDocument(const SDocument&) = delete;
        SDocument& operator=(const SDocument&) = delete;
        SDocument& operator=(SDocument&&) = delete;

        SStringMap                  m_attributes;
        SStringMap                  m_variables;
        std::string                 m_title;
        std::string                 m_description;
        std::vector<SObject*>       m_objects;
        revision_t                  m_revision  = {};
        
        ID  insert(SObject*);

        std::error_code  b3_load(const std::filesystem::path&);
        std::error_code  b3_save(const std::filesystem::path&) const;
        std::error_code  xml_load(const std::filesystem::path&);
        std::error_code  xml_save(const std::filesystem::path&) const;
    };
}
