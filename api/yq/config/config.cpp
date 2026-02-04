////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "config.hpp"
#include <yq/process/Settings.hpp>
#include <yq/core/BasicApp.hpp>

namespace yq::config {
    static Settings&    settings()
    {
        static Settings s_settings(BasicApp::app_dir() / "yquill.cfg");
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
