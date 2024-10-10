////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Cylindrical3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/unit/MKS.hpp>
#include <yq/unit/metatype.hpp>

#include "Cylindrical3.hpp"

YQ_TYPE_IMPLEMENT(yq::Cylindrical3D)
YQ_TYPE_IMPLEMENT(yq::Cylindrical3M)

using namespace yq;

static void reg_cylindrical3()
{
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
}

YQ_INVOKE(reg_cylindrical3();)
