////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Range.hpp>
#include <math/Size4.hpp>
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

        /*! \brief Union of two AABBs
        */
        constexpr AxBox4<T> operator|(const AxBox4<T>&b) const noexcept
        {
            return { min_elem(lo, b.lo), max_elem(hi, b.hi) };
        }

        //! Union in a box
        AxBox4& operator|=(const AxBox4& b) 
        {
            lo  = min_elem(lo, b.lo);
            hi  = max_elem(hi, b.hi);
            return *this;
        }

        //! Unions in a vector
        AxBox4& operator|=(const Vector4<T>& b) 
        {
            lo  = min_elem(lo, b);
            hi  = max_elem(hi, b);
            return *this;
        }

        /*! \brief Intersection of two AABBs
        */
        constexpr AxBox4<T> operator&(const AxBox4<T>&b) const noexcept
        {
            return { max_elem(lo, b.lo), min_elem(hi, b.hi) };
        }

        //! Intersection into self 
        AxBox4& operator&=(const AxBox4& b) 
        {
            lo  = max_elem(lo, b.lo);
            hi  = min_elem(hi, b.hi);
            return *this;
        }

        /*! \brief Computes the center of a 4D axially aligned box
        */
        constexpr Vector4<T>      center() const noexcept
        {
            if constexpr (std::is_floating_point_v<T>)
                return ieee754_t<T>(0.5)*(lo+hi);
            if constexpr (std::is_integral_v<T>)
                return (lo+hi) / T(2);
            return {};
        }

        /*! \brief Checks if the point is inside (or touching) the box
        */
        constexpr bool contains (const Vector4<T>& pt) const noexcept
        {
            return (all(lo) <= pt) && (all(pt) <= hi);
        }

        /*! \brief Returns ALL the corners of the box 
        */
        constexpr AxCorners4<Vector4<T>>  corners() const noexcept
        {
            return { 
                lo, 
                
                { lo.x, lo.y, lo.z, hi.w  }, 
                { lo.x, lo.y, hi.z, lo.w  }, 
                { lo.x, lo.y, hi.z, hi.w  }, 
                { lo.x, hi.y, lo.z, lo.w  }, 
                { lo.x, hi.y, lo.z, hi.w  }, 
                { lo.x, hi.y, hi.z, lo.w  }, 
                { lo.x, hi.y, hi.z, hi.w  }, 
                 
                { hi.x, lo.y, lo.z, lo.w  }, 
                { hi.x, lo.y, lo.z, hi.w  }, 
                { hi.x, lo.y, hi.z, lo.w  }, 
                { hi.x, lo.y, hi.z, hi.w  }, 
                { hi.x, hi.y, lo.z, lo.w  }, 
                { hi.x, hi.y, lo.z, hi.w  }, 
                { hi.x, hi.y, hi.z, lo.w  }, 
                
                hi
            };
        }

        /*! \brief Checks for full occlusion
        
            A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
            \param[in] Big   The "bigger" box, if eclipsed
            \param[in] Small The "smaller" box, if eclipsed
        */
        constexpr bool contains(const AxBox4<T>& b) const noexcept
        {
            return (all(lo) <= b.lo) && (all(b.hi) <= hi);
        }
        

        /*! \brief Computes the hyper volume of the box
        */
        constexpr fourth_t<T> hypervolume() const noexcept
        {
            return (hi-lo).cproduct();
        }

        //! Checks for validity (hi >= lo)
        constexpr bool    is_valid() const noexcept
        {
            return all(lo) <= hi;
        }

        /*! \brief Checks for any overlap
        
            This returns TRUE if *ANY* part of the boxes overlap (or touch)
        */
        constexpr bool overlaps(const AxBox4<T>& b) const noexcept
        {
            return (all(lo) <= b.hi) && (all(b.lo) <= hi);
        }

        /*! \brief Projects a local [0,1] coordinate to a global coordinate based on the provided axially aligned box
        
            \param[in] bx   The axially aligned box
            \param[in] v    The local coordinate
            \return The global coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector4<T>   project(const Vector4<T>& v) const noexcept
        {
            return (one_v<Vector4<T>>-v).emul(lo) + v.emul(hi);
        }

        constexpr Size4<T> size() const noexcept 
        {
            auto s = span();
            return Size4<T>{ s.x, s.y, s.z, s.w  }; 
        }

        /*! \brief Returns the span (dimensions) of the box
        */
        constexpr Vector4<T>    span() const noexcept
        {
            return hi - lo;
        }

        /*! \brief Projects a global coordinate to a local [0,1] coordinate for the axially aligned box

            \param[in] bx   The axially aligned box
            \param[in] v    The global coordinate
            \return The local coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector4<T>   unproject(const Vector4<T>& v) const noexcept
        {
            return div_elem(v-lo, hi-lo);
        }

        //! Tests this box for validness
        constexpr bool          valid() const noexcept 
        {
            return all(lo) <= hi;
        }

        //! X Range of the box
        constexpr Range<T>  x_range() const noexcept
        {
            return range(lo.x, hi.x);
        }

        //! Y Range of the box
        constexpr Range<T>  y_range() const noexcept
        {
            return range(lo.y, hi.y);
        }

        //! Z Range of the box
        constexpr Range<T>  z_range() const noexcept
        {
            return range(lo.z, hi.z);
        }

        //! W Range of the box
        constexpr Range<T>  w_range() const noexcept
        {
            return range(lo.w, hi.w);
        }
    };
    
    YQ_IEEE754_1(AxBox4)
    
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

    /*! \brief Creates a 4D axially aligned box from container of Vector4's
    */
    template <typename T>
    AxBox4<T> aabb(const std::vector<Vector4<T>>& vals)
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

        AxBox4<T>   ret = aabb(vals[0], vals[1]);
        for(size_t i=2;i<vals.size();++i)
            ret |= vals[i];
        return vals;
    }

    YQ_NAN_1(AxBox4, { nan_v<Vector4<T>>, nan_v<Vector4<T>>});
    YQ_ZERO_1(AxBox4, { zero_v<Vector4<T>>, zero_v<Vector4<T>>});

    YQ_IS_FINITE_1( AxBox4, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox4, is_nan(v.lo) || is_nan(v.hi))


    /*! \brief Computes the center of a 4D axially aligned box
    */
    template <typename T>
    constexpr Vector4<T>      center(const AxBox4<T>& box) noexcept
    {
        return box.center();
    }

    /*! \brief Computes the hyper volume of the box
    */
    template <typename T>
    constexpr fourth_t<T>   hypervolume(const AxBox4<T>& box) noexcept
    {
        return box.hypervolume();
    }


    //! Checks for validity (hi >= lo)
    template <typename T>
    constexpr bool    is_valid(const AxBox4<T>& box) noexcept
    {
        return box.is_valid();
    }

    /*! \brief Returns the span (dimensions) of the box
    */
    template <typename T>
    constexpr Vector4<T>    span(const AxBox4<T>&box) noexcept
    {
        return box.span();
    }


}

YQ_TYPE_DECLARE(yq::AxBox4D)
YQ_TYPE_DECLARE(yq::AxBox4F)
YQ_TYPE_DECLARE(yq::AxBox4I)
YQ_TYPE_DECLARE(yq::AxBox4U)

