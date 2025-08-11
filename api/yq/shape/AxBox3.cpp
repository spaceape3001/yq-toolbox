////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AxBox3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>

#include "AxBox3.hxx"

YQ_TYPE_IMPLEMENT(yq::AxBox3D)
YQ_TYPE_IMPLEMENT(yq::AxBox3F)
YQ_TYPE_IMPLEMENT(yq::AxBox3I)
YQ_TYPE_IMPLEMENT(yq::AxBox3U)

using namespace yq;

template <typename T>
void    print_axbox3(Stream& str, const AxBox3<T>& v)
{
    as_stream(str, v);
}

static std::string_view write_axbox3d(const AxBox3D& v)
{
    static thread_local char    buffer [ 512 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*lg,%.*lg,%.*lg,%.*lg,%.*lg,%.*lg", 
        kMaxDoubleDigits, v.lo.x, 
        kMaxDoubleDigits, v.lo.y, 
        kMaxDoubleDigits, v.lo.z, 
        kMaxDoubleDigits, v.hi.x, 
        kMaxDoubleDigits, v.hi.y, 
        kMaxDoubleDigits, v.hi.z
    );
    return std::string_view(buffer, n);
}

static std::string_view write_axbox3f(const AxBox3F& v)
{
    static thread_local char    buffer [ 512 ];
    int n = snprintf(buffer, sizeof(buffer), "%.*g,%.*g,%.*g,%.*g,%.*g,%.*g", 
        kMaxFloatDigits, v.lo.x, 
        kMaxFloatDigits, v.lo.y, 
        kMaxFloatDigits, v.lo.z, 
        kMaxFloatDigits, v.hi.x, 
        kMaxFloatDigits, v.hi.y, 
        kMaxFloatDigits, v.hi.z
    );
    return std::string_view(buffer, n);
}

static std::string_view write_axbox3i(const AxBox3I& v)
{
    static thread_local char    buffer [ 512 ];
    int n = snprintf(buffer, sizeof(buffer), "%i,%i,%i,%i,%i,%i", 
        v.lo.x, 
        v.lo.y, 
        v.lo.z, 
        v.hi.x, 
        v.hi.y, 
        v.hi.z
    );
    return std::string_view(buffer, n);
}

static std::string_view write_axbox3u(const AxBox3U& v)
{
    static thread_local char    buffer [ 512 ];
    int n = snprintf(buffer, sizeof(buffer), "%u,%u,%u,%u,%u,%u", 
        v.lo.x, 
        v.lo.y, 
        v.lo.z, 
        v.hi.x, 
        v.hi.y, 
        v.hi.z
    );
    return std::string_view(buffer, n);
}


static bool  parse_axbox3d(AxBox3D& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 6)
        return false;
    auto lx = to_double(bits[0]);
    auto ly = to_double(bits[1]);
    auto lz = to_double(bits[2]);
    auto hx = to_double(bits[3]);
    auto hy = to_double(bits[4]);
    auto hz = to_double(bits[5]);
    if(!(lx && ly && lz && hx && hy && hz)) 
        return false;
    v   = AxBox3D(Vector3D(*lx, *ly, *lz),Vector3D(*hx, *hy, *hz));
    return true;
}

static bool  parse_axbox3f(AxBox3F& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 6)
        return false;
    auto lx = to_float(bits[0]);
    auto ly = to_float(bits[1]);
    auto lz = to_float(bits[2]);
    auto hx = to_float(bits[3]);
    auto hy = to_float(bits[4]);
    auto hz = to_float(bits[5]);
    if(!(lx && ly && lz && hx && hy && hz)) 
        return false;
    v   = AxBox3F(Vector3F(*lx, *ly, *lz),Vector3F(*hx, *hy, *hz));
    return true;
}

static bool  parse_axbox3i(AxBox3I& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 6)
        return false;
    auto lx = to_integer(bits[0]);
    auto ly = to_integer(bits[1]);
    auto lz = to_integer(bits[2]);
    auto hx = to_integer(bits[3]);
    auto hy = to_integer(bits[4]);
    auto hz = to_integer(bits[5]);
    if(!(lx && ly && lz && hx && hy && hz)) 
        return false;
    v   = AxBox3I(Vector3I(*lx, *ly, *lz),Vector3I(*hx, *hy, *hz));
    return true;
}

static bool  parse_axbox3u(AxBox3U& v, std::string_view str)
{
    auto bits = split(str, ',');
    if(bits.size() != 6)
        return false;
    auto lx = to_unsigned(bits[0]);
    auto ly = to_unsigned(bits[1]);
    auto lz = to_unsigned(bits[2]);
    auto hx = to_unsigned(bits[3]);
    auto hy = to_unsigned(bits[4]);
    auto hz = to_unsigned(bits[5]);
    if(!(lx && ly && lz && hx && hy && hz)) 
        return false;
    v   = AxBox3U(Vector3U(*lx, *ly, *lz),Vector3U(*hx, *hy, *hz));
    return true;
}

