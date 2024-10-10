////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Range.hpp"
#include <yq/strings.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::RangeD)
YQ_TYPE_IMPLEMENT(yq::RangeF)
YQ_TYPE_IMPLEMENT(yq::RangeI)
YQ_TYPE_IMPLEMENT(yq::RangeU)

static void reg_range_math()
{
    {
        auto w  = writer<RangeD>();
        w.description("Range in double");
        w.property(szLow, &RangeD::lo).description(szLow_Range).alias({szLo, szL});
        w.property(szHigh, &RangeD::hi).description(szHigh_Range).alias({szHi, szH});
    }
    
    {
        auto w  = writer<RangeF>();
        w.description("Range in float");
        w.property(szLow, &RangeF::lo).description(szLow_Range).alias({szLo, szL});
        w.property(szHigh, &RangeF::hi).description(szHigh_Range).alias({szHi, szH});
    }

    {
        auto w  = writer<RangeI>();
        w.description("Range in integer");
        w.property(szLow, &RangeI::lo).description(szLow_Range).alias({szLo, szL});
        w.property(szHigh, &RangeI::hi).description(szHigh_Range).alias({szHi, szH});
    }

    {
        auto w  = writer<RangeU>();
        w.description("Range in unsigned integer");
        w.property(szLow, &RangeU::lo).description(szLow_Range).alias({szLo, szL});
        w.property(szHigh, &RangeU::hi).description(szHigh_Range).alias({szHi, szH});
    }
}

YQ_INVOKE(reg_range_math();)

#include "Range.hxx"
