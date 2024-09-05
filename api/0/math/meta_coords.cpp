////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <0/math/preamble.hpp>
#include <yq-toolbox/strings.hpp>

#include <0/math/coord/LatLon.hpp>
#include <0/math/coord/LatLonAlt.hpp>
#include <0/math/coord/Polar2.hpp>
#include <0/math/coord/Cylindrical3.hpp>

#include <yq-toolbox/unit/MKS.hpp>

#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/io/StreamOps.hpp>
#include <yq-toolbox/meta/Init.hpp>

YQ_TYPE_IMPLEMENT(yq::Cylindrical3D)
YQ_TYPE_IMPLEMENT(yq::Cylindrical3M)

YQ_TYPE_IMPLEMENT(yq::Polar2D)
YQ_TYPE_IMPLEMENT(yq::Polar2M)

    
//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

static void reg_coord_math () {

    using namespace yq;

    // General order ... all alphabetical
    //
    //      1. properties
    //      2. methods
    //


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
