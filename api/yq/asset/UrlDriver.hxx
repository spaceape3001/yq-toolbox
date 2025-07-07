////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "UrlDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A> 
    class Asset::TypedUrlInfoer : public Asset::UrlInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const UrlView&, const AssetInfoAPI&)>;
    
        TypedUrlInfoer(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            UrlInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedUrlInfoer()
        {
        }

        AssetInfo* info(const UrlView& url, const AssetInfoAPI& api) const override
        {
            return m_function(url, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const UrlView&, const AssetInfoAPI&)>&&fn, const std::source_location& sl)
    {
        add_infoer(new TypedUrlInfoer<A>(exts, std::move(fn), sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedUrlInfoerNoAPI : public Asset::UrlInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const UrlView&)>;
    
        TypedUrlInfoerNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            UrlInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedUrlInfoerNoAPI()
        {
        }

        AssetInfo* info(const UrlView& url, const AssetInfoAPI&) const override
        {
            return m_function(url);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const UrlView&)>&&fn, const std::source_location& sl) 
    {
        add_infoer(new TypedUrlInfoerNoAPI<A>(exts, std::move(fn), sl));
    }

    template <SomeAsset A> 
    class Asset::TypedUrlLoader : public Asset::UrlLoader {
    public:
        using FN    = std::function<A*(const UrlView&, const AssetLoadAPI&)>;
        
        TypedUrlLoader(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            UrlLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedUrlLoader()
        {
        }

        Asset* load(const UrlView& url, const AssetLoadAPI& api) const override
        {
            return m_function(url, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const UrlView&, const AssetLoadAPI&)>&&fn, const std::source_location& sl)
    {
        add_loader(new TypedUrlLoader<A>(exts, std::move(fn), sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedUrlLoaderNoAPI : public Asset::UrlLoader {
    public:
        using FN    = std::function<A*(const UrlView&)>;
    
        TypedUrlLoaderNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            UrlLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedUrlLoaderNoAPI()
        {
        }

        Asset* info(const UrlView& url, const AssetLoadAPI&) const override
        {
            return m_function(url);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const UrlView&)>&&fn, const std::source_location& sl) 
    {
        add_loader(new TypedUrlLoaderNoAPI<A>(exts, std::move(fn), sl));
    }
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A> 
    class Asset::TypedUrlSaver : public UrlSaver {
    public:
    
        using FN    = std::function<std::error_code(const A&, const UrlView&, const AssetSaveAPI&)>;

        TypedUrlSaver(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            UrlSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedUrlSaver()
        {
        }

        std::error_code  save(const Asset& asset, const UrlView& fp, const AssetSaveAPI& api) const override
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
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, const UrlView&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedUrlSaver<A>(exts, std::move(fn), sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedUrlSaverNoAPI : public UrlSaver {
        using FN    = std::function<std::error_code(const A&, const UrlView&)>;

        TypedUrlSaverNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            UrlSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedUrlSaverNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, const UrlView& fp, const AssetSaveAPI&) const override
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
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, const UrlView&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedUrlSaverNoAPI<A>(exts, std::move(fn), sl));
    }


    template <SomeAsset A> 
    class Asset::TypedUrlSaverBool : public UrlSaver {
    public:
    
        using FN    = std::function<bool(const A&, const UrlView&, const AssetSaveAPI&)>;

        TypedUrlSaverBool(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            UrlSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedUrlSaverBool()
        {
        }

        std::error_code  save(const Asset& asset, const UrlView& fp, const AssetSaveAPI& api) const override
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
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<bool(const A&, const UrlView&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedUrlSaverBool<A>(exts, std::move(fn), sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedUrlSaverBoolNoAPI : public UrlSaver {
        using FN    = std::function<bool(const A&, const UrlView&)>;

        TypedUrlSaverBoolNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            UrlSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedUrlSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, const UrlView& fp, const AssetSaveAPI&) const override
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
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<bool(const A&, const UrlView&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedUrlSaverBoolNoAPI<A>(exts, std::move(fn), sl));
    }
}
