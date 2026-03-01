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
#include <yq/trait/numbers.hpp>
#include <yq/graph/GBase.hpp>
#include <yq/typedef/xg_document.hpp>

namespace yq {
    template <typename> class Ref;
}

namespace yq {
    class Any;

    struct xg_cursor_t {
        uint64_t    file    = 0ULL;
        uint64_t    gid     = 0ULL;
        constexpr auto operator<=>(const xg_cursor_t&) const noexcept = default;
    };
    
    struct xg_next_t {
        xg_cursor_t     cursor;
        int32_t         priority    = 0;
        int32_t         subpri      = 0;
    };

    using xg_result_t  = std::variant<
        std::monostate,     //< Here for an empty variant, usually treated as continue
        std::error_code,    //< Alternate way of errors (can issue messages here)
        bool,               //< Decision node true/false
        continue_k,         //< Continue to next node
        done_k,             //< We're finished graph/sub-graph
        error_k,            //< Error state
        limit_k,            //< Iteration limit reached
        resume_k,           //< Resume previous state (or less-priority always...?)
        wait_k,             //< Wait for conditions to be met
        xg_cursor_t         //< Wait for result (node/edge/etc)
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
    bool    is_limit(const xg_result_t&);
    
    struct xg_execute_t {
        gid_t       gid         = 0;
        double      priority    = NaN;
    };
    
    class XGElement;
    struct XGContext;

    using XGEvaluatorFN     = std::function<xg_result_t(const XGElement&)> ;
    
    
}
