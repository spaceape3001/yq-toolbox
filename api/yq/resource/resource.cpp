////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

    /*
        RESOURCE v2.0
        
        Resources are being redesigned to consider sources from:
        
            1) direct files, or, 
            2) a file that's a collection of resources
            
            (NOTE, Resource Libraries are 100% loaded on query, 
            its all or nothing...)
        
        API is being transitioned to general URLs to facilitate 
        a future redesign.  In the meanwhile, the scheme of
        "file:" will be implied if the host field is blank.
        
        Search paths will include preloaded resource 
        libraried/installed resource libraries.
        
        Real APIs aren't yet supported.  Once they are, a type
        of scheme handler will be employed, to download the 
        contents of the request, and hand off the parsing to
        a more dedicated byte/buffer based loader.

        Terminology
            Resource       Anything that can be loaded (aka Resource)
            Info        Information about the specific resource (by url)
            Library     Collection of Resources
            Meta        Meta information/reflection about the resource's C++ class
    */

#include "ResourceInfo.ipp"


#include "Resource.hpp"
#include "ResourceCache.ipp"
#include "ResourceRepo.ipp"
#include "ResourceDriver.ipp"

#include "ResourceByteDriver.ipp"
#include "ResourceFileDriver.ipp"
#include "ResourceJsonDriver.ipp"
#include "ResourceKVDocumentDriver.ipp"
#include "ResourceKVTreeDriver.ipp"
#include "ResourceStreamDriver.ipp"
#include "ResourceStringDriver.ipp"
#include "ResourceUrlDriver.ipp"
#include "ResourceXmlDriver.ipp"

#include "Resource.ipp"
#include "ResourceLibrary.ipp"

#include "Resource.hxx"

