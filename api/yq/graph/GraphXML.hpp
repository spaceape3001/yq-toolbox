////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/g_document.hpp>
#include <yq/typedef/filesystem_path.hpp>
#include <yq/typedef/url.hpp>
#include <yq/typedef/xml.hpp>

namespace yq {
    gdocument_ptr_x     loadGraphXML(const std::filesystem::path&);
    gdocument_ptr_x     loadGraphXML(const XmlDocument&, const Url&);
    std::error_code     saveGraphXML(const GDocument&, const std::filesystem::path&);
    std::error_code     saveGraphXML(const GDocument&, XmlDocument&);
}
