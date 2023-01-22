#!/usr/bin/python

#   Quick script to generate errors

import io, os, sys, pathlib

if len(sys.argv)>1:
    OUTDIR = sys.argv[1]
else:
    OUTDIR  = '.'

pathlib.Path(OUTDIR).mkdir(parents=True, exist_ok=True)

class ErrorCode:
    ALL     = []
    def __init__(self, k, txt):
        self.name   = k
        self.text   = txt
        ErrorCode.ALL.append(self)

ErrorCode("getter_failed", "Getter function returned false.")
ErrorCode("incompatible_types", "Incompatible types" )
ErrorCode("invalid_conversion", "Cannot convert invalid to anything else")
ErrorCode("name_lookup_failed", "Name Lookup Failed" )
ErrorCode("no_getter", "No getter exists" )
ErrorCode("no_setter", "No setter exists" )
ErrorCode("no_handler", "No handler exists" )
ErrorCode("no_conversion_handler", "No handler registered for desired conversion" )
ErrorCode("no_print_handler", "No print handler registered" )
ErrorCode("no_write_handler", "No print handler registered" )
ErrorCode("null_any_type", "Null type in Any detected" )
ErrorCode("null_destination", "Destination is a NULL pointer")
ErrorCode("null_object", "Object is a NULL pointer" )
ErrorCode("null_pointer", "Null pointer not allowed" )
ErrorCode("null_value", "Value is a NULL pointer" )
ErrorCode("parser_failed", "Parser failed to parse string")
ErrorCode("setter_failed", "Setter function returned false.")
ErrorCode("todo", "Feature is not yet implemented (TODO)")

with open("%s/Errors.hpp" % OUTDIR, "w") as f:
    f.write("""////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//  WARNING... this file is python auto-generated, edit MetaErrors.py and rerun.

#include <system_error>

namespace yq {
    namespace errors {
""")

    for ec in ErrorCode.ALL:
        f.write("        std::error_code %s() noexcept;\n" % ec.name )
    f.write("""    }

    const std::error_category&  error_category() noexcept;
}
""")


with open("%s/Errors.ipp" % OUTDIR, "w") as f:
    f.write("""////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//  WARNING... this file is python auto-generated, edit MetaErrors.py and rerun.

#include "Errors.hpp"

namespace yq {
    enum class error_code : int {""")
    c   = False
    for ec in ErrorCode.ALL:
        if c == True:
            f.write(",")
        else:
            c   = True
        f.write("\n        %s" % ec.name)
    f.write("""
    };
    
    class error_category_impl : public std::error_category {
    public:
        const char* name() const noexcept override { return "yq errors"; }
        virtual std::string message( int condition ) const override
        {
            switch(static_cast<error_code>(condition)){""");
    for ec in ErrorCode.ALL:
        f.write("""
            case error_code::%s:
                return "%s";""" % ( ec.name, ec.text ))
    f.write("""
            default:
                return "Unknown error";
            };
        }
    };
    
    const std::error_category&  error_category() noexcept
    {
        static error_category_impl  s_ret;
        return s_ret;
    }
    
    std::error_code     make_error(error_code ec)
    {
        return std::error_code(static_cast<int>(ec), error_category());
    }

    namespace errors {""")
    
    for ec in ErrorCode.ALL:
        f.write("""
        std::error_code %s() noexcept
        {
            return make_error(error_code::%s);
        }""" % (ec.name, ec.name))
        
    f.write("""
    }
}
""")


