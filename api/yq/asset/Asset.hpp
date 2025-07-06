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
    
    #define YQ_ASSET_DECLARE(asset, base) \
        YQ_OBJECT_DECLARE(asset, base) \
    public:\
        static Ref<const asset> load(std::string_view u) { return load_as<asset>(u); } \
        static Ref<const asset> load(const std::filesystem::path& u) { return load_as<asset>(u); } \
        static Ref<const asset> load(const UrlView& u) { return load_as<asset>(u); } 
    
    #define YQ_ASSET_IMPLEMENT(asset) YQ_OBJECT_IMPLEMENT(asset)
    
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


    private:
        class Driver;
        class Infoer;
        class Loader;
        class Saver;
        class FileInfoer;
        class FileLoader;
        class FileSaver;
        class StreamInfoer;
        class StreamLoader;
        class StreamSaver;
        class XmlInfoer;
        class XmlLoader;
        class XmlSaver;
        class KVDocumentInfoer;
        class KVDocumentLoader;
        class KVDocumentSaver;
        class KVTreeInfoer;
        class KVTreeLoader;
        class KVTreeSaver;
        class JsonInfoer;
        class JsonLoader;
        class JsonSaver;
        class ByteInfoer;
        class ByteLoader;
        class ByteSaver;
        class StringInfoer;
        class StringLoader;
        class StringSaver;
        
            // these are more likely to be used in a scheme... but here for completeness
        class UrlInfoer;
        class UrlLoader;
        class UrlSaver;

        template <SomeAsset> class TypedByteInfoer;
        template <SomeAsset> class TypedByteInfoerNoAPI;
        template <SomeAsset> class TypedByteLoader;
        template <SomeAsset> class TypedByteLoaderNoAPI;
        template <SomeAsset> class TypedByteSaver;
        template <SomeAsset> class TypedByteSaverNoAPI;

        template <SomeAsset> class TypedFileInfoer;
        template <SomeAsset> class TypedFileInfoerNoAPI;
        template <SomeAsset> class TypedFileLoader;
        template <SomeAsset> class TypedFileLoaderNoAPI;
        template <SomeAsset> class TypedFileSaver;
        template <SomeAsset> class TypedFileSaverNoAPI;

        template <SomeAsset> class TypedJsonInfoer;
        template <SomeAsset> class TypedJsonInfoerNoAPI;
        template <SomeAsset> class TypedJsonLoader;
        template <SomeAsset> class TypedJsonLoaderNoAPI;
        template <SomeAsset> class TypedJsonSaver;
        template <SomeAsset> class TypedJsonSaverNoAPI;

        template <SomeAsset> class TypedKVInfoer;
        template <SomeAsset> class TypedKVInfoerNoAPI;
        template <SomeAsset> class TypedKVLoader;
        template <SomeAsset> class TypedKVLoaderNoAPI;
        template <SomeAsset> class TypedKVSaver;
        template <SomeAsset> class TypedKVSaverNoAPI;

        template <SomeAsset> class TypedKVTreeInfoer;
        template <SomeAsset> class TypedKVTreeInfoerNoAPI;
        template <SomeAsset> class TypedKVTreeLoader;
        template <SomeAsset> class TypedKVTreeLoaderNoAPI;
        template <SomeAsset> class TypedKVTreeSaver;
        template <SomeAsset> class TypedKVTreeSaverNoAPI;

        template <SomeAsset> class TypedKVDocumentInfoer;
        template <SomeAsset> class TypedKVDocumentInfoerNoAPI;
        template <SomeAsset> class TypedKVDocumentLoader;
        template <SomeAsset> class TypedKVDocumentLoaderNoAPI;
        template <SomeAsset> class TypedKVDocumentSaver;
        template <SomeAsset> class TypedKVDocumentSaverNoAPI;

        template <SomeAsset> class TypedStreamInfoer;
        template <SomeAsset> class TypedStreamInfoerNoAPI;
        template <SomeAsset> class TypedStreamLoader;
        template <SomeAsset> class TypedStreamLoaderNoAPI;
        template <SomeAsset> class TypedStreamSaver;
        template <SomeAsset> class TypedStreamSaverNoAPI;

        template <SomeAsset> class TypedStringInfoer;
        template <SomeAsset> class TypedStringInfoerNoAPI;
        template <SomeAsset> class TypedStringLoader;
        template <SomeAsset> class TypedStringLoaderNoAPI;
        template <SomeAsset> class TypedStringSaver;
        template <SomeAsset> class TypedStringSaverNoAPI;

        template <SomeAsset> class TypedUrlInfoer;
        template <SomeAsset> class TypedUrlInfoerNoAPI;
        template <SomeAsset> class TypedUrlLoader;
        template <SomeAsset> class TypedUrlLoaderNoAPI;
        template <SomeAsset> class TypedUrlSaver;
        template <SomeAsset> class TypedUrlSaverNoAPI;

        template <SomeAsset> class TypedXmlInfoer;
        template <SomeAsset> class TypedXmlInfoerNoAPI;
        template <SomeAsset> class TypedXmlLoader;
        template <SomeAsset> class TypedXmlLoaderNoAPI;
        template <SomeAsset> class TypedXmlSaver;
        template <SomeAsset> class TypedXmlSaverNoAPI;

        static void         add_infoer(Infoer*);
        static void         add_loader(Loader*);
        static void         add_saver(Saver*);
        
        YQ_OBJECT_META(AssetMeta)
        YQ_OBJECT_DECLARE(Asset, Object)

    public:
    
        using MyInfo            = AssetInfo;
    
        //! Resolve the given string to a filename
        static Url          resolve(std::string_view);
    
    
        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const std::filesystem::path&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const std::filesystem::path&, const AssetInfoAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const UrlView&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const UrlView&, const AssetInfoAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const ByteArray&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const ByteArray&, const AssetInfoAPI&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const XmlDocument&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const XmlDocument&, const AssetInfoAPI&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const json&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const json&, const AssetInfoAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const KVTree&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, recursive_k, std::function<typename A::MyInfo*(const KVTree&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const KVTree&, const AssetInfoAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, recursive_k, std::function<typename A::MyInfo*(const KVTree&, const AssetInfoAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const KVDocument&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, recursive_k, std::function<typename A::MyInfo*(const KVDocument&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const KVDocument&, const AssetInfoAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, recursive_k, std::function<typename A::MyInfo*(const KVDocument&, const AssetInfoAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(std::istream&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, binary_k, std::function<typename A::MyInfo*(std::istream&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(std::istream&, const AssetInfoAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, binary_k, std::function<typename A::MyInfo*(std::istream&, const AssetInfoAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const std::string&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_infoer(string_view_initializer_list_t exts, std::function<typename A::MyInfo*(const std::string&, const AssetInfoAPI&)>&&, const std::source_location& sl=std::source_location::current());
        
        
        //! Adds library (should be perpetually *FIXED* at this point)
        //! \note INITIALIZATION ONLY AS IT'S NOT THREAD SAFE
        static void         add_library(const AssetLibraryCPtr&);

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const std::filesystem::path&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const std::filesystem::path&, const AssetLoadAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const UrlView&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const UrlView&, const AssetLoadAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const ByteArray&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const ByteArray&, const AssetLoadAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const XmlDocument&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const XmlDocument&, const AssetLoadAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const json&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const json&, const AssetLoadAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const KVDocument&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, recursive_k, std::function<A*(const KVDocument&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const KVDocument&, const AssetLoadAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, recursive_k, std::function<A*(const KVDocument&, const AssetLoadAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const KVTree&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, recursive_k, std::function<A*(const KVTree&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const KVTree&, const AssetLoadAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, recursive_k, std::function<A*(const KVTree&, const AssetLoadAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const std::string&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(const std::string&, const AssetLoadAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(std::istream&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, binary_k, std::function<A*(std::istream&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, std::function<A*(std::istream&, const AssetLoadAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void         add_loader(string_view_initializer_list_t exts, binary_k, std::function<A*(std::istream&, const AssetLoadAPI&)>&&, const std::source_location& sl=std::source_location::current());


        //! Add resolver paths
        //! Adds a singular path
        //! \note INITIALIZATION ONLY AS IT'S NOT THREAD SAFE
        static void             add_path(const std::filesystem::path&);
        
        //! Can add multiple paths, splits on ';'
        //! \note INITIALIZATION ONLY AS IT'S NOT THREAD SAFE
        static void             add_paths(std::string_view);
        



        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, const std::filesystem::path&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, const std::filesystem::path&, const AssetSaveAPI&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, const UrlView&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, const UrlView&, const AssetSaveAPI&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, ByteArray&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, ByteArray&, const AssetSaveAPI&)>&&, const std::source_location& sl=std::source_location::current());
    
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, XmlDocument&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, XmlDocument&, const AssetSaveAPI&)>&&, const std::source_location& sl=std::source_location::current());
    
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, json&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, json&, const AssetSaveAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, KVDocument&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, KVDocument&, const AssetSaveAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, KVTree&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, KVTree&, const AssetSaveAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, std::string&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, std::string&, const AssetSaveAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, std::ostream&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, binary_k, std::function<std::error_code(const A&, std::ostream&)>&&, const std::source_location& sl=std::source_location::current());
        
        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, std::function<std::error_code(const A&, std::ostream&, const AssetSaveAPI&)>&&, const std::source_location& sl=std::source_location::current());

        template <SomeAsset A>
        static void             add_saver(string_view_initializer_list_t exts, binary_k, std::function<std::error_code(const A&, std::ostream&, const AssetSaveAPI&)>&&, const std::source_location& sl=std::source_location::current());


        static AssetInfoCPtr    info(std::string_view);
        
        static AssetInfoCPtr    info(const AssetMeta&, std::string_view);

        static AssetInfoCPtr    info(const UrlView&);

        //! Loads from the specific URL
        static AssetInfoCPtr    info(const AssetMeta&, const UrlView&);
        
        //! Loads from the specific file
        static AssetInfoCPtr    info(const std::filesystem::path&);

        //! Loads from the specific file
        static AssetInfoCPtr    info(const AssetMeta&, const std::filesystem::path&);
    
        //! Loads from the specific library
        static AssetInfoCPtr    info(const std::filesystem::path&, std::string_view);

        //! Loads from the specific library
        static AssetInfoCPtr    info(const AssetMeta&, const std::filesystem::path&, std::string_view);



        //! Common, loads from the short specification
        static AssetCPtr        load(std::string_view);

        //! Common, loads from the short specification
        static AssetCPtr        load(const AssetMeta&, std::string_view);

        //! Loads from the specific URL
        static AssetCPtr        load(const UrlView&);

        //! Loads from the specific URL
        static AssetCPtr        load(const AssetMeta&, const UrlView&);
        
        //! Loads from the specific file
        static AssetCPtr        load(const std::filesystem::path&);

        //! Loads from the specific file
        static AssetCPtr        load(const AssetMeta&, const std::filesystem::path&);
    
        //! Loads from the specific library
        static AssetCPtr        load(const std::filesystem::path&, std::string_view);

        //! Loads from the specific library
        static AssetCPtr        load(const AssetMeta&, const std::filesystem::path&, std::string_view);
        
        template <SomeAsset A>
        static Ref<const A>     load_as(std::string_view);

        template <SomeAsset A>
        static Ref<const A>     load_as(const UrlView&);
        
        template <SomeAsset A>
        static Ref<const A>     load_as(const std::filesystem::path&);
        

        //! Common, loads from the short specification
        static AssetCPtr        reload(std::string_view);

        //! Common, loads from the short specification
        static AssetCPtr        reload(const AssetMeta&, std::string_view);

        //! Loads from the specific URL
        static AssetCPtr        reload(const UrlView&);

        //! Loads from the specific URL
        static AssetCPtr        reload(const AssetMeta&, const UrlView&);
        
        //! Loads from the specific file
        static AssetCPtr        reload(const std::filesystem::path&);

        //! Loads from the specific file
        static AssetCPtr        reload(const AssetMeta&, const std::filesystem::path&);
    
        //! Loads from the specific library
        static AssetCPtr        reload(const std::filesystem::path&, std::string_view);

        //! Loads from the specific library
        static AssetCPtr        reload(const AssetMeta&, const std::filesystem::path&, std::string_view);


            //! Resolves & loads w/o cache
        static AssetCPtr        sload(std::string_view);

            //! Resolves & loads w/o cache
        static AssetCPtr        sload(const AssetMeta&, std::string_view);

            //! Resolves & loads w/o cache
        static AssetCPtr        sload(const UrlView&);

            //! Resolves & loads w/o cache
        static AssetCPtr        sload(const AssetMeta&, const UrlView&);

            //! Loads from the specific file w/o cache
        static AssetCPtr        sload(const std::filesystem::path&);

            //! Loads from the specific file w/o cache
        static AssetCPtr        sload(const AssetMeta&, const std::filesystem::path&);
    
            //! Loads from the specific library/sub-component w/o cache
        static AssetCPtr        sload(const std::filesystem::path&, std::string_view);

            //! Loads from the specific library/sub-component w/o cache
        static AssetCPtr        sload(const AssetMeta&, const std::filesystem::path&, std::string_view);



            //! Does what it says, wipes the cache
        static void         wipe_cache();

        // TOBD
        struct CacheStats {
        };



    
    
    
    


        //! Current data size
        virtual size_t                  data_size() const = 0;
        
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
        
        std::error_code                 save_to(const std::filesystem::path&) const;
        std::error_code                 save_to(const std::filesystem::path&, const AssetSaveOptions& options) const;
        
        std::error_code                 save_to(const Url&) const;
        std::error_code                 save_to(const Url&, const AssetSaveOptions& options) const;

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
        
        struct Cache;
        static Cache&   cache();

        struct Repo;
        static Repo&    repo();
        
        enum class CacheOption : uint8_t {
            Auto,
            ForcedLoad,
            NoCache
        };
        
        static AssetInfoCPtr            _info(const AssetMeta&, const UrlView&, CacheOption autoCache=CacheOption::Auto);
        static AssetCPtr                _load(const AssetMeta&, const UrlView&, CacheOption autoCache=CacheOption::Auto);
        static std::error_code          _save(const Asset&, const Url&, const AssetSaveOptions& options);
        
    };

    template <SomeAsset A>
    Ref<const A> Asset::load_as(std::string_view u)
    {
        return static_cast<const A*>(load(meta<A>(), u));
    }
    
    template <SomeAsset A>
    static Ref<const A> load_as(const UrlView&u)
    {
        return static_cast<const A*>(load(meta<A>(), u));
    }
    
    template <SomeAsset A>
    static Ref<const A> load_as(const std::filesystem::path& fp)
    {
        return static_cast<const A*>(load(meta<A>(), fp));
    }
}
