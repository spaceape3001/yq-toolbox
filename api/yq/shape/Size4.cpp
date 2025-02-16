////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Size4.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/utility.hpp>
#include <yq/meta/Init.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "Size4.hxx"

YQ_TYPE_IMPLEMENT(yq::Size4D)
YQ_TYPE_IMPLEMENT(yq::Size4F)
YQ_TYPE_IMPLEMENT(yq::Size4I)
YQ_TYPE_IMPLEMENT(yq::Size4U)

namespace yq {
    Size4I  iround(const Size4D&v)
    {
        return { iround(v.x), iround(v.y), iround(v.z), iround(v.w) };
    }
}

using namespace yq;

template <typename T>
void    print_size4(Stream& str, const Size4<T>& v)
{
    str << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
}


static std::string_view write_size4d(const Size4D& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg,%.*lg,%.*lg", kMaxDoubleDigits, v.x, kMaxDoubleDigits, v.y, kMaxDoubleDigits, v.z, kMaxDoubleDigits, v.w);
    return std::string_view(buffer, n);
}

static std::string_view write_size4f(const Size4F& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g,%.*g,%.*g", kMaxFloatDigits, v.x, kMaxFloatDigits, v.y, kMaxFloatDigits, v.z, kMaxFloatDigits, v.w);
    return std::string_view(buffer, n);
}

static std::string_view write_size4i(const Size4I& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%i,%i,%i,%i", v.x, v.y, v.z, v.w);
    return std::string_view(buffer, n);
}

static std::string_view write_size4u(const Size4U& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%u,%u,%u,%u", v.x, v.y, v.z, v.w);
    return std::string_view(buffer, n);
}

static bool  parse_size4d(Size4D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto x = to_double(bits[0]);
    auto y = to_double(bits[1]);
    auto z = to_double(bits[2]);
    auto w = to_double(bits[3]);
    if(!(x && y && z && w)) 
        return false;
    v   = Size4D(*x, *y, *z, *w);
    return true;
}

static bool  parse_size4f(Size4F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto x = to_float(bits[0]);
    auto y = to_float(bits[1]);
    auto z = to_float(bits[2]);
    auto w = to_float(bits[3]);
    if(!(x && y && z && w)) 
        return false;
    v   = Size4F(*x, *y, *z, *w);
    return true;
}

static bool  parse_size4i(Size4I& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto x = to_int(bits[0]);
    auto y = to_int(bits[1]);
    auto z = to_int(bits[2]);
    auto w = to_int(bits[3]);
    if(!(x && y && z && w)) 
        return false;
    v   = Size4I(*x, *y, *z, *w);
    return true;
}

static bool  parse_size4u(Size4U& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 4)
        return false;
    auto x = to_unsigned(bits[0]);
    auto y = to_unsigned(bits[1]);
    auto z = to_unsigned(bits[2]);
    auto w = to_unsigned(bits[3]);
    if(!(x && y && z && w)) 
        return false;
    v   = Size4U(*x, *y, *z, *w);
    return true;
}

static void reg_size4()
{
    {
        auto w = writer<Size4D>();
        w.description("4D Size in double");
        w.property(szX, &Size4D::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size4D::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size4D::z).description(szZ_Size).alias(szDepth);
        w.property(szW, &Size4D::w).description(szW_Size).alias(szDuration);
        w.print<print_size4<double>>();
        w.format<write_size4d>();
        w.parse<parse_size4d>();
        w.operate_with<double>();
    }

    {
        auto w = writer<Size4F>();
        w.description("4D Size in float");
        w.property(szX, &Size4F::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size4F::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size4F::z).description(szZ_Size).alias(szDepth);
        w.property(szW, &Size4F::w).description(szW_Size).alias(szDuration);
        w.print<print_size4<float>>();
        w.format<write_size4f>();
        w.parse<parse_size4f>();
    }

    {
        auto w = writer<Size4I>();
        w.description("4D Size in integer");
        w.property(szX, &Size4I::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size4I::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size4I::z).description(szZ_Size).alias(szDepth);
        w.property(szW, &Size4I::w).description(szW_Size).alias(szDuration);
        w.print<print_size4<int>>();
        w.format<write_size4i>();
        w.parse<parse_size4i>();
    }

    {
        auto w = writer<Size4U>();
        w.description("4D Size in unsigned integer");
        w.property(szX, &Size4U::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size4U::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size4U::z).description(szZ_Size).alias(szDepth);
        w.property(szW, &Size4U::w).description(szW_Size).alias(szDuration);
        w.print<print_size4<unsigned>>();
        w.format<write_size4u>();
        w.parse<parse_size4u>();
    }
}

YQ_INVOKE(reg_size4();)

