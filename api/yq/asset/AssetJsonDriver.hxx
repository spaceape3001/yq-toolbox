////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetJsonDriver.hpp>
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A, typename Pred> 
    class TypedAssetJsonInfoer : public AssetJsonInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const json&, const AssetInfoAPI&)>;
    
        TypedAssetJsonInfoer(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetJsonInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetJsonInfoer()
        {
        }

        AssetInfo* info(const json& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };
    
    template <SomeAsset A, typename Pred> 
    class TypedAssetJsonInfoerNoAPI : public AssetJsonInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const json&)>;
    
        TypedAssetJsonInfoerNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetJsonInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetJsonInfoerNoAPI()
        {
        }

        AssetInfo* info(const json& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
    template <SomeAsset A, typename Pred> 
    class TypedAssetJsonLoader : public AssetJsonLoader {
    public:
        //using Pred    = std::function<A*(const json&, const AssetLoadAPI&)>;
        
        TypedAssetJsonLoader(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetJsonLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetJsonLoader()
        {
        }

        Asset* load(const json& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };
    
    template <SomeAsset A, typename Pred> 
    class TypedAssetJsonLoaderNoAPI : public AssetJsonLoader {
    public:
        //using Pred    = std::function<A*(const json&)>;
    
        TypedAssetJsonLoaderNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetJsonLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetJsonLoaderNoAPI()
        {
        }

        Asset* info(const json& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A, typename Pred> 
    class TypedAssetJsonSaver : public AssetJsonSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, json&, const AssetSaveAPI&)>;

        TypedAssetJsonSaver(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetJsonSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetJsonSaver()
        {
        }

        std::error_code  save(const Asset& asset, json& fp, const AssetSaveAPI& api) const override
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
    class TypedAssetJsonSaverNoAPI : public AssetJsonSaver {
        //using Pred    = std::function<std::error_code(const A&, json&)>;

        TypedAssetJsonSaverNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetJsonSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetJsonSaverNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, json& fp, const AssetSaveAPI&) const override
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
    class TypedAssetJsonSaverBool : public AssetJsonSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, json&, const AssetSaveAPI&)>;

        TypedAssetJsonSaverBool(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetJsonSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetJsonSaverBool()
        {
        }

        std::error_code  save(const Asset& asset, json& fp, const AssetSaveAPI& api) const override
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
    class TypedAssetJsonSaverBoolNoAPI : public AssetJsonSaver {
        //using Pred    = std::function<bool(const A&, json&)>;

        TypedAssetJsonSaverBoolNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetJsonSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetJsonSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, json& fp, const AssetSaveAPI&) const override
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
