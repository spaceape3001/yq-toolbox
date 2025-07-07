////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "StreamDriver.hpp"
#include <yq/errors.hpp>

namespace yq {
    template <SomeAsset A> 
    class Asset::TypedStreamInfoer : public Asset::StreamInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(std::istream&, const AssetInfoAPI&)>;
    
        TypedStreamInfoer(string_view_initializer_list_t exts, FN&& fn, bool binary, const std::source_location& sl) :
            StreamInfoer(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }
        
        ~TypedStreamInfoer()
        {
        }

        AssetInfo* info(std::istream& file, const AssetInfoAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(std::istream&, const AssetInfoAPI&)>&&fn, const std::source_location& sl)
    {
        add_infoer(new TypedStreamInfoer<A>(exts, std::move(fn), false, sl));
    }
    
    template <SomeAsset A>
    void         Asset::add_infoer(string_view_initializer_list_t exts, binary_k, std::function<typename A::MyInfo*(std::istream&, const AssetInfoAPI&)>&&fn, const std::source_location& sl)
    {
        add_infoer(new TypedStreamInfoer<A>(exts, std::move(fn), true, sl));
    }
    

    template <SomeAsset A> 
    class Asset::TypedStreamInfoerNoAPI : public Asset::StreamInfoer {
    public:
        using FN    = std::function<typename A::MyInfo*(std::istream&)>;
    
        TypedStreamInfoerNoAPI(string_view_initializer_list_t exts, FN&& fn, bool binary, const std::source_location& sl) :
            StreamInfoer(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }
        
        ~TypedStreamInfoerNoAPI()
        {
        }

        AssetInfo* info(std::istream& file, const AssetInfoAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(std::istream&)>&&fn, const std::source_location& sl) 
    {
        add_infoer(new TypedStreamInfoerNoAPI<A>(exts, std::move(fn), false, sl));
    }

    template <SomeAsset A>
    void    Asset::add_infoer(string_view_initializer_list_t exts, binary_k, std::function<typename A::MyInfo*(std::istream&)>&&fn, const std::source_location& sl) 
    {
        add_infoer(new TypedStreamInfoerNoAPI<A>(exts, std::move(fn), true, sl));
    }

    template <SomeAsset A> 
    class Asset::TypedStreamLoader : public Asset::StreamLoader {
    public:
        using FN    = std::function<A*(std::istream&, const AssetLoadAPI&)>;
        
        TypedStreamLoader(string_view_initializer_list_t exts, FN&& fn, bool binary, const std::source_location& sl) :
            StreamLoader(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }
        
        ~TypedStreamLoader()
        {
        }

        Asset* load(std::istream& file, const AssetLoadAPI& api) const override
        {
            return m_function(file, api);
        }
        
    private:
        FN          m_function;
    };

    template <SomeAsset A>
    void         Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(std::istream&, const AssetLoadAPI&)>&&fn, const std::source_location& sl)
    {
        add_loader(new TypedStreamLoader<A>(exts, std::move(fn), false, sl));
    }
    
    template <SomeAsset A>
    void         Asset::add_loader(string_view_initializer_list_t exts, binary_k, std::function<A*(std::istream&, const AssetLoadAPI&)>&&fn, const std::source_location& sl)
    {
        add_loader(new TypedStreamLoader<A>(exts, std::move(fn), true, sl));
    }

    template <SomeAsset A> 
    class Asset::TypedStreamLoaderNoAPI : public Asset::StreamLoader {
    public:
        using FN    = std::function<A*(std::istream&)>;
    
        TypedStreamLoaderNoAPI(string_view_initializer_list_t exts, FN&& fn, bool binary, const std::source_location& sl) :
            StreamLoader(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }
        
        ~TypedStreamLoaderNoAPI()
        {
        }

        Asset* info(std::istream& file, const AssetLoadAPI&) const override
        {
            return m_function(file);
        }
        
    private:
        FN          m_function;
    };
    
    template <SomeAsset A>
    void    Asset::add_loader(string_view_initializer_list_t exts, std::function<A*(std::istream&)>&&fn, const std::source_location& sl) 
    {
        add_loader(new TypedStreamLoaderNoAPI<A>(exts, std::move(fn), false, sl));
    }
    
    template <SomeAsset A>
    void    Asset::add_loader(string_view_initializer_list_t exts, binary_k, std::function<A*(std::istream&)>&&fn, const std::source_location& sl) 
    {
        add_loader(new TypedStreamLoaderNoAPI<A>(exts, std::move(fn), true, sl));
    }
    
////////////////////////////////////////////////////////////////////////////////

    template <SomeAsset A> 
    class Asset::TypedStreamSaver : public StreamSaver {
    public:
    
        using FN    = std::function<std::error_code(const A&, std::ostream&, const AssetSaveAPI&)>;

        TypedStreamSaver(string_view_initializer_list_t exts, FN&& fn, bool binary, const std::source_location& sl) :
            StreamSaver(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }

        ~TypedStreamSaver()
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
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, std::ostream&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedStreamSaver<A>(exts, std::move(fn), false, sl));
    }
        
    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, binary_k, std::function<std::error_code(const A&, std::ostream&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedStreamSaver<A>(exts, std::move(fn), true, sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedStreamSaverNoAPI : public StreamSaver {
        using FN    = std::function<std::error_code(const A&, std::ostream&)>;

        TypedStreamSaverNoAPI(string_view_initializer_list_t exts, FN&& fn, bool binary, const std::source_location& sl) :
            StreamSaver(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }

        ~TypedStreamSaverNoAPI()
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
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, std::ostream&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedStreamSaverNoAPI<A>(exts, std::move(fn), false, sl));
    }

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, binary_k, std::function<std::error_code(const A&, std::ostream&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedStreamSaverNoAPI<A>(exts, std::move(fn), true, sl));
    }


    template <SomeAsset A> 
    class Asset::TypedStreamSaverBool : public StreamSaver {
    public:
    
        using FN    = std::function<bool(const A&, std::ostream&, const AssetSaveAPI&)>;

        TypedStreamSaverBool(string_view_initializer_list_t exts, FN&& fn, bool binary, const std::source_location& sl) :
            StreamSaver(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }

        ~TypedStreamSaverBool()
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
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<bool(const A&, std::ostream&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedStreamSaverBool<A>(exts, std::move(fn), false, sl));
    }
        
    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, binary_k, std::function<bool(const A&, std::ostream&, const AssetSaveAPI&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedStreamSaverBool<A>(exts, std::move(fn), true, sl));
    }
        
    
    template <SomeAsset A> 
    class Asset::TypedStreamSaverBoolNoAPI : public StreamSaver {
        using FN    = std::function<bool(const A&, std::ostream&)>;

        TypedStreamSaverBoolNoAPI(string_view_initializer_list_t exts, FN&& fn, bool binary, const std::source_location& sl) :
            StreamSaver(meta<A>(), exts, sl, binary), m_function(std::move(fn))
        {
        }

        ~TypedStreamSaverBoolNoAPI()
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
        FN          m_function;
    };

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, std::function<bool(const A&, std::ostream&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedStreamSaverBoolNoAPI<A>(exts, std::move(fn), false, sl));
    }

    template <SomeAsset A>
    void    Asset::add_saver(string_view_initializer_list_t exts, binary_k, std::function<bool(const A&, std::ostream&)>&&fn, const std::source_location& sl)
    {
        add_saver(new TypedStreamSaverBoolNoAPI<A>(exts, std::move(fn), true, sl));
    }
}
