////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    /*! \brief Data for a segment
    
        \note Can be the vertex themselves, or other data.
    */
    template <typename V>
    struct SegmentData {
        V   a, b;
        
        constexpr bool operator==(const SegmentData&) const noexcept = default;
    };
}
