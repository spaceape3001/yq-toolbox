////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "RGBA.hpp"
#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::RGBA4D)
YQ_TYPE_IMPLEMENT(yq::RGBA4F)
YQ_TYPE_IMPLEMENT(yq::RGBA4U8)
YQ_TYPE_IMPLEMENT(yq::RGBA4U16)

namespace yq {
    RGBA4F  rgba4f(const color_t&v)
    {
        if(auto p = std::get_if<RGB3U8>(&v)){
            return (RGBA4F) rgba(*p, 255);
        } else if(auto p = std::get_if<RGB3F>(&v)){
            return rgba(*p, 1.0);
        } else if(auto p = std::get_if<RGBA4U8>(&v)){
            return (RGBA4F) *p;
        } else if(auto p = std::get_if<RGBA4F>(&v)){
            return *p;
        } else
            return {0., 0., 0., 0.};
    }
}

static std::string_view write_rgba4d(const RGBA4D& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg,%.*lg,%.*lg", kMaxDoubleDigits, v.red, kMaxDoubleDigits, v.green, kMaxDoubleDigits, v.blue, kMaxDoubleDigits, v.alpha);
    return std::string_view(buffer, n);
}

static std::string_view write_rgba4f(const RGBA4F& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g,%.*g,%.*g", kMaxFloatDigits, v.red, kMaxFloatDigits, v.green, kMaxFloatDigits, v.blue, kMaxFloatDigits, v.alpha);
    return std::string_view(buffer, n);
}


static std::string_view write_rgba4u8(const RGBA4U8& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%hu,%hu,%hu,%hu", (unsigned short) v.red, (unsigned short) v.green, (unsigned short) v.blue, (unsigned short) v.alpha);
    return std::string_view(buffer, n);
}

static std::string_view write_rgba4u16(const RGBA4U16& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%hu,%hu,%hu,%hu", v.red, v.green, v.blue, v.alpha);
    return std::string_view(buffer, n);
}

static bool  parse_rgba4d(RGBA4D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto r = to_double(bits[0]);
    auto g = to_double(bits[1]);
    auto b = to_double(bits[2]);
    auto a = to_double(bits[3]);
    if(!(r && g && b && a)) 
        return false;
    v   = RGBA4D(*r, *g, *b, *a);
    return true;
}

static bool  parse_rgba4f(RGBA4F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto r = to_float(bits[0]);
    auto g = to_float(bits[1]);
    auto b = to_float(bits[2]);
    auto a = to_float(bits[3]);
    if(!(r && g && b && a)) 
        return false;
    v   = RGBA4F(*r, *g, *b, *a);
    return true;
}

static bool  parse_rgba4u8(RGBA4U8& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto r = to_uint8(bits[0]);
    auto g = to_uint8(bits[1]);
    auto b = to_uint8(bits[2]);
    auto a = to_uint8(bits[3]);
    if(!(r && g && b && a)) 
        return false;
    v   = RGBA4U8(*r, *g, *b, *a);
    return true;
}

static bool  parse_rgba4u16(RGBA4U16& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto r = to_ushort(bits[0]);
    auto g = to_ushort(bits[1]);
    auto b = to_ushort(bits[2]);
    auto a = to_ushort(bits[3]);
    if(!(r && g && b && a)) 
        return false;
    v   = RGBA4U16(*r, *g, *b, *a);
    return true;
}


static void reg_rgba_color()
{
    {
        auto w   = writer<RGBA4D>();
        w.description("RGBA color in double");
        w.property(szRed, &RGBA4D::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4D::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4D::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4D::alpha).description(szAlpha_Color).alias(szA);
        w.format<write_rgba4d>();
        w.parse<parse_rgba4d>();
    }

    {
        auto w   = writer<RGBA4F>();
        w.description("RGBA color in float");
        w.property(szRed, &RGBA4F::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4F::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4F::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4F::alpha).description(szAlpha_Color).alias(szA);
        w.format<write_rgba4f>();
        w.parse<parse_rgba4f>();
    }

    {
        auto w   = writer<RGBA4U8>();
        w.description("RGBA color in uint8");
        w.property(szRed, &RGBA4U8::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4U8::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4U8::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4U8::alpha).description(szAlpha_Color).alias(szA);
        w.format<write_rgba4u8>();
        w.parse<parse_rgba4u8>();
    }

    {
        auto w   = writer<RGBA4U16>();
        w.description("RGBA color in uint16");
        w.property(szRed, &RGBA4U16::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4U16::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4U16::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4U16::alpha).description(szAlpha_Color).alias(szA);
        w.format<write_rgba4u16>();
        w.parse<parse_rgba4u16>();
    }
}

YQ_INVOKE(reg_rgba_color();)

