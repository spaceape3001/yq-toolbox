////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_POLYLINE4_HPP 1

#include <math/preamble.hpp>
#include <math/vector/Vector4.hpp>

namespace yq {

    /*! \brief Structure for polyline data
    */
    template <typename T>
    struct Polyline4 {
        //! Capture the template parameter
        using component_type    = T;
        
        //! Vertex data
        std::vector<Vector4<T>>     vertex;
        
        //! Default constructor
        constexpr Polyline4() noexcept = default;

        //! Constructor by copy from vector
        Polyline4(const std::vector<Vector4<T>>&);

        //! Constructor by moving in from vector
        Polyline4(std::vector<Vector4<T>>&&);

        //! Constructor by copy from initializer list
        Polyline4(std::initializer_list<Vector4<T>>);

        //! Constructor by copy from span
        Polyline4(std::span<const Vector4<T>>);
        
        //! Constructor from segment
        explicit Polyline4(const Segment4<T>&);

        //! Converts to another polyline of compatible type
        template <typename U>
        requires std::is_convertible_v<T,U>
        explicit operator Polyline4<U>() const;

        //! Defaulted equality operator
        constexpr bool operator==(const Polyline4&) const noexcept = default;

        //! Conversion to polyline data
        operator PolylineData<Vector4<T>>() const;

        //! Positive affirmation operator
        const Polyline4&    operator+() const;

        //! Negation operator
        Polyline4           operator-() const;
        
        //! Returns a shifted polyline by the given displacement
        Polyline4   operator+(const Vector4<T>&) const;

        //! Displaces this polyline by the given displacement
        Polyline4&  operator+=(const Vector4<T>&);

        //! Returns an shifted polyline by the given anti-displacement
        Polyline4   operator-(const Vector4<T>&) const;

        //! Displaces this polyline by the given anti displacement
        Polyline4&  operator-=(const Vector4<T>&);

        //! Returns a scaled polyline by the given right hand term
        template <typename U>
        requires is_arithmetic_v<U>
        Polyline4<product_t<T,U>> operator*(U) const;
        
        //! Scales this polyline by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Polyline4& operator*=(U);

        //! Projects this polyline into two dimensions
        template <typename U>
        Polyline2<product_t<T,U>>   operator*(const Tensor42<U>&) const;

        //! Projects this polyline into three dimensions
        template <typename U>
        Polyline3<product_t<T,U>>   operator*(const Tensor43<U>&) const;

        //! Projects this polyline to another four dimension space
        template <typename U>
        Polyline4<product_t<T,U>>   operator*(const Tensor44<U>&) const;
        
        //! Self-projects this polyline
        template <typename U>
        requires self_mul_v<T,U>
        Polyline4&  operator*=(const Tensor44<U>&);

        //! Returns a polyline with every element divided by the given amount
        template <typename U>
        requires is_arithmetic_v<U>
        Polyline4<quotient_t<T,U>> operator/(U) const;
        
        //! Divides every element by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Polyline4& operator/=(U);

        //! Adds a point to the polyline
        Polyline4&   operator<<(const Vector4<T>& pt);

        //! Compute the bounding box to this polyline
        constexpr AxBox4<T>   bounds() const noexcept;
        
        //! Computes the length of the polyline
        //! \note May be less accurate with non-floating point types
        T       length() const;

        //! Walks the segments of this polyline
        template <typename Pred>
        void    segments(Pred) const;

        //! Segments of this polyline
        std::vector<Segment4<T>>    segments() const;
    };

    /*! \brief Creates a polyline from a box
    */
    template <typename T>
    Polyline4<T> polyline(const AxBox4<T>& ax);

    /*! \brief Creates a polyline from points
    */
    template <typename T>
    Polyline4<T> polyline(std::span<const Vector4<T>> pts);

    /*! \brief Creates a polyline from points
    */
    template <typename T>
    Polyline4<T> polyline(std::initializer_list<const Vector4<T>> pts);

    /*! \brief Creates a polyline from points
    */
    template <typename T>
    Polyline4<T> polyline(std::vector<Vector4<T>>&& pts);

    /*! \brief Creates a polyline from a segment
    */
    template <typename T>
    Polyline4<T> polyline(const Segment4<T>&);

    YQ_IEEE754_1(Polyline4)
    YQ_INTEGER_1(Polyline4)
    YQ_IS_INTEGER_1(Polyline4)
    YQ_ZERO_1(Polyline4, { })

    /*! \brief Scales the right polyline by the left amount
    */
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Polyline4<product_t<T,U>> operator*(T, const Polyline4<U>&b);

    /*! \brief Create an axially aligned bounding box from a polyline
    */
    template <typename T>
    AxBox4<T>   aabb(const Polyline4<T>&poly);

    //! Tests that all vertices are finite
    template <typename T>
    bool is_finite(const Polyline4<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
    //! Tests for any vertice that is not-a-number
    template <typename T>
    bool is_nan(const Polyline4<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(is_nan(v))
                return true;
        return false;
    }
    
    //! Length of this polyline across all segments
    template <typename T>
    T       length(const Polyline4<T>& poly);
}

