////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetFileDriver.hpp>
#include <iosfwd>

namespace yq {
    class AssetStreamInfoer : public AssetFileInfoer {
    public:
    
        using AssetFileInfoer::info;
        virtual AssetInfo* info(const std::filesystem::path&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(std::istream&, const AssetInfoAPI&) const = 0;
        
    protected:
        AssetStreamInfoer(const AssetMeta&, const string_vector_t& exts, const std::source_location&, bool binary, Type type=Type::stream);
        virtual ~AssetStreamInfoer();
        
    private:
        bool m_binary;
    };
    
    class AssetStreamLoader : public AssetFileLoader {
    public:

        using AssetFileLoader::load;
        virtual Asset* load(const std::filesystem::path&, const AssetLoadAPI&) const override final;
        virtual Asset* load(std::istream&, const AssetLoadAPI&) const = 0;
        
    protected:
        AssetStreamLoader(const AssetMeta&, const string_vector_t& exts, const std::source_location&, bool binary, Type type=Type::stream);
        virtual ~AssetStreamLoader();
        
    private:
        bool m_binary;
    };

    class AssetStreamSaver : public AssetFileSaver {
    public:

        using AssetFileSaver::save;
        virtual std::error_code  save(const Asset&, const std::filesystem::path&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, std::ostream&, const AssetSaveAPI&) const = 0;

    protected:
        AssetStreamSaver(const AssetMeta&, const string_vector_t& exts, const std::source_location&, bool binary, Type type=Type::stream);
        virtual ~AssetStreamSaver();
        
    private:
        bool m_binary;
    };
}
