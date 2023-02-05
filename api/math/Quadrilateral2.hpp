////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "QuadrilateralData.hpp"
#include <math/preamble.hpp>
#include <math/Vector2.hpp>
#include <math/AxBox2.hpp>

namespace yq {
    /*! \brief Quadrilateral in two dimensions
    */
    template <typename T>
    struct Quadrilateral2 {
        //! Capture the template paremater
        using component_type = T;
    
        Vector2<T>     a, b, c, d;

        constexpr AxBox2<T>   bounds() const
        {
            return { 
                min_elem(min_elem(a, b), min_elem(c, d)), 
                max_elem(max_elem(a, b), max_elem(c, d))
            };
        }

        //! Defaulted comparison operator
        constexpr bool operator==(const Quadrilateral2&) const noexcept = default;
    };

//  --------------------------------------------------------
//  COMPOSITION

    YQ_NAN_1(Quadrilateral2, { nan_v<Vector2<T>>, nan_v<Vector2<T>>, nan_v<Vector2<T>>, nan_v<Vector2<T>> })
    YQ_ZERO_1(Quadrilateral2, { zero_v<Vector2<T>>, zero_v<Vector2<T>>, zero_v<Vector2<T>>, zero_v<Vector2<T>> })

    template <typename T>
    Quadrilateral2<T> quadrilateral(const AxBox2<T>& ax)
    {
        return { southwest(ax), southeast(ax), northeast(ax), northwest(ax) };
    }

    template <typename T>
    Quadrilateral2<T> quadrilateral(const Vector2<T>& a, const Vector2<T>& b, const Vector2<T>& c, const Vector2<T>& d)
    {
        return { a, b, c, d };
    }

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1(Quadrilateral2, is_finite(v.a) && is_finite(v.b) && is_finite(v.c) && is_finite(v.d))
    YQ_IS_NAN_1(Quadrilateral2, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) || is_nan(v.d) )

    template <typename T>
    AxBox2<T>   aabb(const Quadrilateral2<T>& quad)
    {
        return { 
            min_elem(min_elem(quad.a, quad.b), min_elem(quad.c, quad.d)), 
            max_elem(max_elem(quad.a, quad.b), min_elem(quad.c, quad.d))
        };
    }

//  --------------------------------------------------------
//  UTILITY FUNCTIONS (FOR OTHER ADVANCED THINGS TO WORK)

    /*! \brief "Point area" of the points
    
        This is a helper to area and other functions, 
        simply does an "area" of the point deltas, 
        no sign correction, no scaling.
    */
    template <typename T>
    trait::square_t<T>    point_area(const Quadrilateral2<T>& quad)
    {
        return delta_area(quad.b, quad.a) + delta_area(quad.c, quad.b) + delta_area(quad.d, quad.c) + delta_area(quad.a, quad.d);
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Computes the area of a 2D quatrilateral
    */
    template <typename T>
    trait::square_t<T>    area(const Quadrilateral2<T>& quad)
    {
        return 0.5*abs(point_area(quad));
    }

    template <typename T>
    bool    is_ccw(const Quadrilateral2<T>& quad)
    {
        return point_area(quad) < zero_v<T>;
    }

    template <typename T>
    requires trait::has_sqrt_v<trait::square_t<T>>
    T       perimeter(const Quadrilateral2<T>& quad)
    {
        return length(quad.b-quad.a)+length(quad.c-quad.b)+length(quad.d-quad.c)+length(quad.a-quad.d);
    }

}

YQ_TYPE_DECLARE(yq::Quadrilateral2D)
YQ_TYPE_DECLARE(yq::Quadrilateral2F)
YQ_TYPE_DECLARE(yq::Quadrilateral2I)
YQ_TYPE_DECLARE(yq::Quadrilateral2U)

