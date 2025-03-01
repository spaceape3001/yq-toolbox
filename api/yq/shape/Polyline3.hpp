////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_POLYLINE3_HPP 1

#include <yq/typedef/polyline3.hpp>

#include <yq/vector/Vector3.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename> struct Polyline2;
    template <typename> struct Polyline4;
    template <typename> struct PolylineData;
    template <typename> struct Tensor32;
    template <typename> struct Tensor33;
    template <typename> struct Tensor34;

    /*! \brief Structure for polyline data
    */
    template <typename T>
    struct Polyline3 {
        //! Capture the template parameter
        using component_type    = T;
        
        //! Vertex data
        std::vector<Vector3<T>>     vertex;
        
        //! Default constructor
        constexpr Polyline3() noexcept = default;

        //! Constructor by copy from vector
        Polyline3(const std::vector<Vector3<T>>&);

        //! Constructor by moving in from vector
        Polyline3(std::vector<Vector3<T>>&&);

        //! Constructor by copy from initializer list
        Polyline3(std::initializer_list<Vector3<T>>);

        //! Constructor by copy from span
        Polyline3(std::span<const Vector3<T>>);
        
        //! Constructor from segment
        explicit Polyline3(const Segment3<T>&);

        //! Converts to another polyline of compatible type
        template <typename U>
        requires std::is_convertible_v<T,U>
        explicit operator Polyline3<U>() const;

        //! Defaulted equality operator
        constexpr bool operator==(const Polyline3&) const noexcept = default;

        //! Conversion to polyline data
        operator PolylineData<Vector3<T>>() const;

        //! Addsa a point to the polyline
        Polyline3&   operator<<(const Vector3<T>& pt);

        //! Positive affirmation operator
        const Polyline3&    operator+() const;

        //! Negation operator
        Polyline3           operator-() const;
        
        //! Returns a shifted polyline by the given displacement
        Polyline3   operator+(const Vector3<T>&) const;

        //! Displaces this polyline by the given displacement
        Polyline3&  operator+=(const Vector3<T>&);

        //! Returns an shifted polyline by the given anti-displacement
        Polyline3   operator-(const Vector3<T>&) const;

        //! Displaces this polyline by the given anti displacement
        Polyline3&  operator-=(const Vector3<T>&);

        //! Returns a scaled polyline by the given right hand term
        template <typename U>
        requires is_arithmetic_v<U>
        Polyline3<product_t<T,U>> operator*(U) const;
        
        //! Scales this polyline by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Polyline3& operator*=(U);

        //! Projects this polyline into two dimensions
        template <typename U>
        Polyline2<product_t<T,U>>   operator*(const Tensor32<U>&) const;

        //! Projects this polyline to another three dimension space
        template <typename U>
        Polyline3<product_t<T,U>>   operator*(const Tensor33<U>&) const;

        //! Projects this polyline into four dimensions
        template <typename U>
        Polyline4<product_t<T,U>>   operator*(const Tensor34<U>&) const;
        
        //! Self-projects this polyline
        template <typename U>
        requires self_multiply_v<T,U>
        Polyline3&  operator*=(const Tensor33<U>&);

        //! Returns a polyline with every element divided by the given amount
        template <typename U>
        requires is_arithmetic_v<U>
        Polyline3<quotient_t<T,U>> operator/(U) const;
        
        //! Divides every element by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Polyline3& operator/=(U);

        //! Compute the bounding box to this polyline
        constexpr AxBox3<T>   bounds() const noexcept;
        
        //! Computes the length of the polyline
        //! \note May be less accurate with non-floating point types
        T       length() const;

        //! Walks the segments of this polyline
        template <typename Pred>
        void    segments(Pred) const;

        //! Segments of this polyline
        std::vector<Segment3<T>>    segments() const;

        size_t  count() const { return vertex.size(); }
    };

    /*! \brief Creates a polyline from a box
    */
    template <typename T>
    Polyline3<T> polyline(const AxBox3<T>& ax);

    /*! \brief Creates a polyline from points
    */
    template <typename T>
    Polyline3<T> polyline(std::span<const Vector3<T>> pts);

    /*! \brief Creates a polyline from points
    */
    template <typename T>
    Polyline3<T> polyline(std::initializer_list<const Vector3<T>> pts);

    /*! \brief Creates a polyline from points
    */
    template <typename T>
    Polyline3<T> polyline(std::vector<Vector3<T>>&& pts);

    /*! \brief Creates a polyline from a segment
    */
    template <typename T>
    Polyline3<T> polyline(const Segment3<T>&);

    YQ_IEEE754_1(Polyline3)
    YQ_INTEGER_1(Polyline3)
    YQ_IS_INTEGER_1(Polyline3)
    YQ_ZERO_1(Polyline3, { })

    /*! \brief Scales the right polyline by the left amount
    */
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Polyline3<product_t<T,U>> operator*(T, const Polyline3<U>&b);

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
    
    //! Length of this polyline across all segments
    template <typename T>
    T       length(const Polyline3<T>& poly);
}

YQ_TYPE_DECLARE(yq::Polyline3D)
YQ_TYPE_DECLARE(yq::Polyline3F)
YQ_TYPE_DECLARE(yq::Polyline3I)
YQ_TYPE_DECLARE(yq::Polyline3U)


