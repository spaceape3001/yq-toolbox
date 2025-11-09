////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq::lua {
    struct later_k {};
    struct table_k {};
    struct upvalue_k {};
    struct upvalues_k {};
    
    static const constexpr later_k      LATER, ILL_GET_AROUND_TO_IT_LATER;
    static const constexpr table_k      TABLE;
    static const constexpr upvalue_k    UPVALUE;
    static const constexpr upvalues_k   UPVALUES;
}
