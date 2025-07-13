////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AssetKVDocumentDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A, typename Pred> 
    class TypedAssetKVDocumentInfoer : public AssetKVDocumentInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const KVDocument&, const AssetInfoAPI&)>;
    
        TypedAssetKVDocumentInfoer(string_view_initializer_list_t exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            AssetKVDocumentInfoer(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetKVDocumentInfoer()
        {
        }

        AssetInfo* info(const KVDocument& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetKVDocumentInfoerNoAPI : public AssetKVDocumentInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const KVDocument&)>;
    
        TypedAssetKVDocumentInfoerNoAPI(string_view_initializer_list_t exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            AssetKVDocumentInfoer(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetKVDocumentInfoerNoAPI()
        {
        }

        AssetInfo* info(const KVDocument& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    

    template <SomeAsset A, typename Pred> 
    class TypedAssetKVDocumentLoader : public AssetKVDocumentLoader {
    public:
        //using Pred    = std::function<A*(const KVDocument&, const AssetLoadAPI&)>;
        
        TypedAssetKVDocumentLoader(string_view_initializer_list_t exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            AssetKVDocumentLoader(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetKVDocumentLoader()
        {
        }

        Asset* load(const KVDocument& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };


    template <SomeAsset A, typename Pred> 
    class TypedAssetKVDocumentLoaderNoAPI : public AssetKVDocumentLoader {
    public:
        //using Pred    = std::function<A*(const KVDocument&)>;
    
        TypedAssetKVDocumentLoaderNoAPI(string_view_initializer_list_t exts, Pred&& fn, bool recursive, const std::source_location& sl) :
            AssetKVDocumentLoader(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetKVDocumentLoaderNoAPI()
        {
        }

        Asset* info(const KVDocument& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
    //template <SomeAsset A>
    //void    Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const KVDocument&)>&&fn, const std::source_location& sl) 
    //{
        //add_loader(new TypedAssetKVDocumentLoaderNoAPI<A>(exts, std::move(fn), false, sl));
    //}
    
    //template <SomeAsset A>
    //void    Asset::add_loader(string_view_initializer_list_t exts, recursive_k, std::function<A*(const KVDocument&)>&&fn, const std::source_location& sl) 
    //{
        //add_loader(new TypedAssetKVDocumentLoaderNoAPI<A>(exts, std::move(fn), true, sl));
    //}

////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A, typename Pred> 
    class TypedAssetKVDocumentSaver : public AssetKVDocumentSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, KVDocument&, const AssetSaveAPI&)>;

        TypedAssetKVDocumentSaver(string_view_initializer_list_t exts, Pred&& fn, bool recurse, const std::source_location& sl) :
            AssetKVDocumentSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetKVDocumentSaver()
        {
        }

        std::error_code  save(const Asset& asset, KVDocument& bytes, const AssetSaveAPI& api) const override
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
    class TypedAssetKVDocumentSaverNoAPI : public AssetKVDocumentSaver {
        //using Pred    = std::function<std::error_code(const A&, KVDocument&)>;

        TypedAssetKVDocumentSaverNoAPI(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetKVDocumentSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedAssetKVDocumentSaverNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, KVDocument& bytes, const AssetSaveAPI&) const override
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
    class TypedAssetKVDocumentSaverBool : public AssetKVDocumentSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, KVDocument&, const AssetSaveAPI&)>;

        TypedAssetKVDocumentSaverBool(string_view_initializer_list_t exts, Pred&& fn, bool recurse, const std::source_location& sl) :
            AssetKVDocumentSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetKVDocumentSaverBool()
        {
        }

        std::error_code  save(const Asset& asset, KVDocument& bytes, const AssetSaveAPI& api) const override
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
    class TypedAssetKVDocumentSaverBoolNoAPI : public AssetKVDocumentSaver {
//        using Pred    = std::function<bool(const A&, KVDocument&)>;

        TypedAssetKVDocumentSaverBoolNoAPI(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetKVDocumentSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedAssetKVDocumentSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, KVDocument& bytes, const AssetSaveAPI&) const override
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
