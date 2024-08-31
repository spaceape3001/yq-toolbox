////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <0/math/preamble.hpp>
#include <0/math/strings.hpp>

#include <0/math/shape/AxBox1.hpp>
#include <0/math/shape/AxBox2.hpp>
#include <0/math/shape/AxBox3.hpp>
#include <0/math/shape/AxBox4.hpp>


#include <0/math/shape/Circle2.hpp>

#include <0/math/shape/Normal2.hpp>
#include <0/math/shape/Normal3.hpp>

#include <0/math/shape/Plane3.hpp>

#include <0/math/shape/Ray2.hpp>
#include <0/math/shape/Ray3.hpp>
#include <0/math/shape/Ray4.hpp>


#include <0/math/shape/Rectangle2.hpp>

#include <0/math/shape/Segment1.hpp>
#include <0/math/shape/Segment2.hpp>
#include <0/math/shape/Segment3.hpp>
#include <0/math/shape/Segment4.hpp>

#include <0/math/shape/Size1.hpp>
#include <0/math/shape/Size2.hpp>
#include <0/math/shape/Size3.hpp>
#include <0/math/shape/Size4.hpp>

#include <0/math/shape/Sphere3.hpp>
#include <0/math/shape/Sphere4.hpp>

#include <0/math/shape/Tetrahedron3.hpp>

#include <0/math/shape/Triangle2.hpp>
#include <0/math/shape/Triangle3.hpp>
#include <0/math/shape/Triangle4.hpp>

#include <0/math/shape/Quadrilateral2.hpp>

#include <yq/basic/DelayInit.hpp>
#include <0/io/StreamOps.hpp>
#include <0/meta/Init.hpp>

#include <0/math/shape/shape_utils.hpp>
#include <0/math/unit/literals.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::AxBox1D)
YQ_TYPE_IMPLEMENT(yq::AxBox1F)
YQ_TYPE_IMPLEMENT(yq::AxBox1I)
YQ_TYPE_IMPLEMENT(yq::AxBox1U)

YQ_TYPE_IMPLEMENT(yq::AxBox2D)
YQ_TYPE_IMPLEMENT(yq::AxBox2F)
YQ_TYPE_IMPLEMENT(yq::AxBox2I)
YQ_TYPE_IMPLEMENT(yq::AxBox2U)

YQ_TYPE_IMPLEMENT(yq::AxBox3D)
YQ_TYPE_IMPLEMENT(yq::AxBox3F)
YQ_TYPE_IMPLEMENT(yq::AxBox3I)
YQ_TYPE_IMPLEMENT(yq::AxBox3U)

YQ_TYPE_IMPLEMENT(yq::AxBox4D)
YQ_TYPE_IMPLEMENT(yq::AxBox4F)
YQ_TYPE_IMPLEMENT(yq::AxBox4I)
YQ_TYPE_IMPLEMENT(yq::AxBox4U)

YQ_TYPE_IMPLEMENT(yq::Circle2D)
YQ_TYPE_IMPLEMENT(yq::Circle2F)
YQ_TYPE_IMPLEMENT(yq::Circle2I)
YQ_TYPE_IMPLEMENT(yq::Circle2U)

YQ_TYPE_IMPLEMENT(yq::Normal2D)
YQ_TYPE_IMPLEMENT(yq::Normal2F)

YQ_TYPE_IMPLEMENT(yq::Normal3D)
YQ_TYPE_IMPLEMENT(yq::Normal3F)

YQ_TYPE_IMPLEMENT(yq::Plane3D)
YQ_TYPE_IMPLEMENT(yq::Plane3F)

YQ_TYPE_IMPLEMENT(yq::Quadrilateral2D)
YQ_TYPE_IMPLEMENT(yq::Quadrilateral2F)
YQ_TYPE_IMPLEMENT(yq::Quadrilateral2I)
YQ_TYPE_IMPLEMENT(yq::Quadrilateral2U)

YQ_TYPE_IMPLEMENT(yq::Ray2D)
YQ_TYPE_IMPLEMENT(yq::Ray2F)

YQ_TYPE_IMPLEMENT(yq::Ray3D)
YQ_TYPE_IMPLEMENT(yq::Ray3F)

YQ_TYPE_IMPLEMENT(yq::Ray4D)
YQ_TYPE_IMPLEMENT(yq::Ray4F)

