////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Range.hpp>
#include <math/Vector2.hpp>
#include <math/AxCorners2.hpp>

namespace yq {

    /*! \brief Axially aligned box in 2 dimension(s).
    
        Note, lo vs hi isn't enforced, however it's expected that lo < hi, which 
        is what "is_valid" will check.
    */
    template <typename T>
    struct AxBox2 {
        //! Component type (ie, the argument)
        using component_t   = T;
        
        Vector2<T>  lo; //!< Lower bounds
        Vector2<T>  hi; //!< Upper bounds
        
        //! Equality operator (defaulted)
        constexpr bool operator==(const AxBox2&) const noexcept = default;
    };

    YQ_IEEE754_1(AxBox2)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a 2D axially aligned box from one vector
    */
    template <typename T>
    constexpr AxBox2<T> aabb(const Vector2<T>& a)
    {
        return { a, a };
    }
    
    /*! \brief Creates a 2D axially aligned box from two vectors
    */
    template <typename T>
    constexpr AxBox2<T> aabb(const Vector2<T>& a, const Vector2<T>& b)
    {
        return { min_elem(a,b), max_elem(a,b) };
    }

    YQ_NAN_1(AxBox2, { nan_v<Vector2<T>>, nan_v<Vector2<T>>});
    YQ_ZERO_1(AxBox2, { zero_v<Vector2<T>>, zero_v<Vector2<T>>});

//  --------------------------------------------------------
//  GETTERS

    //! Northeast corner of the box
    template <typename T>
    constexpr Vector2<T>  northeast(const AxBox2<T>& ax) noexcept
    {
        return ax.hi;
    }

    //! Northwest corner of the box
    template <typename T>
    constexpr Vector2<T>  northwest(const AxBox2<T>& ax) noexcept
    {
        return { ax.lo.x, ax.hi.y };
    }

    //! Souttheast corner of the box
    template <typename T>
    constexpr Vector2<T>  southeast(const AxBox2<T>& ax) noexcept
    {
        return { ax.hi.x, ax.lo.y };
    }

    //! Soutthwest corner of the box
    template <typename T>
    constexpr Vector2<T>  southwest(const AxBox2<T>& ax) noexcept
    {
        return ax.lo;
    }

    //! Corners of the box
    template <typename T>
    AxCorners2<Vector2<T>>  corners(const AxBox2<T>& v)
    {
        return { 
            v.lo,
            { v.lo.x, v.hi.y }, 
            { v.hi.x, v.lo.y }, 
            v.hi
        };
    }

    //! X Range of the box
    template <typename T>
    constexpr Range<T>  x_range(const AxBox2<T>& v) noexcept
    {
        return range(v.lo.x, v.hi.x);
    }

    //! Y Range of the box
    template <typename T>
    constexpr Range<T>  y_range(const AxBox2<T>& v) noexcept
    {
        return range(v.lo.y, v.hi.y);
    }

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1( AxBox2, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox2, is_nan(v.lo) || is_nan(v.hi))

    //! Checks for validity (hi >= lo)
    template <typename T>
    constexpr bool    is_valid(const AxBox2<T>& a) noexcept
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
    constexpr AxBox2<T> operator|(const AxBox2<T>&a, const AxBox2<T>&b) noexcept
    {
        return { min_elem(a.lo, b.lo), max_elem(a.hi, b.hi) };
    }

//  --------------------------------------------------------
//  INTERSECTIONS

    /*! \brief Intersection of two AABBs
    */
    template <typename T>
    constexpr AxBox2<T> operator&(const AxBox2<T>&a, const AxBox2<T>&b) noexcept
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
    constexpr Vector2<T>   local_to_global(const AxBox2<T>& bx, const Vector2<T>& v) noexcept
    {
        return mul_elem(one_v<Vector2<T>>-v, bx.lo) + mul_elem(v, bx.hi);
    }

    /*! \brief Projects a global coordinate to a local [0,1] coordinate for the axially aligned box

        \param[in] bx   The axially aligned box
        \param[in] v    The global coordinate
        \return The local coordinate
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Vector2<T>   global_to_local(const AxBox2<T>& bx, const Vector2<T>& v) noexcept
    {
        return div_elem(v-bx.lo, bx.hi-bx.lo);
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    /*! \brief Computes the area of a 2D axially aligned bounding box
    */
    template <typename T>
    constexpr square_t<T>     area(const AxBox2<T>& ax) noexcept
    {
        return component_product(ax.hi-ax.lo);
    }

    /*! \brief Computes the center of a 2D axially aligned box
    */
    template <typename T>
    constexpr Vector2<T>      center(const AxBox2<T>& box) noexcept
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
    constexpr bool is_eclipsed(const AxBox2<T>& big, const AxBox2<T>& small) noexcept
    {
        return all_less_equal(big.lo, small.lo) && all_greater_equal(big.hi, small.hi);
    }
    
    /*! \brief Checks if the point is inside (or touching) the box
    */
    template <typename T>
    constexpr bool is_inside(const AxBox2<T>& bx, const Vector2<T>& pt) noexcept
    {
        return all_less_equal(bx.lo, pt) && all_less_equal(pt, bx.hi);
    }

    /*! \brief Checks for any overlap
    
        This returns TRUE if *ANY* part of the boxes overlap (or touch)
    */
    template <typename T>
    constexpr bool is_overlapped(const AxBox2<T>& a, const AxBox2<T>& b) noexcept
    {
        return all_less_equal(a.lo, b.hi) && all_greater_equal(a.hi, b.lo);
    }    

    /*! \brief Computes the perimeter of the box */
    template <typename T>
    constexpr T       perimeter(const AxBox2<T>& ax) noexcept
    {
        return 2. * component_sum(ax.hi-ax.lo);
    }

    /*! \brief Returns the span (dimensions) of the box
    */
    template <typename T>
    constexpr Vector2<T>    span(const AxBox2<T>&a) noexcept
    {
        return a.hi - a.lo;
    }
}

YQ_TYPE_DECLARE(yq::AxBox2D)
YQ_TYPE_DECLARE(yq::AxBox2F)
YQ_TYPE_DECLARE(yq::AxBox2I)
YQ_TYPE_DECLARE(yq::AxBox2U)

