////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_POLYGON4_HPP 1


#include <yq/vector/Vector4.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {


    /*! \brief Structure for polygon data
    */
    template <typename T>
    struct Polygon4 {
        //! Capture the template parameter
        using component_type    = T;
        
        //! Vertex data
        std::vector<Vector4<T>>  vertex;
        
        //! Default constructor
        constexpr Polygon4() noexcept = default;

        //! Constructor by copy from vector
        Polygon4(const std::vector<Vector4<T>>&);

        //! Constructor by moving in from vector
        Polygon4(std::vector<Vector4<T>>&&);

        //! Constructor by copy from span
        Polygon4(std::span<const Vector4<T>>);

        //! Constructor by copy from initializer list of points
        Polygon4(std::initializer_list<Vector4<T>>);
        
        //! Constructor by copy from triangle
        explicit Polygon4(const Triangle4<T>&);

        //! Converts to polygon of compatible data type
        template <typename U>
        requires std::is_convertible_v<T,U>
        explicit operator Polygon4<U>() const;

        //! Defaulted equality operator
        constexpr bool operator==(const Polygon4&) const noexcept = default;
        
        //! Converts to polygon data
        operator PolygonData<Vector4<T>>() const;

        //! Addsa a point to the polygon
        Polygon4&   operator<<(const Vector4<T>& pt);

        //! Positive affirmation operator
        const Polygon4&    operator+() const;

        //! Negation operator
        Polygon4           operator-() const;
        
        //! Returns a shifted polygon by the given displacement
        Polygon4   operator+(const Vector4<T>&) const;

        //! Displaces this polygon by the given displacement
        Polygon4&  operator+=(const Vector4<T>&);

        //! Returns an shifted polygon by the given anti-displacement
        Polygon4   operator-(const Vector4<T>&) const;

        //! Displaces this polygon by the given anti displacement
        Polygon4&  operator-=(const Vector4<T>&);

        //! Returns a scaled polygon by the given right hand term
        template <typename U>
        requires is_arithmetic_v<U>
        Polygon4<product_t<T,U>> operator*(U) const;
        
        //! Scales this polygon by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Polygon4& operator*=(U);

        //! Projects this polygon into two dimensions
        template <typename U>
        Polygon2<product_t<T,U>>   operator*(const Tensor42<U>&) const;

        //! Projects this polygon into three dimensions
        template <typename U>
        Polygon3<product_t<T,U>>   operator*(const Tensor43<U>&) const;

        //! Projects this polygon to another four dimension space
        template <typename U>
        Polygon4<product_t<T,U>>   operator*(const Tensor44<U>&) const;
        
        //! Self-projects this polygon
        template <typename U>
        requires self_multiply_v<T,U>
        Polygon4&  operator*=(const Tensor44<U>&);
        
        //! Returns a polygon with every element divided by the given amount
        template <typename U>
        requires is_arithmetic_v<U>
        Polygon4<quotient_t<T,U>> operator/(U) const;
        
        //! Divides every element by the given amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Polygon4& operator/=(U);

        /*! \brief Computes the axially aligned bounding box of this polygon
        */
        constexpr AxBox4<T>   bounds() const noexcept;
        
        //! Geometric center of the polygon (ie, average of the points)
        constexpr Vector4<T>    centroid() const noexcept;

        //! Computes the perimeter of the polygon 
        //! \note accuracy may vary on integral types
        T       perimeter() const;
        
        //! Walks the segments of this polygon
        template <typename Pred>
        void    segments(Pred) const;
        
        //! Converts the polygon to segments
        std::vector<Segment4<T>>    segments() const;
    };
    

    /*! \brief Creates a polygon from points
    */
    template <typename T>
    Polygon4<T> polygon(std::vector<Vector4<T>>&& pts);

    /*! \brief Creates a polygon from points
    */
    template <typename T>
    Polygon4<T> polygon(std::span<const Vector4<T>> pts);

    /*! \brief Creates a polygon from points
    */
    template <typename T>
    Polygon4<T> polygon(std::initializer_list<const Vector4<T>> pts);

    /*! \brief Creates a polygon from a triangle
    */
    template <typename T>
    Polygon4<T> polygon(const Triangle4<T>& ax);

    YQ_IEEE754_1(Polygon4)
    YQ_INTEGER_1(Polygon4)
    YQ_IS_INTEGER_1(Polygon4)
    YQ_ZERO_1(Polygon4, { })

//  --------------------------------------------------------
    /*! \brief Scales the right polygon by the left amount
    */
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Polygon4<product_t<T,U>> operator*(T, const Polygon4<U>&b);

    //! Tests that all vertices are finite
    template <typename T>
    bool is_finite(const Polygon4<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
    //! Tests for any vertice that is not-a-number
    template <typename T>
    bool is_nan(const Polygon4<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(is_nan(v))
                return true;
        return false;
    }

    /*! \brief Create an axially aligned bounding box from a polygon
    */
    template <typename T>
    AxBox4<T>   aabb(const Polygon4<T>&poly);
    
    //! Computes the centroid of the given polygon
    template <typename T>
    Vector4<T>  centroid(const Polygon4<T>& poly);

    //! Computes the perimeter of the polygon
    template <typename T>
    T       perimeter(const Polygon4<T>& poly);
}

YQ_TYPE_DECLARE(yq::Polygon4D)
YQ_TYPE_DECLARE(yq::Polygon4F)

