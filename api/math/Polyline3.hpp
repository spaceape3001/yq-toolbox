////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>

namespace yq {

    /*! \brief Structure for polyline data
    */
    template <typename T>
    struct Polyline3 {
        //! Capture the template parameter
        using component_type    = T;
        
        //! Vertex data
        std::vector<Vector3<T>>     vertex;
        
        constexpr Polyline3() noexcept = default;
        Polyline3(const std::vector<Vector3<T>>&);
        Polyline3(std::vector<Vector3<T>>&&);
        Polyline3(std::initializer_list<Vector3<T>>);
        Polyline3(std::span<const Vector3<T>>);
        
        explicit Polyline3(const Segment3<T>&);

        //! Defaulted equality operator
        constexpr bool operator==(const Polyline3&) const noexcept = default;

        operator PolylineData<Vector3<T>>() const;

        //! Addsa a point to the polyline
        Polyline3&   operator<<(const Vector3<T>& pt);

        const Polyline3&    operator+() const;
        Polyline3           operator-() const;
        
        Polyline3   operator+(const Vector3<T>&) const;
        Polyline3&  operator+=(const Vector3<T>&);
        Polyline3   operator-(const Vector3<T>&) const;
        Polyline3&  operator-=(const Vector3<T>&);

        template <typename U>
        Polyline2<trait::product_t<T,U>>   operator*(const Tensor32<U>&) const;
        template <typename U>
        Polyline3<trait::product_t<T,U>>   operator*(const Tensor33<U>&) const;
        template <typename U>
        Polyline4<trait::product_t<T,U>>   operator*(const Tensor34<U>&) const;
        
        template <typename U>
        requires trait::self_mul_v<T,U>
        Polyline3&  operator*=(const Tensor33<U>&);

        //! Compute the bounding box to this polyline
        constexpr AxBox3<T>   bounds() const noexcept;
        
        //! Computes the length of the polyline
        //! \note May be less accurate with non-floating point types
        T       length() const;

        template <typename Pred>
        void    segments(Pred) const;

        std::vector<Segment3<T>>    segments() const;
    };

    /*! \brief Creates a polyline from a box
    */
    template <typename T>
    Polyline3<T> polyline(const AxBox3<T>& ax);

    template <typename T>
    Polyline3<T> polyline(std::span<const Vector3<T>> pts);

    template <typename T>
    Polyline3<T> polyline(std::initializer_list<const Vector3<T>> pts);

    template <typename T>
    Polyline3<T> polyline(std::vector<Vector3<T>>&& pts);

    template <typename T>
    Polyline3<T> polyline(const Segment3<T>&);

    YQ_IEEE754_1(Polyline3)
    YQ_ZERO_1(Polyline3, { })


    /*! \brief Create an axially aligned bounding box from a polyline
    */
    template <typename T>
    AxBox3<T>   aabb(const Polyline3<T>&poly);

    //! Tests that all vertices are finite
    template <typename T>
    bool is_finite(const Polyline3<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
    //! Tests for any vertice that is not-a-number
    template <typename T>
    bool is_nan(const Polyline3<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(is_nan(v))
                return true;
        return false;
    }
    
    template <typename T>
    T       length(const Polyline3<T>& poly);
}

