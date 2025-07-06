////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Any.hpp>
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
        //! Integer/Any parameters
        uint32_any_map_t            iparams;
        
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
