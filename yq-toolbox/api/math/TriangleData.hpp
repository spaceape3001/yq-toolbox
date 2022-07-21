////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename V>
    struct TriangleData {
        V   a, b, c;
        
        constexpr bool operator==(const TriangleData&) const noexcept = default;
    };

    template <typename V>
    TriangleData<V>    triangle(const V& a, const V& b, const V& c)
    {
        return { a, b, c };
    }
}
