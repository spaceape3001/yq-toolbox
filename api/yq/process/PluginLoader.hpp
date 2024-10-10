////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/filesystem_path.hpp>

namespace yq {

    /*! \brief Loads the plugin 
    
        This loads the plugin defined by the input argument.
        
        \param[in] plugFile Plugin filename
        \return TRUE if successful, FALSE otherwise
        \note Release builds will swallow exceptions, while Debug builds will let them propagate.
    */
    bool        load_plugin(const filesystem_path_t& plugFile);
    
    /*! \brief Loads a directory of plugins
    
        This iterates across and loads every plugin in the speciried directory.
        
        \param[in] plugDir Directory of plugins
        \return Number of successful plugin loads
        \note Release builds will swallow exceptions, while Debug builds will let them propagate.
    */
    size_t      load_plugin_dir(const filesystem_path_t& plugDir);
}
