////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "XmlDriver.hpp"
#include "XmlDriver.hxx"
#include "AssetLogging.hpp"
#include "AssetDriverAPI.hpp"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

namespace yq {
    ///////////////////////////////////

    Asset::XmlInfoer::XmlInfoer(const AssetMeta& meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) :
        StringInfoer(meta, exts, sl, type)
    {
    }

    Asset::XmlInfoer::~XmlInfoer()
    {
    }
    
    AssetInfo* Asset::XmlInfoer::info(const std::string& file, const AssetInfoAPI&api) const 
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

    Asset::XmlLoader::XmlLoader(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        StringLoader(meta, exts, sl, type)
    {
    }
    
    Asset::XmlLoader::~XmlLoader()
    {
    }

    Asset* Asset::XmlLoader::load(const std::string& file, const AssetLoadAPI& api) const
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

    Asset::XmlSaver::XmlSaver(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        StringSaver(meta, exts, sl, type)
    {
    }
    
    Asset::XmlSaver::~XmlSaver()
    {
    }

    std::error_code  Asset::XmlSaver::save(const Asset&asset, std::string& data, const AssetSaveAPI&api) const
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
