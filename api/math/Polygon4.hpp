////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "PolygonData.hpp"
#include <math/preamble.hpp>
#include <math/AxBox4.hpp>
#include <math/Vector4.hpp>

namespace yq {


    /*! \brief Structure for polygon data
    */
    template <typename T>
    struct Polygon4 {
        //! Capture the template parameter
        using component_type    = T;
        
        //! Vertex data
        std::vector<Vector4<T>>  vertex;
        
        constexpr Polygon4() noexcept = default;
        Polygon4(const std::vector<Vector4<T>>&);
        Polygon4(std::vector<Vector4<T>>&&);
        Polygon4(std::span<const Vector4<T>>);
        Polygon4(std::initializer_list<Vector4<T>>);
        
        explicit Polygon4(const Triangle4<T>&);

        template <typename U>
        requires std::is_convertible_v<T,U>
        explicit operator Polygon4<U>() const;

        //! Defaulted equality operator
        constexpr bool operator==(const Polygon4&) const noexcept = default;
        
        operator PolygonData<Vector4<T>>() const;

        //! Addsa a point to the polygon
        Polygon4&   operator<<(const Vector4<T>& pt);

        const Polygon4&    operator+() const;
        Polygon4           operator-() const;
        
        Polygon4   operator+(const Vector4<T>&) const;
        Polygon4&  operator+=(const Vector4<T>&);
        Polygon4   operator-(const Vector4<T>&) const;
        Polygon4&  operator-=(const Vector4<T>&);

        template <typename U>
        requires is_arithmetic_v<U>
        Polygon4<product_t<T,U>> operator*(U) const;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        Polygon4& operator*=(U);


        template <typename U>
        Polygon2<product_t<T,U>>   operator*(const Tensor42<U>&) const;
        template <typename U>
        Polygon3<product_t<T,U>>   operator*(const Tensor43<U>&) const;
        template <typename U>
        Polygon4<product_t<T,U>>   operator*(const Tensor44<U>&) const;
        
        template <typename U>
        requires self_mul_v<T,U>
        Polygon4&  operator*=(const Tensor44<U>&);
        
        template <typename U>
        requires is_arithmetic_v<U>
        Polygon4<quotient_t<T,U>> operator/(U) const;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        Polygon4& operator/=(U);

        /*! \brief Computes the axially aligned bounding box of this polygon
        */
        constexpr AxBox4<T>   bounds() const noexcept;
        
        //! Geometric center of the polygon (ie, average of the points)
        constexpr Vector4<T>    centroid() const noexcept;

        //! Computes the perimeter of the polygon 
        //! \note accuracy may vary on integral types
        T       perimeter() const;
        
        template <typename Pred>
        void    segments(Pred) const;
        
        //! Converts the polygon to segments
        std::vector<Segment4<T>>    segments() const;
    };
    

    template <typename T>
    Polygon4<T> polygon(std::vector<Vector4<T>>&& pts);

    template <typename T>
    Polygon4<T> polygon(std::span<const Vector4<T>> pts);

    template <typename T>
    Polygon4<T> polygon(std::initializer_list<const Vector4<T>> pts);

    template <typename T>
    Polygon4<T> polygon(const Triangle4<T>& ax);

    YQ_IEEE754_1(Polygon4)
    YQ_INTEGER_1(Polygon4)
    YQ_IS_INTEGER_1(Polygon4)
    YQ_ZERO_1(Polygon4, { })

//  --------------------------------------------------------
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    Polygon4<product_t<T,U>> operator*(T, const Polygon4<U>&b);

    template <typename T>
    bool is_finite(const Polygon4<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
    template <typename T>
    bool is_nan(const Polygon4<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(is_nan(v))
                return true;
        return false;
    }

    template <typename T>
    AxBox4<T>   aabb(const Polygon4<T>&poly);
    
    //! Computes the centroid of the given polygon
    template <typename T>
    Vector4<T>  centroid(const Polygon4<T>& poly);

    template <typename T>
    T       perimeter(const Polygon4<T>& poly);
}

YQ_TYPE_DECLARE(yq::Polygon4D)
YQ_TYPE_DECLARE(yq::Polygon4F)

