#!/usr/bin/python

#   Quick script to generate errors

import io, os, sys

class ErrorCode:
    ALL     = []
    def __init__(self, k, txt):
        self.name   = k
        self.text   = txt
        ErrorCode.ALL.append(self)

ErrorCode("incompatible_types", "Incompatible types" )
ErrorCode("name_lookup_failed", "Name Lookup Failed" )
ErrorCode("no_getter", "No getter exists!" )
ErrorCode("no_setter", "No setter exists!" )
ErrorCode("null_destination", "Destination is a NULL pointer!")
ErrorCode("null_object", "Object is a NULL pointer" )
ErrorCode("null_pointer", "Null pointer not allowed" )
ErrorCode("todo", "Feature is not yet implemented (TODO)")

with open("MetaErrors.hpp", "w") as f:
    f.write("""////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//  WARNING... this file is python auto-generated, edit MetaErrors.py and rerun.

#include <system_error>

namespace yq {
    namespace meta_error {
""")

    for ec in ErrorCode.ALL:
        f.write("        std::error_code %s() noexcept;\n" % ec.name )
    f.write("""    }

    const std::error_category&  meta_error_category() noexcept;
}
""")


with open("MetaErrors.ipp", "w") as f:
    f.write("""////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//  WARNING... this file is python auto-generated, edit MetaErrors.py and rerun.

#include "MetaErrors.hpp"

namespace yq {
    enum class meta_error_code : int {""")
    c   = False
    for ec in ErrorCode.ALL:
        if c == True:
            f.write(",")
        else:
            c   = True
        f.write("\n        %s" % ec.name)
    f.write("""
    };
    
    class meta_error_category_impl : public std::error_category {
    public:
        const char* name() const noexcept override { return "Meta Error"; }
        virtual std::string message( int condition ) const override
        {
            switch(static_cast<meta_error_code>(condition)){""");
    for ec in ErrorCode.ALL:
        f.write("""
            case meta_error_code::%s:
                return "%s";""" % ( ec.name, ec.text ))
    f.write("""
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

    namespace meta_error {""")
    
    for ec in ErrorCode.ALL:
        f.write("""
        std::error_code %s() noexcept
        {
            return make_error(meta_error_code::%s);
        }""" % (ec.name, ec.name))
        
    f.write("""
    }
}
""")


