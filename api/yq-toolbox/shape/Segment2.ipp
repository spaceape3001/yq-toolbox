////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Segment2.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

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
    }

    {
        auto w = writer<Segment2F>();
        w.description("2D Segment in float");
        w.property(szA, &Segment2F::a).description(szA_Segment);
        w.property(szB, &Segment2F::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment2I>();
        w.description("2D Segment in integer");
        w.property(szA, &Segment2I::a).description(szA_Segment);
        w.property(szB, &Segment2I::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment2U>();
        w.description("2D Segment in unsigned integer");
        w.property(szA, &Segment2U::a).description(szA_Segment);
        w.property(szB, &Segment2U::b).description(szB_Segment);
    }
}

YQ_INVOKE(reg_segment2();)
