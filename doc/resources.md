#! Resources

Resources (ie resources) are things that represent external/user data needed for the application to run.   Things like images, sounds, meshes, scripts, etc.  

## Resources

Root `Resource` is abstract, and specific resources will derive from this.  So, you'll generally have...

    class MyResourceMeta : public ResourceMeta {
    };
    
    class MyResourceInfo : public ResourceInfo {
    };
    
    class MyResource : public Resource {
        YQ_RESOURCE_META(MyResourceMeta)          // defining meta
        YQ_RESOURCE_INFO(MyResourceInfo)          // defining the info
        YQ_RESOURCE_DECLARE(MyResource, Resource)    // use this one last
    public:
        // My API
    };


## Pathing

For simplicity, all resources use the same search paths.  Specifications are meant to be in FULL (and case sensitive) from this.

### Adding a path

To add a path:

    Resource::add_path("My path");         // adds one directory
    Resource::add_paths("Path1;Path2");    // adds multiple directories (separated by ';')

NOTE: It's legal to submit one path to the `add_paths` method, so for instance, from an environment variable.

In the tachyon library (in the yq-vulqan repository), there is `configure_standand_resource_path()` available in `tachyon/app/Application.hpp`.

Libraries can be added too; however, they should not be subsequently modified!

    ResourceLibraryCPtr        myLibrary;
    Resource::add_library( myLibrary );
    
NOTE: Generic URLs are not yet supported to the pathing, however, the current API should lend itself nicely to adding it in.    
    
### Resolving

Resolving a string is straight forward.  The resource infrastructure will loop through the search paths.  First one to "hit" wins.

#### Filesystem Path

If the search entry is a filesystem path, the string will be treated as a relative path, and tested for existence.  If successful, the result will be `file:${path}/${string}`.

#### Library

If the search entry is a library, the string will be treated as a fragment and tested to the library's contents.  If successful, the result will be `file:${library}#${string}`.

## Libraries

*(Libraries are the general point to resource v2.0)*

A library is a singular file that represents a collection of resources.  (ie, a material library, image library, an object.)

NOTE: Full library support is a TODO... 

## Information

Conceptually, this is information about the resource.  (ie, image dimensions, sound length, approximate number of vertices, etc.)  To get the information, should be as simple as:

    auto info   = MyResource::IO::info("foobar.png");

Resource infrastructure will resolve that string to a URL using the pathing, cycle through available loaders to load it.

## Loading

To load an resource, should be as simple as...

    auto data   = MyResource::IO::load("foobar.png");

## Saving

Saving to local files is generally supported, URLs may be more spotty.  Simple as

    Ref<const MyResource>  data; // gotten somehow
    data -> save( ... full path or URL ... );
    
## Drivers (ie, loaders, savers, infoers)

"Drivers" are standalone bits of code for loading/saving/infoing a particular resource; usually functions.  For flexibility, different function signatures are permitted, and deduced based on the invocation.

With the myresource/source/destination being deduced by the add_loader/infoer/saver routines.

###  Infoers

An infoer is a driver designed to extract information from an resource (and hopefully with less overhead than a full load).  Function signatures are expected to be:

    MyResource::MyInfo* info_resource(${Source});
    MyResource::MyInfo* info_resource(${Source}, const ResourceInfoAPI&);

Do *NOT* ref/deref this... it'll cause chaos.  Throw a `std::error_code()` (or at least return a null pointer) if it can't be info'ed.

###  Loaders

A loader is a driver designed to load the resource.  Function signatures are expected to be:

    MyResource *load_resource(${Source});
    MyResource *load_resource(${Source}, const ResourceLoadAPI&);

Do *NOT* ref/deref this... it'll cause chaos.  Throw a `std::error_code()` (or at least return a null pointer) if it can't be loaded.

### Savers

A saver is a driver designed to save the resource.  Function signatures are expected to be:

    std::error_code save_resource(const MyResource&, ${Destination});
    std::error_code save_resource(const MyResource&, ${Destination}, const ResourceSaveAPI&);
    
    bool save_resource(const MyResource&, ${Destination});
    bool save_resource(const MyResource&, ${Destination}, const ResourceSaveAPI&);

Either return the appropriate `std::error_code` or `false` if the saving cannot be done.

####  Sources

Current sources are

    const UrlView&
    const std::filesystem::path&
    const ByteArray&
    const std::string&,
    std::istream&,
    const XmlDocument&,
    const json&,
    const KVDocument&,
    const KVTree&
    
