////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_QUATERNION3_HPP 1

#include <yq/typedef/quaternion3.hpp>

#include <yq/keywords.hpp>
#include <yq/meta/MetaBinder.hpp>
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
    
        //! Capture our template parameter for the component type
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
        
        //! Initializes to all zeros
        consteval Quaternion3(zero_k) : Quaternion3(ALL, zero_v<T>) {}
        
        #if YQ_USE_GLM
        //! Initializes from a GLM quaternion
        template <glm::qualifier Q>
        explicit constexpr Quaternion3(const glm::qua<T, Q>& q) : w(q.w), x(q.x), y(q.y), z(q.z) {}
        #endif

        //! Creates a quaternion that effects a specified counter-clockwise rotation about the x-axis
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(ccw_k, x_k, MKS<T,dim::Angle>v);
        
        //! Creates a quaternion that effects a specified clockwise rotation about the X-axis
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(clockwise_k, x_k, MKS<T,dim::Angle>v);

        //! Creates a quaternion that effects a specified counter-clockwise rotation about the y-axis
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(ccw_k, y_k, MKS<T,dim::Angle>v);

        //! Creates a quaternion that effects a specified clockwise rotation about the Y-axis
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(clockwise_k, y_k, MKS<T,dim::Angle>v);

        //! Creates a quaternion that effects a specified counter-clockwise rotation about the z-axis
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(ccw_k, z_k, MKS<T,dim::Angle>v);

        //! Creates a quaternion that effects a specified clockwise rotation about the Z-axis
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(clockwise_k, z_k, MKS<T,dim::Angle>v);
        
        //! Creates a quaternion that effects a specified counter-clockwise rotation about the specified axis
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(ccw_k, const Vector3<T>&, MKS<T,dim::Angle>);

        //! Creates a quaternion that effects a specified clockwise rotation about the specified axis
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(clockwise_k, const Vector3<T>&, MKS<T,dim::Angle>);
        
        //! Creates a quaternion that effects a specified counter-clockwise rotation using the three axis angles provided
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(ccw_k, const Vector3<MKS<T,dim::Angle>>);

        //! Creates a quaternion that effects a specified clockwise rotation using the three axis angles provided
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3(clockwise_k, const Vector3<MKS<T,dim::Angle>>);
        
        //! Creates a quaternion that effects a specified rotation using yaw/pitch/roll as the rubric
        Quaternion3(hpr_k, MKS<T,dim::Angle> hdg_or_yaw, MKS<T,dim::Angle> pitch, MKS<T,dim::Angle> roll);
        
        //! Creates a quaternion that effects the same rotation as the given 3x3 matrix
        template <typename=void>
        requires std::is_floating_point_v<T>
        explicit Quaternion3(const Tensor33<T>&);
        

        //! Equality operator (using default)
        constexpr bool operator==(const Quaternion3&) const noexcept = default;
        
        #if YQ_USE_GLM
        /*! \brief Casts to a GLM quaternion
        */
        template <glm::qualifier Q>
        constexpr operator glm::qua<T,Q>() const noexcept 
        {
            return glm::qua<T,Q>(w,x,y,z);
        }
        #endif

        //! Postive affirmation operator
        Quaternion3             operator+() const;
        
        //! Negation operator
        Quaternion3             operator-() const;

        //! Normalization operator (ie, returns a normalized quaternion)
        template <typename=void>
        requires std::is_floating_point_v<T>
        Quaternion3<T>          operator~() const;
        
        //! Operator for length (squared)
        constexpr square_t<T>   operator^(two_k) const noexcept;

        //! Adds two quaternions, returns the result
        constexpr Quaternion3   operator+ (const Quaternion3<T>&b) const noexcept;
        
        //! Adds right hand quaternion to this one, returns reference
        Quaternion3&            operator+=(const Quaternion3<T>&b) noexcept;
        
        //! Subtracts right quaternion from the left, returns the result
        constexpr Quaternion3   operator- (const Quaternion3<T>&b) const noexcept;
        
        //! Subtracts right hand quaternion from this one, returns reference
        Quaternion3&            operator-=(const Quaternion3<T>&b) noexcept;

        //! Multiplies quaternion by a scaling arithmetic type, returns the result
        template <typename U>
        requires (is_arithmetic_v<U>)
        constexpr Quaternion3<product_t<T,U>>  operator* (U b) const noexcept;

        //! Self-multiplies this quaternion by the right hand term, returns reference
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Quaternion3& operator*=(U b) noexcept;

        //! Multiplies two quaternions, returns the result
        template <typename U>
        constexpr Quaternion3<product_t<T,U>>  operator* (const Quaternion3<U>&b) const noexcept;

        //! Self-Multiplies this quaternion by the right hand one, returns reference
        template <typename U>
        requires self_multiply_v<T,U>
        Quaternion3<T>& operator*=(const Quaternion3<U>&b) noexcept;

        //! Multiplies (or rotates) quaternion with vector, returns result
        template <typename U>
        requires (std::is_floating_point_v<T> && std::is_floating_point_v<U>)
        constexpr Vector3<product_t<T,U>>   operator* (const Vector3<U>&b) const noexcept;

        //! Divides quaternion by scalar, returns result
        template <typename U>
        requires (is_arithmetic_v<T>)
        constexpr Quaternion3<quotient_t<T,U>>  operator/ (U b) const noexcept;
        
        //! Self-divides this quaternion by the scalar, returns reference
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Quaternion3<T>& operator/=(U b) noexcept;

        //template <typename>
        //requires std::is_floating_point_v<T>
        Radian                      angle() const;
        
        //! Extracts the effective axis of rotation from the quaternion, returns it
        Vector3<unity_t<T>>         axis() const;
        
        //! Computes the cayley norm, returns it
        constexpr square_t<T>       cayley_norm() const;
        
        //! Computes & returns the conjugate of this quaternion (abbreviated spelling)
        constexpr Quaternion3       conj() const noexcept;

        //! Computes & returns the conjugate of this quaternion
        constexpr Quaternion3       conjugate() const noexcept;
        
        //! Computes & returns the inverse for this quaternion
        constexpr Quaternion3<inverse_t<T>>   inverse() const noexcept;
        
        //! Computes the square of the length to this quaternion
        constexpr square_t<T>    length²() const noexcept;
        
        //! Computes the length to this quaternion, returns result
        //! \note the square root must be valid for T^2
        T                        length() const;
        
        //template <typename>
        //requires std::is_floating_point_v<T>
        
        //! Returns the angle of rotation required around the X-axis for the zyx rotation sequence
        Radian                      angle(zyx_k, x_k) const;

        //template <typename>
        //requires std::is_floating_point_v<T>
        //! Returns the angle of rotation required around the Y-axis for the zyx rotation sequence
        Radian                      angle(zyx_k, y_k) const;

        //template <typename>
        //requires std::is_floating_point_v<T>
        //! Returns the angle of rotation required around the Z-axis for the zyx rotation sequence
        Radian                      angle(zyx_k, z_k) const;

        //template <typename>
        //requires std::is_floating_point_v<T>
        //! Angles around all three axis for the zyx rotation sequenece
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

    //! \brief Creates an equivalent quaternion from a rotation tensor 
    //! \note This is lossy in nature, so tensor(quaterion(tensor)) can lose information if the tensor is more than
    //!       rotation/scaling.
    template <typename T>
    requires std::is_floating_point_v<T>
    Quaternion3<T>  quaternion(const Tensor33<T>& t);

    //! \brief Creates a quaternion rotor with the given counter clockwise angle around the X-axis, returns it
    template <typename T>
    Quaternion3<T>  rotor_x(MKS<T,dim::Angle> v);

    //! \brief Creates a quaternion rotor with the given counter clockwise angle around the Y-axis, returns it
    template <typename T>
    Quaternion3<T>  rotor_y(MKS<T,dim::Angle> v);

    //! \brief Creates a quaternion rotor with the given counter clockwise angle around the Z-axis, returns it
    template <typename T>
    Quaternion3<T>  rotor_z(MKS<T,dim::Angle> v);

