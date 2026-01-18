////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/color/RGBA.hpp>
#include <yq/core/Tristate.hpp>

namespace yq::symbol {

    struct absstyle_t {
        Tristate    use     = Tristate::Inherit;
        RGBA4F      color   = kInvalidColor;
    };

    struct fill_style_t : public absstyle_t {
    };
    
    struct stroke_style_t : public absstyle_t {
    };
    
    struct text_style_t : public absstyle_t {
    };
}

