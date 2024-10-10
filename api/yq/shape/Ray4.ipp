////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Ray4.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include "Ray4.hxx"

YQ_TYPE_IMPLEMENT(yq::Ray4D)
YQ_TYPE_IMPLEMENT(yq::Ray4F)

using namespace yq;

static void reg_ray4()
{
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
}

YQ_INVOKE(reg_ray4();)
