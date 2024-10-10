////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TETRAHEDRON_HPP 1

#include <yq/typedef/tetrahedron3.hpp>

#include <yq-toolbox/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq-toolbox/vector/Vector3.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {

    template <typename> struct TetrahedronData;

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
        
        constexpr Tetrahedron3() noexcept = default;
        constexpr Tetrahedron3(const Vector3<T>& _a, const Vector3<T>& _b, const Vector3<T>& _c, const Vector3<T>& _d) 
            : a(_a), b(_b), c(_c), d(_d) {}
        constexpr Tetrahedron3(all_t, const Vector3<T>& v) noexcept : a(v), b(v), c(v), d(v) {}
        consteval Tetrahedron3(nan_t) noexcept : Tetrahedron3(ALL, Vector3<T>(NAN)) {}
        consteval Tetrahedron3(zero_t) noexcept : Tetrahedron3(ALL, Vector3<T>(ZERO)) {}
        constexpr Tetrahedron3(const Triangle3<T>& _t, const Vector3<T>& d);
        
        /*! \brief Makes a regular tetrahedron 
            
            This makes a regular tetrahedron whose points 
            are on the unit sphere.
            
            \note Once sqrt is constexpr, this will be too
        */
        template <typename=void>
            requires has_sqrt_v<square_t<T>>
        Tetrahedron3(unit_t);
        
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator Tetrahedron3<U>() const noexcept
        {
            return { (Vector3<U>) a, (Vector3<U>) b, (Vector3<U>) c };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator Tetrahedron3<U>() const 
        {
            return { (Vector3<U>) a, (Vector3<U>) b, (Vector3<U>) c };
        }

        //! Implicit conversion to triangle data
        constexpr operator TetrahedronData<Vector3<T>> () const noexcept;

        constexpr Tetrahedron3 operator+() const noexcept;
        constexpr Tetrahedron3 operator-() const noexcept;
        
        constexpr Tetrahedron3 operator+(const Vector3<T>&) const noexcept;
        Tetrahedron3& operator+=(const Vector3<T>&) noexcept;
        constexpr Tetrahedron3 operator-(const Vector3<T>&) const noexcept;
        Tetrahedron3& operator-=(const Vector3<T>&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tetrahedron3<product_t<T,U>> operator*(U) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Tetrahedron3& operator*=(U) noexcept;

        template <typename U>
        Tetrahedron3<product_t<T,U>>   operator*(const Tensor33<U>&) const noexcept;

        template <typename U>
        requires self_multiply_v<T,U>
        Tetrahedron3&   operator*=(const Tensor33<U>&) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tetrahedron3<quotient_t<T,U>> operator/(U) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Tetrahedron3& operator/=(U) noexcept;
        
        
                //! Defaulted comparson operator
        constexpr bool operator==(const Tetrahedron3&) const noexcept = default;
        
        constexpr AxBox3<T>   bounds() const noexcept;
        
        //! Computes the centroid of the tetrahedron
        constexpr Vector3<T>    centroid() const noexcept;

        //! Returns a regular tetrahedron whose points are on the unit sphere */
        template <typename=void>
        requires has_sqrt_v<square_t<T>>
        static const Tetrahedron3&  unit();
        
        //! Computes the volume of this tetrahedron
        constexpr cube_t<T>   volume() const noexcept;
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

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tetrahedron3<product_t<T,U>> operator*(T lhs, const Tetrahedron3<U>& rhs) noexcept;
    
    /*! \brief Creates an axially aligned bounding box from the three triangle vertices */
    template <typename T>
    constexpr AxBox3<T>   aabb(const Tetrahedron3<T>& tri) noexcept;


    //! Computes the centroid of the given tetrahedron
    template <typename T>
    constexpr Vector3<T>  centroid(const Tetrahedron3<T>& tetra) noexcept;

    //! Computes the volume of the given tetrahedron
    template <typename T>
    constexpr cube_t<T>   volume(const Tetrahedron3<T>& tetra) noexcept;
}

YQ_TYPE_DECLARE(yq::Tetrahedron3D)
YQ_TYPE_DECLARE(yq::Tetrahedron3F)
YQ_TYPE_DECLARE(yq::Tetrahedron3I)
YQ_TYPE_DECLARE(yq::Tetrahedron3U)

