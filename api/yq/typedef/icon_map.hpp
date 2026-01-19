////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <yq/typedef/url.hpp>

namespace yq {
    using icon_url_map_t    = std::map<uint16_t, Url>;
    using icon_spec_map_t   = std::map<uint16_t,std::string>;
}

