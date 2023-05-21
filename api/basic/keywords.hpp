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
    struct copy_t {};
    struct move_t {};
    struct no_throw_t {};
    struct parse_t {};
    struct ref_t {};
    struct set_t {};
    struct span_t {};
    struct throw_t {};
    struct zero_t {};

    static constexpr const all_t        ALL;
    static constexpr const copy_t       COPY;
    static constexpr const move_t       MOVE;
    static constexpr const no_throw_t   NO_THROW;
    static constexpr const parse_t      PARSE;
    static constexpr const ref_t        REF;
    static constexpr const set_t        SET;
    static constexpr const span_t       SPAN;
    static constexpr const throw_t      THROW;
    static constexpr const zero_t       ZERO;
}
