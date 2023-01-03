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
        using component_type    = T;
        
        //! Our low corner 
        Vector1<T>  lo;
        
        //! Our high corner
        Vector1<T>  hi;
        
        //! Defaulted equatlity operator
        constexpr bool operator==(const AxBox1&) const noexcept = default;

        /*! \brief Union of two AABBs
        */
        constexpr AxBox1<T> operator|(const AxBox1<T>&b) const noexcept
        {
            return { min_elem(lo, b.lo), max_elem(hi, b.hi) };
        }

        //! Union in a box
        AxBox1& operator|=(const AxBox1& b) 
        {
            lo  = min_elem(lo, b.lo);
            hi  = max_elem(hi, b.hi);
            return *this;
        }

        //! Unions in a vector
        AxBox1& operator|=(const Vector1<T>& b) 
        {
            lo  = min_elem(lo, b);
            hi  = max_elem(hi, b);
            return *this;
        }

        /*! \brief Intersection of two AABBs
        */
        constexpr AxBox1<T> operator&(const AxBox1<T>&b) const noexcept
        {
            return { max_elem(lo, b.lo), min_elem(hi, b.hi) };
        }

        //! Intersection into self 
        AxBox1& operator&=(const AxBox1& b) 
        {
            lo  = max_elem(lo, b.lo);
            hi  = min_elem(hi, b.hi);
            return *this;
        }

        /*! \brief Computes the center of a 1D axially aligned box
        */
        constexpr Vector1<T> center() const noexcept
        {
            if constexpr (std::is_floating_point_v<T>)
                return ieee754_t<T>(0.5)*(lo+hi);
            if constexpr (std::is_integral_v<T>)
                return (lo+hi) / T(2);
            return {};
        }

        /*! \brief Checks if the point is inside (or touching) the box
        */
        constexpr bool contains(const Vector1<T>& pt) const noexcept
        {
            return (all(lo) <= pt) && (all(pt) <<= hi);
        }

        /*! \brief Returns the enumerated corners of the box
        */
        constexpr AxCorners1<Vector1<T>>  corners() const noexcept
        {
            return { 
                lo,
                hi
            };
        }

        /*! \brief Checks for full occlusion
        
            A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
            \param[in] b     The "smaller" box, if eclipsed
        */
        constexpr bool eclipses(const AxBox1<T>& b) const noexcept
        {
            return (all(lo) <= b.lo) && (all(b.hi) <= hi);
        }


        /*! \brief Tests for a valid box */
        constexpr bool    is_valid() const noexcept
        {
            return all(lo) <= hi;
        }

        /*! \brief Checks for any overlap
        
            This returns TRUE if *ANY* part of the boxes overlap (or touch)
        */
        constexpr bool overlaps(const AxBox1<T>& b) const noexcept
        {
            return (all(lo) <= b.hi) && (all(b.lo) <= hi);
        }

        /*! \brief Projects a local [0,1] coordinate to a global coordinate
        
            \param[in] bx   The axially aligned box
            \return The global coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector1<T>   project(const Vector1<T>& v) const noexcept
        {
            return mul_elem(one_v<Vector1<T>>-v, lo) + mul_elem(v, hi);
        }

        constexpr Vector1<T>    span() const noexcept
        {
            return hi - lo;
        }

        /*! \brief Projects a global coordinate to a local [0,1] coordinate
            \param[in] v    The global coordinate
            \return The local coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector1<T>   unproject(const Vector1<T>& v) const noexcept
        {
            return div_elem(v-lo, hi-lo);
        }

        //! Tests this box for validness
        constexpr bool          valid() const noexcept 
        {
            return all(lo) <= hi;
        }

        /*! \brief Returns the x-range of the box
        */
        constexpr Range<T>  x_range() const noexcept
        {
            return range(lo.x, hi.x);
        }
    };
    
    YQ_IEEE754_1(AxBox1)
    
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

    /*! \brief Creates a 3D axially aligned box from container of Vector2's
    */
    template <typename T>
    AxBox1<T> aabb(const std::vector<Vector1<T>>& vals)
    {
        switch(vals.size()){
        case 0:
            return {};
        case 1:
            return aabb(vals[0]);
        case 2:
            return aabb(vals[0],vals[1]);
        default:
            break;
        }

        AxBox1<T>   ret = aabb(vals[0], vals[1]);
        for(size_t i=2;i<vals.size();++i)
            ret |= vals[i];
        return vals;
    }


    YQ_NAN_1(AxBox1, { nan_v<Vector1<T>>, nan_v<Vector1<T>>});
    YQ_ZERO_1(AxBox1, { zero_v<Vector1<T>>, zero_v<Vector1<T>>});

    YQ_IS_FINITE_1( AxBox1, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox1, is_nan(v.lo) || is_nan(v.hi))


    /*! \brief Computes the center of a 1D axially aligned box
    */
    template <typename T>
    constexpr Vector1<T> center(const AxBox1<T>& box)  noexcept
    {
        return box.center();
    }

    /*! \brief Tests for a valid box */
    template <typename T>
    constexpr bool    is_valid(const AxBox1<T>& box) noexcept
    {
        return box.is_valid();
    }

    //! Computes the span for a given box
    template <typename T>
    constexpr Vector1<T>    span(const AxBox1<T>&box) noexcept
    {
        return box.span();
    }
}

YQ_TYPE_DECLARE(yq::AxBox1D)
YQ_TYPE_DECLARE(yq::AxBox1F)
YQ_TYPE_DECLARE(yq::AxBox1I)
YQ_TYPE_DECLARE(yq::AxBox1U)

