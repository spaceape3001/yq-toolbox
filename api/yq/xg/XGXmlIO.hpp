////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/xg_document.hpp>
#include <yq/typedef/filesystem_path.hpp>
#include <yq/typedef/url.hpp>
#include <yq/typedef/xml.hpp>

namespace yq {
    xg_document_ptr_x   loadXGXML(const std::filesystem::path&);
    xg_document_ptr_x   loadXGXML(const XmlDocument&, const Url&);
    bool                saveXGXML(const XGDocument&, const std::filesystem::path&);
    bool                saveXGXML(const XGDocument&, XmlDocument&);
}
