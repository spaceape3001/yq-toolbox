////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Sphere3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include "Sphere3.hxx"

YQ_TYPE_IMPLEMENT(yq::Sphere3D)
YQ_TYPE_IMPLEMENT(yq::Sphere3F)
YQ_TYPE_IMPLEMENT(yq::Sphere3I)
YQ_TYPE_IMPLEMENT(yq::Sphere3U)

using namespace yq;

static void reg_sphere3()
{

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
}

YQ_INVOKE(reg_sphere3();)
