////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/asset/AssetIO.hpp>
#include <yq/core/Flags.hpp>
#include <yq/core/Object.hpp>
#include <yq/core/UniqueID.hpp>
#include <yq/core/Ref.hpp>
#include <yq/container/Set.hpp>
#include <yq/file/SizeTimestamp.hpp>
#include <yq/net/Url.hpp>
#include <yq/typedef/asset.hpp>
#include <yq/typedef/json.hpp>
#include <yq/typedef/string_initlists.hpp>
#include <yq/typedef/xml.hpp>
#include <iosfwd>

#include <atomic>
#include <filesystem>
#include <system_error>

namespace yq {
    class FileResolver;
    class AssetLibraryMeta;
    struct KVTree;
    struct KVDocument;
    
    struct AssetLoadAPI;
    struct AssetInfoAPI;
    struct AssetSaveAPI;

    /*! \brief General asset information
    
        This is the information to the particular asset.
    */
    class AssetMeta : public ObjectMeta {
    public:
        //! Writer of asset information 
        //! \note This is to be used during initialization
        //! \tparam C class being written to
        template <typename C> class Writer;

        //! Constructor of asset info, used by the meta system to initialize the thing (so... don't need to call this outside of that context)
        AssetMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl=std::source_location::current());
        
    protected:
        std::vector<const AssetLibraryMeta*>    m_libraries;
    };
    
    #define YQ_ASSET_INFO(info) \
        using MyInfo = info;
    
    #define YQ_ASSET_DECLARE(asset, base)       \
        YQ_OBJECT_DECLARE(asset, base)          \
        public:\
            using IO    = Asset::IO<asset>;
    
    #define YQ_ASSET_IMPLEMENT(asset) \
        YQ_OBJECT_IMPLEMENT(asset)
    
    class AssetInfo : public Object, public RefCount {
        YQ_OBJECT_DECLARE(AssetInfo, Object)
        
        friend class Asset;
    public:
        
        const Url&  url() const { return m_url; }
    
        static void init_meta();
    
    protected:
        AssetInfo();
        virtual ~AssetInfo();
    
    private:
        Url     m_url;
    
    };
    
    struct AssetIOSpec {
        string_view_initializer_list_t  extensions;
        bool                            binary      = false;
        bool                            recursive   = false;
    };
    
    
    /*! \brief An asset of the graphics engine
    
        An asset (here) is something that can be loaded by the engine, and used in some predefined fashion.  
        (ie, texture, shader, sounds, etc)  
        
        \note Some overlap with the asset-library also exists, predefined cameras & shapes -- TBD
        
        \note Once an asset has been sent to the rest of the system, it's presumed to be READ-ONLY.  
            Any further modifications shall require a clone and modifications of THAT
        
    */
    class Asset : public Object, public UniqueID, public RefCount {
    public:
        template <typename C> class Fixer;

        YQ_OBJECT_META(AssetMeta)
        YQ_OBJECT_DECLARE(Asset, Object)


    private:

        //! \note Takes ownership of the pointer (not going the unique_ptr route here...)
        static void         add_infoer(AssetInfoer*);

        //! \note Takes ownership of the pointer (not going the unique_ptr route here...)
        static void         add_loader(AssetLoader*);

        //! \note Takes ownership of the pointer (not going the unique_ptr route here...)
        static void         add_saver(AssetSaver*);

    public:

        template <SomeAsset> class IO;
    
        using MyInfo            = AssetInfo;
    
        //! Resolve the given string to a filename
        static Url              resolve(std::string_view);
    
        //! Adds library (should be perpetually *FIXED* at this point)
        //! \note INITIALIZATION ONLY AS IT'S NOT THREAD SAFE
        static void             add_library(const AssetLibraryCPtr&);


        //! Add resolver paths
        //! Adds a singular path
        //! \note INITIALIZATION ONLY AS IT'S NOT THREAD SAFE
        static void             add_path(const std::filesystem::path&);
        
        //! Can add multiple paths, splits on ';'
        //! \note INITIALIZATION ONLY AS IT'S NOT THREAD SAFE
        static void             add_paths(std::string_view);
   
        static AssetInfoCPtr    asset_load(info_k, std::string_view, const AssetInfoOptions& options={});
        
        static AssetInfoCPtr    asset_load(info_k, const AssetMeta&, std::string_view, const AssetInfoOptions& options={});

        static AssetInfoCPtr    asset_load(info_k, const UrlView&, const AssetInfoOptions& options={});

        //! Loads from the specific URL
        static AssetInfoCPtr    asset_load(info_k, const AssetMeta&, const UrlView&, const AssetInfoOptions& options={});
        
        //! Loads from the specific file
        static AssetInfoCPtr    asset_load(info_k, const std::filesystem::path&, const AssetInfoOptions& options={});

        //! Loads from the specific file
        static AssetInfoCPtr    asset_load(info_k, const AssetMeta&, const std::filesystem::path&, const AssetInfoOptions& options={});
    
        //! Loads from the specific library
        static AssetInfoCPtr    asset_load(info_k, const std::filesystem::path&, std::string_view, const AssetInfoOptions& options={});

        //! Loads from the specific library
        static AssetInfoCPtr    asset_load(info_k, const AssetMeta&, const std::filesystem::path&, std::string_view, const AssetInfoOptions& options={});


        //! Common, loads from the short specification
        static AssetCPtr        asset_load(std::string_view, const AssetLoadOptions& options={});

        //! Common, loads from the short specification
        static AssetCPtr        asset_load(const AssetMeta&, std::string_view, const AssetLoadOptions& options={});

        //! Loads from the specific URL
        static AssetCPtr        asset_load(const UrlView&, const AssetLoadOptions& options={});

        //! Loads from the specific URL
        static AssetCPtr        asset_load(const AssetMeta&, const UrlView&, const AssetLoadOptions& options={});
        
        //! Loads from the specific file
        static AssetCPtr        asset_load(const std::filesystem::path&, const AssetLoadOptions& options={});

        //! Loads from the specific file
        static AssetCPtr        asset_load(const AssetMeta&, const std::filesystem::path&, const AssetLoadOptions& options={});
    
        //! Loads from the specific library
        static AssetCPtr        asset_load(const std::filesystem::path&, std::string_view, const AssetLoadOptions& options={});

        //! Loads from the specific library
        static AssetCPtr        asset_load(const AssetMeta&, const std::filesystem::path&, std::string_view, const AssetLoadOptions& options={});
      
            //! Does what it says, wipes the cache
        static void         wipe_cache();

        // TOBD
        struct CacheStats {
        };


        bool                            read_only() const { return m_readonly; }


        //! Current data size
        virtual size_t                  data_size() const = 0;
        
        std::string_view                extension() const;
        
        //! File Path part of the URL (here for compatibility, will be deprecated/removed)
        std::filesystem::path           filepath() const;
        
        //! Injects into the cache (& sets to readonly)
        void                            inject();
        
        //! Only works if cached, otherwise empty
        const Url&                      url() const { return m_url; }
        
        //! Saves data to native binary format (whatever that is)
        //virtual bool        save_binary(const std::filesystem::path&) const = 0;
        
        
        
        //! Resolve the given string to a filename (fully spec'd from the root)
        //! \note This is the preference to use as this will have the best performance (ie... no recursive iterator)
        //static std::filesystem::path    resolve(full_k, std::string_view);
        
        //! Resolve the given string to a partial path 
        //! \note This will be a tad slower as it'll require a recurvsive search
        //static std::filesystem::path    resolve(partial_k, std::string_view);
        
        //! Saves the file to the original URL (if able to)
        std::error_code                 save(const AssetSaveOptions& options={}) const;

        std::error_code                 save_to(const std::filesystem::path&, const AssetSaveOptions& options={}) const;
        
        std::error_code                 save_to(const UrlView&, const AssetSaveOptions& options={}) const;


        //static const path_vector_t&             search_path();
        //static const std::filesystem::path&     binary_root();
        //static std::filesystem::path            resolve(const std::filesystem::path&);
        //static std::filesystem::path            binary_path(const std::filesystem::path&);
        
        /*! Searches the given vector for the specified file
        
            \note An ABSOLUTE file will auto-return itself.
            
            This first checks the relative against the current working directory, returns if that file exists.
            Otherwise, it'll march through the paths, doing the same check.
        
            \param[in]  paths   Directories to search
            \param[in]  file    Given filepath
            \return filepath if absolute or detected, empty otherwise
        */
        //static std::filesystem::path            search(const path_vector_t& paths, const std::filesystem::path& file);
    
        static void init_meta();
        
        void    set_url(const std::filesystem::path&);
        void    set_url(const UrlView&);
        
    
    protected:
        friend class AssetMeta;
        friend class AssetLibraryMeta;
        
        Asset();
        virtual ~Asset();
        
    private:
        Url                             m_url;      // URL
        bool                            m_readonly  = false;
        
        struct Cache;
        static Cache&   cache();

        struct Repo;
        static Repo&    repo();
        
        static AssetInfoCPtr            _info(const AssetMeta&, AssetInfoAPI&);
        static AssetCPtr                _load(const AssetMeta&, AssetLoadAPI&);
        static AssetCPtr                _load_file(const AssetMeta&, AssetLoadAPI&);
        static AssetCPtr                _load_fragment(const AssetMeta&, AssetLoadAPI&);
        static std::error_code          _save(const Asset&, AssetSaveAPI&);
        static std::error_code          _save_file(const Asset&, AssetSaveAPI&);
        
    };

    template <SomeAsset A>
    class Asset::IO {
    public:
        static Ref<const typename A::MyInfo> load(info_k, std::string_view u, const AssetInfoOptions& options={})
        {
            AssetInfoCPtr       ret = Asset::asset_load(INFO, meta<A>(), u, options);
            return static_cast<const typename A::MyInfo*>(ret.ptr());
        }
        
        static Ref<const typename A::MyInfo> load(info_k, const std::string& u, const AssetInfoOptions& options={})
        {
            return load(INFO, (std::string_view) u, options);
        }
        
        static Ref<const typename A::MyInfo> load(info_k, const char* u, const AssetInfoOptions& options={})
        {
            return load(INFO, (std::string_view) u, options);
        }
        
        static Ref<const typename A::MyInfo> load(info_k, const std::filesystem::path& u, const AssetInfoOptions& options={})
        {
            AssetInfoCPtr       ret = Asset::asset_load(INFO, meta<A>(), u, options);
            return static_cast<const typename A::MyInfo*>(ret.ptr());
        }
        
        static Ref<const typename A::MyInfo> load(info_k, const UrlView& u, const AssetInfoOptions& options={})
        {
            AssetInfoCPtr       ret = Asset::asset_load(INFO, meta<A>(), u, options);
            return static_cast<const typename A::MyInfo*>(ret.ptr());
        }

        static Ref<const A> load(std::string_view u, const AssetLoadOptions& options={})
        {
            AssetCPtr       ret = Asset::asset_load(meta<A>(), u, options);
            return static_cast<const A*>(ret.ptr());
        }
        
        static Ref<const A> load(const std::string& u, const AssetLoadOptions& options={})
        {
            return load((std::string_view) u, options);
        }
        
        static Ref<const A> load(const char* u, const AssetLoadOptions& options={})
        {
            return load((std::string_view) u, options);
        }
        
        static Ref<const A> load(const std::filesystem::path& u, const AssetLoadOptions& options={})
        {
            AssetCPtr       ret = Asset::asset_load(meta<A>(), u, options);
            return static_cast<const A*>(ret.ptr());
        }
        
        static Ref<const A> load(const UrlView& u, const AssetLoadOptions& options={})
        {
            AssetCPtr       ret = Asset::asset_load(meta<A>(), u, options);
            return static_cast<const A*>(ret.ptr());
        }
        
        
        ///////////////////////////////////////
        //  These definitions are in Asset.hxx
        
        template <typename Pred>
        static void add_loader(const AssetIOSpec&, Pred&&, const std::source_location& sl = std::source_location::current());
        
        template <typename Pred>
        static void add_saver(const AssetIOSpec&, Pred&&, const std::source_location& sl = std::source_location::current());

        template <typename Pred>
        static void add_infoer(const AssetIOSpec&, Pred&&, const std::source_location& sl = std::source_location::current());
    };
}
