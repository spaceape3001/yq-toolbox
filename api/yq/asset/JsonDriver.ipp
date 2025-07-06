////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "JsonDriver.hpp"
#include "JsonDriver.hxx"
#include "AssetLogging.hpp"
#include "AssetDriverAPI.hpp"

#include <yq/net/json.hpp>

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

namespace yq {
    ///////////////////////////////////

    Asset::JsonInfoer::JsonInfoer(const AssetMeta& meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) :
        StringInfoer(meta, exts, sl, type)
    {
    }

    Asset::JsonInfoer::~JsonInfoer()
    {
    }
    
    AssetInfo* Asset::JsonInfoer::info(const std::string& file, const AssetInfoAPI&api) const 
    {
        json        j;
        try {
            j   = json::parse( file.data(), file.data()+file.size());
        }
        catch(...)
        {
            assetError << "Unable to parse json: " << to_string(api.url());
            return nullptr;
        }
        
        return info(j, api);
    }

    ///////////////////////////////////

    Asset::JsonLoader::JsonLoader(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        StringLoader(meta, exts, sl, type)
    {
    }
    
    Asset::JsonLoader::~JsonLoader()
    {
    }

    Asset* Asset::JsonLoader::load(const std::string& file, const AssetLoadAPI& api) const
    {
        json        j;
        try {
            j   = json::parse( file.data(), file.data()+file.size());
        }
        catch(...)
        {
            assetError << "Unable to parse json: " << to_string(api.url());
            return nullptr;
        }
        
        return load(j, api);
    }

    ///////////////////////////////////

    Asset::JsonSaver::JsonSaver(const AssetMeta&meta, string_view_initializer_list_t exts, const std::source_location& sl, Type type) : 
        StringSaver(meta, exts, sl, type)
    {
    }
    
    Asset::JsonSaver::~JsonSaver()
    {
    }

    std::error_code  Asset::JsonSaver::save(const Asset&asset, std::string& data, const AssetSaveAPI&api) const
    {
        json    j;
        std::error_code ec = save(asset, j, api);
        if(ec != std::error_code())
            return ec;
        
        ::nlohmann::detail::serializer<json> s(::nlohmann::detail::output_adapter<char>(data), ' ');
        s.dump(j, false, false, 0);
        return std::error_code();
    }

    ///////////////////////////////////
}
