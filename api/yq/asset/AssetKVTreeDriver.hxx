////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AssetKVTreeDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A, typename Pred> 
    class TypedAssetKVTreeInfoer : public AssetKVTreeInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const KVTree&, const AssetInfoAPI&)>;
    
        TypedAssetKVTreeInfoer(string_view_initializer_list_t exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            AssetKVTreeInfoer(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetKVTreeInfoer()
        {
        }

        AssetInfo* info(const KVTree& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetKVTreeInfoerNoAPI : public AssetKVTreeInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const KVTree&)>;
    
        TypedAssetKVTreeInfoerNoAPI(string_view_initializer_list_t exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            AssetKVTreeInfoer(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetKVTreeInfoerNoAPI()
        {
        }

        AssetInfo* info(const KVTree& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    

    template <SomeAsset A, typename Pred> 
    class TypedAssetKVTreeLoader : public AssetKVTreeLoader {
    public:
        //using Pred    = std::function<A*(const KVTree&, const AssetLoadAPI&)>;
        
        TypedAssetKVTreeLoader(string_view_initializer_list_t exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            AssetKVTreeLoader(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetKVTreeLoader()
        {
        }

        Asset* load(const KVTree& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };


    template <SomeAsset A, typename Pred> 
    class TypedAssetKVTreeLoaderNoAPI : public AssetKVTreeLoader {
    public:
        //using Pred    = std::function<A*(const KVTree&)>;
    
        TypedAssetKVTreeLoaderNoAPI(string_view_initializer_list_t exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            AssetKVTreeLoader(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetKVTreeLoaderNoAPI()
        {
        }

        Asset* info(const KVTree& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A, typename Pred> 
    class TypedAssetKVTreeSaver : public AssetKVTreeSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, KVTree&, const AssetSaveAPI&)>;

        TypedAssetKVTreeSaver(string_view_initializer_list_t exts, Pred&& fn, bool recurse, const std::source_location& sl) :
            AssetKVTreeSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetKVTreeSaver()
        {
        }

        std::error_code  save(const Asset& asset, KVTree& bytes, const AssetSaveAPI& api) const override
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
    class TypedAssetKVTreeSaverNoAPI : public AssetKVTreeSaver {
        //using Pred    = std::function<std::error_code(const A&, KVTree&)>;

        TypedAssetKVTreeSaverNoAPI(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetKVTreeSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedAssetKVTreeSaverNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, KVTree& bytes, const AssetSaveAPI&) const override
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
    class TypedAssetKVTreeSaverBool : public AssetKVTreeSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, KVTree&, const AssetSaveAPI&)>;

        TypedAssetKVTreeSaverBool(string_view_initializer_list_t exts, Pred&& fn, bool recurse, const std::source_location& sl) :
            AssetKVTreeSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetKVTreeSaverBool()
        {
        }

        std::error_code  save(const Asset& asset, KVTree& bytes, const AssetSaveAPI& api) const override
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
    class TypedAssetKVTreeSaverBoolNoAPI : public AssetKVTreeSaver {
        //using Pred    = std::function<bool(const A&, KVTree&)>;

        TypedAssetKVTreeSaverBoolNoAPI(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetKVTreeSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedAssetKVTreeSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, KVTree& bytes, const AssetSaveAPI&) const override
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
