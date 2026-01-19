////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/typedef/rgb.hpp>
#include <yq/typedef/rgba.hpp>
#include <string>
#include <variant>

namespace yq {
    using color_t       = std::variant<std::monostate, RGBA4F, RGBA4U8, RGB3F, RGB3U8>;
    using color_spec    = std::variant<std::monostate, std::string, RGBA4F, RGBA4U8, RGB3F, RGB3U8>;
}
