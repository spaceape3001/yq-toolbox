////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetJsonDriver.hpp>
#include <yq/asset/AssetLogging.hpp>
#include <yq/asset/AssetDriverAPI.hpp>

#include <yq/net/json.hpp>

namespace yq {
    ///////////////////////////////////

    AssetJsonInfoer::AssetJsonInfoer(const AssetMeta& meta, const string_vector_t& exts, const std::source_location& sl, Type type) :
        AssetStringInfoer(meta, exts, sl, type)
    {
    }

    AssetJsonInfoer::~AssetJsonInfoer()
    {
    }
    
    AssetInfo* AssetJsonInfoer::info(const std::string& file, const AssetInfoAPI&api) const 
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

    AssetJsonLoader::AssetJsonLoader(const AssetMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        AssetStringLoader(meta, exts, sl, type)
    {
    }
    
    AssetJsonLoader::~AssetJsonLoader()
    {
    }

    Asset* AssetJsonLoader::load(const std::string& file, const AssetLoadAPI& api) const
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

    AssetJsonSaver::AssetJsonSaver(const AssetMeta&meta, const string_vector_t& exts, const std::source_location& sl, Type type) : 
        AssetStringSaver(meta, exts, sl, type)
    {
    }
    
    AssetJsonSaver::~AssetJsonSaver()
    {
    }

    std::error_code  AssetJsonSaver::save(const Asset&asset, std::string& data, const AssetSaveAPI&api) const
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
