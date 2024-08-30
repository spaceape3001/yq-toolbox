////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "HSV.hpp"
#include <0/math/strings.hpp>
#include <0/basic/DelayInit.hpp>
#include <0/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(HSV3D)
YQ_TYPE_IMPLEMENT(HSV3F)
YQ_TYPE_IMPLEMENT(HSV3U8)
YQ_TYPE_IMPLEMENT(HSV3U16)

namespace {
    void reg_hsl_color()
    {
        {
            auto w = writer<HSV3D>();
            w.property(szHue, &HSV3D::hue).description(szHue_Color).alias(szH);
            w.property(szSaturation, &HSV3D::saturation).description(szSaturation_Color).alias(szS);
            w.property(szValue, &HSV3D::value).description(szValue_Color).alias(szV);
        }

        {
            auto w = writer<HSV3F>();
            w.property(szHue, &HSV3F::hue).description(szHue_Color).alias(szH);
            w.property(szSaturation, &HSV3F::saturation).description(szSaturation_Color).alias(szS);
            w.property(szValue, &HSV3F::value).description(szValue_Color).alias(szV);
        }

        {
            auto w = writer<HSV3U8>();
            w.property(szHue, &HSV3U8::hue).description(szHue_Color).alias(szH);
            w.property(szSaturation, &HSV3U8::saturation).description(szSaturation_Color).alias(szS);
            w.property(szValue, &HSV3U8::value).description(szValue_Color).alias(szV);
        }

        {
            auto w = writer<HSV3U16>();
            w.property(szHue, &HSV3U16::hue).description(szHue_Color).alias(szH);
            w.property(szSaturation, &HSV3U16::saturation).description(szSaturation_Color).alias(szS);
            w.property(szValue, &HSV3U16::value).description(szValue_Color).alias(szV);
        }
    }
}

YQ_INVOKE(reg_hsl_color();)
