////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/asset/Asset.hpp>
#include <yq/asset/AssetIO.hpp>
#include <yq/asset/AssetCache.hpp>
#include <yq/core/ErrorDB.hpp>
#include <yq/core/Object.hpp>
#include <yq/core/Ref.hpp>
#include <yq/container/Set.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/typedef/string_sets.hpp>
#include <functional>
#include <source_location>
#include <system_error>

namespace yq {
    namespace errors {
        using asset_saving_failed   = error_db::entry<"Unable to save asset">;
    }

    /*! \brief Basic asset factory
    
        This is an asset factory for a specific asset.
    */

    class AssetFactory : public AssetCache {
    public:
        const std::source_location&     source_location() const 
        { 
            return m_source; 
        }
        
        struct Loader;
        struct Saver;

    protected:
        friend class Asset;
        
        AssetFactory(const AssetInfo&, const std::source_location& sl);
        ~AssetFactory();

        //! Loads the specified URL (no resolution)
        AssetCPtr    _load(const Url&, const AssetLoadOptions&);
        
        //! Resolves & loads a partial path
        AssetCPtr    _pload(std::string_view, const AssetLoadOptions&);

        //! Resolves & finds a partial path
        AssetCPtr    _pfind(std::string_view) const;
    
        std::vector<Loader*>        m_loaders;
        std::vector<Saver*>         m_savers;
        const AssetInfo*            m_asset;
    
    private:
        AssetFactory(const AssetFactory&) = delete;
        AssetFactory(AssetFactory&&) = delete;
        AssetFactory& operator=(const AssetFactory&) = delete;
        AssetFactory& operator=(AssetFactory&&) = delete;
        
        std::source_location        m_source;
    };
    
    /*! \brief Base loader
        
        This is a basic file loader
    */
    struct AssetFactory::Loader {
        //! This abstraction loads the data from a filesystem path
        virtual Asset*          load(const Url&, const AssetLoadOptions&) const = 0;
        StringSet               extensions;
        std::source_location    location;
        
        Loader(std::initializer_list<std::string_view> exts, const std::source_location& sl);
    };
    
    /*! \brief Specific asset loader
    
        This binds a specific function based loader to the base loader
    */
    template <typename A> 
    struct AssetLoader_Pointer : public AssetFactory::Loader {
        using Function    = std::function<A*(const std::filesystem::path&)>;
        Function            fn;
        
        AssetLoader_Pointer(Function&& f, std::initializer_list<std::string_view> exts, const std::source_location& sl) :
            AssetFactory::Loader(exts, sl), fn(std::move(f)) {}
        
        //! Adapter to load the resource
        A* load(const Url& p, const AssetLoadOptions&) const override
        {
            return fn(p.path);
        }
    };
    
    /*! \brief Specific asset loader
    
        This binds a specific function based loader to the base loader
    */
    template <typename A> 
    struct AssetLoader_PointerWithOptions : public AssetFactory::Loader {
        using Function    = std::function<A*(const std::filesystem::path&, const AssetLoadOptions&)>;
        Function            fn;
        
        AssetLoader_PointerWithOptions(Function&& f, std::initializer_list<std::string_view> exts, const std::source_location& sl) :
            AssetFactory::Loader(exts, sl), fn(std::move(f)) {}
        
        //! Adapter to load the resource
        A* load(const Url& p, const AssetLoadOptions& options) const override
        {
            return fn(p.path, options);
        }
    };

    struct AssetFactory::Saver {
        virtual std::error_code save(const Asset&, const Url&, const AssetSaveOptions&) const = 0;
        StringSet               extensions;
        std::source_location    location;

        Saver(std::initializer_list<std::string_view> exts, const std::source_location& sl);
    };
    
    template <typename A>
    struct AssetSaver_Bool  : public AssetFactory::Saver {
        using Function  = std::function<bool(const A&, const std::filesystem::path&)>;
        Function fn;
        AssetSaver_Bool(Function&& f, std::initializer_list<std::string_view> exts, const std::source_location& sl) :
            AssetFactory::Saver(exts, sl), fn(std::move(f)) {}
        
        virtual std::error_code save(const Asset& a, const Url& p, const AssetSaveOptions&) const override
        {
            if(!fn(static_cast<const A&>(a), p.path)){
                return errors::asset_saving_failed();
            }
            return {};
        }
    };
    
    template <typename A>
    struct AssetSaver_Error : public AssetFactory::Saver {
        using Function  = std::function<std::error_code(const A&, const std::filesystem::path&)>;
        Function fn;
        AssetSaver_Error(Function&& f, std::initializer_list<std::string_view> exts, const std::source_location& sl) :
            AssetFactory::Saver(exts, sl), fn(std::move(f)) {}
        
        virtual std::error_code            save(const Asset& a, const Url& p, const AssetSaveOptions&) const override
        {
            return fn(static_cast<const A&>(a), p.path);
        }
    };

