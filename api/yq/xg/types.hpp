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

namespace yq {
    template <typename> class Ref;
}

namespace yq::xg {
    using result_t  = std::variant<
        std::monostate,     //< Here for an empty variant, usually treated as continue
        continue_k,         //< Continue to next node
        wait_k,             //< Wait for conditions to be met
        error_k,            //< Error state
        std::error_code,    //< Alternate way of errors (can issue messages here)
        done_k              //< We're finished
    >;
    
    bool    is_continue(const result_t&);
    bool    is_wait(const result_t&);
    bool    is_done(const result_t&);
    bool    is_error(const result_t&);
    
    
    using id_t          = uint32_t;
    using order_t       = float;
    
    struct execute_t {
        float   pri     = 0.;
        id_t    idx     = 0;
    };
    
    class XGDocument;
    class XGElement;
    struct XGContext;
    
    using XGDocumentPtr     = Ref<XGDocument>       ;
    using XGDocumentCPtr    = Ref<const XGDocument>;
}