//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  SETTERS


//  --------------------------------------------------------
//  BASIC FUNCTIONS

    //! Returns the conjugate of the given quaternion
    template <typename T>
    constexpr Quaternion3<T> conjugate(const Quaternion3<T>&a);

    //! Returns the square of the length of the given quaternion
    template <typename T>
    constexpr square_t<T>  length²(const Quaternion3<T>&a);

    //! Returns the length of the given quaternion
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
    
    //! Multiplies right side quaternion with left scalar, returns result
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

    //! Creates a quaternion using classic heading-pitch-roll (aviation style)
    template <typename T>
    requires std::is_floating_point_v<T>
    Quaternion3<T>  hpr(const MKS<T,dim::Angle>& hdg, const MKS<T,dim::Angle>& pitch, const MKS<T,dim::Angle>& roll);


    //! Compares two quaternions for closeness (used for unit tests)
    template <typename T, typename R>
    bool is_close(const R& compare, const Quaternion3<T>& actual, const Quaternion3<T>& expected);
    
    //! Compares actual quaternion to expected values (used for unit tests)
    template <typename T, typename R>
    bool is_close(const R& compare, const Quaternion3<T>& actual, std::type_identity_t<T>w, std::type_identity_t<T> x, std::type_identity_t<T> y, std::type_identity_t<T> z);

    //! Streams the quaternion to the stream (generic) in w,x,y,z format
    //! \tparam S   Stream type
    template <typename S, typename T>
    S&  as_stream(S& s, const Quaternion3<T>& v);
    
    //! Prints the quaternion to the given stream
    template <typename T>
    Stream& operator<<(Stream&s, const Quaternion3<T>& v);

    //! Prints the quaternion to the given logger stream
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Quaternion3<T>& v);
}


YQ_TYPE_DECLARE(yq::Quaternion3D)
YQ_TYPE_DECLARE(yq::Quaternion3F)
