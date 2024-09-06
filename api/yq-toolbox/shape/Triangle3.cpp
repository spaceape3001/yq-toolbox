////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Triangle3.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include "Triangle3.hxx"

YQ_TYPE_IMPLEMENT(yq::Triangle3D)
YQ_TYPE_IMPLEMENT(yq::Triangle3F)
YQ_TYPE_IMPLEMENT(yq::Triangle3I)
YQ_TYPE_IMPLEMENT(yq::Triangle3U)

using namespace yq;

static void reg_triangle3()
{
    {
        auto w = writer<Triangle3D>();
        w.description("3D Triangle in double");
        w.property(szA, &Triangle3D::a).description(szA_Triangle);
        w.property(szB, &Triangle3D::b).description(szB_Triangle);
        w.property(szC, &Triangle3D::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle3F>();
        w.description("3D Triangle in float");
        w.property(szA, &Triangle3F::a).description(szA_Triangle);
        w.property(szB, &Triangle3F::b).description(szB_Triangle);
        w.property(szC, &Triangle3F::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle3I>();
        w.description("3D Triangle in integer");
        w.property(szA, &Triangle3I::a).description(szA_Triangle);
        w.property(szB, &Triangle3I::b).description(szB_Triangle);
        w.property(szC, &Triangle3I::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle3U>();
        w.description("3D Triangle in unsigned integer");
        w.property(szA, &Triangle3U::a).description(szA_Triangle);
        w.property(szB, &Triangle3U::b).description(szB_Triangle);
        w.property(szC, &Triangle3U::c).description(szC_Triangle);
    }
}

YQ_INVOKE(reg_triangle3();)
