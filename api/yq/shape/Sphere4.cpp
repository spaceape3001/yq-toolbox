////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Sphere4.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>

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
        w.format<math_io::format<Sphere4D>>();
        w.parse<math_io::parse<Sphere4D>>();
    }

    {
        auto w = writer<Sphere4F>();
        w.description("4D sphere in float");
        w.property(szCenter, &Sphere4F::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere4F::radius).description(szRadius_Sphere).alias({szRad, szR});
        w.property(szHypervolume, &Sphere4F::hypervolume).description(szHypervolume_Sphere4);
        w.format<math_io::format<Sphere4F>>();
        w.parse<math_io::parse<Sphere4F>>();
    }

    {
        auto w = writer<Sphere4I>();
        w.description("4D sphere in integer");
        w.property(szCenter, &Sphere4I::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere4I::radius).description(szRadius_Sphere).alias({szRad, szR});
        w.format<math_io::format<Sphere4I>>();
        w.parse<math_io::parse<Sphere4I>>();
    }

    {
        auto w = writer<Sphere4U>();
        w.description("4D sphere in unsigned integer");
        w.property(szCenter, &Sphere4U::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere4U::radius).description(szRadius_Sphere).alias({szRad, szR});
        w.format<math_io::format<Sphere4U>>();
        w.parse<math_io::parse<Sphere4U>>();
    }
}

YQ_INVOKE(reg_sphere4();)

