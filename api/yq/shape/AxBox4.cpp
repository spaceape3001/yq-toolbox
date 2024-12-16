////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AxBox4.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include "AxBox4.hxx"

YQ_TYPE_IMPLEMENT(yq::AxBox4D)
YQ_TYPE_IMPLEMENT(yq::AxBox4F)
YQ_TYPE_IMPLEMENT(yq::AxBox4I)
YQ_TYPE_IMPLEMENT(yq::AxBox4U)

using namespace yq;

static void reg_axbox4()
{
    {
        auto w = writer<AxBox4D>();
        w.description("4D Axially Aligned Bounding Box in double");
        w.property(szCenter, &AxBox4D::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox4D::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox4D::hi).description(szHigh_Box);
        w.property(szHypervolume, &AxBox4D::hypervolume).description(szHypervolume_Box4);
        w.property(szLow, &AxBox4D::lo).description(szLow_Box);
        w.property(szValid, &AxBox4D::valid).description(szValid_Box);
        w.property(szW, &AxBox4D::w_range).description(szW_Box);
        w.property(szX, &AxBox4D::x_range).description(szX_Box);
        w.property(szY, &AxBox4D::y_range).description(szY_Box);
        w.property(szZ, &AxBox4D::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox4D::*)(const Vector4D&) const) &AxBox4D::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox4D::*)(const AxBox4D&) const) &AxBox4D::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox4D::*)(const AxBox4D&) const) &AxBox4D::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox4D::project).description(szProject_Box);
        w.method(szUnproject, &AxBox4D::unproject).description(szUnproject_Box);
    }

    {
        auto w = writer<AxBox4F>();
        w.description("4D Axially Aligned Bounding Box in float");
        w.property(szCenter, &AxBox4F::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox4F::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox4F::hi).description(szHigh_Box);
        w.property(szHypervolume, &AxBox4F::hypervolume).description(szHypervolume_Box4);
        w.property(szLow, &AxBox4F::lo).description(szLow_Box);
        w.property(szValid, &AxBox4F::valid).description(szValid_Box);
        w.property(szW, &AxBox4F::w_range).description(szW_Box);
        w.property(szX, &AxBox4F::x_range).description(szX_Box);
        w.property(szY, &AxBox4F::y_range).description(szY_Box);
        w.property(szZ, &AxBox4F::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox4F::*)(const Vector4F&) const) &AxBox4F::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox4F::*)(const AxBox4F&) const) &AxBox4F::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox4F::*)(const AxBox4F&) const) &AxBox4F::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox4F::project).description(szProject_Box);
        w.method(szUnproject, &AxBox4F::unproject).description(szUnproject_Box);
    }
    
    {
        auto w = writer<AxBox4I>();
        w.description("4D Axially Aligned Bounding Box in integer");
        w.property(szCenter, &AxBox4I::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox4I::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox4I::hi).description(szHigh_Box);
        w.property(szHypervolume, &AxBox4I::hypervolume).description(szHypervolume_Box4);
        w.property(szLow, &AxBox4I::lo).description(szLow_Box);
        w.property(szValid, &AxBox4I::valid).description(szValid_Box);
        w.property(szW, &AxBox4I::w_range).description(szW_Box);
        w.property(szX, &AxBox4I::x_range).description(szX_Box);
        w.property(szY, &AxBox4I::y_range).description(szY_Box);
        w.property(szZ, &AxBox4I::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox4I::*)(const Vector4I&) const) &AxBox4I::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox4I::*)(const AxBox4I&) const) &AxBox4I::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox4I::*)(const AxBox4I&) const) &AxBox4I::overlaps).description(szOverlaps_Box_Box);
    }
    
    {
        auto w = writer<AxBox4U>();
        w.description("4D Axially Aligned Bounding Box in unsigned integers");
        w.property(szCenter, &AxBox4U::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox4U::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox4U::hi).description(szHigh_Box);
        w.property(szHypervolume, &AxBox4U::hypervolume).description(szHypervolume_Box4);
        w.property(szLow, &AxBox4U::lo).description(szLow_Box);
        w.property(szValid, &AxBox4U::valid).description(szValid_Box);
        w.property(szW, &AxBox4U::w_range).description(szW_Box);
        w.property(szX, &AxBox4U::x_range).description(szX_Box);
        w.property(szY, &AxBox4U::y_range).description(szY_Box);
        w.property(szZ, &AxBox4U::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox4U::*)(const Vector4U&) const) &AxBox4U::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox4U::*)(const AxBox4U&) const) &AxBox4U::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox4U::*)(const AxBox4U&) const) &AxBox4U::overlaps).description(szOverlaps_Box_Box);
    }
}

YQ_INVOKE(reg_axbox4();)
