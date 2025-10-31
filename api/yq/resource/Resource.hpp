////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/resource/ResourceIO.hpp>
#include <yq/core/Flags.hpp>
#include <yq/core/Object.hpp>
#include <yq/core/UniqueID.hpp>
#include <yq/core/Ref.hpp>
#include <yq/container/Set.hpp>
#include <yq/file/SizeTimestamp.hpp>
#include <yq/net/Url.hpp>
#include <yq/typedef/resource.hpp>
#include <yq/typedef/json.hpp>
#include <yq/typedef/string_initlists.hpp>
#include <yq/typedef/xml.hpp>
#include <iosfwd>

#include <atomic>
#include <filesystem>
#include <system_error>

namespace yq {
    class FileResolver;
    class ResourceLibraryMeta;
    struct KVTree;
    struct KVDocument;
    
    struct ResourceLoadAPI;
    struct ResourceInfoAPI;
    struct ResourceSaveAPI;

    /*! \brief General resource information
    
        This is the information to the particular resource.
    */
    class ResourceMeta : public ObjectMeta {
    public:
        //! Writer of resource information 
        //! \note This is to be used during initialization
        //! \tparam C class being written to
        template <typename C> class Writer;

        //! Constructor of resource info, used by the meta system to initialize the thing (so... don't need to call this outside of that context)
        ResourceMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl=std::source_location::current());

    protected:
        std::vector<const ResourceLibraryMeta*>    m_libraries;

