////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetStringDriver.hpp>

namespace yq {
    class AssetJsonInfoer : public AssetStringInfoer {
    public:
    
        using AssetStringInfoer::info;
        virtual AssetInfo* info(const std::string&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(const json&, const AssetInfoAPI&) const = 0;
        
    protected:
        AssetJsonInfoer(const AssetMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::json);
        virtual ~AssetJsonInfoer();
    };
    
    class AssetJsonLoader : public AssetStringLoader {
    public:

        using AssetStringLoader::load;
        virtual Asset* load(const std::string&, const AssetLoadAPI&) const override final;
        virtual Asset* load(const json&, const AssetLoadAPI&) const = 0;
        
    protected:
        AssetJsonLoader(const AssetMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::json);
        virtual ~AssetJsonLoader();
    };

    class AssetJsonSaver : public AssetStringSaver {
    public:

        using AssetStringSaver::save;
        virtual std::error_code  save(const Asset&, std::string&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, json&, const AssetSaveAPI&) const = 0;

    protected:
        AssetJsonSaver(const AssetMeta&, const string_vector_t& exts, const std::source_location&, Type type=Type::json);
        virtual ~AssetJsonSaver();
    };
}
