////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Range.hpp>
#include <math/Vector4.hpp>
#include <math/AxCorners4.hpp>

namespace yq {

    /*! \brief Axially aligned box in 4 dimension(s).
    */
    template <typename T>
    struct AxBox4 {
        //! Component type (ie, the argument)
        using component_type    = T;
        
        //! Low corner
        Vector4<T>  lo;

        //! High corner
        Vector4<T>  hi;
        
        //! Equality operator (defaulted);
        constexpr bool operator==(const AxBox4&) const noexcept = default;
    };
    
    YQ_IEEE754_1(AxBox4)
    
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a 4D axially aligned box from one vector
    */
    template <typename T>
    constexpr AxBox4<T> aabb(const Vector4<T>& a) noexcept
    {
        return { a, a };
    }

    /*! \brief Creates a 4D axially aligned box from two vectors
    */
    template <typename T>
    constexpr AxBox4<T> aabb(const Vector4<T>& a, const Vector4<T>& b) noexcept
    {
        return { min_elem(a,b), max_elem(a,b) };
    }

    YQ_NAN_1(AxBox4, { nan_v<Vector4<T>>, nan_v<Vector4<T>>});
    YQ_ZERO_1(AxBox4, { zero_v<Vector4<T>>, zero_v<Vector4<T>>});

//  --------------------------------------------------------
//  GETTERS

    /*! \brief Returns ALL the corners of the box 
    */
    template <typename T>
    constexpr AxCorners4<Vector4<T>>  corners(const AxBox4<T>& v) noexcept
    {
        return { 
            v.lo, 
            
            { v.lo.x, v.lo.y, v.lo.z, v.hi.w  }, 
            { v.lo.x, v.lo.y, v.hi.z, v.lo.w  }, 
            { v.lo.x, v.lo.y, v.hi.z, v.hi.w  }, 
            { v.lo.x, v.hi.y, v.lo.z, v.lo.w  }, 
            { v.lo.x, v.hi.y, v.lo.z, v.hi.w  }, 
            { v.lo.x, v.hi.y, v.hi.z, v.lo.w  }, 
            { v.lo.x, v.hi.y, v.hi.z, v.hi.w  }, 
             
            { v.hi.x, v.lo.y, v.lo.z, v.lo.w  }, 
            { v.hi.x, v.lo.y, v.lo.z, v.hi.w  }, 
            { v.hi.x, v.lo.y, v.hi.z, v.lo.w  }, 
            { v.hi.x, v.lo.y, v.hi.z, v.hi.w  }, 
            { v.hi.x, v.hi.y, v.lo.z, v.lo.w  }, 
            { v.hi.x, v.hi.y, v.lo.z, v.hi.w  }, 
            { v.hi.x, v.hi.y, v.hi.z, v.lo.w  }, 
            
            v.hi
        };
    }

    //! X Range of the box
    template <typename T>
    constexpr Range<T>  x_range(const AxBox4<T>& v) noexcept
    {
        return range(v.lo.x, v.hi.x);
    }

    //! Y Range of the box
    template <typename T>
    constexpr Range<T>  y_range(const AxBox4<T>& v) noexcept
    {
        return range(v.lo.y, v.hi.y);
    }

    //! Z Range of the box
    template <typename T>
    constexpr Range<T>  z_range(const AxBox4<T>& v) noexcept
    {
        return range(v.lo.z, v.hi.z);
    }

    //! W Range of the box
    template <typename T>
    constexpr Range<T>  w_range(const AxBox4<T>& v) noexcept
    {
        return range(v.lo.w, v.hi.w);
    }

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    YQ_IS_FINITE_1( AxBox4, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox4, is_nan(v.lo) || is_nan(v.hi))


    //! Checks for validity (hi >= lo)
    template <typename T>
    constexpr bool    is_valid(const AxBox4<T>& a) noexcept
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
    constexpr AxBox4<T> operator|(const AxBox4<T>&a, const AxBox4<T>&b) noexcept
    {
        return { min_elem(a.lo, b.lo), max_elem(a.hi, b.hi) };
    }

//  --------------------------------------------------------
//  INTERSECTIONS

    /*! \brief Intersection of two AABBs
    */
    template <typename T>
    constexpr AxBox4<T> operator&(const AxBox4<T>&a, const AxBox4<T>&b) noexcept
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
    constexpr Vector4<T>   local_to_global(const AxBox4<T>& bx, const Vector4<T>& v) noexcept
    {
        return mul_elem(one_v<Vector4<T>>-v, bx.lo) + mul_elem(v, bx.hi);
    }

    /*! \brief Projects a global coordinate to a local [0,1] coordinate for the axially aligned box

        \param[in] bx   The axially aligned box
        \param[in] v    The global coordinate
        \return The local coordinate
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    constexpr Vector4<T>   global_to_local(const AxBox4<T>& bx, const Vector4<T>& v) noexcept
    {
        return div_elem(v-bx.lo, bx.hi-bx.lo);
    }

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS
    

    /*! \brief Computes the center of a 4D axially aligned box
    */
    template <typename T>
    constexpr Vector4<T>      center(const AxBox4<T>& box) noexcept
    {
        if constexpr (std::is_floating_point_v<T>){
            return ieee754_t<T>(0.5)*(box.lo+box.hi);
        } else if(std::is_integral_v<T>){
            return (box.lo+box.hi) / T(2);
        } else
            return {};
    }

    /*! \brief Computes the hyper volume of the box
    */
    template <typename T>
    constexpr fourth_t<T> hypervolume(const AxBox4<T>& bx) noexcept
    {
        return component_product(bx.hi-bx.lo);
    }


    /*! \brief Checks for full occlusion
    
        A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
        \param[in] Big   The "bigger" box, if eclipsed
        \param[in] Small The "smaller" box, if eclipsed
    */
    template <typename T>
    constexpr bool is_eclipsed(const AxBox4<T>& big, const AxBox4<T>& small) noexcept
    {
        return all_less_equal(big.lo, small.lo) && all_greater_equal(big.hi, small.hi);
    }
    
    /*! \brief Checks if the point is inside (or touching) the box
    */
    template <typename T>
    constexpr bool is_inside(const AxBox4<T>& bx, const Vector4<T>& pt) noexcept
    {
        return all_less_equal(bx.lo, pt) && all_less_equal(pt, bx.hi);
    }

    /*! \brief Checks for any overlap
    
        This returns TRUE if *ANY* part of the boxes overlap (or touch)
    */
    template <typename T>
    constexpr bool is_overlapped(const AxBox4<T>& a, const AxBox4<T>& b) noexcept
    {
        return all_less_equal(a.lo, b.hi) && all_greater_equal(a.hi, b.lo);
    }

    /*! \brief Returns the span (dimensions) of the box
    */
    template <typename T>
    constexpr Vector4<T>    span(const AxBox4<T>&a) noexcept
    {
        return a.hi - a.lo;
    }

}

YQ_TYPE_DECLARE(yq::AxBox4D)
YQ_TYPE_DECLARE(yq::AxBox4F)
YQ_TYPE_DECLARE(yq::AxBox4I)
YQ_TYPE_DECLARE(yq::AxBox4U)

