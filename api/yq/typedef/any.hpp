////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <span>
#include <system_error>
#include <utility>
#include <yq/container/forward.hpp>

namespace yq {
    class Any;

    using any_error_t       = std::pair<Any, std::error_code>;
    using any_span_t        = std::span<Any>;
    using const_any_span_t  = std::span<const Any>;
    using any_stack_t       = Stack<Any>;
}
