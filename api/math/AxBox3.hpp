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

        Note, lo vs hi isn't enforced, however it's expected that lo < hi, which 
        is what "is_valid" will check.
    */
    template <typename T>
    struct AxBox3 {
    
        //! Component type (capturing the template argument)
        using component_t   = T;
        
        //! Low corner
        Vector3<T>  lo;
        
        //! High corner
        Vector3<T>  hi;
        
        //! Equality operator (defaulted);
        constexpr bool operator==(const AxBox3&) const noexcept = default;
    };

    YQ_IEEE754_1(AxBox3)
    
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a 3D axially aligned box from one vector
    */
    template <typename T>
    constexpr AxBox3<T> aabb(const Vector3<T>& a) noexcept
    {
        return { a, a };
    }

    /*! \brief Creates a 3D axially aligned box from two vectors
    */
    template <typename T>
    constexpr AxBox3<T> aabb(const Vector3<T>& a, const Vector3<T>& b) noexcept
    {
        return { min_elem(a,b), max_elem(a,b) };
    }

    YQ_NAN_1(AxBox3, { nan_v<Vector3<T>>, nan_v<Vector3<T>>});
    YQ_ZERO_1(AxBox3, { zero_v<Vector3<T>>, zero_v<Vector3<T>>});

//  --------------------------------------------------------
//  GETTERS

    /*! \brief Returns the north east bottom corner
    */
    template <typename T>
    constexpr Vector3<T>  northeast_bottom(const AxBox3<T>& ax) noexcept
    {
        return { ax.hi.x, ax.hi.y, ax.lo.z };
   }

    /*! \brief Returns the north east top corner
    */
    template <typename T>
    constexpr Vector3<T>  northeast_top(const AxBox3<T>& ax) noexcept
    {
        return ax.hi;
    }


    /*! \brief Returns the north west bottom corner
    */
    template <typename T>
    constexpr Vector3<T>  northwest_bottom(const AxBox3<T>& ax) noexcept
    {
        return { ax.lo.x, ax.hi.y, ax.lo.z };
    }
    /*! \brief Returns the north west top corner
    */

    template <typename T>
    constexpr Vector3<T>  northwest_top(const AxBox3<T>& ax) noexcept
    {
        return { ax.lo.x, ax.hi.y, ax.hi.z };
    }

    /*! \brief Returns the south east bottom corner
    */
    template <typename T>
    constexpr Vector3<T>  southeast_bottom(const AxBox2<T>& ax) noexcept
    {
        return { ax.hi.x, ax.lo.y, ax.lo.z };
    }

    /*! \brief Returns the south east top corner
    */
    template <typename T>
    constexpr Vector3<T>  southeast_top(const AxBox2<T>& ax) noexcept
    {
        return { ax.hi.x, ax.lo.y, ax.hi.z };
    }

    /*! \brief Returns the south west bottom corner
    */
    template <typename T>
    constexpr Vector3<T>  southwest_bottom(const AxBox2<T>& ax) noexcept
    {
        return ax.lo;
    }

    /*! \brief Returns the south west top corner
    */
    template <typename T>
    constexpr Vector3<T>  southwest_top(const AxBox2<T>& ax) noexcept
    {
        return { ax.lo.x, ax.lo.y, ax.hi.z };
    }

    /*! \brief Returns ALL the corners of the box 
    */
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

    //! X Range of the box
    template <typename T>
    constexpr Range<T>  x_range(const AxBox3<T>& v) noexcept
    {
        return range(v.lo.x, v.hi.x);
    }

    //! Y Range of the box
    template <typename T>
    constexpr Range<T>  y_range(const AxBox3<T>& v) noexcept
    {
        return range(v.lo.y, v.hi.y);
    }

    //! Z Range of the box
    template <typename T>
    constexpr Range<T>  z_range(const AxBox3<T>& v) noexcept
    {
        return range(v.lo.z, v.hi.z);
    }

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    /*! \brief Checks for finiteness
    */
    template <typename T>
    constexpr bool is_finite(const AxBox3<T>&v)
    {
        return is_finite(v.lo) && is_finite(v.hi);
    }

    YQ_IS_NAN_1(AxBox3, is_nan(v.lo) || is_nan(v.hi))

    //! Checks for validity (hi >= lo)
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

    /*! \brief Projects a local [0,1] coordinate to a global coordinate based on the provided axially aligned box
    
        \param[in] bx   The axially aligned box
        \param[in] v    The local coordinate
        \return The global coordinate
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Vector3<T>   local_to_global(const AxBox3<T>& bx, const Vector3<T>& v) noexcept
    {
        return mul_elem(one_v<Vector3<T>>-v, bx.lo) + mul_elem(v, bx.hi);
    }

    /*! \brief Projects a global coordinate to a local [0,1] coordinate for the axially aligned box

        \param[in] bx   The axially aligned box
        \param[in] v    The global coordinate
        \return The local coordinate
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Vector3<T>   global_to_local(const AxBox3<T>& bx, const Vector3<T>& v) noexcept
    {
        return div_elem(v-bx.lo, bx.hi-bx.lo);
    }

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

    /*! \brief Returns the span (dimensions) of the box
    */
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

    /*! \brief Computes the volume of the box
    */
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

