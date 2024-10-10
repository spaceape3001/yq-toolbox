////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Ray3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include "Ray3.hxx"

YQ_TYPE_IMPLEMENT(yq::Ray3D)
YQ_TYPE_IMPLEMENT(yq::Ray3F)

using namespace yq;

static void reg_ray3()
{
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
}

YQ_INVOKE(reg_ray3();)
