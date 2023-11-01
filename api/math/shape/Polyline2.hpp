////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_POLYLINE2_HPP 1

#include <math/preamble.hpp>
#include <math/vector/Vector2.hpp>

namespace yq {

    /*! \brief Structure for polyline data
    */
    template <typename T>
    struct Polyline2 {
        //! Capture the template parameter
        using component_type    = T;
        
        //! Vertex data
        std::vector<Vector2<T>>     vertex;
        
        //! Default constructor
        constexpr Polyline2() noexcept = default;

        //! Constructor by copy from vector
        Polyline2(const std::vector<Vector2<T>>&);

        //! Constructor by moving in from vector
        Polyline2(std::vector<Vector2<T>>&&);

        //! Constructor by copy from initializer list
        Polyline2(std::initializer_list<Vector2<T>>);

        //! Constructor by copy from span
        Polyline2(std::span<const Vector2<T>>);
        
        //! Constructor from segment
        explicit Polyline2(const Segment2<T>&);

        //! Converts to polyline of compatible data type
        template <typename U>
        requires std::is_convertible_v<T,U>
        explicit operator Polyline2<U>() const;

        //! Defaulted equality operator
        constexpr bool operator==(const Polyline2&) const noexcept = default;

        //! Converts to polyline data
        operator PolylineData<Vector2<T>>() const;
        
        const Polyline2&    operator+() const;
        Polyline2           operator-() const;
        
        Polyline2   operator+(const Vector2<T>&) const;
        Polyline2&  operator+=(const Vector2<T>&);
        Polyline2   operator-(const Vector2<T>&) const;
        Polyline2&  operator-=(const Vector2<T>&);

        template <typename U>
        requires is_arithmetic_v<U>
        Polyline2<product_t<T,U>> operator*(U) const;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Polyline2& operator*=(U);

        
        template <typename U>
        Polyline2<product_t<T,U>>   operator*(const Tensor22<U>&) const;
        template <typename U>
        Polyline3<product_t<T,U>>   operator*(const Tensor23<U>&) const;
        template <typename U>
        Polyline4<product_t<T,U>>   operator*(const Tensor24<U>&) const;
        
        template <typename U>
        requires self_mul_v<T,U>
        Polyline2&  operator*=(const Tensor22<U>&);

        template <typename U>
        requires is_arithmetic_v<U>
        Polyline2<quotient_t<T,U>> operator/(U) const;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Polyline2& operator/=(U);

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
    YQ_INTEGER_1(Polyline2)
    YQ_IS_INTEGER_1(Polyline2)
    YQ_ZERO_1(Polyline2, { })

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Polyline2<product_t<T,U>> operator*(T, const Polyline2<U>&b);

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

