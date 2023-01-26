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
        using component_type   = T;
        
        //! Low corner
        Vector3<T>  lo;
        
        //! High corner
        Vector3<T>  hi;
        
        //! Equality operator (defaulted);
        constexpr bool operator==(const AxBox3&) const noexcept = default;

        /*! \brief Union of two AABBs
        */
        constexpr AxBox3<T> operator|(const AxBox3<T>&b) const noexcept
        {
            return { min_elem(lo, b.lo), max_elem(hi, b.hi) };
        }

        //! Union in a box
        AxBox3& operator|=(const AxBox3& b) 
        {
            lo  = min_elem(lo, b.lo);
            hi  = max_elem(hi, b.hi);
            return *this;
        }

        //! Unions in a vector
        AxBox3& operator|=(const Vector3<T>& b) 
        {
            lo  = min_elem(lo, b);
            hi  = max_elem(hi, b);
            return *this;
        }

        /*! \brief Intersection of two AABBs
        */
        constexpr AxBox3<T> operator&(const AxBox3<T>&b) const noexcept
        {
            return { max_elem(lo, b.lo), min_elem(hi, b.hi) };
        }

        //! Intersection into self 
        AxBox3& operator&=(const AxBox3& b) 
        {
            lo  = max_elem(lo, b.lo);
            hi  = min_elem(hi, b.hi);
            return *this;
        }

        /*! \brief Computes the center of a 3D axially aligned box
        */
        constexpr Vector3<T>      center() const noexcept
        {
            if constexpr (std::is_floating_point_v<T>)
                return ieee754_t<T>(0.5)*(lo+hi);
            if constexpr (std::is_integral_v<T>)
                return (lo+hi) / T(2);
            return {};
        }

        /*! \brief Checks if the point is inside (or touching) the box
        */
        constexpr bool contains(const Vector3<T>& pt) const noexcept
        {
            return (all(lo) <= pt) && (all(pt) <= hi);
        }

        /*! \brief Returns ALL the corners of the box 
        */
        constexpr AxCorners3<Vector3<T>>  corners() const noexcept
        {
            return { 
                lo,
                { lo.x, lo.y, hi.z  }, 
                { lo.x, hi.y, lo.z  }, 
                { lo.x, hi.y, hi.z  }, 
                { hi.x, lo.y, lo.z  }, 
                { hi.x, lo.y, hi.z  }, 
                { hi.x, hi.y, lo.z  }, 
                hi
            };
        }

        /*! \brief Checks for full occlusion
        
            A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
            \param[in] Big   The "bigger" box, if eclipsed
            \param[in] Small The "smaller" box, if eclipsed
        */
        constexpr bool eclipses(const AxBox3<T>& b) const noexcept
        {
            return (all(lo) <= b.lo) && (all(b.hi) <= hi);
        }


        //! Check for validity
        constexpr bool    is_valid() const noexcept
        {
            return all(lo) <= hi;
        }

       /*! \brief Returns the north east bottom corner
        */
        constexpr Vector3<T>  northeast_bottom() const noexcept
        {
            return { hi.x, hi.y, lo.z };
       }

        /*! \brief Returns the north east top corner
        */
        constexpr Vector3<T>  northeast_top() const noexcept
        {
            return hi;
        }

        /*! \brief Returns the north west bottom corner
        */
        constexpr Vector3<T>  northwest_bottom() const noexcept
        {
            return { lo.x, hi.y, lo.z };
        }

        /*! \brief Returns the north west top corner
        */
        constexpr Vector3<T>  northwest_top() const noexcept
        {
            return { lo.x, hi.y, hi.z };
        }

        /*! \brief Checks for any overlap
        
            This returns TRUE if *ANY* part of the boxes overlap (or touch)
        */
        constexpr bool overlaps(const AxBox3<T>& b) const noexcept
        {
            return (all(lo) <= b.hi) && (all(b.lo) <= hi);
        }

        /*! \brief Projects a local [0,1] coordinate to a global coordinate based on the provided axially aligned box
        
            \param[in] v    The local coordinate
            \return The global coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector3<T>   project(const Vector3<T>& v) const noexcept
        {
            return (one_v<Vector3<T>>-v).emul(lo) + v.emul(hi);
        }

        constexpr Size3<T> size() const noexcept 
        {
            auto s = span();
            return Size3<T>{ s.x, s.y, s.z }; 
        }

        /*! \brief Returns the south east bottom corner
        */
        constexpr Vector3<T>  southeast_bottom() const noexcept
        {
            return { hi.x, lo.y, lo.z };
        }

        /*! \brief Returns the south east top corner
        */
        constexpr Vector3<T>  southeast_top() const noexcept
        {
            return { hi.x, lo.y, hi.z };
        }

        /*! \brief Returns the south west bottom corner
        */
        constexpr Vector3<T>  southwest_bottom() const noexcept
        {
            return lo;
        }

        /*! \brief Returns the south west top corner
        */
        constexpr Vector3<T>  southwest_top() const noexcept
        {
            return { lo.x, lo.y, hi.z };
        }

        /*! \brief Returns the span (dimensions) of the box
        */
        constexpr Vector3<T>    span() const noexcept
        {
            return hi - lo;
        }

        /*! \brief Computes the surface area of a 3D axially aligned bounding box
        */
        constexpr square_t<T>    surface_area() const noexcept
        {
            Vector3<T>  del     = hi - lo;
            return 2.0 * ((del.x*del.y)+(del.y*del.z)+(del.z*del.x));
        }


        /*! \brief Projects a global coordinate to a local [0,1] coordinate for the axially aligned box

            \param[in] v    The global coordinate
            \return The local coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector3<T>   unproject(const Vector3<T>& v) const noexcept
        {
            return div_elem(v-lo, hi-lo);
        }

        //! Tests this box for validness
        constexpr bool          valid() const noexcept 
        {
            return all(lo) <= hi;
        }

        /*! \brief Computes the volume of the box
        */
        constexpr cube_t<T>       volume() const noexcept
        {
            return (hi-lo).cproduct();
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

    };

    YQ_IEEE754_1(AxBox3)
    

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

    /*! \brief Creates a 3D axially aligned box from container of Vector2's
    */
    template <typename T>
    AxBox3<T> aabb(const std::vector<Vector3<T>>& vals)
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

        AxBox3<T>   ret = aabb(vals[0], vals[1]);
        for(size_t i=2;i<vals.size();++i)
            ret |= vals[i];
        return vals;
    }

    YQ_NAN_1(AxBox3, { nan_v<Vector3<T>>, nan_v<Vector3<T>>});
    YQ_ZERO_1(AxBox3, { zero_v<Vector3<T>>, zero_v<Vector3<T>>});

    YQ_IS_FINITE_1( AxBox3, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox3, is_nan(v.lo) || is_nan(v.hi))


    /*! \brief Computes the center of a 3D axially aligned box
    */
    template <typename T>
    constexpr Vector3<T>      center(const AxBox3<T>& box) noexcept
    {
        return box.center();
    }

    //! Checks for validity (hi >= lo)
    template <typename T>
    constexpr bool    is_valid(const AxBox3<T>& box) noexcept
    {
        return box.is_valid();
    }


    /*! \brief Returns the span (dimensions) of the box
    */
    template <typename T>
    constexpr Vector3<T>    span(const AxBox3<T>&box) noexcept
    {
        return box.span();
    }

    /*! \brief Computes the surface area of a 3D axially aligned bounding box
    */
    template <typename T>
    constexpr square_t<T>    surface_area(const AxBox3<T>& box) noexcept
    {
        return box.surface_area();
    }

    /*! \brief Computes the volume of the box
    */
    template <typename T>
    constexpr cube_t<T>       volume(const AxBox3<T>& box) noexcept
    {
        return box.volume();
    }

}

YQ_TYPE_DECLARE(yq::AxBox3D)
YQ_TYPE_DECLARE(yq::AxBox3F)
YQ_TYPE_DECLARE(yq::AxBox3I)
YQ_TYPE_DECLARE(yq::AxBox3U)

