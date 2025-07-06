////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

    /*
        ASSET v2.0
        
        Assets are being redesigned to consider sources from:
        
            1) direct files, or, 
            2) a file that's a collection of assets
            
            (NOTE, Asset Libraries are 100% loaded on query, 
            its all or nothing...)
        
        API is being transitioned to general URLs to facilitate 
        a future redesign.  In the meanwhile, the scheme of
        "file:" will be implied if the host field is blank.
        
        Search paths will include preloaded asset 
        libraried/installed asset libraries.
        
        Real APIs aren't yet supported.  Once they are, a type
        of scheme handler will be employed, to download the 
        contents of the request, and hand off the parsing to
        a more dedicated byte/buffer based loader.
        
    */


#include "Asset.hpp"

#include "AssetCache.ipp"
#include "AssetRepo.ipp"

#include "AssetDriver.ipp"
#include "ByteDriver.ipp"
#include "FileDriver.ipp"
#include "JsonDriver.ipp"
#include "KVDocumentDriver.ipp"
#include "KVTreeDriver.ipp"
#include "StreamDriver.ipp"
#include "StringDriver.ipp"
#include "UrlDriver.ipp"
#include "XmlDriver.ipp"

#include "Asset.ipp"
#include "AssetLibrary.ipp"
