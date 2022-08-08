////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Range.hpp>
#include <math/Vector3.hpp>
#include <math/AxCorners3.hpp>

namespace yq {

    /*! \brief Axially aligned box in 3 dimension(s).
    */
    template <typename T>
    struct AxBox3 {
        using component_t   = T;
        
        Vector3<T>  lo, hi;
        
        constexpr bool operator==(const AxBox3&) const noexcept = default;
    };

    YQ_IEEE754_1(AxBox3)
    
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr AxBox3<T> aabb(const Vector3<T>& a, const Vector3<T>& b) noexcept
    {
        return { min_elem(a,b), max_elem(a,b) };
    }

    YQ_NAN_1(AxBox3, { nan_v<Vector3<T>>, nan_v<Vector3<T>>});
    YQ_ZERO_1(AxBox3, { zero_v<Vector3<T>>, zero_v<Vector3<T>>});

//  --------------------------------------------------------
//  GETTERS


    template <typename T>
    constexpr Vector3<T>  northeast_bottom(const AxBox3<T>& ax) noexcept
    {
        return { ax.hi.x, ax.hi.y, ax.lo.z };
   }

    template <typename T>
    constexpr Vector3<T>  northeast_top(const AxBox3<T>& ax) noexcept
    {
        return ax.hi;
    }


    template <typename T>
    constexpr Vector3<T>  northwest_bottom(const AxBox3<T>& ax) noexcept
    {
        return { ax.lo.x, ax.hi.y, ax.lo.z };
    }

    template <typename T>
    constexpr Vector3<T>  northwest_top(const AxBox3<T>& ax) noexcept
    {
        return { ax.lo.x, ax.hi.y, ax.hi.z };
    }

    template <typename T>
    constexpr Vector3<T>  southeast_bottom(const AxBox2<T>& ax) noexcept
    {
        return { ax.hi.x, ax.lo.y, ax.lo.z };
    }

    template <typename T>
    constexpr Vector3<T>  southeast_top(const AxBox2<T>& ax) noexcept
    {
        return { ax.hi.x, ax.lo.y, ax.hi.z };
    }

    template <typename T>
    constexpr Vector3<T>  southwest_bottom(const AxBox2<T>& ax) noexcept
    {
        return ax.lo;
    }

    template <typename T>
    constexpr Vector3<T>  southwest_top(const AxBox2<T>& ax) noexcept
    {
        return { ax.lo.x, ax.lo.y, ax.hi.z };
    }

    template <typename T>
    constexpr AxCorners3<Vector3<T>>  corners(const AxBox3<T>& v) noexcept
    {
        return { 
            v.lo,
            { v.lo.x, v.lo.y, v.hi.z  }, 
            { v.lo.x, v.hi.y, v.lo.z  }, 
            { v.lo.x, v.hi.y, v.hi.z  }, 
            { v.hi.x, v.lo.y, v.lo.z  }, 
            { v.hi.x, v.lo.y, v.hi.z  }, 
            { v.hi.x, v.hi.y, v.lo.z  }, 
            v.hi
        };
    }


    template <typename T>
    constexpr Range<T>  x_range(const AxBox3<T>& v) noexcept
    {
        return range(v.lo.x, v.hi.x);
    }

    template <typename T>
    constexpr Range<T>  y_range(const AxBox3<T>& v) noexcept
    {
        return range(v.lo.y, v.hi.y);
    }

    template <typename T>
    constexpr Range<T>  z_range(const AxBox3<T>& v) noexcept
    {
        return range(v.lo.z, v.hi.z);
    }

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1( AxBox3, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox3, is_nan(v.lo) || is_nan(v.hi))

    template <typename T>
    constexpr bool    is_valid(const AxBox3<T>& a) noexcept
    {
        return all_less_equal(a.lo, a.hi);
    }


//  --------------------------------------------------------
//  POSITIVE


//  --------------------------------------------------------
//  NEGATIVE


//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION


//  --------------------------------------------------------
//  SUBTRACTION


//  --------------------------------------------------------
//  MULTIPLICATION


//  --------------------------------------------------------
//  DIVISION

//  --------------------------------------------------------
//  POWERS

//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT


//  --------------------------------------------------------
//  OUTER PRODUCT


//  --------------------------------------------------------
//  CROSS PRODUCT


///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  UNIONS

    /*! \brief Union of two AABBs
    */
    template <typename T>
    constexpr AxBox3<T> operator|(const AxBox3<T>&a, const AxBox3<T>&b) noexcept
    {
        return { min_elem(a.lo, b.lo), max_elem(a.hi, b.hi) };
    }


//  --------------------------------------------------------
//  INTERSECTIONS


    /*! \brief Intersection of two AABBs
    */
    template <typename T>
    constexpr AxBox3<T> operator&(const AxBox3<T>&a, const AxBox3<T>&b) noexcept
    {
        return { max_elem(a.lo, b.lo), min_elem(a.hi, b.hi) };
    }

//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Computes the center of a 3D axially aligned box
    */
    template <typename T>
    constexpr Vector3<T>      center(const AxBox3<T>& box) noexcept
    {
        if constexpr (std::is_floating_point_v<T>){
            return ieee754_t<T>(0.5)*(box.lo+box.hi);
        } else if(std::is_integral_v<T>){
            return (box.lo+box.hi) / T(2);
        } else
            return {};
    }

    /*! \brief Checks for full occlusion
    
        A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
        \param[in] Big   The "bigger" box, if eclipsed
        \param[in] Small The "smaller" box, if eclipsed
    */
    template <typename T>
    constexpr bool is_eclipsed(const AxBox3<T>& big, const AxBox3<T>& small) noexcept
    {
        return all_less_equal(big.lo, small.lo) && all_greater_equal(big.hi, small.hi);
    }


    /*! \brief Checks if the point is inside (or touching) the box
    */
    template <typename T>
    constexpr bool is_inside(const AxBox3<T>& bx, const Vector3<T>& pt) noexcept
    {
        return all_less_equal(bx.lo, pt) && all_less_equal(pt, bx.hi);
    }

    /*! \brief Checks for any overlap
    
        This returns TRUE if *ANY* part of the boxes overlap (or touch)
    */
    template <typename T>
    constexpr bool is_overlapped(const AxBox3<T>& a, const AxBox3<T>& b) noexcept
    {
        return all_less_equal(a.lo, b.hi) && all_greater_equal(a.hi, b.lo);
    }

    template <typename T>
    constexpr Vector3<T>    span(const AxBox3<T>&a) noexcept
    {
        return a.hi - a.lo;
    }

    /*! \brief Computes the surface area of a 3D axially aligned bounding box
    */
    template <typename T>
    constexpr square_t<T>    surface_area(const AxBox3<T>& ax) noexcept
    {
        Vector3<T>  del     = ax.hi - ax.lo;
        return 2.0 * ((del.x*del.y)+(del.y*del.z)+(del.z*del.x));
    }

    template <typename T>
    constexpr cube_t<T>       volume(const AxBox3<T>& bx) noexcept
    {
        return component_product(bx.hi-bx.lo);
    }

}

YQ_TYPE_DECLARE(yq::AxBox3D)
YQ_TYPE_DECLARE(yq::AxBox3F)
YQ_TYPE_DECLARE(yq::AxBox3I)
YQ_TYPE_DECLARE(yq::AxBox3U)

