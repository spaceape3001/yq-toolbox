////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Segment2.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>

#include "Segment2.hxx"

YQ_TYPE_IMPLEMENT(yq::Segment2D)
YQ_TYPE_IMPLEMENT(yq::Segment2F)
YQ_TYPE_IMPLEMENT(yq::Segment2I)
YQ_TYPE_IMPLEMENT(yq::Segment2U)

using namespace yq;

static void reg_segment2()
{
    {
        auto w = writer<Segment2D>();
        w.description("2D Segment in double");
        w.property(szA, &Segment2D::a).description(szA_Segment);
        w.property(szB, &Segment2D::b).description(szB_Segment);
        w.format<math_io::format<Segment2D>>();
        w.parse<math_io::parse<Segment2D>>();
    }

    {
        auto w = writer<Segment2F>();
        w.description("2D Segment in float");
        w.property(szA, &Segment2F::a).description(szA_Segment);
        w.property(szB, &Segment2F::b).description(szB_Segment);
        w.format<math_io::format<Segment2F>>();
        w.parse<math_io::parse<Segment2F>>();
    }

    {
        auto w = writer<Segment2I>();
        w.description("2D Segment in integer");
        w.property(szA, &Segment2I::a).description(szA_Segment);
        w.property(szB, &Segment2I::b).description(szB_Segment);
        w.format<math_io::format<Segment2I>>();
        w.parse<math_io::parse<Segment2I>>();
    }

    {
        auto w = writer<Segment2U>();
        w.description("2D Segment in unsigned integer");
        w.property(szA, &Segment2U::a).description(szA_Segment);
        w.property(szB, &Segment2U::b).description(szB_Segment);
        w.format<math_io::format<Segment2U>>();
        w.parse<math_io::parse<Segment2U>>();
    }
}

YQ_INVOKE(reg_segment2();)
