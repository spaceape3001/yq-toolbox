////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/LogPriority.hpp>
#include <variant>

namespace yq {
    struct BasicAppConfig {
        using log_spec_t    = std::variant<std::monostate, LogPriority>;
        
        log_spec_t  log_cerr    = LogPriority::Debug;
        log_spec_t  log_cout    = {};
    };
}
