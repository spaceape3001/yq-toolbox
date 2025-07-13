////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/AssetStringDriver.hpp>
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A, typename Pred> 
    class TypedAssetStringInfoer : public AssetStringInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const std::string&, const AssetInfoAPI&)>;
    
        TypedAssetStringInfoer(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetStringInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetStringInfoer()
        {
        }

        AssetInfo* info(const std::string& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };
    
    template <SomeAsset A, typename Pred> 
    class TypedAssetStringInfoerNoAPI : public AssetStringInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(const std::string&)>;
    
        TypedAssetStringInfoerNoAPI(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetStringInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetStringInfoerNoAPI()
        {
        }

        AssetInfo* info(const std::string& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetStringLoader : public AssetStringLoader {
    public:
        //using Pred    = std::function<A*(const std::string&, const AssetLoadAPI&)>;
        
        TypedAssetStringLoader(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetStringLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetStringLoader()
        {
        }

        Asset* load(const std::string& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetStringLoaderNoAPI : public AssetStringLoader {
    public:
        //using Pred    = std::function<A*(const std::string&)>;
    
        TypedAssetStringLoaderNoAPI(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetStringLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetStringLoaderNoAPI()
        {
        }

        Asset* info(const std::string& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A, typename Pred> 
    class TypedAssetStringSaver : public AssetStringSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, std::string&, const AssetSaveAPI&)>;

        TypedAssetStringSaver(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetStringSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetStringSaver()
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
        Pred          m_function;
    };

    
    template <SomeAsset A, typename Pred> 
    class TypedAssetStringSaverNoAPI : public AssetStringSaver {
        //using Pred    = std::function<std::error_code(const A&, std::string&)>;

        TypedAssetStringSaverNoAPI(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetStringSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetStringSaverNoAPI()
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
        Pred          m_function;
    };


    template <SomeAsset A, typename Pred> 
    class TypedAssetStringSaverBool : public AssetStringSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, std::string&, const AssetSaveAPI&)>;

        TypedAssetStringSaverBool(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetStringSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetStringSaverBool()
        {
        }

        std::error_code  save(const Asset& asset, std::string& str, const AssetSaveAPI& api) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, str, api))
                return errors::asset_saving_failed();
            return {};
        }
        

    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetStringSaverBoolNoAPI : public AssetStringSaver {
        //using Pred    = std::function<bool(const A&, std::string&)>;

        TypedAssetStringSaverBoolNoAPI(string_view_initializer_list_t exts, Pred&& fn, const std::source_location& sl) :
            AssetStringSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedAssetStringSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, std::string& str, const AssetSaveAPI&) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, str))
                return errors::asset_saving_failed();
            return {};
        }
        

    private:
        Pred          m_function;
    };
}
