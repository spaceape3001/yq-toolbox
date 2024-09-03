////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "HSL.hpp"
#include <yq/strings.hpp>
#include <yq/basic/DelayInit.hpp>
#include <yq/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(HSL3D)
YQ_TYPE_IMPLEMENT(HSL3F)
YQ_TYPE_IMPLEMENT(HSL3U8)
YQ_TYPE_IMPLEMENT(HSL3U16)

static void reg_hsl_color()
{
    {
        auto w = writer<HSL3D>();
        w.property(szHue, &HSL3D::hue).description(szHue_Color).alias(szH);
        w.property(szSaturation, &HSL3D::saturation).description(szSaturation_Color).alias(szS);
        w.property(szLightness, &HSL3D::lightness).description(szLightness_Color).alias(szL);
    }

    {
        auto w = writer<HSL3F>();
        w.property(szHue, &HSL3F::hue).description(szHue_Color).alias(szH);
        w.property(szSaturation, &HSL3F::saturation).description(szSaturation_Color).alias(szS);
        w.property(szLightness, &HSL3F::lightness).description(szLightness_Color).alias(szL);
    }

    {
        auto w = writer<HSL3U8>();
        w.property(szHue, &HSL3U8::hue).description(szHue_Color).alias(szH);
        w.property(szSaturation, &HSL3U8::saturation).description(szSaturation_Color).alias(szS);
        w.property(szLightness, &HSL3U8::lightness).description(szLightness_Color).alias(szL);
    }

    {
        auto w = writer<HSL3U16>();
        w.property(szHue, &HSL3U16::hue).description(szHue_Color).alias(szH);
        w.property(szSaturation, &HSL3U16::saturation).description(szSaturation_Color).alias(szS);
        w.property(szLightness, &HSL3U16::lightness).description(szLightness_Color).alias(szL);
    }
}

YQ_INVOKE(reg_hsl_color();)