A future feature consideration is a web server source, thus, going to a more specific source, like at least a byte array or string means your driver will directly benefit from this enhancement (whereas a url/filepath would have to be adapted).

##### UrlView

This is the default (root) loader/infoer type, a simple Url, and it's up to the driver to load from it; no file I/O is done on the resource infrastructure's part.

##### std::filesystem::path

This means the driver operates on a filesystem, so as long as the file exists, the driver will be called.  Therefore, it'll be up to the driver to perform file I/O.

##### std::istream

This means the driver operates on a standard istream.  Thus, the file will be opened by the resource infrastructure, and a reference passed to the driver.

NOTE: If you need it to be a binary stream, pass the `.binary=true` to the specification on registration, otherwise, it'll be a text stream.

##### ByteArray

This means the driver operates on a byte array (note this will NOT be null terminated).  Thus, the file will be read by the resource infrastructure, and a reference passed to the driver.

##### std::string

This means the driver operates on a standard string (and it's guaranteed to be null terminated data).  Thus, the file will be read by the resource infrastructure, and a reference passed to the driver.

##### XmlDocument

This means the driver operates on XML and will use the rapidxml API for this.  Thus, the file will be read by the resource infrastructure, the contents will be parsed using the rapid xml, and the document will be passed (by reference) to the driver.  

NOTE: Do NOT keep string views, as this document & contents will be destroyed after load.

NOTE: An XML parsing error will abort the load, and your driver will not be called; if you need better control over this process, register a string-based driver and parse it yourself.

##### Json
    
This means the driver operates on JSON and will use the nlohman JSON api for this.  Thus, the file will be read by the resource infrastructure, the contents will be parsed using the nlohman JSON parse.  This json will be passed (by reference) to the driver.  
    
NOTE: Do NOT keep string views, as this document & contents will be destroyed after load.

NOTE: A JSON parsing error will abort the load, and your driver will not be called; if you need better control over this process, register a string-based driver and parse it yourself.

##### KVDocument

This means the driver operates using the KVDocument format (ie, attributes with body).  Thus, the file will be read by the resource infrastructure, the contents will be parsed using the key-value parsing.  This KVDocument will be passed (by reference) to the driver.  

NOTE: Do NOT keep string views, as this document & contents will be destroyed after load.

##### KVTree

This means the driver operates using the KVTree format (ie, attributes without body).  Thus, the file will be read by the resource infrastructure, the contents will be parsed using the key-value parsing.  This KVTree will be passed (by reference) to the driver.  

NOTE: Do NOT keep string views, as this tree & contents will be destroyed after load.
 
####  Destinations

Current destinations are

    const UrlView&
    const std::filesytems::path&,
    ByteArray&,
    std::string&,
    std::ostream&,
    XmlDocument&,
    json&,
    KVDocument&,
    KVTree&

##### UrlView

This is the default (root) saver type, a simple Url, and it's up to the driver to save to it; no file I/O is done on the resource infrastructure's part.


##### std::filesystem::path

This means the driver operates on a filesystem.  Therefore, it'll be up to the driver to perform file I/O.  

NOTE:  This will be a temporary filename.  Upon success, it'll replace the user-specified file.  (And, if the backup option is enabled, the resource infrastructure will rename an existing file to the backup filename.)

##### ByteArray

This means the driver operates on a byte array.  An empty one will be passed to the driver,  to be filled in.  If the driver is successful, then the contents will be written to the specified destination (ie, usually a file).

##### std::string

This means the driver operates on a string.  An empty one will be passed to the driver, to be filled in.  If the driver is successful, then the contents will be written to the specified destination (ie, usually a file).

##### std::ostream

This means the driver operates on a standard output stream.  Output file stream will be opened, and passed to the driver.

NOTE: If you need it to be a binary stream, pass the `.binary=true` to the specification on registration, otherwise, it'll be a text stream.

##### XmlDocument

This means the driver operates on an XML document.  An empty one will be populated by the standard XML header, and then passed to the driver to be filled in.  If the driver is successful, the contents will be formatted and written to the specified destination.

##### JSON

This means the driver operates on JSON.  An empty one will be passed to the driver, to be filled in.  If the driver is successful, the contents will be formatted and written to the specified destination.

###### KVDocument

This means the driver operates on a KVDocument.  An empty one will be passed to the driver, to be filled in.  If the driver is successful, the contents will be formatted and written to the specified destination.

###### KVDocument

This means the driver operates on a KVTree.  An empty one will be passed to the driver, to be filled in.  If the driver is successful, the contents will be formatted and written to the specified destination.

