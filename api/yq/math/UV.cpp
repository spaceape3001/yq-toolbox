////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "UV.hpp"
#include <yq/meta/Init.hpp>
#include <yq/tags.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

YQ_TYPE_IMPLEMENT(yq::UV2D)
YQ_TYPE_IMPLEMENT(yq::UV2F)
YQ_TYPE_IMPLEMENT(yq::UV2U)
YQ_TYPE_IMPLEMENT(yq::UV2I)

using namespace yq;

template <typename T>
void    print_uv(Stream& str, const UV<T>& v)
{
    str << "(" << v.u << "," << v.v << ")";
}

static std::string_view write_uv2d(const UV2D& v)
{
    static thread_local char    buffer [ 192 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg", kMaxDoubleDigits, v.u, kMaxDoubleDigits, v.v);
    return std::string_view(buffer, n);
}

static std::string_view write_uv2f(const UV2F& v)
{
    static thread_local char    buffer [ 192 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g", kMaxFloatDigits, v.u, kMaxFloatDigits, v.v);
    return std::string_view(buffer, n);
}

static std::string_view write_uv2i(const UV2I& v)
{
    static thread_local char    buffer [ 192 ];
    int n = snprintf(buffer, sizeof(buffer), "%i,%i", v.u, v.v);
    return std::string_view(buffer, n);
}

static std::string_view write_uv2u(const UV2U& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%u,%u", v.u, v.v);
    return std::string_view(buffer, n);
}

static bool  parse_uv2d(UV2D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto x = to_double(bits[0]);
    auto y = to_double(bits[1]);
    if(!(x && y)) 
        return false;
    v   = UV2D(*x, *y);
    return true;
}

static bool  parse_uv2f(UV2F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto x = to_float(bits[0]);
    auto y = to_float(bits[1]);
    if(!(x && y)) 
        return false;
    v   = UV2F(*x, *y);
    return true;
}

static bool  parse_uv2i(UV2I& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto x = to_int(bits[0]);
    auto y = to_int(bits[1]);
    if(!(x && y)) 
        return false;
    v   = UV2I(*x, *y);
    return true;
}

static bool  parse_uv2u(UV2U& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 2)
        return false;
    auto x = to_unsigned(bits[0]);
    auto y = to_unsigned(bits[1]);
    if(!(x && y)) 
        return false;
    v   = UV2U(*x, *y);
    return true;
}

static void reg_uv2d()
{
    auto w = writer<UV2D>();
    w.property("u", &UV2D::u).tag(kTag_Save);
    w.property("v", &UV2D::v).tag(kTag_Save);
    w.print<print_uv<double>>();
    w.format<write_uv2d>();
    w.parse<parse_uv2d>();
}

static void reg_uv2f()
{
    auto w = writer<UV2F>();
    w.property("u", &UV2F::u).tag(kTag_Save);
    w.property("v", &UV2F::v).tag(kTag_Save);
    w.print<print_uv<float>>();
    w.format<write_uv2f>();
    w.parse<parse_uv2f>();
}

static void reg_uv2u()
{
    auto w = writer<UV2U>();
    w.property("u", &UV2U::u).tag(kTag_Save);
    w.property("v", &UV2U::v).tag(kTag_Save);
    w.print<print_uv<unsigned>>();
    w.format<write_uv2u>();
    w.parse<parse_uv2u>();
}

static void reg_uv2i()
{
    auto w = writer<UV2I>();
    w.property("u", &UV2I::u).tag(kTag_Save);
    w.property("v", &UV2I::v).tag(kTag_Save);
    w.print<print_uv<int>>();
    w.format<write_uv2i>();
    w.parse<parse_uv2i>();
}


YQ_INVOKE(
    reg_uv2d();
    reg_uv2f();
    reg_uv2u();
    reg_uv2i();
);

