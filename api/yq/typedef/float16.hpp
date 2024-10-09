////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

//! This is *specific* for x86/GCC, need to adjust for other compilers

#if defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
    using float16_t  = _Float16;
#else
    #error "Need to specify 16-float for this architecture/compiler"
#endif
