////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/core/Flags.hpp>
#include <yq/core/Object.hpp>
#include <yq/core/UniqueID.hpp>
#include <yq/core/Ref.hpp>
#include <yq/container/Set.hpp>
#include <yq/file/SizeTimestamp.hpp>
#include <yq/net/Url.hpp>
#include <yq/typedef/asset.hpp>

#include <atomic>
#include <filesystem>
#include <system_error>

namespace yq {
    class FileResolver;
    class AssetLibraryInfo;

    /*! \brief General asset information
    
        This is the information to the particular asset.
    */
    class AssetInfo : public ObjectInfo {
    public:
        //! Writer of asset information 
        //! \note This is to be used during initialization
        //! \tparam C class being written to
        template <typename C> class Writer;

        //! Constructor of asset info, used by the meta system to initialize the thing (so... don't need to call this outside of that context)
        AssetInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl=std::source_location::current());
        
        //! Loads the asset from native binary format (whatever that is)
        //virtual Ref<Asset>  load_binary(const std::filesystem::path&) { return nullptr; }
        
        //! Gets the factory for this asset type
        //! \note Don't DELETE the pointer!
        virtual AssetFactory*   factory() const { return nullptr; }
        
        //! Uses the factory to do a load of the specified file/partial path of the asset
        virtual AssetCPtr       load(std::string_view) const { return {}; }
        
        const std::vector<const AssetLibraryInfo*>& libraries() const { return m_libraries; }
        
    protected:
        std::vector<const AssetLibraryInfo*>    m_libraries;
    };
    
    /*! \brief An asset of the graphics engine
    
        An asset (here) is something that can be loaded by the engine, and used in some predefined fashion.  
        (ie, texture, shader, sounds, etc)  
        
        \note Some overlap with  the asset-library also exists, predefined cameras & shapes -- TBD
        
        \note Once an asset has been sent to the rest of the system, it's presumed to be READ-ONLY.  
            Any further modifications shall require a clone and modifications of THAT
        
    */
    class Asset : public Object, public UniqueID, public RefCount {
    public:
        template <typename C> class Fixer;

    private:
        YQ_OBJECT_INFO(AssetInfo)
        YQ_OBJECT_FIXER(Fixer)
        YQ_OBJECT_DECLARE(Asset, Object)
    public:

        //! Current data size
        virtual size_t                  data_size() const = 0;
        
        //! Only works if cached, otherwise empty
        std::filesystem::path           filepath() const;
        
        //! Only works if cached, otherwise empty
        const Url&                      url() const { return m_url; }
        
        //! Saves data to native binary format (whatever that is)
        //virtual bool        save_binary(const std::filesystem::path&) const = 0;
        
        //! Add resolver paths
        //! Adds a singular path
        static void  resolver_add_path(const std::filesystem::path&);
        
        //! Can add multiple paths, splits on ';'
        static void  resolver_add_paths(std::string_view);
        
        //! Non-writable reference to the asset system's file resolver (aka search paths)
        static const FileResolver&      resolver();
        
        //! Resolve the given string to a filename
        static std::filesystem::path    resolve(std::string_view);
        static std::filesystem::path    resolve(full_k, std::string_view);
        static std::filesystem::path    resolve(partial_k, std::string_view);
        
        std::error_code                 save_to(const std::filesystem::path&) const;
        std::error_code                 save_to(const std::filesystem::path&, const AssetSaveOptions& options) const;
        
        //std::error_code                 save_to(const Url&) const;
        //std::error_code                 save_to(const Url&, const AssetSaveOptions& options) const;

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
    
        static void init_info();
        
        void    set_url(const std::filesystem::path&);
        void    set_url(const Url&);
        
    
    protected:
        friend class AssetFactory;
        
        Asset();
        [[deprecated]] Asset(const std::filesystem::path&);
        virtual ~Asset();
        
        virtual AssetFactory&       factory() const = 0;
        
    private:
        Url                             m_url;
        
        
        static FileResolver&            _resolver();
    };
}
