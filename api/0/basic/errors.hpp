////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/ErrorDB.hpp>

namespace yq::errors {
    using bad_access                = error_db::entry<"Bad access">;
    using bad_argument              = error_db::entry<"Bad argument provided">;
    using bad_constant              = error_db::entry<"Bad constant">;
    using bad_conversion            = error_db::entry<"Bad conversion">;
    using bad_instruction           = error_db::entry<"Bad instruction">;
    using bad_operator              = error_db::entry<"Bad operator">;
    using bad_userexpr              = error_db::entry<"Bad user expression">;
    using bad_variable              = error_db::entry<"Bad variable">;
    using checksum_failure          = error_db::entry<"Checksum failure">;
    using const_object_violation    = error_db::entry<"Constant object violated">;
    using empty_key                 = error_db::entry<"Empty key">;
    using empty_stack               = error_db::entry<"Empty stack">;
    using empty_string              = error_db::entry<"Empty string">;
    using existing_error            = error_db::entry<"Existing error in argument">;
    using getter_failed             = error_db::entry<"Getter function returned false">;
    using incompatible_types        = error_db::entry<"Incompatible types">;
    using insufficient_arguments    = error_db::entry<"Not enough arguments for method call">;
    using internal_error            = error_db::entry<"Internal consistency error">;
    using invalid_conversion        = error_db::entry<"Cannot convert invalid to anything else">;
    using key_not_found             = error_db::entry<"Key not found">;
    using mulitple_values           = error_db::entry<"Multiple values remain">;
    using name_lookup_failed        = error_db::entry<"Name Lookup Failed" >;
    using no_file_name              = error_db::entry<"No filename specified">;
    using no_getter                 = error_db::entry<"No getter exists" >;
    using no_setter                 = error_db::entry<"No setter exists" >;
    using no_handler                = error_db::entry<"No handler exists" >;
    using no_conversion_handler     = error_db::entry<"No handler registered for desired conversion" >;
    using no_print_handler          = error_db::entry<"No print handler registered" >;
    using no_write_handler          = error_db::entry<"No print handler registered" >;
    using none                      = std::error_code;
    using not_read_enabled          = error_db::entry<"Not read enabled">;
    using not_write_enabled         = error_db::entry<"Not write enabled">;
    using null_any_type             = error_db::entry<"Null type in Any detected" >;
    using null_destination          = error_db::entry<"Destination is a NULL pointer">;
    using null_object               = error_db::entry<"Object is a NULL pointer" >;
    using null_pointer              = error_db::entry<"Null pointer not allowed" >;
    using null_source               = error_db::entry<"Source is a NULL pointer">;
    using null_result               = error_db::entry<"Result is a NULL pointer" >;
    using null_value                = error_db::entry<"Value is a NULL pointer" >;
    using parenthesis_mismatch      = error_db::entry<"Parenthesis mismatch">;
    using parser_failed             = error_db::entry<"Parser failed to parse string">;
    using setter_failed             = error_db::entry<"Setter function returned false">;
    using todo                      = error_db::entry<"Feature is not yet implemented (TODO)">;
}
