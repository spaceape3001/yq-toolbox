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
        float           width   = 0.;
    };
    
    struct font_style_t : public absstyle_t {
        std::string     family;
        float           size        = 12.;
        bool            bold        = false;
        bool            italic      = false;
    };
    
    struct style_t {
        fill_style_t        fill;
        font_style_t        font;
        stroke_style_t      stroke;
    };
}

