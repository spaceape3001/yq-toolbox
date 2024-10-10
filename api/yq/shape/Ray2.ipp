////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Ray2.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include "Ray2.hxx"

YQ_TYPE_IMPLEMENT(yq::Ray2D)
YQ_TYPE_IMPLEMENT(yq::Ray2F)

using namespace yq;

static void reg_ray2()
{
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
}

YQ_INVOKE(reg_ray2();)
