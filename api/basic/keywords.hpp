////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/*
    This file is about making new keywords that can be used in the constructors and function overloads.
*/

namespace yq {
        //  keywords
    struct all_t {};
    struct no_throw_t {};
    struct parse_t {};
    struct throw_t {};

    static constexpr const all_t            ALL;
    static constexpr const no_throw_t   NO_THROW;
    static constexpr const parse_t      PARSE;
    static constexpr const throw_t      THROW;
}
