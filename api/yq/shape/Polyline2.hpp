////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_POLYLINE2_HPP 1

#include <yq/typedef/polyline2.hpp>

#include <yq/vector/Vector2.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename> struct Polyline3;
    template <typename> struct Polyline4;
    template <typename> struct PolylineData;
    template <typename> struct Tensor22;
    template <typename> struct Tensor23;
    template <typename> struct Tensor24;

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
        
        //! Positive affirmation operator
        const Polyline2&    operator+() const;

        //! Negation operator
        Polyline2           operator-() const;
        
        //! Returns a shifted polyline by the given displacement
        Polyline2   operator+(const Vector2<T>&) const;

        //! Displaces this polyline by the given displacement
        Polyline2&  operator+=(const Vector2<T>&);

        //! Returns an shifted polyline by the given anti-displacement
        Polyline2   operator-(const Vector2<T>&) const;

        //! Displaces this polyline by the given anti displacement
        Polyline2&  operator-=(const Vector2<T>&);

        //! Returns a scaled polyline by the given right hand term
        template <typename U>
        requires is_arithmetic_v<U>
        Polyline2<product_t<T,U>> operator*(U) const;
        
        //! Scales this polyline by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Polyline2& operator*=(U);

        
        //! Projects this polyline to another two dimension space
        template <typename U>
        Polyline2<product_t<T,U>>   operator*(const Tensor22<U>&) const;

        //! Projects this polyline into three dimensions
        template <typename U>
        Polyline3<product_t<T,U>>   operator*(const Tensor23<U>&) const;

        //! Projects this polyline into four dimensions
        template <typename U>
        Polyline4<product_t<T,U>>   operator*(const Tensor24<U>&) const;
        
        //! Self-projects this polyline
        template <typename U>
        requires self_multiply_v<T,U>
        Polyline2&  operator*=(const Tensor22<U>&);

        //! Returns a polyline with every element divided by the given amount
        template <typename U>
        requires is_arithmetic_v<U>
        Polyline2<quotient_t<T,U>> operator/(U) const;
        
        //! Divides every element by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Polyline2& operator/=(U);

        //! Addsa a point to the polyline
        Polyline2&   operator<<(const Vector2<T>& pt);

        //! Compute the bounding box to this polyline
        constexpr AxBox2<T>   bounds() const noexcept;
        
        //! Computes the length of the polyline
        //! \note May be less accurate with non-floating point types
        T       length() const;

        //! Walks the segments of this polyline
        template <typename Pred>
        void    segments(Pred) const;

        //! Segments of this polyline
        std::vector<Segment2<T>>    segments() const;
    };

    /*! \brief Creates a polyline from a box
    */
    template <typename T>
    Polyline2<T> polyline(const AxBox2<T>& ax);

    /*! \brief Creates a polyline from points
    */
    template <typename T>
    Polyline2<T> polyline(std::span<const Vector2<T>> pts);

    /*! \brief Creates a polyline from points
    */
    template <typename T>
    Polyline2<T> polyline(std::initializer_list<const Vector2<T>> pts);

    /*! \brief Creates a polyline from points
    */
    template <typename T>
    Polyline2<T> polyline(std::vector<Vector2<T>>&& pts);

    /*! \brief Creates a polyline from a segment
    */
    template <typename T>
    Polyline2<T> polyline(const Segment2<T>&);

    YQ_IEEE754_1(Polyline2)
    YQ_INTEGER_1(Polyline2)
    YQ_IS_INTEGER_1(Polyline2)
    YQ_ZERO_1(Polyline2, { })

    /*! \brief Scales the right polyline by the left amount
    */
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
    
    //! Length of this polyline across all segments
    template <typename T>
    T       length(const Polyline2<T>& poly);
}

