////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetDriverAPI.hpp>
#include <yq/asset/AssetLogging.hpp>
#include <yq/asset/AssetXmlDriver.hpp>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

namespace yq {
    ///////////////////////////////////

    AssetXmlInfoer::AssetXmlInfoer(const AssetMeta& meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) :
        AssetStringInfoer(meta, exts, sl, type)
    {
    }

    AssetXmlInfoer::~AssetXmlInfoer()
    {
    }
    
    AssetInfo* AssetXmlInfoer::info(const std::string& file, const AssetInfoAPI&api) const 
    {
        std::string     buffer = file;
        XmlDocument     doc;
        try {
            doc.parse<0>(buffer.data());
        } catch(const rapidxml::parse_error& pe){
            size_t  pt  = pe.where<char>() - buffer.data();
            assetError << "Xml parse error: " << pe.what() << " (at byte " << pt << ") : " << to_string(api.url());
            return {};
        }
        
        return info(doc,api);
    }

    ///////////////////////////////////

    AssetXmlLoader::AssetXmlLoader(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        AssetStringLoader(meta, exts, sl, type)
    {
    }
    
    AssetXmlLoader::~AssetXmlLoader()
    {
    }

    Asset* AssetXmlLoader::load(const std::string& file, const AssetLoadAPI& api) const
    {
        std::string     buffer = file;
        XmlDocument     doc;
        try {
            doc.parse<0>(buffer.data());
        } catch(const rapidxml::parse_error& pe){
            size_t  pt  = pe.where<char>() - buffer.data();
            assetError << "Xml parse error: " << pe.what() << " (at byte " << pt << ") : " << to_string(api.url());
            return {};
        }
        
        return load(doc,api);
    }

    ///////////////////////////////////

    AssetXmlSaver::AssetXmlSaver(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        AssetStringSaver(meta, exts, sl, type)
    {
    }
    
    AssetXmlSaver::~AssetXmlSaver()
    {
    }

    std::error_code  AssetXmlSaver::save(const Asset&asset, std::string& data, const AssetSaveAPI&api) const
    {
        XmlDocument     doc;
        XmlNode*        x   = doc.allocate_node(rapidxml::node_pi, "xml", "version=\"1.0\" encoding=\"UTF-8\"");
        doc.append_node(x);
        std::error_code ec = save(asset, doc, api);
        if(ec != std::error_code())
            return ec;
        rapidxml::print(std::back_inserter(data), doc, 0);
        return std::error_code();
    }

    ///////////////////////////////////
}
