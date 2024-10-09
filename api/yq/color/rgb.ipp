////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "rgb.hpp"
#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::RGB3D)
YQ_TYPE_IMPLEMENT(yq::RGB3F)
YQ_TYPE_IMPLEMENT(yq::RGB3U8)
YQ_TYPE_IMPLEMENT(yq::RGB3U16)

static void reg_rgb_color()
{
    {
        auto w   = writer<RGB3D>();
        w.description("RGB color in double");
        w.property(szRed, &RGB3D::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3D::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3D::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGB3F>();
        w.description("RGB color in float");
        w.property(szRed, &RGB3F::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3F::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3F::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGB3U8>();
        w.description("RGB color in uint8");
        w.property(szRed, &RGB3U8::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3U8::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3U8::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGB3U16>();
        w.description("RGB color in uint16");
        w.property(szRed, &RGB3U16::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3U16::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3U16::blue).description(szBlue_Color).alias(szB);
    }

}

YQ_INVOKE(reg_rgb_color();)
