////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {

    /*! \brief Structure for polyline data
    */
    template <typename T>
    struct Polyline2 {
        //! Capture the template parameter
        using component_type    = T;
        
        //! Vertex data
        std::vector<Vector2<T>>     vertex;
        
        constexpr Polyline2() noexcept = default;
        Polyline2(const std::vector<Vector2<T>>&);
        Polyline2(std::vector<Vector2<T>>&&);
        Polyline2(std::initializer_list<Vector2<T>>);
        Polyline2(std::span<const Vector2<T>>);
        
        explicit Polyline2(const Segment2<T>&);

        //! Defaulted equality operator
        constexpr bool operator==(const Polyline2&) const noexcept = default;

        operator PolylineData<Vector2<T>>() const;

        //! Addsa a point to the polyline
        Polyline2&   operator<<(const Vector2<T>& pt);

        //! Compute the bounding box to this polyline
        constexpr AxBox2<T>   bounds() const noexcept;
        
        //! Computes the length of the polyline
        //! \note May be less accurate with non-floating point types
        T       length() const;

        template <typename Pred>
        void    segments(Pred) const;

        std::vector<Segment2<T>>    segments() const;
    };

    /*! \brief Creates a polyline from a box
    */
    template <typename T>
    Polyline2<T> polyline(const AxBox2<T>& ax);

    template <typename T>
    Polyline2<T> polyline(std::span<const Vector2<T>> pts);

    template <typename T>
    Polyline2<T> polyline(std::initializer_list<const Vector2<T>> pts);

    template <typename T>
    Polyline2<T> polyline(std::vector<Vector2<T>>&& pts);

    template <typename T>
    Polyline2<T> polyline(const Segment2<T>&);

    YQ_IEEE754_1(Polyline2)
    YQ_ZERO_1(Polyline2, { })


    /*! \brief Create an axially aligned bounding box from a polyline
    */
    template <typename T>
    AxBox2<T>   aabb(const Polyline2<T>&poly);

    //! Tests that all vertices are finite
    template <typename T>
    bool is_finite(const Polyline2<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
    //! Tests for any vertice that is not-a-number
    template <typename T>
    bool is_nan(const Polyline2<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(is_nan(v))
                return true;
        return false;
    }
    
    template <typename T>
    T       length(const Polyline2<T>& poly);
}

