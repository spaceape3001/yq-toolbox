////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/resource/ResourceDriverAPI.hpp>
#include <yq/resource/ResourceLogging.hpp>
#include <yq/resource/ResourceXmlDriver.hpp>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

namespace yq {
    ///////////////////////////////////

    ResourceXmlInfoer::ResourceXmlInfoer(const ResourceMeta& meta, const string_vector_t& exts, const std::source_location& sl, Type type) :
        ResourceStringInfoer(meta, exts, sl, type)
    {
    }

    ResourceXmlInfoer::~ResourceXmlInfoer()
    {
    }
    
    ResourceInfo* ResourceXmlInfoer::info(const std::string& file, const ResourceInfoAPI&api) const 
    {
        std::string     buffer = file;
        XmlDocument     doc;
        try {
            doc.parse<0>(buffer.data());
        } catch(const rapidxml::parse_error& pe){
            size_t  pt  = pe.where<char>() - buffer.data();
            resourceError << "Xml parse error: " << pe.what() << " (at byte " << pt << ") : " << to_string(api.url());
            return {};
        }
        
        return info(doc,api);
    }

    ///////////////////////////////////

    ResourceXmlLoader::ResourceXmlLoader(const ResourceMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        ResourceStringLoader(meta, exts, sl, type)
    {
    }
    
    ResourceXmlLoader::~ResourceXmlLoader()
    {
    }

    Resource* ResourceXmlLoader::load(const std::string& file, const ResourceLoadAPI& api) const
    {
        std::string     buffer = file;
        XmlDocument     doc;
        try {
            doc.parse<0>(buffer.data());
        } catch(const rapidxml::parse_error& pe){
            size_t  pt  = pe.where<char>() - buffer.data();
            resourceError << "Xml parse error: " << pe.what() << " (at byte " << pt << ") : " << to_string(api.url());
            return {};
        }
        
        return load(doc,api);
    }

    ///////////////////////////////////

    ResourceXmlSaver::ResourceXmlSaver(const ResourceMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        ResourceStringSaver(meta, exts, sl, type)
    {
    }
    
    ResourceXmlSaver::~ResourceXmlSaver()
    {
    }

    std::error_code  ResourceXmlSaver::save(const Resource&resource, std::string& data, const ResourceSaveAPI&api) const
    {
        XmlDocument     doc;
        XmlNode*        x   = doc.allocate_node(rapidxml::node_pi, "xml", "version=\"1.0\" encoding=\"UTF-8\"");
        doc.append_node(x);
        std::error_code ec = save(resource, doc, api);
        if(ec != std::error_code())
            return ec;
        rapidxml::print(std::back_inserter(data), doc, 0);
        return std::error_code();
    }

    ///////////////////////////////////
}
