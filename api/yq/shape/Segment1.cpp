////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Segment1.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>

#include "Segment1.hxx"

YQ_TYPE_IMPLEMENT(yq::Segment1D)
YQ_TYPE_IMPLEMENT(yq::Segment1F)
YQ_TYPE_IMPLEMENT(yq::Segment1I)
YQ_TYPE_IMPLEMENT(yq::Segment1U)

using namespace yq;

static void reg_segment1()
{
    {
        auto w = writer<Segment1D>();
        w.description("1D Segment in double");
        w.property(szA, &Segment1D::a).description(szA_Segment);
        w.property(szB, &Segment1D::b).description(szB_Segment);
        w.format<math_io::format<Segment1D>>();
        w.parse<math_io::parse<Segment1D>>();
    }

    {
        auto w = writer<Segment1F>();
        w.description("1D Segment in float");
        w.property(szA, &Segment1F::a).description(szA_Segment);
        w.property(szB, &Segment1F::b).description(szB_Segment);
        w.format<math_io::format<Segment1F>>();
        w.parse<math_io::parse<Segment1F>>();
    }

    {
        auto w = writer<Segment1I>();
        w.description("1D Segment in integer");
        w.property(szA, &Segment1I::a).description(szA_Segment);
        w.property(szB, &Segment1I::b).description(szB_Segment);
        w.format<math_io::format<Segment1I>>();
        w.parse<math_io::parse<Segment1I>>();
    }

    {
        auto w = writer<Segment1U>();
        w.description("1D Segment in unsigned integer");
        w.property(szA, &Segment1U::a).description(szA_Segment);
        w.property(szB, &Segment1U::b).description(szB_Segment);
        w.format<math_io::format<Segment1U>>();
        w.parse<math_io::parse<Segment1U>>();
    }
}

YQ_INVOKE(reg_segment1();)
