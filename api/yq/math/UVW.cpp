////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "UVW.hpp"
#include <yq/meta/Init.hpp>
#include <yq/tags.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

YQ_TYPE_IMPLEMENT(yq::UVW3D)
YQ_TYPE_IMPLEMENT(yq::UVW3F)
YQ_TYPE_IMPLEMENT(yq::UVW3U)
YQ_TYPE_IMPLEMENT(yq::UVW3I)

using namespace yq;

template <typename T>
void    print_uvw(Stream& str, const UVW<T>& v)
{
    str << "(" << v.u << "," << v.v << "," << v.w << ")";
}

static std::string_view write_uvw3d(const UVW3D& v)
{
    static thread_local char    buffer [ 192 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg,%.*lg", kMaxDoubleDigits, v.u, kMaxDoubleDigits, v.v, kMaxDoubleDigits, v.w);
    return std::string_view(buffer, n);
}

static std::string_view write_uvw3f(const UVW3F& v)
{
    static thread_local char    buffer [ 192 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g,%.*g", kMaxFloatDigits, v.u, kMaxFloatDigits, v.v, kMaxFloatDigits, v.w);
    return std::string_view(buffer, n);
}

static std::string_view write_uvw3i(const UVW3I& v)
{
    static thread_local char    buffer [ 192 ];
    int n = snprintf(buffer, sizeof(buffer), "%i,%i,%i", v.u, v.v, v.w);
    return std::string_view(buffer, n);
}

static std::string_view write_uvw3u(const UVW3U& v)
{
    static thread_local char    buffer [ 256 ];
    int n = snprintf(buffer, sizeof(buffer), "%u,%u,%u", v.u, v.v, v.w);
    return std::string_view(buffer, n);
}

static bool  parse_uvw3d(UVW3D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto x = to_double(bits[0]);
    auto y = to_double(bits[1]);
    auto z = to_double(bits[2]);
    if(!(x && y && z)) 
        return false;
    v   = UVW3D(*x, *y, *z);
    return true;
}

static bool  parse_uvw3f(UVW3F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto x = to_float(bits[0]);
    auto y = to_float(bits[1]);
    auto z = to_float(bits[2]);
    if(!(x && y && z)) 
        return false;
    v   = UVW3F(*x, *y, *z);
    return true;
}

static bool  parse_uvw3i(UVW3I& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto x = to_int(bits[0]);
    auto y = to_int(bits[1]);
    auto z = to_int(bits[2]);
    if(!(x && y && z)) 
        return false;
    v   = UVW3I(*x, *y, *z);
    return true;
}

static bool  parse_uvw3u(UVW3U& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 3)
        return false;
    auto x = to_unsigned(bits[0]);
    auto y = to_unsigned(bits[1]);
    auto z = to_unsigned(bits[2]);
    if(!(x && y && z)) 
        return false;
    v   = UVW3U(*x, *y, *z);
    return true;
}

static void reg_uvw3d()
{
    auto w = writer<UVW3D>();
    w.property("u", &UVW3D::u).tag(kTag_Save);
    w.property("v", &UVW3D::v).tag(kTag_Save);
    w.property("w", &UVW3D::w).tag(kTag_Save);
    w.print<print_uvw<double>>();
    w.format<write_uvw3d>();
    w.parse<parse_uvw3d>();
}

static void reg_uvw3f()
{
    auto w = writer<UVW3F>();
    w.property("u", &UVW3F::u).tag(kTag_Save);
    w.property("v", &UVW3F::v).tag(kTag_Save);
    w.property("w", &UVW3F::w).tag(kTag_Save);
    w.print<print_uvw<float>>();
    w.format<write_uvw3f>();
    w.parse<parse_uvw3f>();
}

static void reg_uvw3u()
{
    auto w = writer<UVW3U>();
    w.property("u", &UVW3U::u).tag(kTag_Save);
    w.property("v", &UVW3U::v).tag(kTag_Save);
    w.property("w", &UVW3U::w).tag(kTag_Save);
    w.print<print_uvw<unsigned>>();
    w.format<write_uvw3u>();
    w.parse<parse_uvw3u>();
}

static void reg_uvw3i()
{
    auto w = writer<UVW3I>();
    w.property("u", &UVW3I::u).tag(kTag_Save);
    w.property("v", &UVW3I::v).tag(kTag_Save);
    w.property("w", &UVW3I::w).tag(kTag_Save);
    w.print<print_uvw<int>>();
    w.format<write_uvw3i>();
    w.parse<parse_uvw3i>();
}


YQ_INVOKE(
    reg_uvw3d();
    reg_uvw3f();
    reg_uvw3u();
    reg_uvw3i();
);

