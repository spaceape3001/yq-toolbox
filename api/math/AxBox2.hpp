////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Range.hpp>
#include <math/Size2.hpp>
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
        using component_type    = T;
        
        Vector2<T>  lo; //!< Lower bounds
        Vector2<T>  hi; //!< Upper bounds
        
        //! Equality operator (defaulted)
        constexpr bool operator==(const AxBox2&) const noexcept = default;

        //! Union
        constexpr AxBox2 operator|(const AxBox2<T>&b) const noexcept
        {
            return { min_elem(lo, b.lo), max_elem(hi, b.hi) };
        }

        //! Union in a box
        AxBox2& operator|=(const AxBox2& b) 
        {
            lo  = min_elem(lo, b.lo);
            hi  = max_elem(hi, b.hi);
            return *this;
        }

        //! Unions in a vector
        AxBox2& operator|=(const Vector2<T>& b) 
        {
            lo  = min_elem(lo, b);
            hi  = max_elem(hi, b);
            return *this;
        }

        //! Intersection 
        constexpr AxBox2 operator&(const AxBox2<T>&b) const noexcept
        {
            return { max_elem(lo, b.lo), min_elem(hi, b.hi) };
        }
        
        //! Intersection into self 
        AxBox2& operator&=(const AxBox2& b) 
        {
            lo  = max_elem(lo, b.lo);
            hi  = min_elem(hi, b.hi);
            return *this;
        }

        /*! \brief Computes the area
        */
        constexpr square_t<T>               area() const noexcept
        {
            return (hi-lo).cproduct();
        }

        /*! \brief Computes the center
        */
        constexpr Vector2<T>                center() const noexcept
        {
            if constexpr (std::is_floating_point_v<T>)
                return ieee754_t<T>(0.5)*(lo+hi);
            if constexpr (std::is_integral_v<T>)
                return (lo+hi) / T(2);
            return {};
        }

        /*! \brief Our corners
        */
        constexpr AxCorners2<Vector2<T>>    corners() const noexcept 
        {
            return { 
                southwest(),
                northwest(),
                southeast(),
                northeast()
            };
        }

        /*! \brief Checks for full occlusion
        
            A small box is "eclipsed" if it's wholy contained (or touching edges) by this box.
            \param[in] Small The "smaller" box, if eclipsed
        */
        constexpr bool          eclipses(const AxBox2<T>& b) const noexcept
        {
            return (lo <<= b.lo) && (b.hi <<= hi);
        }

        /*! \brief Checks if the point is inside (or touching) the box
        */
        constexpr bool          inside(const Vector2<T>& pt) const noexcept
        {
            return (lo <<= pt) && (pt <<= hi);
        }

        //! Tests this box for validness
        constexpr bool          is_valid() const noexcept 
        {
            return lo <<= hi;
        }
            
        //! Returns the northeast corner of the box
        constexpr Vector2<T>    northeast() const noexcept { return hi; };

        //! Returns the northwest corner of the box
        constexpr Vector2<T>    northwest() const noexcept { return { lo.x, hi.y}; }
        
        /*! \brief Checks for any overlap
        
            This returns TRUE if *ANY* part of the boxes overlap (or touch)
        */
        constexpr bool          overlaps(const AxBox2<T>& b) noexcept
        {
            return (lo <<= b.hi) && (b.lo <<= hi);
        }    

        /*! \brief Computes the perimeter of the box */
        constexpr T             perimeter() const noexcept
        {
            return T(2) * (hi-lo).csum();
        }

        /*! \brief Projects a local [0,1] coordinate to a global coordinate based on the provided axially aligned box
        
            \param[in] v    The local coordinate
            \return The global coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector2<T>    project(const Vector2<T>& v) const noexcept
        {
            return mul_elem(one_v<Vector2<T>>-v, lo) + mul_elem(v, hi);
        }

        //! Returns the southeast corner of the box
        constexpr Vector2<T>    southeast() const noexcept { return { hi.x, lo.y }; }
        
        //! Returns the southwest corner of the box
        constexpr Vector2<T>    southwest() const noexcept { return lo; }

        /*! \brief Returns the span (dimensions) of the box
        */
        constexpr Vector2<T>    span() const noexcept
        {
            return hi - lo;
        }
        
        /*! \brief Returns the size of the box
        */
        constexpr Size2<T>      size() const noexcept
        {
            return { x_size(), y_size() };
        }

        /*! \brief Projects a global coordinate to a local [0,1] coordinate for the axially aligned box

            \param[in] bx   The axially aligned box
            \param[in] v    The global coordinate
            \return The local coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector2<T>   unproject(const Vector2<T>& v) const noexcept
        {
            return div_elem(v-lo, span());
        }

        //! X Range of the box
        constexpr Range<T>      x_range() const noexcept { return { lo.x, hi.x }; }
        
        //! X size of the box
        constexpr T             x_size() const noexcept { return hi.x - lo.x; }
        
        //! Y Range of the box
        constexpr Range<T>      y_range() const noexcept { return { lo.y, hi.y }; }
        
        //! Y size of the box
        constexpr T             y_size() const noexcept { return hi.y - lo.y; }
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

    /*! \brief Creates a 2D axially aligned box from container of Vector2's
    */
    template <typename T>
    AxBox2<T> aabb(const std::vector<Vector2<T>>& vals)
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

        AxBox2<T>   ret = aabb(vals[0], vals[1]);
        for(size_t i=2;i<vals.size();++i)
            ret |= vals[i];
        return vals;
    }

    YQ_NAN_1(AxBox2, { nan_v<Vector2<T>>, nan_v<Vector2<T>>});
    YQ_ZERO_1(AxBox2, { zero_v<Vector2<T>>, zero_v<Vector2<T>>});

    YQ_IS_FINITE_1( AxBox2, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox2, is_nan(v.lo) || is_nan(v.hi))


    /*! \brief Computes the area of a 2D axially aligned bounding box
    */
    template <typename T>
    constexpr square_t<T>   area(const AxBox2<T>& ax) noexcept
    {
        return ax.area();
    }

    /*! \brief Computes the center of a 2D axially aligned box
    */
    template <typename T>
    constexpr Vector2<T>    center(const AxBox2<T>& box) noexcept
    {
        return box.center();
    }

    //! Checks for validity (hi >= lo)
    template <typename T>
    constexpr bool          is_valid(const AxBox2<T>& a) noexcept
    {
        return a.is_valid();
    }

    /*! \brief Computes the perimeter of the box */
    template <typename T>
    constexpr T             perimeter(const AxBox2<T>& ax) noexcept
    {
        return ax.perimeter();
    }

    /*! \brief Returns the span (dimensions) of the box
    */
    template <typename T>
    constexpr Vector2<T>    span(const AxBox2<T>&a) noexcept
    {
        return a.span();
    }
}

YQ_TYPE_DECLARE(yq::AxBox2D)
YQ_TYPE_DECLARE(yq::AxBox2F)
YQ_TYPE_DECLARE(yq::AxBox2I)
YQ_TYPE_DECLARE(yq::AxBox2U)