YQ_TYPE_IMPLEMENT(yq::Rectangle2D)
YQ_TYPE_IMPLEMENT(yq::Rectangle2F)
YQ_TYPE_IMPLEMENT(yq::Rectangle2I)
YQ_TYPE_IMPLEMENT(yq::Rectangle2U)

YQ_TYPE_IMPLEMENT(yq::Segment1D)
YQ_TYPE_IMPLEMENT(yq::Segment1F)
YQ_TYPE_IMPLEMENT(yq::Segment1I)
YQ_TYPE_IMPLEMENT(yq::Segment1U)

YQ_TYPE_IMPLEMENT(yq::Segment2D)
YQ_TYPE_IMPLEMENT(yq::Segment2F)
YQ_TYPE_IMPLEMENT(yq::Segment2I)
YQ_TYPE_IMPLEMENT(yq::Segment2U)

YQ_TYPE_IMPLEMENT(yq::Segment3D)
YQ_TYPE_IMPLEMENT(yq::Segment3F)
YQ_TYPE_IMPLEMENT(yq::Segment3I)
YQ_TYPE_IMPLEMENT(yq::Segment3U)

YQ_TYPE_IMPLEMENT(yq::Segment4D)
YQ_TYPE_IMPLEMENT(yq::Segment4F)
YQ_TYPE_IMPLEMENT(yq::Segment4I)
YQ_TYPE_IMPLEMENT(yq::Segment4U)

YQ_TYPE_IMPLEMENT(yq::Size1D)
YQ_TYPE_IMPLEMENT(yq::Size1F)
YQ_TYPE_IMPLEMENT(yq::Size1I)
YQ_TYPE_IMPLEMENT(yq::Size1U)

YQ_TYPE_IMPLEMENT(yq::Size2D)
YQ_TYPE_IMPLEMENT(yq::Size2F)
YQ_TYPE_IMPLEMENT(yq::Size2I)
YQ_TYPE_IMPLEMENT(yq::Size2U)

YQ_TYPE_IMPLEMENT(yq::Size3D)
YQ_TYPE_IMPLEMENT(yq::Size3F)
YQ_TYPE_IMPLEMENT(yq::Size3I)
YQ_TYPE_IMPLEMENT(yq::Size3U)

YQ_TYPE_IMPLEMENT(yq::Size4D)
YQ_TYPE_IMPLEMENT(yq::Size4F)
YQ_TYPE_IMPLEMENT(yq::Size4I)
YQ_TYPE_IMPLEMENT(yq::Size4U)

YQ_TYPE_IMPLEMENT(yq::Sphere3D)
YQ_TYPE_IMPLEMENT(yq::Sphere3F)
YQ_TYPE_IMPLEMENT(yq::Sphere3I)
YQ_TYPE_IMPLEMENT(yq::Sphere3U)

YQ_TYPE_IMPLEMENT(yq::Sphere4D)
YQ_TYPE_IMPLEMENT(yq::Sphere4F)
YQ_TYPE_IMPLEMENT(yq::Sphere4I)
YQ_TYPE_IMPLEMENT(yq::Sphere4U)

YQ_TYPE_IMPLEMENT(yq::Tetrahedron3D)
YQ_TYPE_IMPLEMENT(yq::Tetrahedron3F)
YQ_TYPE_IMPLEMENT(yq::Tetrahedron3I)
YQ_TYPE_IMPLEMENT(yq::Tetrahedron3U)

YQ_TYPE_IMPLEMENT(yq::Triangle2D)
YQ_TYPE_IMPLEMENT(yq::Triangle2F)
YQ_TYPE_IMPLEMENT(yq::Triangle2I)
YQ_TYPE_IMPLEMENT(yq::Triangle2U)

YQ_TYPE_IMPLEMENT(yq::Triangle3D)
YQ_TYPE_IMPLEMENT(yq::Triangle3F)
YQ_TYPE_IMPLEMENT(yq::Triangle3I)
YQ_TYPE_IMPLEMENT(yq::Triangle3U)

YQ_TYPE_IMPLEMENT(yq::Triangle4D)
YQ_TYPE_IMPLEMENT(yq::Triangle4F)
YQ_TYPE_IMPLEMENT(yq::Triangle4I)
YQ_TYPE_IMPLEMENT(yq::Triangle4U)

