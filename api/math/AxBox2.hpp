////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Vector2.hpp>

namespace yq {

    /*! \brief Axially aligned box in 2 dimension(s).
    
        Note, lo vs hi isn't enforced, however it's expected that lo < hi, which 
        is what "is_valid" of "shape_math.hpp" will check.
    */
    template <typename T>
    struct AxBox2 {
        using component_t   = T;
        
        Vector2<T>  lo; //!< Lower bounds
        Vector2<T>  hi; //!< Upper bounds
        
        constexpr bool operator==(const AxBox2&) const noexcept = default;
    };

    YQ_IEEE754_1(AxBox2)

//  --------------------------------------------------------
//  COMPOSITION

    template <typename T>
    constexpr AxBox2<T> aabb(const Vector2<T>& a, const Vector2<T>& b)
    {
        return { min_elem(a,b), max_elem(a,b) };
    }
    
    YQ_NAN_1(AxBox2, { nan_v<Vector2<T>>, nan_v<Vector2<T>>});
    YQ_ZERO_1(AxBox2, { zero_v<Vector2<T>>, zero_v<Vector2<T>>});

//  --------------------------------------------------------
//  GETTERS

    template <typename T>
    Vector2<T>  northeast(const AxBox2<T>& ax)
    {
        return ax.hi;
    }

    template <typename T>
    Vector2<T>  northwest(const AxBox2<T>& ax)
    {
        return { ax.lo.x, ax.hi.y };
    }

    template <typename T>
    Vector2<T>  southeast(const AxBox2<T>& ax)
    {
        return { ax.hi.x, ax.lo.y };
    }

    template <typename T>
    Vector2<T>  southwest(const AxBox2<T>& ax)
    {
        return ax.lo;
    }


//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1( AxBox2, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox2, is_nan(v.lo) || is_nan(v.hi))

    template <typename T>
    bool    valid(const AxBox2<T>& a)
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
    constexpr AxBox2<T> operator|(const AxBox2<T>&a, const AxBox2<T>&b)
    {
        return { min_elem(a.lo, b.lo), max_elem(a.hi, b.hi) };
    }

//  --------------------------------------------------------
//  INTERSECTIONS

    /*! \brief Intersection of two AABBs
    */
    template <typename T>
    constexpr AxBox2<T> operator&(const AxBox2<T>&a, const AxBox2<T>&b)
    {
        return { max_elem(a.lo, b.lo), min_elem(a.hi, b.hi) };
    }

//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Computes the area of a 2D axially aligned bounding box
    */
    template <typename T>
    square_t<T>     area(const AxBox2<T>& ax)
    {
        return component_product(ax.hi-ax.lo);
    }

    /*! \brief Computes the center of a 2D axially aligned box
    */
    template <typename T>
    Vector2<T>      center(const AxBox2<T>& box)
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
    constexpr bool is_eclipsed(const AxBox2<T>& big, const AxBox2<T>& small)
    {
        return all_less_equal(big.lo, small.lo) && all_greater_equal(big.hi, small.hi);
    }
    
    /*! \brief Checks if the point is inside (or touching) the box
    */
    template <typename T>
    constexpr bool is_inside(const AxBox2<T>& bx, const Vector2<T>& pt)
    {
        return all_less_equal(bx.lo, pt) && all_less_equal(pt, bx.hi);
    }

    /*! \brief Checks for any overlap
    
        This returns TRUE if *ANY* part of the boxes overlap (or touch)
    */
    template <typename T>
    constexpr bool is_overlapped(const AxBox2<T>& a, const AxBox2<T>& b)
    {
        return all_less_equal(a.lo, b.hi) && all_greater_equal(a.hi, b.lo);
    }    

    template <typename T>
    T       perimeter(const AxBox2<T>& ax)
    {
        return 2. * component_sum(ax.hi-ax.lo);
    }

}

YQ_TYPE_DECLARE(yq::AxBox2D)
YQ_TYPE_DECLARE(yq::AxBox2F)
YQ_TYPE_DECLARE(yq::AxBox2I)
YQ_TYPE_DECLARE(yq::AxBox2U)

