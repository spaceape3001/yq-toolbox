////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "config.hpp"
#include <yq/process/Settings.hpp>

namespace yq::config {
    static Settings&    settings()
    {
        static Settings s_settings("yquill.cfg");
        return s_settings;
    }

    std::string_view    data_dir()
    {
        return settings().value("data");
    }
    
    std::string_view    vklibs()
    {
        return settings().value("vklibs");
    }
    
    std::string_view    qtlibs()
    {
        return settings().value("qtlibs");
    }
}
