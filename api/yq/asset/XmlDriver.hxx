////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "XmlDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A> 
    class Asset::TypedXmlInfoer : public Asset::XmlInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const XmlDocument&, const AssetInfoAPI&)>;
    
        TypedXmlInfoer(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            XmlInfoer(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedXmlInfoer()
        {
        }

        AssetInfo* info(const XmlDocument& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const XmlDocument&, const AssetInfoAPI&)>&&fn, const std::source_location& sl)
    {
        add_infoer(new TypedXmlInfoer<A>(exts, std::move(fn), sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedXmlInfoerNoAPI : public Asset::XmlInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const XmlDocument&)>;
    
        TypedXmlInfoerNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            XmlInfoer(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedXmlInfoerNoAPI()
        {
        }

        AssetInfo* info(const XmlDocument& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const XmlDocument&)>&&fn, const std::source_location& sl) 
    {
        add_infoer(new TypedXmlInfoerNoAPI<A>(exts, std::move(fn), sl));
    }

    template <SomeAsset A> 
    class Asset::TypedXmlLoader : public Asset::XmlLoader {
    public:
        using FN    = std::function<A*(const XmlDocument&, const AssetLoadAPI&)>;
        
        TypedXmlLoader(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            XmlLoader(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedXmlLoader()
        {
        }

        Asset* load(const XmlDocument& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const XmlDocument&, const AssetLoadAPI&)>&&fn, const std::source_location& sl)
    {
        add_loader(new TypedXmlLoader<A>(exts, std::move(fn), sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedXmlLoaderNoAPI : public Asset::XmlLoader {
    public:
        using FN    = std::function<A*(const XmlDocument&)>;
    
        TypedXmlLoaderNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            XmlLoader(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedXmlLoaderNoAPI()
        {
        }

        Asset* info(const XmlDocument& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const XmlDocument&)>&&fn, const std::source_location& sl) 
    {
        add_loader(new TypedXmlLoaderNoAPI<A>(exts, std::move(fn), sl));
    }
    

    template <SomeAsset A> 
    class Asset::TypedXmlSaver : public XmlSaver {
    public:
    
        using FN    = std::function<std::error_code(const A&, XmlDocument&, const AssetSaveAPI&)>;

        TypedXmlSaver(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            XmlSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedXmlSaver()
        {
        }

        std::error_code  save(const Asset& asset, XmlDocument& fp, const AssetSaveAPI& api) const override
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
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, XmlDocument&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedXmlSaver<A>(exts, std::move(fn), sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedXmlSaverNoAPI : public XmlSaver {
        using FN    = std::function<std::error_code(const A&, XmlDocument&)>;

        TypedXmlSaverNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            XmlSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedXmlSaverNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, XmlDocument& fp, const AssetSaveAPI&) const override
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
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, XmlDocument&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedXmlSaverNoAPI<A>(exts, std::move(fn), sl));
    }
}
