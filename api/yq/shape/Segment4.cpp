////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Segment4.hpp"

#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>

#include "Segment4.hxx"

YQ_TYPE_IMPLEMENT(yq::Segment4D)
YQ_TYPE_IMPLEMENT(yq::Segment4F)
YQ_TYPE_IMPLEMENT(yq::Segment4I)
YQ_TYPE_IMPLEMENT(yq::Segment4U)

using namespace yq;

static void reg_segment4()
{
    {
        auto w = writer<Segment4D>();
        w.description("4D Segment in double");
        w.property(szA, &Segment4D::a).description(szA_Segment);
        w.property(szB, &Segment4D::b).description(szB_Segment);
        w.format<math_io::format<Segment4D>>();
        w.parse<math_io::parse<Segment4D>>();
    }

    {
        auto w = writer<Segment4F>();
        w.description("4D Segment in float");
        w.property(szA, &Segment4F::a).description(szA_Segment);
        w.property(szB, &Segment4F::b).description(szB_Segment);
        w.format<math_io::format<Segment4F>>();
        w.parse<math_io::parse<Segment4F>>();
    }

    {
        auto w = writer<Segment4I>();
        w.description("4D Segment in integer");
        w.property(szA, &Segment4I::a).description(szA_Segment);
        w.property(szB, &Segment4I::b).description(szB_Segment);
        w.format<math_io::format<Segment4I>>();
        w.parse<math_io::parse<Segment4I>>();
    }

    {
        auto w = writer<Segment4U>();
        w.description("4D Segment in unsigned integer");
        w.property(szA, &Segment4U::a).description(szA_Segment);
        w.property(szB, &Segment4U::b).description(szB_Segment);
        w.format<math_io::format<Segment4U>>();
        w.parse<math_io::parse<Segment4U>>();
    }
}

YQ_INVOKE(reg_segment4();)