//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//  OTHER HELPERS FOR MATH

    
//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

static void reg_shape_math () {

    // General order ... all alphabetical
    //
    //      1. properties
    //      2. methods
    //


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  AxBox1

    {
        auto w = writer<AxBox1D>();
        w.description("1D Axially Aligned Bounding Box in double");
        w.property(szCenter, &AxBox1D::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox1D::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox1D::hi).description(szHigh_Box);
        w.property(szLow, &AxBox1D::lo).description(szLow_Box);
        w.property(szValid, &AxBox1D::valid).description(szValid_Box);
        w.property(szX, &AxBox1D::x_range).description(szX_Box);
        w.method(szContains, (bool(AxBox1D::*)(const Vector1D&) const) &AxBox1D::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox1D::*)(const AxBox1D&) const) &AxBox1D::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox1D::*)(const AxBox1D&) const) &AxBox1D::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox1D::project).description(szProject_Box);
        w.method(szUnproject, &AxBox1D::unproject).description(szUnproject_Box);
    }

    {
        auto w = writer<AxBox1F>();
        w.description("1D Axially Aligned Bounding Box in float");
        w.property(szCenter, &AxBox1F::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox1F::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox1F::hi).description(szHigh_Box);
        w.property(szLow, &AxBox1F::lo).description(szLow_Box);
        w.property(szValid, &AxBox1F::valid).description(szValid_Box);
        w.property(szX, &AxBox1F::x_range).description(szX_Box);
        w.method(szContains, (bool(AxBox1F::*)(const Vector1F&) const) &AxBox1F::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox1F::*)(const AxBox1F&) const) &AxBox1F::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox1F::*)(const AxBox1F&) const) &AxBox1F::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox1F::project).description(szProject_Box);
        w.method(szUnproject, &AxBox1F::unproject).description(szUnproject_Box);
    }

    {
        auto w = writer<AxBox1I>();
        w.description("1D Axially Aligned Bounding Box in integer");
        w.property(szCenter, &AxBox1I::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox1I::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox1I::hi).description(szHigh_Box);
        w.property(szLow, &AxBox1I::lo).description(szLow_Box);
        w.property(szValid, &AxBox1I::valid).description(szValid_Box);
        w.property(szX, &AxBox1I::x_range).description(szX_Box);
        w.method(szContains, (bool(AxBox1I::*)(const Vector1I&) const) &AxBox1I::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox1I::*)(const AxBox1I&) const) &AxBox1I::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox1I::*)(const AxBox1I&) const) &AxBox1I::overlaps).description(szOverlaps_Box_Box);
    }

    {
        auto w = writer<AxBox1U>();
        w.description("1D Axially Aligned Bounding Box in unsigned integers");
        w.property(szCenter, &AxBox1U::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox1U::span).description(szDimension_Box).alias(szDim);
        w.property(szLow, &AxBox1U::lo).description(szLow_Box);
        w.property(szHigh, &AxBox1U::hi).description(szHigh_Box);
        w.property(szValid, &AxBox1U::valid).description(szValid_Box);
        w.property(szX, &AxBox1U::x_range).description(szX_Box);
        w.method(szContains, (bool(AxBox1U::*)(const Vector1U&) const) &AxBox1U::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox1U::*)(const AxBox1U&) const) &AxBox1U::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox1U::*)(const AxBox1U&) const) &AxBox1U::overlaps).description(szOverlaps_Box_Box);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  AxBox2

    {
        auto w = writer<AxBox2D>();
        w.description("2D Axially Aligned Bounding Box in double");
        w.property(szArea, &AxBox2D::area).description(szArea_Box);
        w.property(szCenter, &AxBox2D::center).description(szCenter_Box).alias(szCtr);
        w.property(szCircumcircle, &AxBox2D::circumcircle).description(szCircumcircle);
        w.property(szDimension, &AxBox2D::span).description(szDimension_Box).alias(szDim);
        w.property(szIncircle, &AxBox2D::incircle).description(szIncircle_Box);
        w.property(szLow, &AxBox2D::lo).description(szLow_Box);
        w.property(szHigh, &AxBox2D::hi).description(szHigh_Box);
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
        w.property(szLow, &AxBox2F::lo).description(szLow_Box);
        w.property(szHigh, &AxBox2F::hi).description(szHigh_Box);
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
        w.property(szLow, &AxBox2I::lo).description(szLow_Box);
        w.property(szHigh, &AxBox2I::hi).description(szHigh_Box);
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
        w.property(szHigh, &AxBox2U::hi).description(szHigh_Box);
        w.property(szLow, &AxBox2U::lo).description(szLow_Box);
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

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  AxBox3
    
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
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  AxBox4
    
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

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Circle2
    
    {
        auto w = writer<Circle2D>();
        w.description("2D circle in double");
        w.property(szArea, &Circle2D::area).description(szArea_Circle).alias(szA);
        w.property(szBox, &Circle2D::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2D::center).description(szCenter_Circle).alias({szPoint, szPt});
        w.property(szCircumference, &Circle2D::circumference).description(szCircumference).alias({szCirc, szPerimeter, szPeri});
        w.property(szDiameter, &Circle2D::diameter).description(szDiameter_Circle).alias({szDia, szD});
        w.property(szRadius, &Circle2D::radius).description(szRadius_Circle).alias({szRad, szR});
        w.property(szValid, &Circle2D::valid).description(szValid_Circle);
    }
    
    {
        auto w = writer<Circle2F>();
        w.description("2D circle in float");
        w.property(szArea, &Circle2F::area).description(szArea_Circle).alias(szA);
        w.property(szBox, &Circle2F::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2F::center).description(szCenter_Circle).alias({szPoint, szPt});
        w.property(szCircumference, &Circle2F::circumference).description(szCircumference).alias({szCirc, szPerimeter, szPeri});
        w.property(szDiameter, &Circle2F::diameter).description(szDiameter_Circle).alias({szDia, szD});
        w.property(szRadius, &Circle2F::radius).description(szRadius_Circle).alias({szRad, szR});
        w.property(szValid, &Circle2F::valid).description(szValid_Circle);
    }
    
    {
        auto w = writer<Circle2I>();
        w.description("2D circle in integer");
        w.property(szBox, &Circle2I::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2I::center).description(szCenter_Circle).alias({szPoint, szPt});
        w.property(szDiameter, &Circle2I::diameter).description(szDiameter_Circle).alias({szDia, szD});
        w.property(szRadius, &Circle2I::radius).description(szRadius_Circle).alias({szRad, szR});
        w.property(szValid, &Circle2I::valid).description(szValid_Circle);
    }
    
    {
        auto w = writer<Circle2U>();
        w.description("2D circle in unsigned int");
        w.property(szBox, &Circle2U::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2U::center).description(szCenter_Circle).alias({szPoint, szPt});
        w.property(szDiameter, &Circle2U::diameter).description(szDiameter_Circle).alias({szDia, szD});
        w.property(szRadius, &Circle2U::radius).description(szRadius_Circle).alias({szRad, szR});
        w.property(szValid, &Circle2U::valid).description(szValid_Circle);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Normal

    {
        auto w = writer<Normal2D>();
        w.description("2D normal in double");
        w.property(szDirection, &Normal2D::direction).description(szDirection_Normal).alias(szDir);
    }

    {
        auto w = writer<Normal2F>();
        w.description("2D normal in float");
        w.property(szDirection, &Normal2F::direction).description(szDirection_Normal).alias(szDir);
    }

    {
        auto w = writer<Normal3D>();
        w.description("3D normal in double");
        w.property(szDirection, &Normal3D::direction).description(szDirection_Normal).alias(szDir);
    }

    {
        auto w = writer<Normal3F>();
        w.description("3D normal in float");
        w.property(szDirection, &Normal3F::direction).description(szDirection_Normal).alias(szDir);
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Quadrilateral
    
    {
        auto w = writer<Quadrilateral2D>();
        w.description("2D Quadrilateral in double");
        w.property(szA, &Quadrilateral2D::a).description(szA_Quadrilateral);
        w.property(szB, &Quadrilateral2D::b).description(szB_Quadrilateral);
        w.property(szC, &Quadrilateral2D::c).description(szC_Quadrilateral);
        w.property(szD, &Quadrilateral2D::d).description(szD_Quadrilateral);
    }

    {
        auto w = writer<Quadrilateral2F>();
        w.description("2D Quadrilateral in float");
        w.property(szA, &Quadrilateral2F::a).description(szA_Quadrilateral);
        w.property(szB, &Quadrilateral2F::b).description(szB_Quadrilateral);
        w.property(szC, &Quadrilateral2F::c).description(szC_Quadrilateral);
        w.property(szD, &Quadrilateral2F::d).description(szD_Quadrilateral);
    }

    {
        auto w = writer<Quadrilateral2I>();
        w.description("2D Quadrilateral in integer");
        w.property(szA, &Quadrilateral2I::a).description(szA_Quadrilateral);
        w.property(szB, &Quadrilateral2I::b).description(szB_Quadrilateral);
        w.property(szC, &Quadrilateral2I::c).description(szC_Quadrilateral);
        w.property(szD, &Quadrilateral2I::d).description(szD_Quadrilateral);
    }

    {
        auto w = writer<Quadrilateral2U>();
        w.description("2D Quadrilateral in unsigned integer");
        w.property(szA, &Quadrilateral2U::a).description(szA_Quadrilateral);
        w.property(szB, &Quadrilateral2U::b).description(szB_Quadrilateral);
        w.property(szC, &Quadrilateral2U::c).description(szC_Quadrilateral);
        w.property(szD, &Quadrilateral2U::d).description(szD_Quadrilateral);
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Rays

    {
        auto w = writer<Ray2D>();
        w.description("2D ray in double");
        w.property(szPoint, &Ray2D::point).description(szPoint_Ray).alias(szPt);
        w.property(szDirection, &Ray2D::direction).description(szDirection_Ray).alias(szDir);
    }

    {
        auto w = writer<Ray2F>();
        w.description("2D ray in float");
        w.property(szPoint, &Ray2F::point).description(szPoint_Ray).alias(szPt);
        w.property(szDirection, &Ray2F::direction).description(szDirection_Ray).alias(szDir);
    }

    {
        auto w = writer<Ray3D>();
        w.description("3D ray in double");
        w.property(szPoint, &Ray3D::point).description(szPoint_Ray).alias(szPt);
        w.property(szDirection, &Ray3D::direction).description(szDirection_Ray).alias(szDir);
    }

    {
        auto w = writer<Ray3F>();
        w.description("3D ray in float");
        w.property(szPoint, &Ray3F::point).description(szPoint_Ray).alias(szPt);
        w.property(szDirection, &Ray3F::direction).description(szDirection_Ray).alias(szDir);
    }

    {
        auto w = writer<Ray4D>();
        w.description("4D ray in double");
        w.property(szPoint, &Ray4D::point).description(szPoint_Ray).alias(szPt);
        w.property(szDirection, &Ray4D::direction).description(szDirection_Ray).alias(szDir);
    }

    {
        auto w = writer<Ray4F>();
        w.description("4D ray in float");
        w.property(szPoint, &Ray4F::point).description(szPoint_Ray).alias(szPt);
        w.property(szDirection, &Ray4F::direction).description(szDirection_Ray).alias(szDir);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Rectangle

    {
        auto w = writer<Rectangle2D>();
        w.description("2D rectangle in double");
        w.property(szPosition, &Rectangle2D::position).description(szPosition_Rectangle).alias({szPos, szCorner});
        w.property(szSize, &Rectangle2D::size).description(szSize_Rectangle);
    }

    {
        auto w = writer<Rectangle2F>();
        w.description("2D rectangle in float");
        w.property(szPosition, &Rectangle2F::position).description(szPosition_Rectangle).alias({szPos, szCorner});
        w.property(szSize, &Rectangle2F::size).description(szSize_Rectangle);
    }

    {
        auto w = writer<Rectangle2I>();
        w.description("2D rectangle in integer");
        w.property(szPosition, &Rectangle2I::position).description(szPosition_Rectangle).alias({szPos, szCorner});
        w.property(szSize, &Rectangle2I::size).description(szSize_Rectangle);
    }

    {
        auto w = writer<Rectangle2U>();
        w.description("2D rectangle in unsigned integer");
        w.property(szPosition, &Rectangle2U::position).description(szPosition_Rectangle).alias({szPos, szCorner});
        w.property(szSize, &Rectangle2U::size).description(szSize_Rectangle);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Segment

    {
        auto w = writer<Segment1D>();
        w.description("1D Segment in double");
        w.property(szA, &Segment1D::a).description(szA_Segment);
        w.property(szB, &Segment1D::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment1F>();
        w.description("1D Segment in float");
        w.property(szA, &Segment1F::a).description(szA_Segment);
        w.property(szB, &Segment1F::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment1I>();
        w.description("1D Segment in integer");
        w.property(szA, &Segment1I::a).description(szA_Segment);
        w.property(szB, &Segment1I::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment1U>();
        w.description("1D Segment in unsigned integer");
        w.property(szA, &Segment1U::a).description(szA_Segment);
        w.property(szB, &Segment1U::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment2D>();
        w.description("2D Segment in double");
        w.property(szA, &Segment2D::a).description(szA_Segment);
        w.property(szB, &Segment2D::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment2F>();
        w.description("2D Segment in float");
        w.property(szA, &Segment2F::a).description(szA_Segment);
        w.property(szB, &Segment2F::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment2I>();
        w.description("2D Segment in integer");
        w.property(szA, &Segment2I::a).description(szA_Segment);
        w.property(szB, &Segment2I::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment2U>();
        w.description("2D Segment in unsigned integer");
        w.property(szA, &Segment2U::a).description(szA_Segment);
        w.property(szB, &Segment2U::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment3D>();
        w.description("3D Segment in double");
        w.property(szA, &Segment3D::a).description(szA_Segment);
        w.property(szB, &Segment3D::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment3F>();
        w.description("3D Segment in float");
        w.property(szA, &Segment3F::a).description(szA_Segment);
        w.property(szB, &Segment3F::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment3I>();
        w.description("3D Segment in integer");
        w.property(szA, &Segment3I::a).description(szA_Segment);
        w.property(szB, &Segment3I::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment3U>();
        w.description("3D Segment in unsigned integer");
        w.property(szA, &Segment3U::a).description(szA_Segment);
        w.property(szB, &Segment3U::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment4D>();
        w.description("4D Segment in double");
        w.property(szA, &Segment4D::a).description(szA_Segment);
        w.property(szB, &Segment4D::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment4F>();
        w.description("4D Segment in float");
        w.property(szA, &Segment4F::a).description(szA_Segment);
        w.property(szB, &Segment4F::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment4I>();
        w.description("4D Segment in integer");
        w.property(szA, &Segment4I::a).description(szA_Segment);
        w.property(szB, &Segment4I::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment4U>();
        w.description("4D Segment in unsigned integer");
        w.property(szA, &Segment4U::a).description(szA_Segment);
        w.property(szB, &Segment4U::b).description(szB_Segment);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Size

    {
        auto w = writer<Size2D>();
        w.description("2D Size in double");
        w.property(szX, &Size2D::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2D::y).description(szY_Size).alias(szHeight);
    }

    {
        auto w = writer<Size2F>();
        w.description("2D Size in float");
        w.property(szX, &Size2F::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2F::y).description(szY_Size).alias(szHeight);
    }

    {
        auto w = writer<Size2I>();
        w.description("2D Size in integer");
        w.property(szX, &Size2I::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2I::y).description(szY_Size).alias(szHeight);
    }

    {
        auto w = writer<Size2U>();
        w.description("2D Size in unsigned integer");
        w.property(szX, &Size2U::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2U::y).description(szY_Size).alias(szHeight);
    }

    {
        auto w = writer<Size3D>();
        w.description("3D Size in double");
        w.property(szX, &Size3D::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3D::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3D::z).description(szZ_Size).alias(szDepth);
    }

    {
        auto w = writer<Size3F>();
        w.description("3D Size in float");
        w.property(szX, &Size3F::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3F::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3F::z).description(szZ_Size).alias(szDepth);
    }

    {
        auto w = writer<Size3I>();
        w.description("3D Size in integer");
        w.property(szX, &Size3I::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3I::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3I::z).description(szZ_Size).alias(szDepth);
    }

    {
        auto w = writer<Size3U>();
        w.description("3D Size in unsigned integer");
        w.property(szX, &Size3U::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3U::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3U::z).description(szZ_Size).alias(szDepth);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Sphere

    {
        auto w = writer<Sphere3D>();
        w.description("3D sphere in double");
        w.property(szCenter, &Sphere3D::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere3D::radius).description(szRadius_Sphere).alias({szRad, szR});
        w.property(szVolume, &Sphere3D::volume).description(szVolume_Sphere).alias({szVol});
    }

    {
        auto w = writer<Sphere3F>();
        w.description("3D sphere in float");
        w.property(szCenter, &Sphere3F::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere3F::radius).description(szRadius_Sphere).alias({szRad, szR});
        w.property(szVolume, &Sphere3F::volume).description(szVolume_Sphere).alias({szVol});
    }

    {
        auto w = writer<Sphere3I>();
        w.description("3D sphere in integer");
        w.property(szCenter, &Sphere3I::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere3I::radius).description(szRadius_Sphere).alias({szRad, szR});
    }

    {
        auto w = writer<Sphere3U>();
        w.description("3D sphere in unsigned integer");
        w.property(szCenter, &Sphere3U::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere3U::radius).description(szRadius_Sphere).alias({szRad, szR});
    }

    {
        auto w = writer<Sphere4D>();
        w.description("4D sphere in double");
        w.property(szCenter, &Sphere4D::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere4D::radius).description(szRadius_Sphere).alias({szRad, szR});
        w.property(szHypervolume, &Sphere4D::hypervolume).description(szHypervolume_Sphere4);
    }

    {
        auto w = writer<Sphere4F>();
        w.description("4D sphere in float");
        w.property(szCenter, &Sphere4F::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere4F::radius).description(szRadius_Sphere).alias({szRad, szR});
        w.property(szHypervolume, &Sphere4F::hypervolume).description(szHypervolume_Sphere4);
    }

    {
        auto w = writer<Sphere4I>();
        w.description("4D sphere in integer");
        w.property(szCenter, &Sphere4I::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere4I::radius).description(szRadius_Sphere).alias({szRad, szR});
    }

    {
        auto w = writer<Sphere4U>();
        w.description("4D sphere in unsigned integer");
        w.property(szCenter, &Sphere4U::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere4U::radius).description(szRadius_Sphere).alias({szRad, szR});
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Tetrahedron

    {
        auto w = writer<Tetrahedron3D>();
        w.description("3D Tetrahedron in double");
        w.property(szA, &Tetrahedron3D::a).description(szA_Tetrahedron);
        w.property(szB, &Tetrahedron3D::b).description(szB_Tetrahedron);
        w.property(szC, &Tetrahedron3D::c).description(szC_Tetrahedron);
        w.property(szD, &Tetrahedron3D::d).description(szD_Tetrahedron);
    }

    {
        auto w = writer<Tetrahedron3F>();
        w.description("3D Tetrahedron in float");
        w.property(szA, &Tetrahedron3F::a).description(szA_Tetrahedron);
        w.property(szB, &Tetrahedron3F::b).description(szB_Tetrahedron);
        w.property(szC, &Tetrahedron3F::c).description(szC_Tetrahedron);
        w.property(szD, &Tetrahedron3F::d).description(szD_Tetrahedron);
    }

    {
        auto w = writer<Tetrahedron3I>();
        w.description("3D Tetrahedron in integer");
        w.property(szA, &Tetrahedron3I::a).description(szA_Tetrahedron);
        w.property(szB, &Tetrahedron3I::b).description(szB_Tetrahedron);
        w.property(szC, &Tetrahedron3I::c).description(szC_Tetrahedron);
        w.property(szD, &Tetrahedron3I::d).description(szD_Tetrahedron);
    }
    
    {
        auto w = writer<Tetrahedron3U>();
        w.description("3D Tetrahedron in unsigned integer");
        w.property(szA, &Tetrahedron3U::a).description(szA_Tetrahedron);
        w.property(szB, &Tetrahedron3U::b).description(szB_Tetrahedron);
        w.property(szC, &Tetrahedron3U::c).description(szC_Tetrahedron);
        w.property(szD, &Tetrahedron3U::d).description(szD_Tetrahedron);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Triangle

    {
        auto w = writer<Triangle2D>();
        w.description("2D Triangle in double");
        w.property(szA, &Triangle2D::a).description(szA_Triangle);
        w.property(szB, &Triangle2D::b).description(szB_Triangle);
        w.property(szC, &Triangle2D::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle2F>();
        w.description("2D Triangle in float");
        w.property(szA, &Triangle2F::a).description(szA_Triangle);
        w.property(szB, &Triangle2F::b).description(szB_Triangle);
        w.property(szC, &Triangle2F::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle2I>();
        w.description("2D Triangle in integer");
        w.property(szA, &Triangle2I::a).description(szA_Triangle);
        w.property(szB, &Triangle2I::b).description(szB_Triangle);
        w.property(szC, &Triangle2I::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle2U>();
        w.description("2D Triangle in unsigned integer");
        w.property(szA, &Triangle2U::a).description(szA_Triangle);
        w.property(szB, &Triangle2U::b).description(szB_Triangle);
        w.property(szC, &Triangle2U::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle3D>();
        w.description("3D Triangle in double");
        w.property(szA, &Triangle3D::a).description(szA_Triangle);
        w.property(szB, &Triangle3D::b).description(szB_Triangle);
        w.property(szC, &Triangle3D::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle3F>();
        w.description("3D Triangle in float");
        w.property(szA, &Triangle3F::a).description(szA_Triangle);
        w.property(szB, &Triangle3F::b).description(szB_Triangle);
        w.property(szC, &Triangle3F::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle3I>();
        w.description("3D Triangle in integer");
        w.property(szA, &Triangle3I::a).description(szA_Triangle);
        w.property(szB, &Triangle3I::b).description(szB_Triangle);
        w.property(szC, &Triangle3I::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle3U>();
        w.description("3D Triangle in unsigned double");
        w.property(szA, &Triangle3U::a).description(szA_Triangle);
        w.property(szB, &Triangle3U::b).description(szB_Triangle);
        w.property(szC, &Triangle3U::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle4D>();
        w.description("4D Triangle in double");
        w.property(szA, &Triangle4D::a).description(szA_Triangle);
        w.property(szB, &Triangle4D::b).description(szB_Triangle);
        w.property(szC, &Triangle4D::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle4F>();
        w.description("4D Triangle in float");
        w.property(szA, &Triangle4F::a).description(szA_Triangle);
        w.property(szB, &Triangle4F::b).description(szB_Triangle);
        w.property(szC, &Triangle4F::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle4I>();
        w.description("4D Triangle in integer");
        w.property(szA, &Triangle4I::a).description(szA_Triangle);
        w.property(szB, &Triangle4I::b).description(szB_Triangle);
        w.property(szC, &Triangle4I::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle4U>();
        w.description("4D Triangle in unsigned integer");
        w.property(szA, &Triangle4U::a).description(szA_Triangle);
        w.property(szB, &Triangle4U::b).description(szB_Triangle);
        w.property(szC, &Triangle4U::c).description(szC_Triangle);
    }
}

YQ_INVOKE(reg_shape_math();)

#include "Range.hxx"

#include "shape/AxBox1.hxx"
#include "shape/AxBox2.hxx"
#include "shape/AxBox3.hxx"
#include "shape/AxBox4.hxx"

#include "shape/Circle2.hxx"
#include "shape/Circle3.hxx"

#include "shape/Normal2.hxx"
#include "shape/Normal3.hxx"

#include "shape/Plane3.hxx"

#include "shape/Polygon2.hxx"
#include "shape/Polygon3.hxx"
#include "shape/Polygon4.hxx"

#include "shape/Polyline2.hxx"
#include "shape/Polyline3.hxx"
#include "shape/Polyline4.hxx"

#include "shape/Quadrilateral2.hxx"
#include "shape/Ray2.hxx"
#include "shape/Ray3.hxx"
#include "shape/Ray4.hxx"
#include "shape/Rectangle2.hxx"

#include "shape/Segment1.hxx"
#include "shape/Segment2.hxx"
#include "shape/Segment3.hxx"
#include "shape/Segment4.hxx"

#include "shape/Size1.hxx"
#include "shape/Size2.hxx"
#include "shape/Size3.hxx"
#include "shape/Size4.hxx"

#include "shape/Sphere3.hxx"
#include "shape/Sphere4.hxx"

#include "shape/Tetrahedron3.hxx"

#include "shape/Triangle2.hxx"
#include "shape/Triangle3.hxx"
#include "shape/Triangle4.hxx"

#include "vector/Vector1.hxx"
#include "vector/Vector2.hxx"
#include "vector/Vector3.hxx"
#include "vector/Vector4.hxx"

