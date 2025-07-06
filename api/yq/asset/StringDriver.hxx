////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "StringDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A> 
    class Asset::TypedStringInfoer : public Asset::StringInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const std::string&, const AssetInfoAPI&)>;
    
        TypedStringInfoer(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            StringInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedStringInfoer()
        {
        }

        AssetInfo* info(const std::string& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const std::string&, const AssetInfoAPI&)>&&fn, const std::source_location& sl)
    {
        add_infoer(new TypedStringInfoer<A>(exts, std::move(fn), sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedStringInfoerNoAPI : public Asset::StringInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const std::string&)>;
    
        TypedStringInfoerNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            StringInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedStringInfoerNoAPI()
        {
        }

        AssetInfo* info(const std::string& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const std::string&)>&&fn, const std::source_location& sl) 
    {
        add_infoer(new TypedStringInfoerNoAPI<A>(exts, std::move(fn), sl));
    }

    template <SomeAsset A> 
    class Asset::TypedStringLoader : public Asset::StringLoader {
    public:
        using FN    = std::function<A*(const std::string&, const AssetLoadAPI&)>;
        
        TypedStringLoader(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            StringLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedStringLoader()
        {
        }

        Asset* load(const std::string& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const std::string&, const AssetLoadAPI&)>&&fn, const std::source_location& sl)
    {
        add_loader(new TypedStringLoader<A>(exts, std::move(fn), sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedStringLoaderNoAPI : public Asset::StringLoader {
    public:
        using FN    = std::function<A*(const std::string&)>;
    
        TypedStringLoaderNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            StringLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedStringLoaderNoAPI()
        {
        }

        Asset* info(const std::string& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const std::string&)>&&fn, const std::source_location& sl) 
    {
        add_loader(new TypedStringLoaderNoAPI<A>(exts, std::move(fn), sl));
    }
    

    template <SomeAsset A> 
    class Asset::TypedStringSaver : public StringSaver {
    public:
    
        using FN    = std::function<std::error_code(const A&, std::string&, const AssetSaveAPI&)>;

        TypedStringSaver(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            StringSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedStringSaver()
        {
        }

        std::error_code  save(const Asset& asset, std::string& str, const AssetSaveAPI& api) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            return m_function(*a, str, api);
        }
        

    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, std::string&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedStringSaver<A>(exts, std::move(fn), sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedStringSaverNoAPI : public StringSaver {
        using FN    = std::function<std::error_code(const A&, std::string&)>;

        TypedStringSaverNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            StringSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedStringSaverNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, std::string& str, const AssetSaveAPI&) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            return m_function(*a, str);
        }
        

    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, std::string&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedStringSaverNoAPI<A>(exts, std::move(fn), sl));
    }
}
