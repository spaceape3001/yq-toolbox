////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "JsonDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A> 
    class Asset::TypedJsonInfoer : public Asset::JsonInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const json&, const AssetInfoAPI&)>;
    
        TypedJsonInfoer(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            JsonInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedJsonInfoer()
        {
        }

        AssetInfo* info(const json& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const json&, const AssetInfoAPI&)>&&fn, const std::source_location& sl)
    {
        add_infoer(new TypedJsonInfoer<A>(exts, std::move(fn), sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedJsonInfoerNoAPI : public Asset::JsonInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const json&)>;
    
        TypedJsonInfoerNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            JsonInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedJsonInfoerNoAPI()
        {
        }

        AssetInfo* info(const json& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const json&)>&&fn, const std::source_location& sl) 
    {
        add_infoer(new TypedJsonInfoerNoAPI<A>(exts, std::move(fn), sl));
    }

    template <SomeAsset A> 
    class Asset::TypedJsonLoader : public Asset::JsonLoader {
    public:
        using FN    = std::function<A*(const json&, const AssetLoadAPI&)>;
        
        TypedJsonLoader(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            JsonLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedJsonLoader()
        {
        }

        Asset* load(const json& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const json&, const AssetLoadAPI&)>&&fn, const std::source_location& sl)
    {
        add_loader(new TypedJsonLoader<A>(exts, std::move(fn), sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedJsonLoaderNoAPI : public Asset::JsonLoader {
    public:
        using FN    = std::function<A*(const json&)>;
    
        TypedJsonLoaderNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            JsonLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedJsonLoaderNoAPI()
        {
        }

        Asset* info(const json& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const json&)>&&fn, const std::source_location& sl) 
    {
        add_loader(new TypedJsonLoaderNoAPI<A>(exts, std::move(fn), sl));
    }
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A> 
    class Asset::TypedJsonSaver : public JsonSaver {
    public:
    
        using FN    = std::function<std::error_code(const A&, json&, const AssetSaveAPI&)>;

        TypedJsonSaver(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            JsonSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedJsonSaver()
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
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, json&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedJsonSaver<A>(exts, std::move(fn), sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedJsonSaverNoAPI : public JsonSaver {
        using FN    = std::function<std::error_code(const A&, json&)>;

        TypedJsonSaverNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            JsonSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedJsonSaverNoAPI()
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
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, json&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedJsonSaverNoAPI<A>(exts, std::move(fn), sl));
    }


    template <SomeAsset A> 
    class Asset::TypedJsonSaverBool : public JsonSaver {
    public:
    
        using FN    = std::function<bool(const A&, json&, const AssetSaveAPI&)>;

        TypedJsonSaverBool(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            JsonSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedJsonSaverBool()
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
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<bool(const A&, json&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedJsonSaverBool<A>(exts, std::move(fn), sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedJsonSaverBoolNoAPI : public JsonSaver {
        using FN    = std::function<bool(const A&, json&)>;

        TypedJsonSaverBoolNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            JsonSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedJsonSaverBoolNoAPI()
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
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<bool(const A&, json&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedJsonSaverBoolNoAPI<A>(exts, std::move(fn), sl));
    }
}
