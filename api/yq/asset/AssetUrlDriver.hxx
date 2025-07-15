////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetUrlDriver.hpp>
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A, typename Pred> 
    class TypedAssetUrlInfoer : public AssetUrlInfoer {
    public:
        // using Pred    = std::function<typename A::MyInfo*(const UrlView&, const AssetInfoAPI&)>;
    
        TypedAssetUrlInfoer(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetUrlInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetUrlInfoer()
        {
        }

        AssetInfo* info(const UrlView& url, const AssetInfoAPI& api) const override
        {
            return m_function(url, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetUrlInfoerNoAPI : public AssetUrlInfoer {
    public:
        // using Pred    = std::function<typename A::MyInfo*(const UrlView&)>;
    
        TypedAssetUrlInfoerNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetUrlInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetUrlInfoerNoAPI()
        {
        }

        AssetInfo* info(const UrlView& url, const AssetInfoAPI&) const override
        {
            return m_function(url);
        }
        
    private:
        Pred          m_function;
    };
    
    template <SomeAsset A, typename Pred> 
    class TypedAssetUrlLoader : public AssetUrlLoader {
    public:
        //using Pred    = std::function<A*(const UrlView&, const AssetLoadAPI&)>;
        
        TypedAssetUrlLoader(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetUrlLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetUrlLoader()
        {
        }

        Asset* load(const UrlView& url, const AssetLoadAPI& api) const override
        {
            return m_function(url, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetUrlLoaderNoAPI : public AssetUrlLoader {
    public:
        // using Pred    = std::function<A*(const UrlView&)>;
    
        TypedAssetUrlLoaderNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetUrlLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetUrlLoaderNoAPI()
        {
        }

        Asset* info(const UrlView& url, const AssetLoadAPI&) const override
        {
            return m_function(url);
        }
        
    private:
        Pred          m_function;
    };
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A, typename Pred> 
    class TypedAssetUrlSaver : public AssetUrlSaver {
    public:
    
        // using Pred    = std::function<std::error_code(const A&, const UrlView&, const AssetSaveAPI&)>;

        TypedAssetUrlSaver(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetUrlSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetUrlSaver()
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
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetUrlSaverNoAPI : public AssetUrlSaver {
        // using Pred    = std::function<std::error_code(const A&, const UrlView&)>;

        TypedAssetUrlSaverNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetUrlSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetUrlSaverNoAPI()
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
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetUrlSaverBool : public AssetUrlSaver {
    public:
        TypedAssetUrlSaverBool(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetUrlSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetUrlSaverBool()
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
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred>
    class TypedAssetUrlSaverBoolNoAPI : public AssetUrlSaver {
        //using Pred    = std::function<bool(const A&, const UrlView&)>;

        TypedAssetUrlSaverBoolNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetUrlSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetUrlSaverBoolNoAPI()
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
        Pred          m_function;
    };
}
