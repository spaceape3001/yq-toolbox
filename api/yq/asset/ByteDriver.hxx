////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ByteDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A> 
    class Asset::TypedByteInfoer : public Asset::ByteInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const ByteArray&, const AssetInfoAPI&)>;
    
        TypedByteInfoer(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            ByteInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedByteInfoer()
        {
        }

        AssetInfo* info(const ByteArray& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const ByteArray&, const AssetInfoAPI&)>&&fn, const std::source_location& sl)
    {
        add_infoer(new TypedByteInfoer<A>(exts, std::move(fn), sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedByteInfoerNoAPI : public Asset::ByteInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(const ByteArray&)>;
    
        TypedByteInfoerNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            ByteInfoer(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedByteInfoerNoAPI()
        {
        }

        AssetInfo* info(const ByteArray& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const ByteArray&)>&&fn, const std::source_location& sl) 
    {
        add_infoer(new TypedByteInfoerNoAPI<A>(exts, std::move(fn), sl));
    }

    template <SomeAsset A> 
    class Asset::TypedByteLoader : public Asset::ByteLoader {
    public:
        using FN    = std::function<A*(const ByteArray&, const AssetLoadAPI&)>;
        
        TypedByteLoader(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            ByteLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedByteLoader()
        {
        }

        Asset* load(const ByteArray& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const ByteArray&, const AssetLoadAPI&)>&&fn, const std::source_location& sl)
    {
        add_loader(new TypedByteLoader<A>(exts, std::move(fn), sl));
    }
    
    template <SomeAsset A> 
    class Asset::TypedByteLoaderNoAPI : public Asset::ByteLoader {
    public:
        using FN    = std::function<A*(const ByteArray&)>;
    
        TypedByteLoaderNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            ByteLoader(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }
        
        ~TypedByteLoaderNoAPI()
        {
        }

        Asset* info(const ByteArray& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(const ByteArray&)>&&fn, const std::source_location& sl) 
    {
        add_loader(new TypedByteLoaderNoAPI<A>(exts, std::move(fn), sl));
    }
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A> 
    class Asset::TypedByteSaver : public ByteSaver {
    public:
    
        using FN    = std::function<std::error_code(const A&, ByteArray&, const AssetSaveAPI&)>;

        TypedByteSaver(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            ByteSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedByteSaver()
        {
        }

        std::error_code  save(const Asset& asset, ByteArray& bytes, const AssetSaveAPI& api) const override
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
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, ByteArray&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedByteSaver<A>(exts, std::move(fn), sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedByteSaverNoAPI : public ByteSaver {
        using FN    = std::function<std::error_code(const A&, ByteArray&)>;

        TypedByteSaverNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            ByteSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedByteSaverNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, ByteArray& bytes, const AssetSaveAPI&) const override
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
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, ByteArray&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedByteSaverNoAPI<A>(exts, std::move(fn), sl));
    }

    template <SomeAsset A> 
    class Asset::TypedByteSaverBool : public ByteSaver {
    public:
    
        using FN    = std::function<bool(const A&, ByteArray&, const AssetSaveAPI&)>;

        TypedByteSaverBool(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            ByteSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedByteSaverBool()
        {
        }

        std::error_code  save(const Asset& asset, ByteArray& bytes, const AssetSaveAPI& api) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, bytes, api))
                return errors::asset_saving_failed();
            return {};
        }
        

    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<bool(const A&, ByteArray&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedByteSaverBool<A>(exts, std::move(fn), sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedByteSaverBoolNoAPI : public ByteSaver {
        using FN    = std::function<bool(const A&, ByteArray&)>;

        TypedByteSaverBoolNoAPI(string_view_initializer_list_t exts, FN&& fn, const std::source_location& sl) :
            ByteSaver(meta<A>(), exts, sl), m_function(std::move(fn))
        {
        }

        ~TypedByteSaverBoolNoAPI()
        {
        }

        std::error_code  save(const Asset& asset, ByteArray& bytes, const AssetSaveAPI&) const override
        {
            const A*    a   = dynamic_cast<const A*>(&asset);
            if(!a)
                return errors::bad_argument();
            if(!m_function(*a, bytes))
                return errors::asset_saving_failed();
            return {};
        }
        

    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<bool(const A&, ByteArray&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedByteSaverBoolNoAPI<A>(exts, std::move(fn), sl));
    }
}
