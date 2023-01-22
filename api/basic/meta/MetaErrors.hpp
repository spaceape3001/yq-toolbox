////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//  WARNING... this file is python auto-generated, edit MetaErrors.py and rerun.

#include <system_error>

namespace yq {
    namespace meta_error {
        std::error_code incompatible_types() noexcept;
        std::error_code name_lookup_failed() noexcept;
        std::error_code no_getter() noexcept;
        std::error_code no_setter() noexcept;
        std::error_code null_destination() noexcept;
        std::error_code null_object() noexcept;
        std::error_code null_pointer() noexcept;
        std::error_code todo() noexcept;
    }

    const std::error_category&  meta_error_category() noexcept;
}
