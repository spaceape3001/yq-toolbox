////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <math/preamble.hpp>
#include <math/Tensor33.hpp>

namespace yq {

    /*! \brief Quaternion (3D)
    */
    template <typename T>
    struct Quaternion3 {
        using component_type = T;

        T w, x, y, z;

        constexpr Quaternion3() noexcept = default;
        constexpr Quaternion3(T _w, T _x, T _y, T _z) : w(_w), x(_x), y(_y), z(_z) {}
        
        constexpr Quaternion3(all_t, T v) : w(v), x(v), y(v), z(v) {}
        consteval Quaternion3(identity_t) : w(one_v<T>), x(zero_v<T>), y(zero_v<T>), z(zero_v<T>) {}
        consteval Quaternion3(nan_t) : Quaternion3(ALL, nan_v<T>) {}
        consteval Quaternion3(w_t) noexcept : w(one_v<T>), x(zero_v<T>), y(zero_v<T>), z(zero_v<T>) {}
        constexpr Quaternion3(w_t, T v) noexcept :  w(v), x(zero_v<T>), y(zero_v<T>), z(zero_v<T>) {}
        consteval Quaternion3(x_t) noexcept : w(zero_v<T>), x(one_v<T>), y(zero_v<T>), z(zero_v<T>) {}
        constexpr Quaternion3(x_t, T v) noexcept : w(zero_v<T>), x(v), y(zero_v<T>), z(zero_v<T>)  {}
        consteval Quaternion3(y_t) noexcept : w(zero_v<T>), x(zero_v<T>), y(one_v<T>), z(zero_v<T>) {}
        constexpr Quaternion3(y_t, T v) noexcept : w(zero_v<T>), x(zero_v<T>), y(v), z(zero_v<T>) {}
        consteval Quaternion3(z_t) noexcept : w(zero_v<T>), x(zero_v<T>), y(zero_v<T>), z(one_v<T>) {}
        constexpr Quaternion3(z_t, T v) noexcept : w(zero_v<T>), x(zero_v<T>), y(zero_v<T>), z(v) {}
        consteval Quaternion3(zero_t) : Quaternion3(ALL, zero_v<T>) {}
        
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(ccw_t, x_t, MKS<T,dim::Angle>v);
        
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(clockwise_t, x_t, MKS<T,dim::Angle>v);

        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(ccw_t, y_t, MKS<T,dim::Angle>v);

        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(clockwise_t, y_t, MKS<T,dim::Angle>v);

        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(ccw_t, z_t, MKS<T,dim::Angle>v);

        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(clockwise_t, z_t, MKS<T,dim::Angle>v);
        
        
        
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(hpr_t, MKS<T,dim::Angle> hdg_or_yaw, MKS<T,dim::Angle> pitch, MKS<T,dim::Angle> roll);
        

        template <typename=void>
        requires std::is_floating_point_v<T>
        explicit Quaternion3(const Tensor33<T>&);
        

        //! Equality operator (using default)
        constexpr bool operator==(const Quaternion3&) const noexcept = default;
        
        Quaternion3             operator+() const;
        Quaternion3             operator-() const;

        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3<T>          operator~() const;
        
        constexpr trait::square_t<T>   operator^(two_t) const noexcept;

        constexpr Quaternion3   operator+ (const Quaternion3<T>&b) const noexcept;
        Quaternion3&            operator+=(const Quaternion3<T>&b) noexcept;
        constexpr Quaternion3   operator- (const Quaternion3<T>&b) const noexcept;
        Quaternion3&            operator-=(const Quaternion3<T>&b) noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U>)
        constexpr Quaternion3<trait::product_t<T,U>>  operator* (U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Quaternion3& operator*=(U b) noexcept;

        template <typename U>
        constexpr Quaternion3<trait::product_t<T,U>>  operator* (const Quaternion3<U>&b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Quaternion3<T>& operator*=(const Quaternion3<U>&b) noexcept;

        template <typename U>
        requires (std::is_floating_point_v<T> && std::is_floating_point_v<U>)
        constexpr Vector3<trait::product_t<T,U>>   operator* (const Vector3<U>&b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Quaternion3<T>& operator/=(U b) noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<T>)
        constexpr Quaternion3<trait::quotient_t<T,U>>  operator/ (U b) const noexcept;
        
        Vector3<trait::unity_t<T>>  axis() const;
        
        constexpr Quaternion3    conj() const noexcept;
        constexpr Quaternion3    conjugate() const noexcept;
        constexpr Quaternion3<trait::inverse_t<T>>   inverse() const noexcept;
        constexpr trait::square_t<T>    length²() const noexcept;
        T                        length() const;
    };

    YQ_IEEE754_1(Quaternion3)

//  --------------------------------------------------------
//  COMPOSITION

    YQ_IDENTITY_1(Quaternion3, Quaternion3<T>(IDENTITY))
    YQ_NAN_1(Quaternion3, Quaternion3<T>(NAN))
    YQ_ZERO_1(Quaternion3, Quaternion3<T>(ZERO))

    /*! \brief Creates a quaternion
    */
    template <typename T>
    constexpr Quaternion3<T> quaternion(T w, std::type_identity_t<T> x, std::type_identity_t<T> y, std::type_identity_t<T> z)
    {
        return {w,x,y,z};
    }

    template <typename T>
    requires std::is_floating_point_v<T>
    Quaternion3<T>  quaternion(const Tensor33<T>& t);

    template <typename T>
    Quaternion3<T>  rotor_x(MKS<T,dim::Angle> v);

    template <typename T>
    Quaternion3<T>  rotor_y(MKS<T,dim::Angle> v);

    template <typename T>
    Quaternion3<T>  rotor_z(MKS<T,dim::Angle> v);

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  SETTERS


//  --------------------------------------------------------
//  BASIC FUNCTIONS

    template <typename T>
    constexpr Quaternion3<T> conjugate(const Quaternion3<T>&a);

    template <typename T>
    constexpr trait::square_t<T>  length²(const Quaternion3<T>&a);

    template <typename T>
    constexpr T  length(const Quaternion3<T>&a);
    

    YQ_IS_NAN_1(Quaternion3, is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || is_nan(v.w))
    YQ_IS_FINITE_1(Quaternion3, is_finite(v.x) && is_finite(v.y) && is_finite(v.z) && is_finite(v.w))
        

//  --------------------------------------------------------

//  --------------------------------------------------------
//  NORMALIZATION



//  --------------------------------------------------------
//  ADDITION


//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T>
    requires std::is_floating_point_v<T>
    void    pre_mult(const Quaternion3<T>&a, Quaternion3<T>&b);

    template <typename T>
    requires std::is_floating_point_v<T>
    void    post_mult(Quaternion3<T>&a, const Quaternion3<T>&b);
    

    template <typename T, typename U>
    requires (trait::is_arithmetic_v<T>)
    constexpr Quaternion3<trait::product_t<T,U>>  operator*(T a, const Quaternion3<U>&b);



//  --------------------------------------------------------
//  DIVISION


//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT


//  --------------------------------------------------------
//  OUTER PRODUCT


///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T>
    requires std::is_floating_point_v<T>
    Quaternion3<T>  hpr(const MKS<T,dim::Angle>& hdg, const MKS<T,dim::Angle>& pitch, const MKS<T,dim::Angle>& roll);



}


YQ_TYPE_DECLARE(yq::Quaternion3D)
YQ_TYPE_DECLARE(yq::Quaternion3F)
