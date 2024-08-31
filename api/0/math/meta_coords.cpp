////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <0/math/preamble.hpp>
#include <0/math/Coord1.hpp>
#include <0/math/Coord2.hpp>
#include <0/math/Coord3.hpp>
#include <0/math/Coord4.hpp>
#include <0/math/Coord5.hpp>
#include <0/math/Coord6.hpp>
#include <0/math/strings.hpp>

#include <0/math/coord/LatLon.hpp>
#include <0/math/coord/LatLonAlt.hpp>
#include <0/math/coord/Polar2.hpp>
#include <0/math/coord/Cylindrical3.hpp>

#include <0/math/unit/MKS.hpp>

#include <yq/basic/DelayInit.hpp>
#include <0/io/StreamOps.hpp>
#include <0/meta/Init.hpp>

using namespace yq;


YQ_TYPE_IMPLEMENT(yq::Coord1D)
YQ_TYPE_IMPLEMENT(yq::Coord1F)
YQ_TYPE_IMPLEMENT(yq::Coord1I)
YQ_TYPE_IMPLEMENT(yq::Coord1U)

YQ_TYPE_IMPLEMENT(yq::Coord2D)
YQ_TYPE_IMPLEMENT(yq::Coord2F)
YQ_TYPE_IMPLEMENT(yq::Coord2I)
YQ_TYPE_IMPLEMENT(yq::Coord2U)

YQ_TYPE_IMPLEMENT(yq::Coord3D)
YQ_TYPE_IMPLEMENT(yq::Coord3F)
YQ_TYPE_IMPLEMENT(yq::Coord3I)
YQ_TYPE_IMPLEMENT(yq::Coord3U)

YQ_TYPE_IMPLEMENT(yq::Coord4D)
YQ_TYPE_IMPLEMENT(yq::Coord4F)
YQ_TYPE_IMPLEMENT(yq::Coord4I)
YQ_TYPE_IMPLEMENT(yq::Coord4U)

YQ_TYPE_IMPLEMENT(yq::Coord5D)
YQ_TYPE_IMPLEMENT(yq::Coord5F)
YQ_TYPE_IMPLEMENT(yq::Coord5I)
YQ_TYPE_IMPLEMENT(yq::Coord5U)

YQ_TYPE_IMPLEMENT(yq::Coord6D)
YQ_TYPE_IMPLEMENT(yq::Coord6F)
YQ_TYPE_IMPLEMENT(yq::Coord6I)
YQ_TYPE_IMPLEMENT(yq::Coord6U)

YQ_TYPE_IMPLEMENT(yq::Cylindrical3D)
YQ_TYPE_IMPLEMENT(yq::Cylindrical3M)

YQ_TYPE_IMPLEMENT(yq::Polar2D)
YQ_TYPE_IMPLEMENT(yq::Polar2M)


//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//  OTHER HELPERS FOR MATH

namespace {
    template <typename T>
    void     print_coord1(Stream& str, const Coord1<T>& v)
    {
        str << "(" << v.i << ")";
    }


    template <typename T>
    void     print_coord2(Stream& str, const Coord2<T>& v)
    {
        str << "(" << v.i << "," << v.j << ")";
    }

    template <typename T>
    void     print_coord3(Stream& str, const Coord3<T>& v)
    {
        str << "(" << v.i << "," << v.j << "," << v.k << ")";
    }

    template <typename T>
    void     print_coord4(Stream& str, const Coord4<T>& v)
    {
        str << "(" << v.i << "," << v.j << "," << v.k << "," << v.l << ")";
    }

    template <typename T>
    void     print_coord5(Stream& str, const Coord5<T>& v)
    {
        str << "(" << v.i << "," << v.j << "," << v.k << "," << v.l << "," << v.m << ")";
    }

    template <typename T>
    void     print_coord6(Stream& str, const Coord6<T>& v)
    {
        str << "(" << v.i << "," << v.j << "," << v.k << "," << v.l << "," << v.m << "," << v.n << ")";
    }
}
    
//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