    template <typename A>
    struct AssetSaver_BoolWithOptions : public AssetFactory::Saver {
        using Function  = std::function<bool(const A&, const std::filesystem::path&, const AssetSaveOptions&)>;
        Function fn;
        AssetSaver_BoolWithOptions(Function&& f, std::initializer_list<std::string_view> exts, const std::source_location& sl) :
            AssetFactory::Saver(exts, sl), fn(std::move(f)) {}
        
        virtual std::error_code save(const Asset& a, const Url& p, const AssetSaveOptions& options) const override
        {
            if(!fn(static_cast<const A&>(a), p.path, options)){
                return errors::asset_saving_failed();
            }
            return {};
        }
    };
    
    template <typename A>
    struct AssetSaver_ErrorWithOptions : public AssetFactory::Saver {
        using Function  = std::function<std::error_code(const A&, const std::filesystem::path&, const AssetSaveOptions&)>;
        Function fn;
        AssetSaver_ErrorWithOptions(Function&& f, std::initializer_list<std::string_view> exts, const std::source_location& sl) :
            AssetFactory::Saver(exts, sl), fn(std::move(f)) {}
        
        virtual std::error_code            save(const Asset& a, const Url& p, const AssetSaveOptions& options) const override
        {
            return fn(static_cast<const A&>(a), p.path, options);
        }
    };


    /*! \brief Specific factory
    
        This binds the specific asset type to the generic underlying asset factory
    */
    template <typename A>
    class TypedAssetFactory : public AssetFactory {
        friend A;
    public:
    
        //! Gets the specific resource (by ID) from the cache (if already loaded)
        Ref<const A>    get(uint64_t i) const
        {
            return static_cast<const A*>(_find(i).ptr());
        }
    
        //! Gets the specific resource (resolved path) from the cache (if already loaded)
        Ref<const A>    getx(const Url& u) const
        {
            return static_cast<const A*>(_find(u).ptr());
        }
        
        Ref<const A>    getx(const std::filesystem::path&p) const
        {
            return getx(to_url(p));
        }

        //! Gets the specific resource (partial path) from the cache (if already loaded)
        Ref<const A>    get(std::string_view p) const
        {
            return static_cast<const A*>(_pfind(p).ptr());
        }
        
        //! Inserts a manually created resource into the factory
        void            insert(Ref<const A> a)
        {
            if(a)
                _insert(a.ptr());
        }

        //! Loads exact path (no resolution)
        Ref<const A>    loadx(const Url&p, const AssetLoadOptions& options={})
        {
            return static_cast<const A*>(_load(p,options).ptr());
        }
        
        Ref<const A>    loadx(const std::filesystem::path&p, const AssetLoadOptions& options={})
        {
            return static_cast<const A*>(_load(to_url(p),options).ptr());
        }

        //! Loads the item
        Ref<const A>    load(std::string_view p, const AssetLoadOptions& options={})
        {
            return static_cast<const A*>(_pload(p,options).ptr());
        }
        
        /*! \brief Adds a loader to the factory
        
            WARNING this is NOT thread-safe.  Do not call outside of startup-initialization!
        */
        void    add_loader(std::initializer_list<std::string_view> exts, std::function<A*(const std::filesystem::path&)>&& fn, const std::source_location& sl=std::source_location::current())
        {
            m_loaders.push_back(new AssetLoader_Pointer<A>(std::move(fn), exts, sl));
        }
        
        void    add_loader(std::initializer_list<std::string_view> exts, std::function<A*(const std::filesystem::path&, const AssetLoadOptions&)>&& fn, const std::source_location& sl=std::source_location::current())
        {
            m_loaders.push_back(new AssetLoader_PointerWithOptions<A>(std::move(fn), exts, sl));
        }

        void    add_saver(std::initializer_list<std::string_view> exts, std::function<bool(const A&, const std::filesystem::path&)>&& fn, const std::source_location& sl=std::source_location::current())
        {
            m_savers.push_back(new AssetSaver_Bool<A>(std::move(fn), exts, sl));
        }
        
        void    add_saver(std::initializer_list<std::string_view> exts, std::function<std::error_code(const A&, const std::filesystem::path&)>&& fn, const std::source_location& sl=std::source_location::current())
        {
            m_savers.push_back(new AssetSaver_Error<A>(std::move(fn), exts, sl));
        }
        
        void    add_saver(std::initializer_list<std::string_view> exts, std::function<bool(const A&, const std::filesystem::path&, const AssetSaveOptions&)>&& fn, const std::source_location& sl=std::source_location::current())
        {
            m_savers.push_back(new AssetSaver_BoolWithOptions<A>(std::move(fn), exts, sl));
        }

        void    add_saver(std::initializer_list<std::string_view> exts, std::function<std::error_code(const A&, const std::filesystem::path&, const AssetSaveOptions&)>&& fn, const std::source_location& sl=std::source_location::current())
        {
            m_savers.push_back(new AssetSaver_ErrorWithOptions<A>(std::move(fn), exts, sl));
        }

    private:
        TypedAssetFactory(const std::source_location& sl = std::source_location::current()) : AssetFactory(meta<A>(), sl)
        {
        }
    
    };
}
