////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string_view>

namespace yq::config {

    //! Returns the data directory listed in the general config file (';' separates)
    std::string_view    data_dir();

    //! Returns the vulkan libraries listed in the general config file (';' separates)
    std::string_view    vklibs();

    //! Returns the Qt libraries listed in the general config file (';' separates)
    std::string_view    qtlibs();
}
