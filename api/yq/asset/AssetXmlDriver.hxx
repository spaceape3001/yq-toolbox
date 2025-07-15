////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AssetXmlDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A, typename Pred> 
    class TypedAssetXmlInfoer : public AssetXmlInfoer {
    public:
        TypedAssetXmlInfoer(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetXmlInfoer(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetXmlInfoer()
        {
        }

        AssetInfo* info(const XmlDocument& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetXmlInfoerNoAPI : public AssetXmlInfoer {
    public:
        TypedAssetXmlInfoerNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetXmlInfoer(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetXmlInfoerNoAPI()
        {
        }

        AssetInfo* info(const XmlDocument& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
    template <SomeAsset A, typename Pred> 
    class TypedAssetXmlLoader : public AssetXmlLoader {
    public:
        TypedAssetXmlLoader(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetXmlLoader(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetXmlLoader()
        {
        }

        Asset* load(const XmlDocument& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetXmlLoaderNoAPI : public AssetXmlLoader {
    public:
        TypedAssetXmlLoaderNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetXmlLoader(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetXmlLoaderNoAPI()
        {
        }

        Asset* info(const XmlDocument& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };

////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A, typename Pred> 
    class TypedAssetXmlSaver : public AssetXmlSaver {
    public:
        TypedAssetXmlSaver(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetXmlSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedAssetXmlSaver()
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
        Pred          m_function;
    };
    
    template <SomeAsset A, typename Pred> 
    class TypedAssetXmlSaverNoAPI : public AssetXmlSaver {
        TypedAssetXmlSaverNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetXmlSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedAssetXmlSaverNoAPI()
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
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetXmlSaverBool : public AssetXmlSaver {
    public:
    
        TypedAssetXmlSaverBool(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetXmlSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedAssetXmlSaverBool()
        {
        }

        std::error_code  save(const Asset& asset, XmlDocument& fp, const AssetSaveAPI& api) const override
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
    class TypedAssetXmlSaverBoolNoAPI : public AssetXmlSaver {
        TypedAssetXmlSaverBoolNoAPI(const string_vector_t& exts, Pred&& fn, const std::source_location& sl) :
            AssetXmlSaver(meta<A>(), exts, sl, Type::file), m_function(std::move(fn))
        {
        }

        ~TypedAssetXmlSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, XmlDocument& fp, const AssetSaveAPI&) const override
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
