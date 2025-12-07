////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Any.hpp>
#include <yq/core/Tristate.hpp>
#include <yq/net/Url.hpp>
#include <yq/typedef/any_maps.hpp>
#include <yq/typedef/string_maps.hpp>

namespace yq {
    enum class FileCollisionStrategy {
        Abort,
        Overwrite,
        Backup
    };
    
    //! Options that can be passed to the info loading
    struct ResourceInfoOptions {
        //! Integer/Any parameters
        uint32_any_map_t            iparams;
        
        //! String/Any parameters
        string_any_map_t            sparams;
    };
    
    struct ResourceLoadOptions {
        //! Set to cache the load result (maybe is left to the loader)
        Tristate    cache       = Tristate::Maybe;

        //! Integer/Any parameters
        uint32_any_map_t            iparams;

        //! Loading options
        //! yes -> always load
        //! maybe -> load if not in cache
        //! no -> never load, so we'll fail if *NOT* in the cache
        Tristate    load        = Tristate::Maybe;
        
        //! Library options (null is default)
        const ResourceLoadOptions*    library = nullptr;
        
        
        //! String/Any parameters
        string_any_map_t            sparams;

    };
    
    struct ResourceSaveOptions {
        //! How to deal with file collisions (on drive)
        FileCollisionStrategy       collision   = FileCollisionStrategy::Abort;

        //! Integer/Any parameters
        uint32_any_map_t            iparams;
        
        //! String/Any parameters
        string_any_map_t            sparams;

        //! TRUE to set the name.  (CAUTION, don't do this with cached-resources)
        bool                        set_name    = false;
    };
}
