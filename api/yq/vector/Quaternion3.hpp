////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_QUATERNION3_HPP 1

#include <yq/typedef/quaternion3.hpp>

#include <yq/keywords.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/trait/has_identity.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/ieee754.hpp>
#include <yq/trait/is_arithmetic.hpp>
#include <yq/trait/inverse.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/trait/square.hpp>
#include <yq/trait/unity.hpp>
#include <yq/unit/declare.hpp>
#include <yq/unit/dims.hpp>

#if YQ_USE_GLM
    #include <yq/math/glm.hpp>
#endif

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename, typename> struct MKS;
    template <typename> struct Tensor33;
    template <typename> struct Vector3;
    class Stream;

    /*! \brief Quaternion (3D)
    */
    template <typename T>
    struct Quaternion3 {
        using component_type = T;

        T w;    //!< W component
        T x;    //!< X component
        T y;    //!< Y component
        T z;    //!< Z component

        //! Default constructor (does nothing)
        constexpr Quaternion3() noexcept = default;
        
        //! Component wise constructor
        constexpr Quaternion3(T _w, T _x, T _y, T _z) : w(_w), x(_x), y(_y), z(_z) {}
        
        //! Initializes to all components having the same value
        constexpr Quaternion3(all_k, T v) : w(v), x(v), y(v), z(v) {}
        
        //! Initializes to an identity quaternion
        consteval Quaternion3(identity_k) : w(one_v<T>), x(zero_v<T>), y(zero_v<T>), z(zero_v<T>) {}
        
        //! Initializes all components to not-a-number
        consteval Quaternion3(nan_k) : Quaternion3(ALL, nan_v<T>) {}
        
        //! Initializes to a unit quaternion in W (rest are zero)
        consteval Quaternion3(w_k) noexcept : w(one_v<T>), x(zero_v<T>), y(zero_v<T>), z(zero_v<T>) {}
        
        //! Initializes to a single value on the W-component
        constexpr Quaternion3(w_k, T v) noexcept :  w(v), x(zero_v<T>), y(zero_v<T>), z(zero_v<T>) {}
        
        //! Initializes to a unit quaternion in X
        consteval Quaternion3(x_k) noexcept : w(zero_v<T>), x(one_v<T>), y(zero_v<T>), z(zero_v<T>) {}
        
        //! Initializes to a single value on the X-component (rest are zero)
        constexpr Quaternion3(x_k, T v) noexcept : w(zero_v<T>), x(v), y(zero_v<T>), z(zero_v<T>)  {}
        
        //! Initializes to a unit quaternion in Y
        consteval Quaternion3(y_k) noexcept : w(zero_v<T>), x(zero_v<T>), y(one_v<T>), z(zero_v<T>) {}
        
        //! Initializes to a single value on the Y-component (rest are zero)
        constexpr Quaternion3(y_k, T v) noexcept : w(zero_v<T>), x(zero_v<T>), y(v), z(zero_v<T>) {}
        
        //! Initializes to a unit quaternion in Z
        consteval Quaternion3(z_k) noexcept : w(zero_v<T>), x(zero_v<T>), y(zero_v<T>), z(one_v<T>) {}
        
        //! Initializes to a single value on the Z-component (rest are zero)
        constexpr Quaternion3(z_k, T v) noexcept : w(zero_v<T>), x(zero_v<T>), y(zero_v<T>), z(v) {}
        consteval Quaternion3(zero_k) : Quaternion3(ALL, zero_v<T>) {}
        
        #if YQ_USE_GLM
        template <glm::qualifier Q>
        explicit constexpr Quaternion3(const glm::qua<T, Q>& q) : w(q.w), x(q.x), y(q.y), z(q.z) {}
        #endif

        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(ccw_k, x_k, MKS<T,dim::Angle>v);
        
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(clockwise_k, x_k, MKS<T,dim::Angle>v);

        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(ccw_k, y_k, MKS<T,dim::Angle>v);

        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(clockwise_k, y_k, MKS<T,dim::Angle>v);

        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(ccw_k, z_k, MKS<T,dim::Angle>v);

        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(clockwise_k, z_k, MKS<T,dim::Angle>v);
        
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(ccw_k, const Vector3<T>&, MKS<T,dim::Angle>);

        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(clockwise_k, const Vector3<T>&, MKS<T,dim::Angle>);
        
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(ccw_k, const Vector3<MKS<T,dim::Angle>>);

        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(clockwise_k, const Vector3<MKS<T,dim::Angle>>);
        
        Quaternion3(hpr_k, MKS<T,dim::Angle> hdg_or_yaw, MKS<T,dim::Angle> pitch, MKS<T,dim::Angle> roll);
        

        template <typename=void>
        requires std::is_floating_point_v<T>
        explicit Quaternion3(const Tensor33<T>&);
        

        //! Equality operator (using default)
        constexpr bool operator==(const Quaternion3&) const noexcept = default;
        
        #if YQ_USE_GLM
        template <glm::qualifier Q>
        constexpr operator glm::qua<T,Q>() const noexcept 
        {
            return glm::qua<T,Q>(w,x,y,z);
        }
        #endif

        Quaternion3             operator+() const;
        Quaternion3             operator-() const;

        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3<T>          operator~() const;
        
        constexpr square_t<T>   operator^(two_k) const noexcept;

        constexpr Quaternion3   operator+ (const Quaternion3<T>&b) const noexcept;
        Quaternion3&            operator+=(const Quaternion3<T>&b) noexcept;
        constexpr Quaternion3   operator- (const Quaternion3<T>&b) const noexcept;
        Quaternion3&            operator-=(const Quaternion3<T>&b) noexcept;

        template <typename U>
        requires (is_arithmetic_v<U>)
        constexpr Quaternion3<product_t<T,U>>  operator* (U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Quaternion3& operator*=(U b) noexcept;

        template <typename U>
        constexpr Quaternion3<product_t<T,U>>  operator* (const Quaternion3<U>&b) const noexcept;

        template <typename U>
        requires self_multiply_v<T,U>
        Quaternion3<T>& operator*=(const Quaternion3<U>&b) noexcept;

        template <typename U>
        requires (std::is_floating_point_v<T> && std::is_floating_point_v<U>)
        constexpr Vector3<product_t<T,U>>   operator* (const Vector3<U>&b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Quaternion3<T>& operator/=(U b) noexcept;

        template <typename U>
        requires (is_arithmetic_v<T>)
        constexpr Quaternion3<quotient_t<T,U>>  operator/ (U b) const noexcept;
        
        //template <typename>
        //requires std::is_floating_point_v<T>
        Radian                      angle() const;
        
        Vector3<unity_t<T>>         axis() const;
        
        constexpr square_t<T>       cayley_norm() const;
        
        constexpr Quaternion3       conj() const noexcept;
        constexpr Quaternion3       conjugate() const noexcept;
        constexpr Quaternion3<inverse_t<T>>   inverse() const noexcept;
        constexpr square_t<T>    length²() const noexcept;
        T                        length() const;
        
        //template <typename>
        //requires std::is_floating_point_v<T>
        Radian                      angle(zyx_k, x_k) const;

        //template <typename>
        //requires std::is_floating_point_v<T>
        Radian                      angle(zyx_k, y_k) const;

        //template <typename>
        //requires std::is_floating_point_v<T>
        Radian                      angle(zyx_k, z_k) const;

        //template <typename>
        //requires std::is_floating_point_v<T>
        unit::Radian3D              angle(zyx_k) const;
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
    constexpr square_t<T>  length²(const Quaternion3<T>&a);

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
    requires (is_arithmetic_v<T>)
    constexpr Quaternion3<product_t<T,U>>  operator*(T a, const Quaternion3<U>&b);



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


    template <typename T, typename R>
    bool is_close(const R& compare, const Quaternion3<T>& actual, const Quaternion3<T>& expected);
    
    template <typename T, typename R>
    bool is_close(const R& compare, const Quaternion3<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y, std::type_identity_t<T> z,std::type_identity_t<T>w);

    template <typename S, typename T>
    S&  as_stream(S& s, const Quaternion3<T>& v);
    
    template <typename T>
    Stream& operator<<(Stream&s, const Quaternion3<T>& v);

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Quaternion3<T>& v);
}


YQ_TYPE_DECLARE(yq::Quaternion3D)
YQ_TYPE_DECLARE(yq::Quaternion3F)
