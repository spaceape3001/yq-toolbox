////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {

    /*! \brief Data for a triangle
    */
    template <typename V>
    struct TriangleData {
    
        //! Data for "A" vertex
        V   a;
        
        //! Data for "B" vertex
        V   b;
        
        //! Data for "C" vertex
        V   c;
        
        //! Defaulted equality operator
        constexpr bool operator==(const TriangleData&) const noexcept = default;
    };


    //! Creates triangle data from three datas 
    //  (TODO, preclude Vector1/2/3/4 types)?
    template <typename V>
    TriangleData<V>    triangle(const V& a, const V& b, const V& c)
    {
        return { a, b, c };
    }
}