static void reg_coord_math () {

    // General order ... all alphabetical
    //
    //      1. properties
    //      2. methods
    //
    

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Coordinates

    {
        auto w = writer<Coord1D>();
        w.description("1D coordinate in double");
        w.property(szI, &Coord1D::i).description(szI_Coord);
        w.print<print_coord1<double>>();
    }

    {
        auto w = writer<Coord1F>();
        w.description("1D coordinate in float");
        w.property(szI, &Coord1F::i).description(szI_Coord);
        w.print<print_coord1<float>>();
    }

    {
        auto w = writer<Coord1I>();
        w.description("1D coordinate in integer");
        w.property(szI, &Coord1I::i).description(szI_Coord);
        w.print<print_coord1<int>>();
    }

    {
        auto w = writer<Coord1U>();
        w.description("1D coordinate in unsigned integer");
        w.property(szI, &Coord1U::i).description(szI_Coord);
        w.print<print_coord1<unsigned>>();
    }

    {
        auto w = writer<Coord2D>();
        w.description("2D coordinate in double");
        w.property(szI, &Coord2D::i).description(szI_Coord);
        w.property(szJ, &Coord2D::j).description(szJ_Coord);
        w.print<print_coord2<double>>();
    }

    {
        auto w = writer<Coord2F>();
        w.description("2D coordinate in float");
        w.property(szI, &Coord2F::i).description(szI_Coord);
        w.property(szJ, &Coord2F::j).description(szJ_Coord);
        w.print<print_coord2<float>>();
    }

    {
        auto w = writer<Coord2I>();
        w.description("2D coordinate in integer");
        w.property(szI, &Coord2I::i).description(szI_Coord);
        w.property(szJ, &Coord2I::j).description(szJ_Coord);
        w.print<print_coord2<int>>();
    }

    {
        auto w = writer<Coord2U>();
        w.description("2D coordinate in unsigned integer");
        w.property(szI, &Coord2U::i).description(szI_Coord);
        w.property(szJ, &Coord2U::j).description(szJ_Coord);
        w.print<print_coord2<unsigned>>();
    }

    {
        auto w = writer<Coord3D>();
        w.description("3D coordinate in double");
        w.property(szI, &Coord3D::i).description(szI_Coord);
        w.property(szJ, &Coord3D::j).description(szJ_Coord);
        w.property(szK, &Coord3D::k).description(szK_Coord);
        w.print<print_coord3<double>>();
    }

    {
        auto w = writer<Coord3F>();
        w.description("3D coordinate in float");
        w.property(szI, &Coord3F::i).description(szI_Coord);
        w.property(szJ, &Coord3F::j).description(szJ_Coord);
        w.property(szK, &Coord3F::k).description(szK_Coord);
        w.print<print_coord3<float>>();
    }

    {
        auto w = writer<Coord3I>();
        w.description("3D coordinate in integer");
        w.property(szI, &Coord3I::i).description(szI_Coord);
        w.property(szJ, &Coord3I::j).description(szJ_Coord);
        w.property(szK, &Coord3I::k).description(szK_Coord);
        w.print<print_coord3<int>>();
    }

    {
        auto w = writer<Coord3U>();
        w.description("3D coordinate in unsigned integer");
        w.property(szI, &Coord3U::i).description(szI_Coord);
        w.property(szJ, &Coord3U::j).description(szJ_Coord);
        w.property(szK, &Coord3U::k).description(szK_Coord);
        w.print<print_coord3<unsigned>>();
    }

    {
        auto w = writer<Coord4D>();
        w.description("4D coordinate in double");
        w.property(szI, &Coord4D::i).description(szI_Coord);
        w.property(szJ, &Coord4D::j).description(szJ_Coord);
        w.property(szK, &Coord4D::k).description(szK_Coord);
        w.property(szL, &Coord4D::l).description(szL_Coord);
        w.print<print_coord4<double>>();
    }

    {
        auto w = writer<Coord4F>();
        w.description("4D coordinate in float");
        w.property(szI, &Coord4F::i).description(szI_Coord);
        w.property(szJ, &Coord4F::j).description(szJ_Coord);
        w.property(szK, &Coord4F::k).description(szK_Coord);
        w.property(szL, &Coord4F::l).description(szL_Coord);
        w.print<print_coord4<float>>();
    }

    {
        auto w = writer<Coord4I>();
        w.description("4D coordinate in integer");
        w.property(szI, &Coord4I::i).description(szI_Coord);
        w.property(szJ, &Coord4I::j).description(szJ_Coord);
        w.property(szK, &Coord4I::k).description(szK_Coord);
        w.property(szL, &Coord4I::l).description(szL_Coord);
        w.print<print_coord4<int>>();
    }

    {
        auto w = writer<Coord4U>();
        w.description("4D coordinate in unsigned integer");
        w.property(szI, &Coord4U::i).description(szI_Coord);
        w.property(szJ, &Coord4U::j).description(szJ_Coord);
        w.property(szK, &Coord4U::k).description(szK_Coord);
        w.property(szL, &Coord4U::l).description(szL_Coord);
        w.print<print_coord4<unsigned>>();
    }

    {
        auto w = writer<Coord5D>();
        w.description("5D coordinate in double");
        w.property(szI, &Coord5D::i).description(szI_Coord);
        w.property(szJ, &Coord5D::j).description(szJ_Coord);
        w.property(szK, &Coord5D::k).description(szK_Coord);
        w.property(szL, &Coord5D::l).description(szL_Coord);
        w.property(szM, &Coord5D::m).description(szM_Coord);
        w.print<print_coord5<double>>();
    }

    {
        auto w = writer<Coord5F>();
        w.description("5D coordinate in float");
        w.property(szI, &Coord5F::i).description(szI_Coord);
        w.property(szJ, &Coord5F::j).description(szJ_Coord);
        w.property(szK, &Coord5F::k).description(szK_Coord);
        w.property(szL, &Coord5F::l).description(szL_Coord);
        w.property(szM, &Coord5F::m).description(szM_Coord);
        w.print<print_coord5<float>>();
    }

    {
        auto w = writer<Coord5I>();
        w.description("5D coordinate in integer");
        w.property(szI, &Coord5I::i).description(szI_Coord);
        w.property(szJ, &Coord5I::j).description(szJ_Coord);
        w.property(szK, &Coord5I::k).description(szK_Coord);
        w.property(szL, &Coord5I::l).description(szL_Coord);
        w.property(szM, &Coord5I::m).description(szM_Coord);
        w.print<print_coord5<int>>();
    }

    {
        auto w = writer<Coord5U>();
        w.description("5D coordinate in unsigned integer");
        w.property(szI, &Coord5U::i).description(szI_Coord);
        w.property(szJ, &Coord5U::j).description(szJ_Coord);
        w.property(szK, &Coord5U::k).description(szK_Coord);
        w.property(szL, &Coord5U::l).description(szL_Coord);
        w.property(szM, &Coord5U::m).description(szM_Coord);
        w.print<print_coord5<unsigned>>();
    }

    {
        auto w = writer<Coord6D>();
        w.description("6D coordinate in double");
        w.property(szI, &Coord6D::i).description(szI_Coord);
        w.property(szJ, &Coord6D::j).description(szJ_Coord);
        w.property(szK, &Coord6D::k).description(szK_Coord);
        w.property(szL, &Coord6D::l).description(szL_Coord);
        w.property(szM, &Coord6D::m).description(szM_Coord);
        w.property(szN, &Coord6D::n).description(szN_Coord);
        w.print<print_coord6<double>>();
    }

    {
        auto w = writer<Coord6F>();
        w.description("6D coordinate in float");
        w.property(szI, &Coord6F::i).description(szI_Coord);
        w.property(szJ, &Coord6F::j).description(szJ_Coord);
        w.property(szK, &Coord6F::k).description(szK_Coord);
        w.property(szL, &Coord6F::l).description(szL_Coord);
        w.property(szM, &Coord6F::m).description(szM_Coord);
        w.property(szN, &Coord6F::n).description(szN_Coord);
        w.print<print_coord6<float>>();
    }

    {
        auto w = writer<Coord6I>();
        w.description("6D coordinate in integer");
        w.property(szI, &Coord6I::i).description(szI_Coord);
        w.property(szJ, &Coord6I::j).description(szJ_Coord);
        w.property(szK, &Coord6I::k).description(szK_Coord);
        w.property(szL, &Coord6I::l).description(szL_Coord);
        w.property(szM, &Coord6I::m).description(szM_Coord);
        w.property(szN, &Coord6I::n).description(szN_Coord);
        w.print<print_coord6<int>>();
    }

    {
        auto w = writer<Coord6U>();
        w.description("6D coordinate in unsigned integer");
        w.property(szI, &Coord6U::i).description(szI_Coord);
        w.property(szJ, &Coord6U::j).description(szJ_Coord);
        w.property(szK, &Coord6U::k).description(szK_Coord);
        w.property(szL, &Coord6U::l).description(szL_Coord);
        w.property(szM, &Coord6U::m).description(szM_Coord);
        w.property(szN, &Coord6U::n).description(szN_Coord);
        w.print<print_coord6<unsigned>>();
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Cylindrical3
    
    {
        auto w = writer<Cylindrical3D>();
        w.description("3D Cylindrical coordinate in double");
        w.property(szAngle, &Cylindrical3D::angle).description(szAngle_Cylindrical).alias({szAng, szA});
        w.property(szRadius, &Cylindrical3D::radius).description(szRadius_Cylindrical).alias({szRad, szR, szDistance, szDist});
        w.property(szZ, &Cylindrical3D::z).description(szZ_Cylindrical);
    }
    
    {
        auto w = writer<Cylindrical3M>();
        w.description("3D Cylindrical coordinate in meter");
        w.property(szAngle, &Cylindrical3M::angle).description(szAngle_Cylindrical).alias({szAng, szA});
        w.property(szRadius, &Cylindrical3M::radius).description(szRadius_Cylindrical).alias({szRad, szR, szDistance, szDist});
        w.property(szZ, &Cylindrical3M::z).description(szZ_Cylindrical);
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Polar2
    
    {
        auto w = writer<Polar2D>();
        w.description("2D Polar coordinate in double");
        w.property(szAngle, &Polar2D::angle).description(szAngle_Polar).alias({szAng, szA});
        w.property(szRadius, &Polar2D::radius).description(szRadius_Polar).alias({szRad, szR, szDistance, szDist});
    }
    
    {
        auto w = writer<Polar2M>();
        w.description("2D Polar coordinate in meter");
        w.property(szAngle, &Polar2M::angle).description(szAngle_Polar).alias({szAng, szA});
        w.property(szRadius, &Polar2M::radius).description(szRadius_Polar).alias({szRad, szR, szDistance, szDist});
    }
}

YQ_INVOKE(reg_coord_math();)

#include "coord/LatLon.hxx"
#include "coord/LatLonAlt.hxx"
#include "coord/Polar2.hxx"
#include "coord/Cylindrical3.hxx"

//#include "vector/Quaternion3.hxx"
//#include "vector/Tensor33.hxx"
