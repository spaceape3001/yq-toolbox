////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "PolygonData.hpp"
#include <math/preamble.hpp>
#include <math/AxBox3.hpp>
#include <math/Segment3.hpp>
#include <math/Vector3.hpp>

namespace yq {

    /*! \brief Structure for polygon data
    */
    template <typename T>
    struct Polygon3 {
        //! Capture the template parameter
        using component_type    = T;
        
        //! Vertex data
        std::vector<Vector3<T>>  vertex;
        
        constexpr Polygon3() noexcept = default;
        Polygon3(const std::vector<Vector3<T>>&);
        Polygon3(std::vector<Vector3<T>>&&);
        Polygon3(std::span<const Vector3<T>>);
        Polygon3(std::initializer_list<Vector3<T>>);
        explicit Polygon3(const Triangle3<T>&);


        //! Defaulted equality operator
        constexpr bool operator==(const Polygon3&) const noexcept = default;
        
        operator PolygonData<Vector3<T>>() const;

        //! Addsa a point to the polygon
        Polygon3&   operator<<(const Vector3<T>& pt);


        template <typename U>
        Polygon2<trait::product_t<T,U>>   operator*(const Tensor32<U>&) const;
        template <typename U>
        Polygon3<trait::product_t<T,U>>   operator*(const Tensor33<U>&) const;
        template <typename U>
        Polygon4<trait::product_t<T,U>>   operator*(const Tensor34<U>&) const;
        
        template <typename U>
        requires trait::self_mul_v<T,U>
        Polygon3&  operator*=(const Tensor33<U>&);
        
        /*! \brief Computes the axially aligned bounding box of this polygon
        */
        constexpr AxBox3<T>   bounds() const noexcept;
        
        //! Geometric center of the polygon (ie, average of the points)
        constexpr Vector3<T>    centroid() const noexcept;

        //! Computes the perimeter of the polygon (ie, sum of lengths of the segments)
        //! \note accuracy may vary on integral types
        T       perimeter() const;
        
        template <typename Pred>
        void    segments(Pred) const;
        
        //! Converts the polygon to segments
        std::vector<Segment3<T>>    segments() const;
    };
    
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    Polygon3<T> polygon(std::vector<Vector3<T>>&& pts);

    template <typename T>
    Polygon3<T> polygon(std::span<const Vector3<T>> pts);

    template <typename T>
    Polygon3<T> polygon(std::initializer_list<const Vector3<T>> pts);

    template <typename T>
    Polygon3<T> polygon(const Triangle3<T>& ax);

    YQ_IEEE754_1(Polygon3)
    YQ_ZERO_1(Polygon3, { })

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    /*! \brief Create an axially aligned bounding box from a polygon
    */
    template <typename T>
    AxBox3<T>   aabb(const Polygon3<T>&poly);

    //! Computes the centroid of the given polygon
    template <typename T>
    Vector3<T>  centroid(const Polygon3<T>& poly);

    //! Tests that all vertices are finite
    template <typename T>
    bool is_finite(const Polygon3<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(!is_finite(v))
                return false;
        return true;
    }
    
    //! Tests for any vertice that is not-a-number
    template <typename T>
    bool is_nan(const Polygon3<T>& poly)
    {
        for(auto& v : poly.vertex)
            if(is_nan(v))
                return true;
        return false;
    }

    //! Computes the perimeter of the polygon
    template <typename T>
    T       perimeter(const Polygon3<T>& poly);

}

YQ_TYPE_DECLARE(yq::Polygon3D)
YQ_TYPE_DECLARE(yq::Polygon3F)

