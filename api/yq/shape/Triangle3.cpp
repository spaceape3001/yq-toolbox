////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Triangle3.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>

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
        w.format<math_io::format<Triangle3D>>();
        w.parse<math_io::parse<Triangle3D>>();
    }

    {
        auto w = writer<Triangle3F>();
        w.description("3D Triangle in float");
        w.property(szA, &Triangle3F::a).description(szA_Triangle);
        w.property(szB, &Triangle3F::b).description(szB_Triangle);
        w.property(szC, &Triangle3F::c).description(szC_Triangle);
        w.format<math_io::format<Triangle3F>>();
        w.parse<math_io::parse<Triangle3F>>();
    }

    {
        auto w = writer<Triangle3I>();
        w.description("3D Triangle in integer");
        w.property(szA, &Triangle3I::a).description(szA_Triangle);
        w.property(szB, &Triangle3I::b).description(szB_Triangle);
        w.property(szC, &Triangle3I::c).description(szC_Triangle);
        w.format<math_io::format<Triangle3I>>();
        w.parse<math_io::parse<Triangle3I>>();
    }

    {
        auto w = writer<Triangle3U>();
        w.description("3D Triangle in unsigned integer");
        w.property(szA, &Triangle3U::a).description(szA_Triangle);
        w.property(szB, &Triangle3U::b).description(szB_Triangle);
        w.property(szC, &Triangle3U::c).description(szC_Triangle);
        w.format<math_io::format<Triangle3U>>();
        w.parse<math_io::parse<Triangle3U>>();
    }
}

YQ_INVOKE(reg_triangle3();)
