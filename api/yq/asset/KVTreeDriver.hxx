////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "KVTreeDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A> 
    class Asset::TypedKVTreeInfoer : public Asset::KVTreeInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const KVTree&, const AssetInfoAPI&)>;
    
        TypedKVTreeInfoer(string_view_initializer_list_t exts, FN&& fn, bool recursive, const std::source_location& sl) :
            KVTreeInfoer(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedKVTreeInfoer()
        {
        }

        AssetInfo* info(const KVTree& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const KVTree&, const AssetInfoAPI&)>&&fn, const std::source_location& sl)
    {
        add_infoer(new TypedKVTreeInfoer<A>(exts, std::move(fn), false, sl));
    }
    
    template <SomeAsset A>
    void         Asset::add_infoer(string_view_initializer_list_t exts, recursive_k, std::function<typename A::MyInfo*(const KVTree&, const AssetInfoAPI&)>&&fn, const std::source_location& sl)
    {
        add_infoer(new TypedKVTreeInfoer<A>(exts, std::move(fn), true, sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedKVTreeInfoerNoAPI : public Asset::KVTreeInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const KVTree&)>;
    
        TypedKVTreeInfoerNoAPI(string_view_initializer_list_t exts, FN&& fn, bool recursive, const std::source_location& sl) :
            KVTreeInfoer(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedKVTreeInfoerNoAPI()
        {
        }

        AssetInfo* info(const KVTree& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const KVTree&)>&&fn, const std::source_location& sl) 
    {
        add_infoer(new TypedKVTreeInfoerNoAPI<A>(exts, std::move(fn), false, sl));
    }

    template <SomeAsset A>
    void    Asset::add_infoer(string_view_initializer_list_t exts, recursive_k, std::function<typename A::MyInfo*(const KVTree&)>&&fn, const std::source_location& sl) 
    {
        add_infoer(new TypedKVTreeInfoerNoAPI<A>(exts, std::move(fn), true, sl));
    }


    template <SomeAsset A> 
    class Asset::TypedKVTreeLoader : public Asset::KVTreeLoader {
    public:
        using FN    = std::function<A*(const KVTree&, const AssetLoadAPI&)>;
        
        TypedKVTreeLoader(string_view_initializer_list_t exts, FN&& fn, bool recursive, const std::source_location& sl) :
            KVTreeLoader(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedKVTreeLoader()
        {
        }

        Asset* load(const KVTree& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const KVTree&, const AssetLoadAPI&)>&&fn, const std::source_location& sl)
    {
        add_loader(new TypedKVTreeLoader<A>(exts, std::move(fn), false, sl));
    }
    
    template <SomeAsset A>
    void         Asset::add_loader(string_view_initializer_list_t exts, recursive_k, std::function<A*(const KVTree&, const AssetLoadAPI&)>&&fn, const std::source_location& sl)
    {
        add_loader(new TypedKVTreeLoader<A>(exts, std::move(fn), true, sl));
    }
    

    template <SomeAsset A> 
    class Asset::TypedKVTreeLoaderNoAPI : public Asset::KVTreeLoader {
    public:
        using FN    = std::function<A*(const KVTree&)>;
    
        TypedKVTreeLoaderNoAPI(string_view_initializer_list_t exts, FN&& fn, bool recursive, const std::source_location& sl) :
            KVTreeLoader(meta<A>(), exts, recursive, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedKVTreeLoaderNoAPI()
        {
        }

        Asset* info(const KVTree& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const KVTree&)>&&fn, const std::source_location& sl) 
    {
        add_loader(new TypedKVTreeLoaderNoAPI<A>(exts, std::move(fn), false, sl));
    }
    
    template <SomeAsset A>
    void    Asset::add_loader(string_view_initializer_list_t exts, recursive_k, std::function<A*(const KVTree&)>&&fn, const std::source_location& sl) 
    {
        add_loader(new TypedKVTreeLoaderNoAPI<A>(exts, std::move(fn), true, sl));
    }

    template <SomeAsset A> 
    class Asset::TypedKVTreeSaver : public KVTreeSaver {
    public:
    
        using FN    = std::function<std::error_code(const A&, KVTree&, const AssetSaveAPI&)>;

        TypedKVTreeSaver(string_view_initializer_list_t exts, FN&& fn, bool recurse, const std::source_location& sl) :
            KVTreeSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedKVTreeSaver()
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
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, KVTree&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedKVTreeSaver<A>(exts, std::move(fn), sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedKVTreeSaverNoAPI : public KVTreeSaver {
        using FN    = std::function<std::error_code(const A&, KVTree&)>;

        TypedKVTreeSaverNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            ByteSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedKVTreeSaverNoAPI()
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
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, KVTree&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedKVTreeSaverNoAPI<A>(exts, std::move(fn), sl));
    }
}
