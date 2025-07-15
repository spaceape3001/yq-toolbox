////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AssetStreamDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A, typename Pred> 
    class TypedAssetStreamInfoer : public AssetStreamInfoer {
    public:
        //using Pred    = std::function<typename A::MyInfo*(std::istream&, const AssetInfoAPI&)>;
    
        TypedAssetStreamInfoer(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            AssetStreamInfoer(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetStreamInfoer()
        {
        }

        AssetInfo* info(std::istream& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetStreamInfoerNoAPI : public AssetStreamInfoer {
    public:
//        using Pred    = std::function<typename A::MyInfo*(std::istream&)>;
    
        TypedAssetStreamInfoerNoAPI(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            AssetStreamInfoer(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetStreamInfoerNoAPI()
        {
        }

        AssetInfo* info(std::istream& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetStreamLoader : public AssetStreamLoader {
    public:
        //using Pred    = std::function<A*(std::istream&, const AssetLoadAPI&)>;
        
        TypedAssetStreamLoader(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            AssetStreamLoader(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetStreamLoader()
        {
        }

        Asset* load(std::istream& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        Pred          m_function;
    };

    template <SomeAsset A, typename Pred> 
    class TypedAssetStreamLoaderNoAPI : public AssetStreamLoader {
    public:
        //using Pred    = std::function<A*(std::istream&)>;
    
        TypedAssetStreamLoaderNoAPI(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            AssetStreamLoader(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }
        
        ~TypedAssetStreamLoaderNoAPI()
        {
        }

        Asset* info(std::istream& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        Pred          m_function;
    };
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A, typename Pred> 
    class TypedAssetStreamSaver : public AssetStreamSaver {
    public:
    
        //using Pred    = std::function<std::error_code(const A&, std::ostream&, const AssetSaveAPI&)>;

        TypedAssetStreamSaver(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            AssetStreamSaver(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }

        ~TypedAssetStreamSaver()
        {
        }

        std::error_code  save(const Asset& asset, std::ostream& str, const AssetSaveAPI& api) const override
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
    class TypedAssetStreamSaverNoAPI : public AssetStreamSaver {
        //using Pred    = std::function<std::error_code(const A&, std::ostream&)>;

        TypedAssetStreamSaverNoAPI(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            AssetStreamSaver(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }

        ~TypedAssetStreamSaverNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, std::ostream& str, const AssetSaveAPI&) const override
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
    class TypedAssetStreamSaverBool : public AssetStreamSaver {
    public:
    
        //using Pred    = std::function<bool(const A&, std::ostream&, const AssetSaveAPI&)>;

        TypedAssetStreamSaverBool(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            AssetStreamSaver(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }

        ~TypedAssetStreamSaverBool()
        {
        }

        std::error_code  save(const Asset& asset, std::ostream& str, const AssetSaveAPI& api) const override
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

#if 0
    template <SomeAsset A>
    void    Asset::add_saver(const string_vector_t& exts, std::function<bool(const A&, std::ostream&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedAssetStreamSaverBool<A>(exts, std::move(fn), false, sl));
    }
        
    template <SomeAsset A>
    void    Asset::add_saver(const string_vector_t& exts, binary_k, std::function<bool(const A&, std::ostream&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedAssetStreamSaverBool<A>(exts, std::move(fn), true, sl));
    }
#endif
    
    template <SomeAsset A, typename Pred> 
    class TypedAssetStreamSaverBoolNoAPI : public AssetStreamSaver {
        //using Pred    = std::function<bool(const A&, std::ostream&)>;

        TypedAssetStreamSaverBoolNoAPI(const string_vector_t& exts, Pred&& fn, bool binary, const std::source_location& sl) :
            AssetStreamSaver(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }

        ~TypedAssetStreamSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, std::ostream& str, const AssetSaveAPI&) const override
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
