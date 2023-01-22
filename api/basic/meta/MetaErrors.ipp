////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//  WARNING... this file is python auto-generated, edit MetaErrors.py and rerun.

#include "MetaErrors.hpp"

namespace yq {
    enum class meta_error_code : int {
        incompatible_types,
        name_lookup_failed,
        no_getter,
        no_setter,
        null_destination,
        null_object,
        null_pointer,
        todo
    };
    
    class meta_error_category_impl : public std::error_category {
    public:
        const char* name() const noexcept override { return "Meta Error"; }
        virtual std::string message( int condition ) const override
        {
            switch(static_cast<meta_error_code>(condition)){
            case meta_error_code::incompatible_types:
                return "Incompatible types";
            case meta_error_code::name_lookup_failed:
                return "Name Lookup Failed";
            case meta_error_code::no_getter:
                return "No getter exists!";
            case meta_error_code::no_setter:
                return "No setter exists!";
            case meta_error_code::null_destination:
                return "Destination is a NULL pointer!";
            case meta_error_code::null_object:
                return "Object is a NULL pointer";
            case meta_error_code::null_pointer:
                return "Null pointer not allowed";
            case meta_error_code::todo:
                return "Feature is not yet implemented (TODO)";
            default:
                return "Unknown error";
            };
        }
    };
    
    const std::error_category&  meta_error_category() noexcept
    {
        static meta_error_category_impl  s_ret;
        return s_ret;
    }
    
    std::error_code     make_error(meta_error_code ec)
    {
        return std::error_code(static_cast<int>(ec), meta_error_category());
    }

    namespace meta_error {
        std::error_code incompatible_types() noexcept
        {
            return make_error(meta_error_code::incompatible_types);
        }
        std::error_code name_lookup_failed() noexcept
        {
            return make_error(meta_error_code::name_lookup_failed);
        }
        std::error_code no_getter() noexcept
        {
            return make_error(meta_error_code::no_getter);
        }
        std::error_code no_setter() noexcept
        {
            return make_error(meta_error_code::no_setter);
        }
        std::error_code null_destination() noexcept
        {
            return make_error(meta_error_code::null_destination);
        }
        std::error_code null_object() noexcept
        {
            return make_error(meta_error_code::null_object);
        }
        std::error_code null_pointer() noexcept
        {
            return make_error(meta_error_code::null_pointer);
        }
        std::error_code todo() noexcept
        {
            return make_error(meta_error_code::todo);
        }
    }
}
