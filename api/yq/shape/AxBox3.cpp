////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AxBox3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
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
        w.format<math_io::format<AxBox3D>>();
        w.parse<math_io::parse<AxBox3D>>();
        w.print<print_axbox3<double>>();
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
        w.format<math_io::format<AxBox3F>>();
        w.parse<math_io::parse<AxBox3F>>();
        w.print<print_axbox3<float>>();
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
        w.format<math_io::format<AxBox3I>>();
        w.parse<math_io::parse<AxBox3I>>();
        w.print<print_axbox3<int>>();
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
        w.format<math_io::format<AxBox3U>>();
        w.parse<math_io::parse<AxBox3U>>();
        w.print<print_axbox3<unsigned>>();
    }
}

YQ_INVOKE(reg_axbox3();)
