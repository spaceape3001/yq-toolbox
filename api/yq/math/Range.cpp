////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Range.hpp"
#include <yq/strings.hpp>
#include <yq/tags.hpp>
#include <yq/core/DelayInit.hpp>
#include <yq/math/math_io.hpp>
#include <yq/meta/Init.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::RangeD)
YQ_TYPE_IMPLEMENT(yq::RangeF)
YQ_TYPE_IMPLEMENT(yq::RangeI)
YQ_TYPE_IMPLEMENT(yq::RangeU)
YQ_TYPE_IMPLEMENT(yq::RangeM)
YQ_TYPE_IMPLEMENT(yq::RangeCM)
YQ_TYPE_IMPLEMENT(yq::RangeMM)

namespace {
}

static void reg_range_math()
{
    {
        auto w  = writer<RangeD>();
        w.description("Range in double");
        w.property(szLow, &RangeD::lo).description(szLow_Range).alias({szLo, szL}).tag(kTag_Save).tag(kTag_Print);
        w.property(szHigh, &RangeD::hi).description(szHigh_Range).alias({szHi, szH}).tag(kTag_Save).tag(kTag_Print);
        w.format<math_io::format<RangeD>>();
        w.parse<math_io::parse<RangeD>>();
    }
    
    {
        auto w  = writer<RangeF>();
        w.description("Range in float");
        w.property(szLow, &RangeF::lo).description(szLow_Range).alias({szLo, szL}).tag(kTag_Save).tag(kTag_Print);
        w.property(szHigh, &RangeF::hi).description(szHigh_Range).alias({szHi, szH}).tag(kTag_Save).tag(kTag_Print);
        w.format<math_io::format<RangeF>>();
        w.parse<math_io::parse<RangeF>>();
    }

    {
        auto w  = writer<RangeI>();
        w.description("Range in integer");
        w.property(szLow, &RangeI::lo).description(szLow_Range).alias({szLo, szL}).tag(kTag_Save).tag(kTag_Print);
        w.property(szHigh, &RangeI::hi).description(szHigh_Range).alias({szHi, szH}).tag(kTag_Save).tag(kTag_Print);
        w.format<math_io::format<RangeI>>();
        w.parse<math_io::parse<RangeI>>();
    }

    {
        auto w  = writer<RangeU>();
        w.description("Range in unsigned integer");
        w.property(szLow, &RangeU::lo).description(szLow_Range).alias({szLo, szL}).tag(kTag_Save).tag(kTag_Print);
        w.property(szHigh, &RangeU::hi).description(szHigh_Range).alias({szHi, szH}).tag(kTag_Save).tag(kTag_Print);
        w.format<math_io::format<RangeU>>();
        w.parse<math_io::parse<RangeU>>();
    }

    {
        auto w  = writer<RangeM>();
        w.description("Range in meter");
        w.property(szLow, &RangeM::lo).description(szLow_Range).alias({szLo, szL}).tag(kTag_Save).tag(kTag_Print);
        w.property(szHigh, &RangeM::hi).description(szHigh_Range).alias({szHi, szH}).tag(kTag_Save).tag(kTag_Print);
    }
    
    {
        auto w  = writer<RangeCM>();
        w.description("Range in centimeter");
        w.property(szLow, &RangeCM::lo).description(szLow_Range).alias({szLo, szL}).tag(kTag_Save).tag(kTag_Print);
        w.property(szHigh, &RangeCM::hi).description(szHigh_Range).alias({szHi, szH}).tag(kTag_Save).tag(kTag_Print);
    }

    {
        auto w  = writer<RangeMM>();
        w.description("Range in millimeter");
        w.property(szLow, &RangeMM::lo).description(szLow_Range).alias({szLo, szL}).tag(kTag_Save).tag(kTag_Print);
        w.property(szHigh, &RangeMM::hi).description(szHigh_Range).alias({szHi, szH}).tag(kTag_Save).tag(kTag_Print);
    }
}

YQ_INVOKE(reg_range_math();)

#include "Range.hxx"
