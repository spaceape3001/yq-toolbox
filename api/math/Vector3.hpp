////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_3__HPP 1
#include <math/preamble.hpp>

namespace yq {
    /*! \brief Vector of 3 dimension(s)
    
        This is a 3 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector3 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector3 unit_x();
        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector3 unit_y();
        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector3 unit_z();

        //! Component for the $(bit)s dimension.
        T       x;
        //! Component for the $(bit)s dimension.
        T       y;
        //! Component for the $(bit)s dimension.
        T       z;;
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector3&) const noexcept = default;

        constexpr operator glm::vec<3, T, glm::defaultp>() const noexcept
        {
            return { x, y, z };
        }
    };

    YQ_IEEE754_1(Vector3)
    

    /*! \brief Creates a $(N)d dimensioal vector
    
        Helper function to create a $(N) dimensional cartesian vector where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr Vector3<T> vector(T x, std::type_identity_t<T> y, std::type_identity_t<T> z)
    {
        return {x,y,z};
    }
    
    template <typename T, glm::qualifier Q>
    constexpr Vector3<T> vector(const glm::vec<3,T,Q>& v)
    {
        return { v.x, v.y, v.z };
    }

    template <typename T>
    consteval Vector3<T> Vector3<T>::unit_x()
    {
        return {one_v<T>,zero_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector3<T> Vector3<T>::unit_y()
    {
        return {zero_v<T>,one_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector3<T> Vector3<T>::unit_z()
    {
        return {zero_v<T>,zero_v<T>,one_v<T>};
    }

    constexpr Vector3D operator "" _x3(unsigned long long int v)
    {
        return {(double) v, 0., 0.};
    }

    constexpr Vector3D operator "" _x3(long double v)
    {
        return {(double) v, 0., 0.};
    }

    constexpr Vector3D operator "" _y3(unsigned long long int v)
    {
        return {0., (double) v, 0.};
    }

    constexpr Vector3D operator "" _y3(long double v)
    {
        return {0., (double) v, 0.};
    }

    constexpr Vector3D operator "" _z3(unsigned long long int v)
    {
        return {0., 0., (double) v};
    }

    constexpr Vector3D operator "" _z3(long double v)
    {
        return {0., 0., (double) v};
    }


    YQ_NAN_1(Vector3, Vector3<T>{nan_v<T>, nan_v<T>, nan_v<T>})
    YQ_ZERO_1(Vector3, Vector3<T>{zero_v<T>, zero_v<T>, zero_v<T>})
    

    YQ_IS_NAN_1(Vector3, is_nan(v.x) || is_nan(v.y) || is_nan(v.z))
    YQ_IS_FINITE_1(Vector3, is_finite(v.x) && is_finite(v.y) && is_finite(v.z))
        
}

YQ_TYPE_DECLARE(yq::Vector3D)
YQ_TYPE_DECLARE(yq::Vector3F)
YQ_TYPE_DECLARE(yq::Vector3I)
YQ_TYPE_DECLARE(yq::Vector3U)

