////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "KVDocumentDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A> 
    class Asset::TypedKVDocumentInfoer : public Asset::KVDocumentInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const KVDocument&, const AssetInfoAPI&)>;
    
        TypedKVDocumentInfoer(string_view_initializer_list_t exts, FN&& fn, bool recursive, const std::source_location& sl) :
            KVDocumentInfoer(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedKVDocumentInfoer()
        {
        }

        AssetInfo* info(const KVDocument& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const KVDocument&, const AssetInfoAPI&)>&&fn, const std::source_location& sl)
    {
        add_infoer(new TypedKVDocumentInfoer<A>(exts, std::move(fn), false, sl));
    }
    
    template <SomeAsset A>
    void         Asset::add_infoer(string_view_initializer_list_t exts, recursive_k, std::function<typename A::MyInfo*(const KVDocument&, const AssetInfoAPI&)>&&fn, const std::source_location& sl)
    {
        add_infoer(new TypedKVDocumentInfoer<A>(exts, std::move(fn), true, sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedKVDocumentInfoerNoAPI : public Asset::KVDocumentInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const KVDocument&)>;
    
        TypedKVDocumentInfoerNoAPI(string_view_initializer_list_t exts, FN&& fn, bool recursive, const std::source_location& sl) :
            KVDocumentInfoer(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedKVDocumentInfoerNoAPI()
        {
        }

        AssetInfo* info(const KVDocument& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const KVDocument&)>&&fn, const std::source_location& sl) 
    {
        add_infoer(new TypedKVDocumentInfoerNoAPI<A>(exts, std::move(fn), false, sl));
    }

    template <SomeAsset A>
    void    Asset::add_infoer(string_view_initializer_list_t exts, recursive_k, std::function<typename A::MyInfo*(const KVDocument&)>&&fn, const std::source_location& sl) 
    {
        add_infoer(new TypedKVDocumentInfoerNoAPI<A>(exts, std::move(fn), true, sl));
    }


    template <SomeAsset A> 
    class Asset::TypedKVDocumentLoader : public Asset::KVDocumentLoader {
    public:
        using FN    = std::function<A*(const KVDocument&, const AssetLoadAPI&)>;
        
        TypedKVDocumentLoader(string_view_initializer_list_t exts, FN&& fn, bool recursive, const std::source_location& sl) :
            KVDocumentLoader(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedKVDocumentLoader()
        {
        }

        Asset* load(const KVDocument& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const KVDocument&, const AssetLoadAPI&)>&&fn, const std::source_location& sl)
    {
        add_loader(new TypedKVDocumentLoader<A>(exts, std::move(fn), false, sl));
    }
    
    template <SomeAsset A>
    void         Asset::add_loader(string_view_initializer_list_t exts, recursive_k, std::function<A*(const KVDocument&, const AssetLoadAPI&)>&&fn, const std::source_location& sl)
    {
        add_loader(new TypedKVDocumentLoader<A>(exts, std::move(fn), true, sl));
    }
    

    template <SomeAsset A> 
    class Asset::TypedKVDocumentLoaderNoAPI : public Asset::KVDocumentLoader {
    public:
        using FN    = std::function<A*(const KVDocument&)>;
    
        TypedKVDocumentLoaderNoAPI(string_view_initializer_list_t exts, FN&& fn, bool recursive, const std::source_location& sl) :
            KVDocumentLoader(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedKVDocumentLoaderNoAPI()
        {
        }

        Asset* info(const KVDocument& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const KVDocument&)>&&fn, const std::source_location& sl) 
    {
        add_loader(new TypedKVDocumentLoaderNoAPI<A>(exts, std::move(fn), false, sl));
    }
    
    template <SomeAsset A>
    void    Asset::add_loader(string_view_initializer_list_t exts, recursive_k, std::function<A*(const KVDocument&)>&&fn, const std::source_location& sl) 
    {
        add_loader(new TypedKVDocumentLoaderNoAPI<A>(exts, std::move(fn), true, sl));
    }

    template <SomeAsset A> 
    class Asset::TypedKVDocumentSaver : public KVDocumentSaver {
    public:
    
        using FN    = std::function<std::error_code(const A&, KVDocument&, const AssetSaveAPI&)>;

        TypedKVDocumentSaver(string_view_initializer_list_t exts, FN&& fn, bool recurse, const std::source_location& sl) :
            KVDocumentSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedKVDocumentSaver()
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
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, KVDocument&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedKVDocumentSaver<A>(exts, std::move(fn), sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedKVDocumentSaverNoAPI : public KVDocumentSaver {
        using FN    = std::function<std::error_code(const A&, KVDocument&)>;

        TypedKVDocumentSaverNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            ByteSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedKVDocumentSaverNoAPI()
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
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, KVDocument&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedKVDocumentSaverNoAPI<A>(exts, std::move(fn), sl));
    }
}
