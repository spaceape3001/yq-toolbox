////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Ray2.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>

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
        w.format<math_io::format<Ray2D>>();
        w.parse<math_io::parse<Ray2D>>();
    }

    {
        auto w = writer<Ray2F>();
        w.description("2D ray in float");
        w.property(szPoint, &Ray2F::point).description(szPoint_Ray).alias(szPt);
        w.property(szDirection, &Ray2F::direction).description(szDirection_Ray).alias(szDir);
        w.format<math_io::format<Ray2F>>();
        w.parse<math_io::parse<Ray2F>>();
    }
}

YQ_INVOKE(reg_ray2();)
