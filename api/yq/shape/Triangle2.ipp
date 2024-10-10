////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Triangle2.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

#include "Triangle2.hxx"

YQ_TYPE_IMPLEMENT(yq::Triangle2D)
YQ_TYPE_IMPLEMENT(yq::Triangle2F)
YQ_TYPE_IMPLEMENT(yq::Triangle2I)
YQ_TYPE_IMPLEMENT(yq::Triangle2U)

using namespace yq;

static void reg_triangle2()
{
    {
        auto w = writer<Triangle2D>();
        w.description("2D Triangle in double");
        w.property(szA, &Triangle2D::a).description(szA_Triangle);
        w.property(szB, &Triangle2D::b).description(szB_Triangle);
        w.property(szC, &Triangle2D::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle2F>();
        w.description("2D Triangle in float");
        w.property(szA, &Triangle2F::a).description(szA_Triangle);
        w.property(szB, &Triangle2F::b).description(szB_Triangle);
        w.property(szC, &Triangle2F::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle2I>();
        w.description("2D Triangle in integer");
        w.property(szA, &Triangle2I::a).description(szA_Triangle);
        w.property(szB, &Triangle2I::b).description(szB_Triangle);
        w.property(szC, &Triangle2I::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle2U>();
        w.description("2D Triangle in unsigned integer");
        w.property(szA, &Triangle2U::a).description(szA_Triangle);
        w.property(szB, &Triangle2U::b).description(szB_Triangle);
        w.property(szC, &Triangle2U::c).description(szC_Triangle);
    }
}

YQ_INVOKE(reg_triangle2();)
