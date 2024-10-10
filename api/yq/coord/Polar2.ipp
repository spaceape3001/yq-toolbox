////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Polar2.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>
#include <yq/unit/MKS.hpp>
#include <yq/unit/metatype.hpp>

#include "Polar2.hxx"

YQ_TYPE_IMPLEMENT(yq::Polar2D)
YQ_TYPE_IMPLEMENT(yq::Polar2M)

using namespace yq;

static void reg_polar2()
{
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

YQ_INVOKE(reg_polar2();)
