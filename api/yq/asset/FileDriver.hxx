////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "FileDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A> 
    class Asset::TypedFileInfoer : public Asset::FileInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const std::filesystem::path&, const AssetInfoAPI&)>;
    
        TypedFileInfoer(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            FileInfoer(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedFileInfoer()
        {
        }

        AssetInfo* info(const std::filesystem::path& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const std::filesystem::path&, const AssetInfoAPI&)>&&fn, const std::source_location& sl)
    {
        add_infoer(new TypedFileInfoer<A>(exts, std::move(fn), sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedFileInfoerNoAPI : public Asset::FileInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const std::filesystem::path&)>;
    
        TypedFileInfoerNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            FileInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedFileInfoerNoAPI()
        {
        }

        AssetInfo* info(const std::filesystem::path& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const std::filesystem::path&)>&&fn, const std::source_location& sl) 
    {
        add_infoer(new TypedFileInfoerNoAPI<A>(exts, std::move(fn), sl));
    }

    template <SomeAsset A> 
    class Asset::TypedFileLoader : public Asset::FileLoader {
    public:
        using FN    = std::function<A*(const std::filesystem::path&, const AssetLoadAPI&)>;
        
        TypedFileLoader(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            FileLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedFileLoader()
        {
        }

        Asset* load(const std::filesystem::path& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const std::filesystem::path&, const AssetLoadAPI&)>&&fn, const std::source_location& sl)
    {
        add_loader(new TypedFileLoader<A>(exts, std::move(fn), sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedFileLoaderNoAPI : public Asset::FileLoader {
    public:
        using FN    = std::function<A*(const std::filesystem::path&)>;
    
        TypedFileLoaderNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            FileLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedFileLoaderNoAPI()
        {
        }

        Asset* info(const std::filesystem::path& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const std::filesystem::path&)>&&fn, const std::source_location& sl) 
    {
        add_loader(new TypedFileLoaderNoAPI<A>(exts, std::move(fn), sl));
    }
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A> 
    class Asset::TypedFileSaver : public FileSaver {
    public:
    
        using FN    = std::function<std::error_code(const A&, const std::filesystem::path&, const AssetSaveAPI&)>;

        TypedFileSaver(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            FileSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedFileSaver()
        {
        }

        std::error_code  save(const Asset& asset, const std::filesystem::path& fp, const AssetSaveAPI& api) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            return m_function(*a, fp, api);
        }
        

    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, const std::filesystem::path&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedFileSaver<A>(exts, std::move(fn), sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedFileSaverNoAPI : public FileSaver {
        using FN    = std::function<std::error_code(const A&, const std::filesystem::path&)>;

        TypedFileSaverNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            FileSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedFileSaverNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, const std::filesystem::path& fp, const AssetSaveAPI&) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            return m_function(*a, fp);
        }
        

    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, const std::filesystem::path&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedFileSaverNoAPI<A>(exts, std::move(fn), sl));
    }


    template <SomeAsset A> 
    class Asset::TypedFileSaverBool : public FileSaver {
    public:
    
        using FN    = std::function<bool(const A&, const std::filesystem::path&, const AssetSaveAPI&)>;

        TypedFileSaverBool(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            FileSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedFileSaverBool()
        {
        }

        std::error_code  save(const Asset& asset, const std::filesystem::path& fp, const AssetSaveAPI& api) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, fp, api))
                return errors::asset_saving_failed();
            return {};
        }
        

    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<bool(const A&, const std::filesystem::path&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedFileSaverBool<A>(exts, std::move(fn), sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedFileSaverBoolNoAPI : public FileSaver {
        using FN    = std::function<bool(const A&, const std::filesystem::path&)>;

        TypedFileSaverBoolNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            FileSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedFileSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, const std::filesystem::path& fp, const AssetSaveAPI&) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, fp))
                return errors::asset_saving_failed();
            return {};
        }
        

    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<bool(const A&, const std::filesystem::path&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedFileSaverBoolNoAPI<A>(exts, std::move(fn), sl));
    }
}
