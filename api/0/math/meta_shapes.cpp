////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <0/math/preamble.hpp>
#include <yq-toolbox/strings.hpp>

#include <yq-toolbox/shape/AxBox1.hpp>
#include <yq-toolbox/shape/AxBox2.hpp>
#include <yq-toolbox/shape/AxBox3.hpp>
#include <yq-toolbox/shape/AxBox4.hpp>


#include <yq-toolbox/shape/Circle2.hpp>

#include <yq-toolbox/shape/Normal2.hpp>
#include <yq-toolbox/shape/Normal3.hpp>

#include <yq-toolbox/shape/Plane3.hpp>

#include <yq-toolbox/shape/Ray2.hpp>
#include <yq-toolbox/shape/Ray3.hpp>
#include <yq-toolbox/shape/Ray4.hpp>


#include <yq-toolbox/shape/Rectangle2.hpp>

#include <yq-toolbox/shape/Segment1.hpp>
#include <yq-toolbox/shape/Segment2.hpp>
#include <yq-toolbox/shape/Segment3.hpp>
#include <yq-toolbox/shape/Segment4.hpp>

#include <yq-toolbox/shape/Size1.hpp>
#include <yq-toolbox/shape/Size2.hpp>
#include <yq-toolbox/shape/Size3.hpp>
#include <yq-toolbox/shape/Size4.hpp>

#include <yq-toolbox/shape/Sphere3.hpp>
#include <yq-toolbox/shape/Sphere4.hpp>

#include <yq-toolbox/shape/Tetrahedron3.hpp>

#include <yq-toolbox/shape/Triangle2.hpp>
#include <yq-toolbox/shape/Triangle3.hpp>
#include <yq-toolbox/shape/Triangle4.hpp>

#include <yq-toolbox/shape/Quadrilateral2.hpp>

#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/io/StreamOps.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include <yq-toolbox/shape/shape_utils.hpp>
#include <yq-toolbox/unit/literals.hpp>

using namespace yq;




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


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  AxBox2

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  AxBox3
    

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  AxBox4
    

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Circle2
    


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Normal


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

#include <yq-toolbox/math/Range.hxx>

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

