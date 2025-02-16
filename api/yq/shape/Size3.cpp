////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Size3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/utility.hpp>
#include <yq/meta/Init.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "Size3.hxx"

YQ_TYPE_IMPLEMENT(yq::Size3D)
YQ_TYPE_IMPLEMENT(yq::Size3F)
YQ_TYPE_IMPLEMENT(yq::Size3I)
YQ_TYPE_IMPLEMENT(yq::Size3U)

namespace yq {
    Size3I  iround(const Size3D&v)
    {
        return { iround(v.x), iround(v.y), iround(v.z) };
    }
}

using namespace yq;


template <typename T>
void    print_size3(Stream& str, const Size3<T>& v)
{
    str << "(" << v.x << "," << v.y << "," << v.z << ")";
}


static std::string_view write_size3d(const Size3D& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg,%.*lg", kMaxDoubleDigits, v.x, kMaxDoubleDigits, v.y, kMaxDoubleDigits, v.z);
    return std::string_view(buffer, n);
}

static std::string_view write_size3f(const Size3F& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g,%.*g", kMaxFloatDigits, v.x, kMaxFloatDigits, v.y, kMaxFloatDigits, v.z);
    return std::string_view(buffer, n);
}

static std::string_view write_size3i(const Size3I& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%i,%i,%i", v.x, v.y, v.z);
    return std::string_view(buffer, n);
}

static std::string_view write_size3u(const Size3U& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%u,%u,%u", v.x, v.y, v.z);
    return std::string_view(buffer, n);
}

static bool  parse_size3d(Size3D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto x = to_double(bits[0]);
    auto y = to_double(bits[1]);
    auto z = to_double(bits[2]);
    if(!(x && y && z)) 
        return false;
    v   = Size3D(*x, *y, *z);
    return true;
}

static bool  parse_size3f(Size3F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto x = to_float(bits[0]);
    auto y = to_float(bits[1]);
    auto z = to_float(bits[2]);
    if(!(x && y && z)) 
        return false;
    v   = Size3F(*x, *y, *z);
    return true;
}

static bool  parse_size3i(Size3I& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto x = to_int(bits[0]);
    auto y = to_int(bits[1]);
    auto z = to_int(bits[2]);
    if(!(x && y && z)) 
        return false;
    v   = Size3I(*x, *y, *z);
    return true;
}

static bool  parse_size3u(Size3U& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto x = to_unsigned(bits[0]);
    auto y = to_unsigned(bits[1]);
    auto z = to_unsigned(bits[2]);
    if(!(x && y && z)) 
        return false;
    v   = Size3U(*x, *y, *z);
    return true;
}


static void reg_size3()
{
    {
        auto w = writer<Size3D>();
        w.description("3D Size in double");
        w.property(szX, &Size3D::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3D::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3D::z).description(szZ_Size).alias(szDepth);
        w.print<print_size3<double>>();
        w.format<write_size3d>();
        w.parse<parse_size3d>();
        w.operate_with<double>();
    }

    {
        auto w = writer<Size3F>();
        w.description("3D Size in float");
        w.property(szX, &Size3F::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3F::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3F::z).description(szZ_Size).alias(szDepth);
        w.print<print_size3<float>>();
        w.format<write_size3f>();
        w.parse<parse_size3f>();
    }

    {
        auto w = writer<Size3I>();
        w.description("3D Size in integer");
        w.property(szX, &Size3I::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3I::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3I::z).description(szZ_Size).alias(szDepth);
        w.print<print_size3<int>>();
        w.format<write_size3i>();
        w.parse<parse_size3i>();
    }

    {
        auto w = writer<Size3U>();
        w.description("3D Size in unsigned integer");
        w.property(szX, &Size3U::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3U::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3U::z).description(szZ_Size).alias(szDepth);
        w.print<print_size3<unsigned>>();
        w.format<write_size3u>();
        w.parse<parse_size3u>();
    }
}

YQ_INVOKE(reg_size3();)

