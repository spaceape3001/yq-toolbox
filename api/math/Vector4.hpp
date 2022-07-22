////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_4__HPP 1
#include <math/preamble.hpp>
#include <math/trig.hpp>

namespace yq {
    /*! \brief Vector of 4 dimension(s)
    
        This is a 4 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector4 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;
        
        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector4 unit_x();
        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector4 unit_y();
        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector4 unit_z();
        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector4 unit_w();

        //! Component for the $(bit)s dimension.
        T       x;
        //! Component for the $(bit)s dimension.
        T       y;
        //! Component for the $(bit)s dimension.
        T       z;
        //! Component for the $(bit)s dimension.
        T       w;;
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector4&) const noexcept = default;
        
        constexpr operator glm::vec<4, T, glm::defaultp>() const noexcept
        {
            return { x, y, z, w };
        }
    };
    
    YQ_IEEE754_1(Vector4)
    

    /*! \brief Creates a 4 dimensioal vector
    
        Helper function to create a 4 dimensional cartesian vector where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr Vector4<T> vector(T x, std::type_identity_t<T> y, std::type_identity_t<T> z, std::type_identity_t<T> w)
    {
        return {x,y,z,w};
    }
    
    template <typename T, glm::qualifier Q>
    constexpr Vector4<T> vector(const glm::vec<4,T,Q>& v)
    {
        return { v.x, v.y, v.z, v.w };
    }

    template <typename T>
    consteval Vector4<T> Vector4<T>::unit_x()
    {
        return {one_v<T>,zero_v<T>,zero_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector4<T> Vector4<T>::unit_y()
    {
        return {zero_v<T>,one_v<T>,zero_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector4<T> Vector4<T>::unit_z()
    {
        return {zero_v<T>,zero_v<T>,one_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector4<T> Vector4<T>::unit_w()
    {
        return {zero_v<T>,zero_v<T>,zero_v<T>,one_v<T>};
    }

    constexpr Vector4D operator "" _x4(unsigned long long int v)
    {
        return {(double) v, 0., 0., 0.};
    }

    constexpr Vector4D operator "" _x4(long double v)
    {
        return {(double) v, 0., 0., 0.};
    }

    constexpr Vector4D operator "" _y4(unsigned long long int v)
    {
        return {0., (double) v, 0., 0.};
    }

    constexpr Vector4D operator "" _y4(long double v)
    {
        return {0., (double) v, 0., 0.};
    }

    constexpr Vector4D operator "" _z4(unsigned long long int v)
    {
        return {0., 0., (double) v, 0.};
    }

    constexpr Vector4D operator "" _z4(long double v)
    {
        return {0., 0., (double) v, 0.};
    }

    constexpr Vector4D operator "" _w4(unsigned long long int v)
    {
        return {0., 0., 0., (double) v};
    }

    constexpr Vector4D operator "" _w4(long double v)
    {
        return {0., 0., 0., (double) v};
    }

    YQ_NAN_1(Vector4, Vector4<T>{nan_v<T>, nan_v<T>, nan_v<T>, nan_v<T>})
    YQ_ZERO_1(Vector4, Vector4<T>{zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>})
    
    YQ_IS_NAN_1(Vector4, is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || is_nan(v.w))
    YQ_IS_FINITE_1(Vector4, is_finite(v.x) && is_finite(v.y) && is_finite(v.z) && is_finite(v.w))

}

YQ_TYPE_DECLARE(yq::Vector4D)
YQ_TYPE_DECLARE(yq::Vector4F)
YQ_TYPE_DECLARE(yq::Vector4I)
YQ_TYPE_DECLARE(yq::Vector4U)

