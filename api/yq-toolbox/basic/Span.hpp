////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    /*! \brief Span object
    
        This is a nominal span with from/to (instead of the data/size of std::span)
    */
    template <typename T>
    struct Span {
        T       from, to;
    };
}
