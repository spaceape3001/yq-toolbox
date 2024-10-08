////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq-toolbox/math/Ax.hpp>

namespace yq {
    template <typename I>
    struct ScanLine2 {
        I           a       = {};
        I           b0      = {};
        I           b1      = {}; 
        
        //! Axis we're on, valid usages will be I & J
        Ax          axis    = Ax::None;
    };
}
