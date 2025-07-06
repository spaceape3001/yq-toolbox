////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/FileDriver.hpp>
#include <iosfwd>

namespace yq {
    class Asset::StreamInfoer : public FileInfoer {
    public:
    
        using FileInfoer::info;
        virtual AssetInfo* info(const std::filesystem::path&, const AssetInfoAPI&) const override final;
        virtual AssetInfo* info(std::istream&, const AssetInfoAPI&) const = 0;
        
    protected:
        StreamInfoer(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, bool binary, Type type=Type::stream);
        virtual ~StreamInfoer();
        
    private:
        bool m_binary;
    };
    
    class Asset::StreamLoader : public FileLoader {
    public:

        using FileLoader::load;
        virtual Asset* load(const std::filesystem::path&, const AssetLoadAPI&) const override final;
        virtual Asset* load(std::istream&, const AssetLoadAPI&) const = 0;
        
    protected:
        StreamLoader(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, bool binary, Type type=Type::stream);
        virtual ~StreamLoader();
        
    private:
        bool m_binary;
    };

    class Asset::StreamSaver : public FileSaver {
    public:

        using FileSaver::save;
        virtual std::error_code  save(const Asset&, const std::filesystem::path&, const AssetSaveAPI&) const override final;
        virtual std::error_code  save(const Asset&, std::ostream&, const AssetSaveAPI&) const = 0;

    protected:
        StreamSaver(const AssetMeta&, string_view_initializer_list_t exts, const std::source_location&, bool binary, Type type=Type::stream);
        virtual ~StreamSaver();
        
    private:
        bool m_binary;
    };
}
