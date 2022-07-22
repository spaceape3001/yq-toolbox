////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_1__HPP 1
#include <math/preamble.hpp>

namespace yq {
    /*! \brief Vector of 1 dimension(s)
    
        This is a 1 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector1 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector1 unit_x();

        //! Component for the $(bit)s dimension.
        T       x;;
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector1&) const noexcept = default;

        constexpr operator glm::vec<1, T, glm::defaultp>() const noexcept
        {
            return { x  };
        }
    };

    YQ_IEEE754_1(Vector1)
    
    /*! \brief Creates a $(N)d dimensioal vector
    
        Helper function to create a $(N) dimensional cartesian vector where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr Vector1<T> vector(T x)
    {
        return {x};
    }
    
    template <typename T, glm::qualifier Q>
    constexpr Vector1<T> vector(const glm::vec<1,T,Q>& v)
    {
        return { v.x };
    }
    
    template <typename T>
    consteval Vector1<T> Vector1<T>::unit_x()
    {
        return {one_v<T>};
    }

    constexpr Vector1D operator "" _x1(unsigned long long int v)
    {
        return {(double) v};
    }

    constexpr Vector1D operator "" _x1(long double v)
    {
        return {(double) v};
    }

    YQ_NAN_1(Vector1, Vector1<T>{nan_v<T>})
    YQ_ZERO_1(Vector1, Vector1<T>{zero_v<T>})
    
    YQ_IS_NAN_1(Vector1, is_nan(v.x))
    YQ_IS_FINITE_1(Vector1, is_finite(v.x))
        
    
}

YQ_TYPE_DECLARE(yq::Vector1D)
YQ_TYPE_DECLARE(yq::Vector1F)
YQ_TYPE_DECLARE(yq::Vector1I)
YQ_TYPE_DECLARE(yq::Vector1U)

