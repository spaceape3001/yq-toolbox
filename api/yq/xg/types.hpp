////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>

#include <cstdint>
#include <variant>
#include <system_error>
#include <yq/typedef/xg_document.hpp>

namespace yq {
    template <typename> class Ref;
}

namespace yq {
    class Any;
    
    using xg_result_t  = std::variant<
        std::monostate,     //< Here for an empty variant, usually treated as continue
        continue_k,         //< Continue to next node
        wait_k,             //< Wait for conditions to be met
        resume_k,           //< Resume previous state (or less-priority always...?)
        error_k,            //< Error state
        std::error_code,    //< Alternate way of errors (can issue messages here)
        done_k              //< We're finished graph/sub-graph
    >;
    
    
    // This might not be generic enough (TBD)
    using xg_value_t       = std::variant<
        std::monostate, 
        bool, 
        Any
    >;

    bool    is_continue(const xg_result_t&);
    bool    is_wait(const xg_result_t&);
    bool    is_done(const xg_result_t&);
    bool    is_error(const xg_result_t&);
    
    
    using xg_id_t          = uint32_t;
    using xg_priority_t    = float;
    
    struct xg_execute_t {
        xg_priority_t   pri = 0.;
        xg_id_t         idx = 0;
    };
    
    class XGElement;
    struct XGContext;
}
