////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector4.hpp>

namespace yq {

    /*! \brief Axially aligned box in 4 dimension(s).
    */
    template <typename T>
    struct AxBox4 {
        using component_t   = T;
        
        Vector4<T>  lo, hi;
        
        constexpr bool operator==(const AxBox4&) const noexcept = default;
    };
    
    YQ_IEEE754_1(AxBox4)
    
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr AxBox4<T> aabb(const Vector4<T>& a, const Vector4<T>& b)
    {
        return { min_elem(a,b), max_elem(a,b) };
    }

    YQ_NAN_1(AxBox4, { nan_v<Vector4<T>>, nan_v<Vector4<T>>});
    YQ_ZERO_1(AxBox4, { zero_v<Vector4<T>>, zero_v<Vector4<T>>});

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1( AxBox4, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox4, is_nan(v.lo) || is_nan(v.hi))


    template <typename T>
    bool    valid(const AxBox4<T>& a)
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
    constexpr AxBox4<T> operator|(const AxBox4<T>&a, const AxBox4<T>&b)
    {
        return { min_elem(a.lo, b.lo), max_elem(a.hi, b.hi) };
    }

//  --------------------------------------------------------
//  INTERSECTIONS

    /*! \brief Intersection of two AABBs
    */
    template <typename T>
    constexpr AxBox4<T> operator&(const AxBox4<T>&a, const AxBox4<T>&b)
    {
        return { max_elem(a.lo, b.lo), min_elem(a.hi, b.hi) };
    }


//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS
    

    /*! \brief Computes the center of a 4D axially aligned box
    */
    template <typename T>
    Vector4<T>      center(const AxBox4<T>& box)
    {
        if constexpr (std::is_floating_point_v<T>){
            return ieee754_t<T>(0.5)*(box.lo+box.hi);
        } else if(std::is_integral_v<T>){
            return (box.lo+box.hi) / T(2);
        } else
            return {};
    }

    template <typename T>
    fourth_t<T> hypervolume(const AxBox4<T>& bx)
    {
        return component_product(bx.hi-bx.lo);
    }


    /*! \brief Checks for full occlusion
    
        A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
        \param[in] Big   The "bigger" box, if eclipsed
        \param[in] Small The "smaller" box, if eclipsed
    */
    template <typename T>
    constexpr bool is_eclipsed(const AxBox4<T>& big, const AxBox4<T>& small)
    {
        return all_less_equal(big.lo, small.lo) && all_greater_equal(big.hi, small.hi);
    }
    
    /*! \brief Checks if the point is inside (or touching) the box
    */
    template <typename T>
    constexpr bool is_inside(const AxBox4<T>& bx, const Vector4<T>& pt)
    {
        return all_less_equal(bx.lo, pt) && all_less_equal(pt, bx.hi);
    }

    /*! \brief Checks for any overlap
    
        This returns TRUE if *ANY* part of the boxes overlap (or touch)
    */
    template <typename T>
    constexpr bool is_overlapped(const AxBox4<T>& a, const AxBox4<T>& b)
    {
        return all_less_equal(a.lo, b.hi) && all_greater_equal(a.hi, b.lo);
    }

}

YQ_TYPE_DECLARE(yq::AxBox4D)
YQ_TYPE_DECLARE(yq::AxBox4F)
YQ_TYPE_DECLARE(yq::AxBox4I)
YQ_TYPE_DECLARE(yq::AxBox4U)

