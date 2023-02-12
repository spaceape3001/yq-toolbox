////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/ErrorDB.hpp>

namespace yq {
    namespace errors {
        using bad_argument              = error_code<"Bad argument provided">;
        using const_object_violation    = error_code<"Constant object violated">;
        using getter_failed             = error_code<"Getter function returned false">;
        using incompatible_types        = error_code<"Incompatible types">;
        using insufficient_arguments    = error_code<"Not enough arguments for method call">;
        using internal_error            = error_code<"Internal consistency error">;
        using invalid_conversion        = error_code<"Cannot convert invalid to anything else">;
        using invalid_conversion        = error_code<"Cannot convert invalid to anything else">;
        using name_lookup_failed        = error_code<"Name Lookup Failed" >;
        using no_getter                 = error_code<"No getter exists" >;
        using no_setter                 = error_code<"No setter exists" >;
        using no_handler                = error_code<"No handler exists" >;
        using no_conversion_handler     = error_code<"No handler registered for desired conversion" >;
        using no_print_handler          = error_code<"No print handler registered" >;
        using no_write_handler          = error_code<"No print handler registered" >;
        using null_any_type             = error_code<"Null type in Any detected" >;
        using null_destination          = error_code<"Destination is a NULL pointer">;
        using null_object               = error_code<"Object is a NULL pointer" >;
        using null_pointer              = error_code<"Null pointer not allowed" >;
        using null_result               = error_code<"Result is a NULL pointer" >;
        using null_value                = error_code<"Value is a NULL pointer" >;
        using parser_failed             = error_code<"Parser failed to parse string">;
        using setter_failed             = error_code<"Setter function returned false.">;
        using todo                      = error_code<"Feature is not yet implemented (TODO>;">;
    }
}