    private:
        friend class Resource;
        virtual ResourceInfo*  createInfo() const { return nullptr; }
    };
    
    #define YQ_RESOURCE_INFO(info) \
        using MyInfo = info;
    
    #define YQ_RESOURCE_META(meta) YQ_OBJECT_META(meta)

    #define YQ_RESOURCE_DECLARE(resource, base)       \
        YQ_OBJECT_DECLARE(resource, base)          \
        public:\
            using IO    = ResourceIO<resource>;
    
    #define YQ_RESOURCE_IMPLEMENT(resource) \
        YQ_OBJECT_IMPLEMENT(resource)
        
    template <typename> class ResourceIO;
    
    /*! \brief Used to declare driver information upon registration
    */
    struct ResourceIOSpec {
        std::vector<std::string>        extensions;
        bool                            binary      = false;
        bool                            recursive   = false;
    };
    
    template <typename> class ResourceFixer;
    
    
    /*! \brief An resource of the graphics engine
    
        An resource (here) is something that can be loaded by the engine, and used in some predefined fashion.  
        (ie, texture, shader, sounds, etc)  
        
        \note Some overlap with the resource-library also exists, predefined cameras & shapes -- TBD
        
        \note Once an resource has been sent to the rest of the system, it's presumed to be READ-ONLY.  
            Any further modifications shall require a clone and modifications of THAT
        
    */
    class Resource : public Object, public UniqueID, public RefCount {
    public:
        template <typename C> class Fixer;

        YQ_OBJECT_META(ResourceMeta)
        YQ_OBJECT_DECLARE(Resource, Object)


    private:
    
        template <typename> friend class ResourceIO;
    public:

        // unfortunately, with all the C++ shennigans, can't make these private...

        //! \note Takes ownership of the pointer (not going the unique_ptr route here...)
        static void         add_infoer(ResourceInfoer*);

        //! \note Takes ownership of the pointer (not going the unique_ptr route here...)
        static void         add_loader(ResourceLoader*);

        //! \note Takes ownership of the pointer (not going the unique_ptr route here...)
        static void         add_saver(ResourceSaver*);


        using MyInfo            = ResourceInfo;
    
        //! Resolve the given string to a filename
        static Url              resolve(std::string_view);
    
        //! Adds library (should be perpetually *FIXED* at this point)
        //! \note INITIALIZATION ONLY AS IT'S NOT THREAD SAFE
        static void             add_library(const ResourceLibraryCPtr&);


        //! Add resolver paths
        //! Adds a singular path
        //! \note INITIALIZATION ONLY AS IT'S NOT THREAD SAFE
        //! \note This does a path search first, to avoid duplicates, means O(N^2) behavior for large counts of paths
        static void             add_path(const std::filesystem::path&);
        
        //! Can add multiple paths, splits on ';'
        //! \note INITIALIZATION ONLY AS IT'S NOT THREAD SAFE
        static void             add_paths(std::string_view);
        
        static std::vector<std::filesystem::path>   all_paths();
        
        //! \note Linear search as we're assuming a short one
        static bool             has_path(const std::filesystem::path&);
   
        //! Gets resource information from the specific resource (short specification)
        static ResourceInfoCPtr    resource_info(std::string_view, const ResourceInfoOptions& options={});
        
        //! Gets resource information from the specific resource (short specification), narrowed down to a specific type
        static ResourceInfoCPtr    resource_info(const ResourceMeta&, std::string_view, const ResourceInfoOptions& options={});

        //! Gets resource information from the specific resource (url)
        static ResourceInfoCPtr    resource_info(const UrlView&, const ResourceInfoOptions& options={});

        //! Gets resource information from the specific resource (url), narrowed down to a specific type
        static ResourceInfoCPtr    resource_info(const ResourceMeta&, const UrlView&, const ResourceInfoOptions& options={});
        
        //! Gets resource information from the specific resource (filepath)
        static ResourceInfoCPtr    resource_info(const std::filesystem::path&, const ResourceInfoOptions& options={});

        //! Gets resource information from the specific resource (filepath), narrowed down to a specific type
        static ResourceInfoCPtr    resource_info(const ResourceMeta&, const std::filesystem::path&, const ResourceInfoOptions& options={});
    
        //! Loads from the specific library
        static ResourceInfoCPtr    resource_info(const std::filesystem::path&, std::string_view, const ResourceInfoOptions& options={});

        //! Loads from the specific library
        static ResourceInfoCPtr    resource_info(const ResourceMeta&, const std::filesystem::path&, std::string_view, const ResourceInfoOptions& options={});


        //! Common, loads from the short specification
        static ResourceCPtr        resource_load(std::string_view, const ResourceLoadOptions& options={});

        //! Common, loads from the short specification
        static ResourceCPtr        resource_load(const ResourceMeta&, std::string_view, const ResourceLoadOptions& options={});

        //! Loads from the specific URL
        static ResourceCPtr        resource_load(const UrlView&, const ResourceLoadOptions& options={});

        //! Loads from the specific URL
        static ResourceCPtr        resource_load(const ResourceMeta&, const UrlView&, const ResourceLoadOptions& options={});
        
        //! Loads from the specific file
        static ResourceCPtr        resource_load(const std::filesystem::path&, const ResourceLoadOptions& options={});

        //! Loads from the specific file
        static ResourceCPtr        resource_load(const ResourceMeta&, const std::filesystem::path&, const ResourceLoadOptions& options={});
    
        //! Loads from the specific library
        static ResourceCPtr        resource_load(const std::filesystem::path&, std::string_view, const ResourceLoadOptions& options={});

        //! Loads from the specific library
        static ResourceCPtr        resource_load(const ResourceMeta&, const std::filesystem::path&, std::string_view, const ResourceLoadOptions& options={});
      
            //! Does what it says, wipes the cache
        static void         wipe_cache();

        // TOBD
        struct CacheStats {
        };

        //! Indicates this resource is "read only", usually in the cache and shouldn't be modified (as it'll be thread unsafe to do so)
        bool                            read_only() const { return m_readonly; }


        //! Current data size
        virtual size_t                  data_size() const = 0;

        //! Original file "extension" for our resource
        std::string_view                extension() const;
        
        //! File Path part of the URL (here for compatibility, will be deprecated/removed)
        std::filesystem::path           filepath() const;
        
        //! Injects into the cache (& sets to readonly)
        void                            inject();
        
        //! Only works if cached, otherwise empty
        const Url&                      url() const { return m_url; }
        
        //! Saves data to native binary format (whatever that is)
        //virtual bool        save_binary(const std::filesystem::path&) const = 0;
        
        //! User supplied "name"
        std::string_view                name() const { return m_name; }
        
        //! Resolve the given string to a filename (fully spec'd from the root)
        //! \note This is the preference to use as this will have the best performance (ie... no recursive iterator)
        //static std::filesystem::path    resolve(full_k, std::string_view);
        
        //! Resolve the given string to a partial path 
        //! \note This will be a tad slower as it'll require a recurvsive search
        //static std::filesystem::path    resolve(partial_k, std::string_view);
        
        //! Saves the file to the original URL (if able to)
        std::error_code                 save(const ResourceSaveOptions& options={}) const;

        //! Saves the resource to the specified filename
        std::error_code                 save_to(const std::filesystem::path&, const ResourceSaveOptions& options={}) const;
        
        //! Saves the resource to the specified url (if able)
        std::error_code                 save_to(const UrlView&, const ResourceSaveOptions& options={}) const;


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
        
        //! Sets the url for this resource (readonly disables this)
        void    set_url(const std::filesystem::path&);

        //! Sets the url for this resource (readonly disables this)
        void    set_url(const UrlView&);
        
        //! Sets the resource name (readonly disables this)
        void    set_name(std::string_view);
        
    
        //  INFO... TODO
        //  LIBRARY (somewhat TODO)
    
    protected:
        friend class ResourceMeta;
        friend class ResourceLibraryMeta;
        friend class ResourceLibrary;
        
        Resource();
        virtual ~Resource();
        
        //bool        extract(ResourceInfo&);
        
    private:
        Url                             m_url;      // URL
        bool                            m_readonly  = false;
        std::string                     m_name;
        
        struct Cache;
        static Cache&   cache();

        struct Repo;
        static Repo&    repo();
        
        static ResourceInfoCPtr            _info(const ResourceMeta&, ResourceInfoAPI&);
        static ResourceCPtr                _load(const ResourceMeta&, ResourceLoadAPI&);
        static ResourceCPtr                _load_file(const ResourceMeta&, ResourceLoadAPI&);
        static ResourceCPtr                _load_fragment(const ResourceMeta&, ResourceLoadAPI&);
        static std::error_code          _save(const Resource&, ResourceSaveAPI&);
        static std::error_code          _save_file(const Resource&, ResourceSaveAPI&);
        
    };

    /*! IO Helper to specfic derived resources.  
    
        This is here due to limitations on inheritance and template parameter deduction, it's a one-stop
        for a paraticular resource type.  To access, it's like `Resource::IO::load(whatever)`.
    */
    template <typename A>
    class ResourceIO {
    public:
        static Ref<const typename A::MyInfo> info( std::string_view u, const ResourceInfoOptions& options={})
        {
            ResourceInfoCPtr       ret = Resource::resource_info(meta<A>(), u, options);
            return static_cast<const typename A::MyInfo*>(ret.ptr());
        }
        
        static Ref<const typename A::MyInfo> info( const std::string& u, const ResourceInfoOptions& options={})
        {
            return info( (std::string_view) u, options);
        }
        
        static Ref<const typename A::MyInfo> info( const char* u, const ResourceInfoOptions& options={})
        {
            return info( (std::string_view) u, options);
        }
        
        static Ref<const typename A::MyInfo> info( const std::filesystem::path& u, const ResourceInfoOptions& options={})
        {
            ResourceInfoCPtr       ret = Resource::resource_info(meta<A>(), u, options);
            return static_cast<const typename A::MyInfo*>(ret.ptr());
        }
        
        static Ref<const typename A::MyInfo> info( const UrlView& u, const ResourceInfoOptions& options={})
        {
            ResourceInfoCPtr       ret = Resource::resource_info(meta<A>(), u, options);
            return static_cast<const typename A::MyInfo*>(ret.ptr());
        }

        static Ref<const A> load(std::string_view u, const ResourceLoadOptions& options={})
        {
            ResourceCPtr       ret = Resource::resource_load(meta<A>(), u, options);
            return static_cast<const A*>(ret.ptr());
        }
        
        static Ref<const A> load(const std::string& u, const ResourceLoadOptions& options={})
        {
            return load((std::string_view) u, options);
        }
        
        static Ref<const A> load(const char* u, const ResourceLoadOptions& options={})
        {
            return load((std::string_view) u, options);
        }
        
        static Ref<const A> load(const std::filesystem::path& u, const ResourceLoadOptions& options={})
        {
            ResourceCPtr       ret = Resource::resource_load(meta<A>(), u, options);
            return static_cast<const A*>(ret.ptr());
        }
        
        static Ref<const A> load(const UrlView& u, const ResourceLoadOptions& options={})
        {
            ResourceCPtr       ret = Resource::resource_load(meta<A>(), u, options);
            return static_cast<const A*>(ret.ptr());
        }
        
        ///////////////////////////////////////
        //  These definitions are in Resource.hxx
        
        template <typename Pred>
        static void add_loader(const ResourceIOSpec&, Pred&&, const std::source_location& sl = std::source_location::current());
        
        template <typename Pred>
        static void add_saver(const ResourceIOSpec&, Pred&&, const std::source_location& sl = std::source_location::current());

        template <typename Pred>
        static void add_infoer(const ResourceIOSpec&, Pred&&, const std::source_location& sl = std::source_location::current());
    };
}
