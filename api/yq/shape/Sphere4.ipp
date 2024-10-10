////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Sphere4.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include "Sphere4.hxx"

YQ_TYPE_IMPLEMENT(yq::Sphere4D)
YQ_TYPE_IMPLEMENT(yq::Sphere4F)
YQ_TYPE_IMPLEMENT(yq::Sphere4I)
YQ_TYPE_IMPLEMENT(yq::Sphere4U)

using namespace yq;

static void reg_sphere4()
{
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
}

YQ_INVOKE(reg_sphere4();)

