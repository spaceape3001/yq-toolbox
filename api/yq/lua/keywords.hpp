////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq::lua {
    struct later_k {};
    struct upvalue_k {};
    struct upvalues_k {};
    
    static constexpr const later_k      LATER, ILL_GET_AROUND_TO_IT_LATER;
    static constexpr const upvalue_k    UPVALUE;
    static constexpr const upvalues_k   UPVALUES;
}
