////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Size2.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/utility.hpp>
#include <yq/meta/Init.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "Size2.hxx"

YQ_TYPE_IMPLEMENT(yq::Size2D)
YQ_TYPE_IMPLEMENT(yq::Size2F)
YQ_TYPE_IMPLEMENT(yq::Size2I)
YQ_TYPE_IMPLEMENT(yq::Size2U)

namespace yq {
    Size2I  iround(const Size2D&v)
    {
        return { iround(v.x), iround(v.y) };
    }
}

using namespace yq;


template <typename T>
void    print_size2(Stream& str, const Size2<T>& v)
{
    str << "(" << v.x << "," << v.y << ")";
}


static std::string_view write_size2d(const Size2D& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg", kMaxDoubleDigits, v.x, kMaxDoubleDigits, v.y);
    return std::string_view(buffer, n);
}

static std::string_view write_size2f(const Size2F& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g", kMaxFloatDigits, v.x, kMaxFloatDigits, v.y);
    return std::string_view(buffer, n);
}

static std::string_view write_size2i(const Size2I& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%i,%i", v.x, v.y);
    return std::string_view(buffer, n);
}

static std::string_view write_size2u(const Size2U& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%u,%u", v.x, v.y);
    return std::string_view(buffer, n);
}

static bool  parse_size2d(Size2D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto x = to_double(bits[0]);
    auto y = to_double(bits[1]);
    if(!(x && y)) 
        return false;
    v   = Size2D(*x, *y);
    return true;
}

static bool  parse_size2f(Size2F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto x = to_float(bits[0]);
    auto y = to_float(bits[1]);
    if(!(x && y)) 
        return false;
    v   = Size2F(*x, *y);
    return true;
}

static bool  parse_size2i(Size2I& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto x = to_int(bits[0]);
    auto y = to_int(bits[1]);
    if(!(x && y)) 
        return false;
    v   = Size2I(*x, *y);
    return true;
}

static bool  parse_size2u(Size2U& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto x = to_unsigned(bits[0]);
    auto y = to_unsigned(bits[1]);
    if(!(x && y)) 
        return false;
    v   = Size2U(*x, *y);
    return true;
}

static void reg_size2()
{
    {
        auto w = writer<Size2D>();
        w.description("2D Size in double");
        w.property(szX, &Size2D::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2D::y).description(szY_Size).alias(szHeight);
        w.print<print_size2<double>>();
        w.format<write_size2d>();
        w.parse<parse_size2d>();
        w.operate_with<double>();
    }

    {
        auto w = writer<Size2F>();
        w.description("2D Size in float");
        w.property(szX, &Size2F::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2F::y).description(szY_Size).alias(szHeight);
        w.print<print_size2<float>>();
        w.format<write_size2f>();
        w.parse<parse_size2f>();
    }

    {
        auto w = writer<Size2I>();
        w.description("2D Size in integer");
        w.property(szX, &Size2I::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2I::y).description(szY_Size).alias(szHeight);
        w.print<print_size2<int>>();
        w.format<write_size2i>();
        w.parse<parse_size2i>();
    }

    {
        auto w = writer<Size2U>();
        w.description("2D Size in unsigned integer");
        w.property(szX, &Size2U::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2U::y).description(szY_Size).alias(szHeight);
        w.print<print_size2<unsigned>>();
        w.format<write_size2u>();
        w.parse<parse_size2u>();
    }
}

YQ_INVOKE(reg_size2();)

