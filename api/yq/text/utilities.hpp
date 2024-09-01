////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/text/basics.hpp>
#include <yq/text/chars.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>
#include <yq/text/starts.hpp>
#include <yq/text/vsplit.hpp>

namespace yq {
    //! Concatenates the given 32-bit UTF character on to the string as UTF-8
    std::string&  operator+=(std::string&, char32_t);



}
