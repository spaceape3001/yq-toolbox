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
    
    struct AssetInfoOptions {
        //! Integer/Any parameters
        uint32_any_map_t            iparams;
        
        //! String/Any parameters
        string_any_map_t            sparams;
    };
    
    struct AssetLoadOptions {
        //! Set to cache the load result (maybe is left to the loader)
        Tristate    cache       = Tristate::Maybe;

        //! Integer/Any parameters
        uint32_any_map_t            iparams;

        //! Loading options
        //! yes -> always load
        //! maybe -> load if in cache
        //! no -> never load, so we'll fail if *NOT* in the cache
        Tristate    load        = Tristate::Maybe;
        
        //! Library options (null is default)
        const AssetLoadOptions*    library = nullptr;
        
        
        //! String/Any parameters
        string_any_map_t            sparams;

    };
    
    struct AssetSaveOptions {
        //! How to deal with file collisions (on drive)
        FileCollisionStrategy       collision   = FileCollisionStrategy::Abort;

        //! Integer/Any parameters
        uint32_any_map_t            iparams;
        
        //! String/Any parameters
        string_any_map_t            sparams;

        //! TRUE to set the name.  (CAUTION, don't do this with cached-assets)
        bool                        set_name    = false;
    };
}
