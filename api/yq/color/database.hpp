////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/text/IgCase.hpp>
#include <yq/typedef/expected.hpp>
#include <map>

namespace yq::color {
    using color_map_t   = std::map<std::string_view,RGB3U8,IgCase>;
    const color_map_t&  database();
    rgb3u8_x            lookup(std::string_view);
}
