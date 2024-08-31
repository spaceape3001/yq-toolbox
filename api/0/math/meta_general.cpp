////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <0/math/preamble.hpp>
#include <0/math/Counter.hpp>
#include <0/math/strings.hpp>
#include <yq/basic/DelayInit.hpp>
#include <0/meta/Init.hpp>


using namespace yq;

YQ_TYPE_IMPLEMENT(yq::CountI8)
YQ_TYPE_IMPLEMENT(yq::CountI16)
YQ_TYPE_IMPLEMENT(yq::CountI32)
YQ_TYPE_IMPLEMENT(yq::CountI64)

YQ_TYPE_IMPLEMENT(yq::CountU8)
YQ_TYPE_IMPLEMENT(yq::CountU16)
YQ_TYPE_IMPLEMENT(yq::CountU32)
YQ_TYPE_IMPLEMENT(yq::CountU64)



YQ_TYPE_IMPLEMENT(yq::HCountI8)
YQ_TYPE_IMPLEMENT(yq::HCountI16)
YQ_TYPE_IMPLEMENT(yq::HCountI32)
YQ_TYPE_IMPLEMENT(yq::HCountI64)

YQ_TYPE_IMPLEMENT(yq::HCountU8)
YQ_TYPE_IMPLEMENT(yq::HCountU16)
YQ_TYPE_IMPLEMENT(yq::HCountU32)
YQ_TYPE_IMPLEMENT(yq::HCountU64)

YQ_TYPE_IMPLEMENT(yq::LCountI8)
YQ_TYPE_IMPLEMENT(yq::LCountI16)
YQ_TYPE_IMPLEMENT(yq::LCountI32)
YQ_TYPE_IMPLEMENT(yq::LCountI64)

//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//  OTHER HELPERS FOR MATH

    
//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

static void reg_general_math () {

    // General order ... all alphabetical
    //
    //      1. properties
    //      2. methods
    //
    

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Counters

    {
        auto w   = writer<CountI8>();
        w.description("Counter with 8-bit integer");
        w.property(szCount, &CountI8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountI16>();
        w.description("Counter with 16-bit integer");
        w.property(szCount, &CountI16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountI32>();
        w.description("Counter with 32-bit integer");
        w.property(szCount, &CountI32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountI64>();
        w.description("Counter with 64-bit integer");
        w.property(szCount, &CountI64::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountU8>();
        w.description("Counter with 8-bit unsigned integer");
        w.property(szCount, &CountU8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountU16>();
        w.description("Counter with 16-bit unsigned integer");
        w.property(szCount, &CountU16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountU32>();
        w.description("Counter with 32-bit unsigned integer");
        w.property(szCount, &CountU32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountU64>();
        w.description("Counter with 64-bit unsigned integer");
        w.property(szCount, &CountU64::cnt).description(szCount_Count).alias(szCnt);
    }



    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Hi-counters (start at max-value)
    {
        auto w   = writer<HCountI8>();
        w.description("8-bit signed integer counter that starts at max value");
        w.property(szCount, &HCountI8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountI16>();
        w.description("16-bit signed integer counter that starts at max value");
        w.property(szCount, &HCountI16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountI32>();
        w.description("32-bit signed integer counter that starts at max value");
        w.property(szCount, &HCountI32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountI64>();
        w.description("64-bit signed integer counter that starts at max value");
        w.property(szCount, &HCountI64::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountU8>();
        w.description("8-bit unsigned integer counter that starts at max value");
        w.property(szCount, &HCountU8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountU16>();
        w.description("16-bit unsigned integer counter that starts at max value");
        w.property(szCount, &HCountU16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountU32>();
        w.description("32-bit unsigned integer counter that starts at max value");
        w.property(szCount, &HCountU32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountU64>();
        w.description("64-bit unsigned integer counter that starts at max value");
        w.property(szCount, &HCountU64::cnt).description(szCount_Count).alias(szCnt);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Lo-counters (start at min-value)
    
    {
        auto w   = writer<LCountI8>();
        w.description("8-bit integer counter that starts at minimum value");
        w.property(szCount, &LCountI8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<LCountI16>();
        w.description("16-bit integer counter that starts at minimum value");
        w.property(szCount, &LCountI16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<LCountI32>();
        w.description("32-bit integer counter that starts at minimum value");
        w.property(szCount, &LCountI32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<LCountI64>();
        w.description("64-bit integer counter that starts at minimum value");
        w.property(szCount, &LCountI64::cnt).description(szCount_Count).alias(szCnt);
    }


}

YQ_INVOKE(reg_general_math();)

