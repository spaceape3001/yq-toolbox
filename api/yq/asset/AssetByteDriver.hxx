////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AssetByteDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A, typename Pred> 
    class TypedAssetByteInfoer : public AssetByteInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const ByteArray&, const AssetInfoAPI&)>;
    
        TypedAssetByteInfoer(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetByteInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetByteInfoer()
        {
        }

        AssetInfo* info(const ByteArray& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    
    template <SomeAsset A, typename Pred> 
    class TypedAssetByteInfoerNoAPI : public AssetByteInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const ByteArray&)>;
    
        TypedAssetByteInfoerNoAPI(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetByteInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetByteInfoerNoAPI()
        {
        }

        AssetInfo* info(const ByteArray& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    

    template <SomeAsset A, typename Pred> 
    class TypedAssetByteLoader : public AssetByteLoader {
    public:
        //using Pred    = std::function<A*(const ByteArray&, const AssetLoadAPI&)>;
        
        TypedAssetByteLoader(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetByteLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetByteLoader()
        {
        }

        Asset* load(const ByteArray& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    
    template <SomeAsset A, typename Pred> 
    class TypedAssetByteLoaderNoAPI : public AssetByteLoader {
    public:
        //using Pred    = std::function<A*(const ByteArray&)>;
    
        TypedAssetByteLoaderNoAPI(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetByteLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetByteLoaderNoAPI()
        {
        }

        Asset* info(const ByteArray& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A, typename Pred> 
    class TypedAssetByteSaver : public AssetByteSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, ByteArray&, const AssetSaveAPI&)>;

        TypedAssetByteSaver(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetByteSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetByteSaver()
        {
        }

        std::error_code  save(const Asset& asset, ByteArray& bytes, const AssetSaveAPI& api) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            return m_function(*a, bytes, api);
        }
        

    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetByteSaverNoAPI : public AssetByteSaver {
        //using Pred    = std::function<std::error_code(const A&, ByteArray&)>;

        TypedAssetByteSaverNoAPI(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetByteSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetByteSaverNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, ByteArray& bytes, const AssetSaveAPI&) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            return m_function(*a, bytes);
        }
        

    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetByteSaverBool : public AssetByteSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, ByteArray&, const AssetSaveAPI&)>;

        TypedAssetByteSaverBool(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetByteSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetByteSaverBool()
        {
        }

        std::error_code  save(const Asset& asset, ByteArray& bytes, const AssetSaveAPI& api) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, bytes, api))
                return errors::asset_saving_failed();
            return {};
        }
        

    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetByteSaverBoolNoAPI : public AssetByteSaver {
        //using Pred    = std::function<bool(const A&, ByteArray&)>;

        TypedAssetByteSaverBoolNoAPI(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetByteSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetByteSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, ByteArray& bytes, const AssetSaveAPI&) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, bytes))
                return errors::asset_saving_failed();
            return {};
        }
        

    private:
        Pred          m_function;
    };
}
