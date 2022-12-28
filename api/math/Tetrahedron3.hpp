////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Vector3.hpp>
#include "TetrahedronData.hpp"

namespace yq {

    /*! \brief Tetrahedron
    
        \note This isn't required to be a *REGULAR* tetrahedron, simply
        any four cornered polyhedra is considered okay
    */
    template <typename T>
    struct Tetrahedron3 {
        //!  Capture the template parameter
        using component_type    = T;
    
        //!     Corners (call 'em a, b, c, & d)
        Vector3<T>     a, b, c, d;

        //! Defaulted comparson operator
        constexpr bool operator==(const Tetrahedron3&) const noexcept = default;
        
        //! Computes the centroid of the tetrahedron
        constexpr Vector3<T>    centroid() const noexcept
        {
            if constexpr (std::is_floating_point_v<T>)
                return ((a+b)+(c+d)) * T(0.25);
            if constexpr (std::is_integral_v<T>)
                return ((a+b)+(c+d)) / T(4);
            return {};
        }
        
        /*! \brief Makes a regular tetrahedron 
            
            This makes a regular tetrahedron whose points 
            are on the unit sphere.
        */
        template <typename=void>
        requires trait::has_sqrt_v<square_t<T>>
        static Tetrahedron3  make_unit()
        {
            //  formula taken from https://en.wikipedia.org/wiki/Tetrahedron
            const T third    = T(1./3.);
            const T sq29    = sqrt(square_t<T>(2./9.));
            const T sq89    = sqrt(square_t<T>(8./9.));
            const T sq23    = sqrt(square_t<T>(2./2.));
            
            return { 
                { sq89, T(0.), -third },
                { -sq29, sq23, -third },
                { -sq29, -sq23, -third },
                { T(0.), T(0.), T(1.) }
            };
        }

        //! Returns a regular tetrahedron whose points are on the unit sphere */
        template <typename=void>
        requires trait::has_sqrt_v<square_t<T>>
        static const Tetrahedron3&  unit()
        {
            static const Tetrahedron3 ret = make_unit();
            return ret;
        }
        
        //! Computes the volume of this tetrahedron
        constexpr cube_t<T>   volume() const noexcept
        {
            return abs((a-d) DOT ((b-d) CROSS (c-d))) / ieee754_t<T>(6.);
        }
    };

    YQ_IEEE754_1(Tetrahedron3)

    //! Creates a tetrahedron from four points
    template <typename T>
    Tetrahedron3<T>    tetrahedron(const Vector3<T>& a, const std::type_identity_t<Vector3<T>>& b, const std::type_identity_t<Vector3<T>>& c, const std::type_identity_t<Vector3<T>>& d)
    {
        return { a, b, c, d };
    }

    YQ_NAN_1(Tetrahedron3, { nan_v<Vector3<T>>, nan_v<Vector3<T>>, nan_v<Vector3<T>>, nan_v<Vector3<T>> })
    YQ_ZERO_1(Tetrahedron3, { zero_v<Vector3<T>>, zero_v<Vector3<T>>, zero_v<Vector3<T>>, zero_v<Vector3<T>> })


    YQ_IS_FINITE_1(Tetrahedron3, is_finite(v.a) && is_finite(v.b) && is_finite(v.c) && is_finite(v.d))
    YQ_IS_NAN_1(Tetrahedron3, is_nan(v.a) || is_nan(v.b) || is_nan(v.c) || is_nan(v.d))

    //! Computes the centroid of the given tetrahedron
    template <typename T>
    constexpr Vector3<T>  centroid(const Tetrahedron3<T>& tetra) noexcept
    {
        return tetra.centroid();
    }

    //! Computes the volume of the given tetrahedron
    template <typename T>
    constexpr cube_t<T>   volume(const Tetrahedron3<T>& tetra) noexcept
    {
        return tetra.volume();
    }
}

YQ_TYPE_DECLARE(yq::Tetrahedron3D)
YQ_TYPE_DECLARE(yq::Tetrahedron3F)
YQ_TYPE_DECLARE(yq::Tetrahedron3I)
YQ_TYPE_DECLARE(yq::Tetrahedron3U)

