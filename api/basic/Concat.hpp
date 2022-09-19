////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//  To use preprocessor right, for concatenation, the double-invoke is required (nuiance)

//! Concatenate two things together, this implementation required for the macro magic
#define YQ_CONCAT_IMPL(a, b) a##b
//! Concatenate two things together, a second macro has to be called for this to work.
#define YQ_CONCAT(a, b) YQ_CONCAT_IMPL(a,b)