static void reg_axbox3()
{

    {
        auto w = writer<AxBox3D>();
        w.description("3D Axially Aligned Bounding Box in double");
        w.property(szCenter, &AxBox3D::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox3D::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox3D::hi).description(szHigh_Box);
        w.property(szLow, &AxBox3D::lo).description(szLow_Box);
        w.property(szSurfaceArea, &AxBox3D::surface_area).description(szSurfaceArea_Box3).alias(szSArea);
        w.property(szValid, &AxBox3D::valid).description(szValid_Box);
        w.property(szVolume, &AxBox3D::volume).description(szVolume_Box).alias(szVol);
        w.property(szX, &AxBox3D::x_range).description(szX_Box);
        w.property(szY, &AxBox3D::y_range).description(szY_Box);
        w.property(szZ, &AxBox3D::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox3D::*)(const Vector3D&) const) &AxBox3D::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox3D::*)(const AxBox3D&) const) &AxBox3D::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox3D::*)(const AxBox3D&) const) &AxBox3D::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox3D::project).description(szProject_Box);
        w.method(szUnproject, &AxBox3D::unproject).description(szUnproject_Box);
        w.parse<parse_axbox3d>();
        w.print<print_axbox3<double>>();
        w.format<write_axbox3d>();
    }

    {
        auto w = writer<AxBox3F>();
        w.description("3D Axially Aligned Bounding Box in float");
        w.property(szCenter, &AxBox3F::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox3F::span).description(szDimension_Box).alias(szDim);
        w.property(szLow, &AxBox3F::lo).description(szLow_Box);
        w.property(szHigh, &AxBox3F::hi).description(szHigh_Box);
        w.property(szSurfaceArea, &AxBox3F::surface_area).description(szSurfaceArea_Box3).alias(szSArea);
        w.property(szValid, &AxBox3F::valid).description(szValid_Box);
        w.property(szVolume, &AxBox3F::volume).description(szVolume_Box).alias(szVol);
        w.property(szX, &AxBox3F::x_range).description(szX_Box);
        w.property(szY, &AxBox3F::y_range).description(szY_Box);
        w.property(szZ, &AxBox3F::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox3F::*)(const Vector3F&) const) &AxBox3F::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox3F::*)(const AxBox3F&) const) &AxBox3F::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox3F::*)(const AxBox3F&) const) &AxBox3F::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox3F::project).description(szProject_Box);
        w.method(szUnproject, &AxBox3F::unproject).description(szUnproject_Box);
        w.parse<parse_axbox3f>();
        w.print<print_axbox3<float>>();
        w.format<write_axbox3f>();
    }

    {
        auto w = writer<AxBox3I>();
        w.description("3D Axially Aligned Bounding Box in integer");
        w.property(szCenter, &AxBox3I::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox3I::span).description(szDimension_Box).alias(szDim);
        w.property(szLow, &AxBox3I::lo).description(szLow_Box);
        w.property(szHigh, &AxBox3I::hi).description(szHigh_Box);
        w.property(szSurfaceArea, &AxBox3I::surface_area).description(szSurfaceArea_Box3).alias(szSArea);
        w.property(szValid, &AxBox3I::valid).description(szValid_Box);
        w.property(szVolume, &AxBox3I::volume).description(szVolume_Box).alias(szVol);
        w.property(szX, &AxBox3I::x_range).description(szX_Box);
        w.property(szY, &AxBox3I::y_range).description(szY_Box);
        w.property(szZ, &AxBox3I::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox3I::*)(const Vector3I&) const) &AxBox3I::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox3I::*)(const AxBox3I&) const) &AxBox3I::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox3I::*)(const AxBox3I&) const) &AxBox3I::overlaps).description(szOverlaps_Box_Box);
        w.parse<parse_axbox3i>();
        w.print<print_axbox3<int>>();
        w.format<write_axbox3i>();
    }

    {
        auto w = writer<AxBox3U>();
        w.description("3D Axially Aligned Bounding Box in unsigned integers");
        w.property(szCenter, &AxBox3U::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox3U::span).description(szDimension_Box).alias(szDim);
        w.property(szLow, &AxBox3U::lo).description(szLow_Box);
        w.property(szHigh, &AxBox3U::hi).description(szHigh_Box);
        w.property(szSurfaceArea, &AxBox3U::surface_area).description(szSurfaceArea_Box3);
        w.property(szValid, &AxBox3U::valid).description(szValid_Box);
        w.property(szVolume, &AxBox3U::volume).description(szVolume_Box).alias(szVol);
        w.property(szX, &AxBox3U::x_range).description(szX_Box);
        w.property(szY, &AxBox3U::y_range).description(szY_Box);
        w.property(szZ, &AxBox3U::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox3U::*)(const Vector3U&) const) &AxBox3U::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox3U::*)(const AxBox3U&) const) &AxBox3U::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox3U::*)(const AxBox3U&) const) &AxBox3U::overlaps).description(szOverlaps_Box_Box);
        w.parse<parse_axbox3u>();
        w.print<print_axbox3<unsigned>>();
        w.format<write_axbox3u>();
    }
}

YQ_INVOKE(reg_axbox3();)
