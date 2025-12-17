////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Triangle4.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>

#include "Triangle4.hxx"

YQ_TYPE_IMPLEMENT(yq::Triangle4D)
YQ_TYPE_IMPLEMENT(yq::Triangle4F)
YQ_TYPE_IMPLEMENT(yq::Triangle4I)
YQ_TYPE_IMPLEMENT(yq::Triangle4U)

using namespace yq;

static void reg_triangle4()
{
    {
        auto w = writer<Triangle4D>();
        w.description("4D Triangle in double");
        w.property(szA, &Triangle4D::a).description(szA_Triangle);
        w.property(szB, &Triangle4D::b).description(szB_Triangle);
        w.property(szC, &Triangle4D::c).description(szC_Triangle);
        w.format<math_io::format<Triangle4D>>();
        w.parse<math_io::parse<Triangle4D>>();
    }

    {
        auto w = writer<Triangle4F>();
        w.description("4D Triangle in float");
        w.property(szA, &Triangle4F::a).description(szA_Triangle);
        w.property(szB, &Triangle4F::b).description(szB_Triangle);
        w.property(szC, &Triangle4F::c).description(szC_Triangle);
        w.format<math_io::format<Triangle4F>>();
        w.parse<math_io::parse<Triangle4F>>();
    }

    {
        auto w = writer<Triangle4I>();
        w.description("4D Triangle in integer");
        w.property(szA, &Triangle4I::a).description(szA_Triangle);
        w.property(szB, &Triangle4I::b).description(szB_Triangle);
        w.property(szC, &Triangle4I::c).description(szC_Triangle);
        w.format<math_io::format<Triangle4I>>();
        w.parse<math_io::parse<Triangle4I>>();
    }

    {
        auto w = writer<Triangle4U>();
        w.description("4D Triangle in unsigned integer");
        w.property(szA, &Triangle4U::a).description(szA_Triangle);
        w.property(szB, &Triangle4U::b).description(szB_Triangle);
        w.property(szC, &Triangle4U::c).description(szC_Triangle);
        w.format<math_io::format<Triangle4U>>();
        w.parse<math_io::parse<Triangle4U>>();
    }
}

YQ_INVOKE(reg_triangle4();)
