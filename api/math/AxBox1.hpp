////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Range.hpp>
#include <math/Vector1.hpp>
#include <math/AxCorners1.hpp>

namespace yq {

    /*! \brief Axially aligned box in 1 dimension(s).
    
        \note default construction does not enforce that lo <= hi
    */
    template <typename T>
    struct AxBox1 {
    
        //! Component type (ie, capture our argument)
        using component_t   = T;
        
        //! Our low corner 
        Vector1<T>  lo;
        
        //! Our high corner
        Vector1<T>  hi;
        
        //! Defaulted equatlity operator
        constexpr bool operator==(const AxBox1&) const noexcept = default;
    };
    
    YQ_IEEE754_1(AxBox1)
    
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates an axially alligned box from one corner vertex
    */
    template <typename T>
    constexpr AxBox1<T> aabb(const Vector1<T>& a) noexcept
    {
        return { a, a };
    }

    /*! \brief Creates an axially alligned box from two corner vertices
    */
    template <typename T>
    constexpr AxBox1<T> aabb(const Vector1<T>& a, const Vector1<T>& b) noexcept
    {
        return { min_elem(a,b), max_elem(a,b) };
    }


    YQ_NAN_1(AxBox1, { nan_v<Vector1<T>>, nan_v<Vector1<T>>});
    YQ_ZERO_1(AxBox1, { zero_v<Vector1<T>>, zero_v<Vector1<T>>});

//  --------------------------------------------------------
//  GETTERS

    /*! \brief Returns the enumerated corners of the box
    */
    template <typename T>
    AxCorners1<Vector1<T>>  corners(const AxBox1<T>& v)
    {
        return { 
            v.lo,
            v.hi
        };
    }

    /*! \brief Returns the x-range of the box
    */
    template <typename T>
    constexpr Range<T>  x_range(const AxBox1<T>& v) noexcept
    {
        return range(v.lo.x, v.hi.x);
    }

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1( AxBox1, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox1, is_nan(v.lo) || is_nan(v.hi))

    /*! \brief Tests for a valid box */
    template <typename T>
    constexpr bool    is_valid(const AxBox1<T>& a) noexcept
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
    constexpr AxBox1<T> operator|(const AxBox1<T>&a, const AxBox1<T>&b) noexcept
    {
        return { min_elem(a.lo, b.lo), max_elem(a.hi, b.hi) };
    }


//  --------------------------------------------------------
//  INTERSECTIONS

    /*! \brief Intersection of two AABBs
    */
    template <typename T>
    constexpr AxBox1<T> operator&(const AxBox1<T>&a, const AxBox1<T>&b) noexcept
    {
        return { max_elem(a.lo, b.lo), min_elem(a.hi, b.hi) };
    }



//  --------------------------------------------------------
//  PROJECTIONS

    /*! \brief Projects a local [0,1] coordinate to a global coordinate based on the provided axially aligned box
    
        \param[in] bx   The axially aligned box
        \param[in] v    The local coordinate
        \return The global coordinate
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Vector1<T>   local_to_global(const AxBox1<T>& bx, const Vector1<T>& v) noexcept
    {
        return mul_elem(one_v<Vector1<T>>-v, bx.lo) + mul_elem(v, bx.hi);
    }

    /*! \brief Projects a global coordinate to a local [0,1] coordinate for the axially aligned box

        \param[in] bx   The axially aligned box
        \param[in] v    The global coordinate
        \return The local coordinate
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Vector1<T>   global_to_local(const AxBox1<T>& bx, const Vector1<T>& v) noexcept
    {
        return div_elem(v-bx.lo, bx.hi-bx.lo);
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Computes the center of a 1D axially aligned box
    */
    template <typename T>
    constexpr Vector1<T>      center(const AxBox1<T>& box) noexcept
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
    constexpr bool is_eclipsed(const AxBox1<T>& big, const AxBox1<T>& small) noexcept
    {
        return all_less_equal(big.lo, small.lo) && all_greater_equal(big.hi, small.hi);
    }

    /*! \brief Checks if the point is inside (or touching) the box
    */
    template <typename T>
    constexpr bool is_inside(const AxBox1<T>& bx, const Vector1<T>& pt) noexcept
    {
        return all_less_equal(bx.lo, pt) && all_less_equal(pt, bx.hi);
    }

    /*! \brief Checks for any overlap
    
        This returns TRUE if *ANY* part of the boxes overlap (or touch)
    */
    template <typename T>
    constexpr bool is_overlapped(const AxBox1<T>& a, const AxBox1<T>& b) noexcept
    {
        return all_less_equal(a.lo, b.hi) && all_greater_equal(a.hi, b.lo);
    }

    template <typename T>
    constexpr Vector1<T>    span(const AxBox1<T>&a) noexcept
    {
        return a.hi - a.lo;
    }
}

YQ_TYPE_DECLARE(yq::AxBox1D)
YQ_TYPE_DECLARE(yq::AxBox1F)
YQ_TYPE_DECLARE(yq::AxBox1I)
YQ_TYPE_DECLARE(yq::AxBox1U)

