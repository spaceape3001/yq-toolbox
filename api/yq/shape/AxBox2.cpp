////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "AxBox2.hpp"

#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/units.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/shape/Circle2.hpp>

#include "AxBox2.hxx"
#include "Circle2.hxx"

YQ_TYPE_IMPLEMENT(yq::AxBox2D)
YQ_TYPE_IMPLEMENT(yq::AxBox2F)
YQ_TYPE_IMPLEMENT(yq::AxBox2I)
YQ_TYPE_IMPLEMENT(yq::AxBox2U)
YQ_TYPE_IMPLEMENT(yq::AxBox2M)
YQ_TYPE_IMPLEMENT(yq::AxBox2CM)
YQ_TYPE_IMPLEMENT(yq::AxBox2MM)

using namespace yq;

static void reg_axbox2()
{
    {
        auto w = writer<AxBox2D>();
        w.description("2D Axially Aligned Bounding Box in double");
        w.property(szArea, &AxBox2D::area).description(szArea_Box);
        w.property(szCenter, &AxBox2D::center).description(szCenter_Box).alias(szCtr);
        w.property(szCircumcircle, &AxBox2D::circumcircle).description(szCircumcircle);
        w.property(szDimension, &AxBox2D::span).description(szDimension_Box).alias(szDim);
        w.property(szIncircle, &AxBox2D::incircle).description(szIncircle_Box);
        w.property(szLow, &AxBox2D::lo).description(szLow_Box).tag(kTag_Save);
        w.property(szHigh, &AxBox2D::hi).description(szHigh_Box).tag(kTag_Save);
        w.property(szNortheast, &AxBox2D::northeast).description(szNortheast_Box).alias(szNE);
        w.property(szNorthwest, &AxBox2D::northwest).description(szNorthwest_Box).alias(szNW);
        w.property(szPerimeter, &AxBox2D::perimeter).description(szPerimeter_Box);
        w.property(szSoutheast, &AxBox2D::southeast).description(szSoutheast_Box).alias(szSE);
        w.property(szSouthwest, &AxBox2D::southwest).description(szSouthwest_Box).alias(szSW);
        w.property(szValid, &AxBox2D::valid).description(szValid_Box);
        w.property(szX, &AxBox2D::x_range).description(szX_Box);
        w.property(szY, &AxBox2D::y_range).description(szY_Box);
        w.method(szContains, (bool(AxBox2D::*)(const Vector2D&) const) &AxBox2D::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox2D::*)(const AxBox2D&) const) &AxBox2D::eclipses).description(szEclipses_Box_Box);
        w.method(szEclipses, (bool(AxBox2D::*)(const Circle2D&) const) &AxBox2D::eclipses).description(szEclipses_Box_Circle);
        w.method(szOverlaps, (bool(AxBox2D::*)(const AxBox2D&) const) &AxBox2D::overlaps).description(szContains_Box_Box);
        w.method(szProject, &AxBox2D::project).description(szProject_Box);
        w.method(szUnproject, &AxBox2D::unproject).description(szUnproject_Box);
    }
    
    {
        auto w = writer<AxBox2F>();
        w.description("2D Axially Aligned Bounding Box in float");
        w.property(szArea, &AxBox2F::area).description(szArea_Box);
        w.property(szCenter, &AxBox2F::center).description(szCenter_Box).alias(szCtr);
        w.property(szCircumcircle, &AxBox2F::circumcircle).description(szCircumcircle);
        w.property(szDimension, &AxBox2F::span).description(szDimension_Box).alias(szDim);
        w.property(szIncircle, &AxBox2F::incircle).description(szIncircle_Box);
        w.property(szLow, &AxBox2F::lo).description(szLow_Box).tag(kTag_Save);
        w.property(szHigh, &AxBox2F::hi).description(szHigh_Box).tag(kTag_Save);
        w.property(szNortheast, &AxBox2F::northeast).description(szNortheast_Box).alias(szNE);
        w.property(szNorthwest, &AxBox2F::northwest).description(szNorthwest_Box).alias(szNW);
        w.property(szPerimeter, &AxBox2F::perimeter).description(szPerimeter_Box);
        w.property(szSoutheast, &AxBox2F::southeast).description(szSoutheast_Box).alias(szSE);
        w.property(szSouthwest, &AxBox2F::southwest).description(szSouthwest_Box).alias(szSW);
        w.property(szValid, &AxBox2F::valid).description(szValid_Box);
        w.property(szX, &AxBox2F::x_range).description(szX_Box);
        w.property(szY, &AxBox2F::y_range).description(szY_Box);
        w.method(szContains, (bool(AxBox2F::*)(const Vector2F&) const) &AxBox2F::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox2F::*)(const AxBox2F&) const) &AxBox2F::eclipses).description(szEclipses_Box_Box);
        w.method(szEclipses, (bool(AxBox2F::*)(const Circle2F&) const) &AxBox2F::eclipses).description(szEclipses_Box_Circle);
        w.method(szOverlaps, (bool(AxBox2F::*)(const AxBox2F&) const) &AxBox2F::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox2F::project).description(szProject_Box);
        w.method(szUnproject, &AxBox2F::unproject).description(szUnproject_Box);
    }
    
    {
        auto w = writer<AxBox2I>();
        w.description("2D Axially Aligned Bounding Box in integer");
        w.property(szArea, &AxBox2I::area).description(szArea_Box);
        w.property(szCenter, &AxBox2I::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox2I::span).description(szDimension_Box).alias(szDim);
        w.property(szLow, &AxBox2I::lo).description(szLow_Box).tag(kTag_Save);
        w.property(szHigh, &AxBox2I::hi).description(szHigh_Box).tag(kTag_Save);
        w.property(szNortheast, &AxBox2I::northeast).description(szNortheast_Box).alias(szNE);
        w.property(szNorthwest, &AxBox2I::northwest).description(szNorthwest_Box).alias(szNW);
        w.property(szPerimeter, &AxBox2I::perimeter).description(szPerimeter_Box);
        w.property(szSoutheast, &AxBox2I::southeast).description(szSoutheast_Box).alias(szSE);
        w.property(szSouthwest, &AxBox2I::southwest).description(szSouthwest_Box).alias(szSW);
        w.property(szValid, &AxBox2I::valid).description(szValid_Box);
        w.property(szX, &AxBox2I::x_range).description(szX_Box);
        w.property(szY, &AxBox2I::y_range).description(szY_Box);
        w.method(szContains, (bool(AxBox2I::*)(const Vector2I&) const) &AxBox2I::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox2I::*)(const AxBox2I&) const) &AxBox2I::eclipses).description(szEclipses_Box_Box);
        w.method(szEclipses, (bool(AxBox2I::*)(const Circle2I&) const) &AxBox2I::eclipses).description(szEclipses_Box_Circle);
        w.method(szOverlaps, (bool(AxBox2I::*)(const AxBox2I&) const) &AxBox2I::overlaps).description(szOverlaps_Box_Box);
    }
    
    {
        auto w = writer<AxBox2U>();
        w.description("2D Axially Aligned Bounding Box in unsigned integers");
        w.property(szArea, &AxBox2U::area).description(szArea_Box);
        w.property(szCenter, &AxBox2U::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox2U::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox2U::hi).description(szHigh_Box).tag(kTag_Save);
        w.property(szLow, &AxBox2U::lo).description(szLow_Box).tag(kTag_Save);
        w.property(szNortheast, &AxBox2U::northeast).description(szNortheast_Box).alias(szNE);
        w.property(szNorthwest, &AxBox2U::northwest).description(szNorthwest_Box).alias(szNW);
        w.property(szPerimeter, &AxBox2U::perimeter).description(szPerimeter_Box);
        w.property(szSoutheast, &AxBox2U::southeast).description(szSoutheast_Box).alias(szSE);
        w.property(szSouthwest, &AxBox2U::southwest).description(szSouthwest_Box).alias(szSW);
        w.property(szValid, &AxBox2U::valid).description(szValid_Box);
        w.property(szX, &AxBox2U::x_range).description(szX_Box);
        w.property(szY, &AxBox2U::y_range).description(szY_Box);
        w.method(szContains, (bool(AxBox2U::*)(const Vector2U&) const) &AxBox2U::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox2U::*)(const AxBox2U&) const) &AxBox2U::eclipses).description(szEclipses_Box_Box);
        w.method(szEclipses, (bool(AxBox2U::*)(const Circle2U&) const) &AxBox2U::eclipses).description(szEclipses_Box_Circle);
        w.method(szOverlaps, (bool(AxBox2U::*)(const AxBox2U&) const) &AxBox2U::overlaps).description(szOverlaps_Box_Box);
    }

    {
        auto w = writer<AxBox2M>();
        w.description("2M Axially Aligned Bounding Box in meters");
        w.property(szArea, &AxBox2M::area).description(szArea_Box);
        w.property(szCenter, &AxBox2M::center).description(szCenter_Box).alias(szCtr);
        //w.property(szCircumcircle, &AxBox2M::circumcircle).description(szCircumcircle);
        w.property(szDimension, &AxBox2M::span).description(szDimension_Box).alias(szDim);
        //w.property(szIncircle, &AxBox2M::incircle).description(szIncircle_Box);
        w.property(szLow, &AxBox2M::lo).description(szLow_Box).tag(kTag_Save);
        w.property(szHigh, &AxBox2M::hi).description(szHigh_Box).tag(kTag_Save);
        w.property(szNortheast, &AxBox2M::northeast).description(szNortheast_Box).alias(szNE);
        w.property(szNorthwest, &AxBox2M::northwest).description(szNorthwest_Box).alias(szNW);
        //w.property(szPerimeter, &AxBox2M::perimeter).description(szPerimeter_Box);
        w.property(szSoutheast, &AxBox2M::southeast).description(szSoutheast_Box).alias(szSE);
        w.property(szSouthwest, &AxBox2M::southwest).description(szSouthwest_Box).alias(szSW);
        w.property(szValid, &AxBox2M::valid).description(szValid_Box);
        w.property(szX, &AxBox2M::x_range).description(szX_Box);
        w.property(szY, &AxBox2M::y_range).description(szY_Box);
        w.method(szContains, (bool(AxBox2M::*)(const Vector2M&) const) &AxBox2M::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox2M::*)(const AxBox2M&) const) &AxBox2M::eclipses).description(szEclipses_Box_Box);
        //w.method(szEclipses, (bool(AxBox2M::*)(const Circle2M&) const) &AxBox2M::eclipses).description(szEclipses_Box_Circle);
        w.method(szOverlaps, (bool(AxBox2M::*)(const AxBox2M&) const) &AxBox2M::overlaps).description(szContains_Box_Box);
        //w.method(szProject, &AxBox2M::project).description(szProject_Box);
        //w.method(szUnproject, &AxBox2M::unproject).description(szUnproject_Box);
    }

    {
        auto w = writer<AxBox2CM>();
        w.description("2D Axially Aligned Bounding Box in centimeters");
        w.property(szArea, &AxBox2CM::area).description(szArea_Box);
        //w.property(szCenter, &AxBox2CM::center).description(szCenter_Box).alias(szCtr);
        //w.property(szCircumcircle, &AxBox2CM::circumcircle).description(szCircumcircle);
        w.property(szDimension, &AxBox2CM::span).description(szDimension_Box).alias(szDim);
        //w.property(szIncircle, &AxBox2CM::incircle).description(szIncircle_Box);
        w.property(szLow, &AxBox2CM::lo).description(szLow_Box).tag(kTag_Save);
        w.property(szHigh, &AxBox2CM::hi).description(szHigh_Box).tag(kTag_Save);
        w.property(szNortheast, &AxBox2CM::northeast).description(szNortheast_Box).alias(szNE);
        w.property(szNorthwest, &AxBox2CM::northwest).description(szNorthwest_Box).alias(szNW);
        //w.property(szPerimeter, &AxBox2CM::perimeter).description(szPerimeter_Box);
        w.property(szSoutheast, &AxBox2CM::southeast).description(szSoutheast_Box).alias(szSE);
        w.property(szSouthwest, &AxBox2CM::southwest).description(szSouthwest_Box).alias(szSW);
        w.property(szValid, &AxBox2CM::valid).description(szValid_Box);
        w.property(szX, &AxBox2CM::x_range).description(szX_Box);
        w.property(szY, &AxBox2CM::y_range).description(szY_Box);
        w.method(szContains, (bool(AxBox2CM::*)(const Vector2CM&) const) &AxBox2CM::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox2CM::*)(const AxBox2CM&) const) &AxBox2CM::eclipses).description(szEclipses_Box_Box);
        //w.method(szEclipses, (bool(AxBox2CM::*)(const Circle2CM&) const) &AxBox2CM::eclipses).description(szEclipses_Box_Circle);
        w.method(szOverlaps, (bool(AxBox2CM::*)(const AxBox2CM&) const) &AxBox2CM::overlaps).description(szContains_Box_Box);
        //w.method(szProject, &AxBox2CM::project).description(szProject_Box);
        //w.method(szUnproject, &AxBox2CM::unproject).description(szUnproject_Box);
    }
    
    {
        auto w = writer<AxBox2MM>();
        w.description("2MM Axially Aligned Bounding Box in millimeters");
        w.property(szArea, &AxBox2MM::area).description(szArea_Box);
        //w.property(szCenter, &AxBox2MM::center).description(szCenter_Box).alias(szCtr);
        //w.property(szCircumcircle, &AxBox2MM::circumcircle).description(szCircumcircle);
        w.property(szDimension, &AxBox2MM::span).description(szDimension_Box).alias(szDim);
        //w.property(szIncircle, &AxBox2MM::incircle).description(szIncircle_Box);
        w.property(szLow, &AxBox2MM::lo).description(szLow_Box).tag(kTag_Save);
        w.property(szHigh, &AxBox2MM::hi).description(szHigh_Box).tag(kTag_Save);
        w.property(szNortheast, &AxBox2MM::northeast).description(szNortheast_Box).alias(szNE);
        w.property(szNorthwest, &AxBox2MM::northwest).description(szNorthwest_Box).alias(szNW);
        //w.property(szPerimeter, &AxBox2MM::perimeter).description(szPerimeter_Box);
        w.property(szSoutheast, &AxBox2MM::southeast).description(szSoutheast_Box).alias(szSE);
        w.property(szSouthwest, &AxBox2MM::southwest).description(szSouthwest_Box).alias(szSW);
        w.property(szValid, &AxBox2MM::valid).description(szValid_Box);
        w.property(szX, &AxBox2MM::x_range).description(szX_Box);
        w.property(szY, &AxBox2MM::y_range).description(szY_Box);
        w.method(szContains, (bool(AxBox2MM::*)(const Vector2MM&) const) &AxBox2MM::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox2MM::*)(const AxBox2MM&) const) &AxBox2MM::eclipses).description(szEclipses_Box_Box);
        //w.method(szEclipses, (bool(AxBox2MM::*)(const Circle2MM&) const) &AxBox2MM::eclipses).description(szEclipses_Box_Circle);
        w.method(szOverlaps, (bool(AxBox2MM::*)(const AxBox2MM&) const) &AxBox2MM::overlaps).description(szContains_Box_Box);
        //w.method(szProject, &AxBox2MM::project).description(szProject_Box);
        //w.method(szUnproject, &AxBox2MM::unproject).description(szUnproject_Box);
    }    
}

YQ_INVOKE(reg_axbox2();)
