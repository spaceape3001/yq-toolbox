////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AssetFileDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A, typename Pred> 
    class TypedAssetFileInfoer : public AssetFileInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const std::filesystem::path&, const AssetInfoAPI&)>;
    
        TypedAssetFileInfoer(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetFileInfoer(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetFileInfoer()
        {
        }

        AssetInfo* info(const std::filesystem::path& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    
    template <SomeAsset A, typename Pred> 
    class TypedAssetFileInfoerNoAPI : public AssetFileInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const std::filesystem::path&)>;
    
        TypedAssetFileInfoerNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetFileInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetFileInfoerNoAPI()
        {
        }

        AssetInfo* info(const std::filesystem::path& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetFileLoader : public AssetFileLoader {
    public:
        //using Pred    = std::function<A*(const std::filesystem::path&, const AssetLoadAPI&)>;
        
        TypedAssetFileLoader(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetFileLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetFileLoader()
        {
        }

        Asset* load(const std::filesystem::path& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetFileLoaderNoAPI : public AssetFileLoader {
    public:
        //using Pred    = std::function<A*(const std::filesystem::path&)>;
    
        TypedAssetFileLoaderNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetFileLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetFileLoaderNoAPI()
        {
        }

        Asset* load(const std::filesystem::path& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    

////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A, typename Pred> 
    class TypedAssetFileSaver : public AssetFileSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, const std::filesystem::path&, const AssetSaveAPI&)>;

        TypedAssetFileSaver(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetFileSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetFileSaver()
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
        Pred          m_function;
    };

    
    template <SomeAsset A, typename Pred> 
    class TypedAssetFileSaverNoAPI : public AssetFileSaver {
    public:
        //using Pred    = std::function<std::error_code(const A&, const std::filesystem::path&)>;

        TypedAssetFileSaverNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetFileSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetFileSaverNoAPI()
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
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetFileSaverBool : public AssetFileSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, const std::filesystem::path&, const AssetSaveAPI&)>;

        TypedAssetFileSaverBool(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetFileSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetFileSaverBool()
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
        Pred          m_function;
    };
    
    template <SomeAsset A, typename Pred> 
    class TypedAssetFileSaverBoolNoAPI : public AssetFileSaver {
    public:
        //using Pred    = std::function<bool(const A&, const std::filesystem::path&)>;

        TypedAssetFileSaverBoolNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetFileSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetFileSaverBoolNoAPI()
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
        Pred          m_function;
    };
}
