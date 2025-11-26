////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "RGB.hpp"
#include <yq/strings.hpp>
#include <yq/color/database.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::RGB3D)
YQ_TYPE_IMPLEMENT(yq::RGB3F)
YQ_TYPE_IMPLEMENT(yq::RGB3U8)
YQ_TYPE_IMPLEMENT(yq::RGB3U16)



static std::string_view write_rgb3d(const RGB3D& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg,%.*lg", kMaxDoubleDigits, v.red, kMaxDoubleDigits, v.green, kMaxDoubleDigits, v.blue);
    return std::string_view(buffer, n);
}

static std::string_view write_rgb3f(const RGB3F& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g,%.*g", kMaxFloatDigits, v.red, kMaxFloatDigits, v.green, kMaxFloatDigits, v.blue);
    return std::string_view(buffer, n);
}


static std::string_view write_rgb3u8(const RGB3U8& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%hu,%hu,%hu", (unsigned short) v.red, (unsigned short) v.green, (unsigned short) v.blue);
    return std::string_view(buffer, n);
}

static std::string_view write_rgb3u16(const RGB3U16& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%hu,%hu,%hu", v.red, v.green, v.blue);
    return std::string_view(buffer, n);
}

static bool  parse_rgb3d(RGB3D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto r = to_double(bits[0]);
    auto g = to_double(bits[1]);
    auto b = to_double(bits[2]);
    if(!(r && g && b)) 
        return false;
    v   = RGB3D(*r, *g, *b);
    return true;
}

static bool  parse_rgb3f(RGB3F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto r = to_float(bits[0]);
    auto g = to_float(bits[1]);
    auto b = to_float(bits[2]);
    if(!(r && g && b)) 
        return false;
    v   = RGB3F(*r, *g, *b);
    return true;
}

static bool  parse_rgb3u8(RGB3U8& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto r = to_uint8(bits[0]);
    auto g = to_uint8(bits[1]);
    auto b = to_uint8(bits[2]);
    if(!(r && g && b)) 
        return false;
    v   = RGB3U8(*r, *g, *b);
    return true;
}

static bool  parse_rgb3u16(RGB3U16& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto r = to_ushort(bits[0]);
    auto g = to_ushort(bits[1]);
    auto b = to_ushort(bits[2]);
    if(!(r && g && b)) 
        return false;
    v   = RGB3U16(*r, *g, *b);
    return true;
}


static void reg_rgb_color()
{
    {
        auto w   = writer<RGB3D>();
        w.description("RGB color in double");
        w.property(szRed, &RGB3D::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3D::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3D::blue).description(szBlue_Color).alias(szB);
        w.format<write_rgb3d>();
        w.parse<parse_rgb3d>();
    }

    {
        auto w   = writer<RGB3F>();
        w.description("RGB color in float");
        w.property(szRed, &RGB3F::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3F::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3F::blue).description(szBlue_Color).alias(szB);
        w.format<write_rgb3f>();
        w.parse<parse_rgb3f>();
    }

    {
        auto w   = writer<RGB3U8>();
        w.description("RGB color in uint8");
        w.property(szRed, &RGB3U8::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3U8::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3U8::blue).description(szBlue_Color).alias(szB);
        w.format<write_rgb3u8>();
        w.parse<parse_rgb3u8>();
    }

    {
        auto w   = writer<RGB3U16>();
        w.description("RGB color in uint16");
        w.property(szRed, &RGB3U16::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3U16::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3U16::blue).description(szBlue_Color).alias(szB);
        w.format<write_rgb3u16>();
        w.parse<parse_rgb3u16>();
    }

}

YQ_INVOKE(reg_rgb_color();)

namespace yq {
    std::string_view    fmt_hex(const RGB3U8&v)
    {
        static char buffer[256];
        snprintf(buffer, sizeof(buffer), "#%02X%02X%02X", (int) v.red, (int) v.green, (int) v.blue);
        return buffer;
    }

    rgb3u8_x            to_rgb3u8(std::string_view s)
    {
        RGB3U8  ret;
        if(parse_rgb3u8(ret, s))
            return ret;
        auto x  = color::lookup(s);
        if(x)
            return *x;
        return errors::parser_failed();
    }
    
    rgb3f_x             to_rgb3f(std::string_view s)
    {
        RGB3F  ret;
        if(parse_rgb3f(ret, s))
            return ret;
        auto x  = color::lookup(s);
        if(x)
            return (RGB3F) *x;
        return errors::parser_failed();
    }
    
    std::string_view    to_string_view(const RGB3F&v)
    {
        return write_rgb3f(v);
    }
    
    std::string_view    to_string_view(const RGB3U8&v)
    {
        return write_rgb3u8(v);
    }
}

