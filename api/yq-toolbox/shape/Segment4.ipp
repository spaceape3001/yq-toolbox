////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Segment4.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>

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
    }

    {
        auto w = writer<Segment4F>();
        w.description("4D Segment in float");
        w.property(szA, &Segment4F::a).description(szA_Segment);
        w.property(szB, &Segment4F::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment4I>();
        w.description("4D Segment in integer");
        w.property(szA, &Segment4I::a).description(szA_Segment);
        w.property(szB, &Segment4I::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment4U>();
        w.description("4D Segment in unsigned integer");
        w.property(szA, &Segment4U::a).description(szA_Segment);
        w.property(szB, &Segment4U::b).description(szB_Segment);
    }
}

YQ_INVOKE(reg_segment4();)
