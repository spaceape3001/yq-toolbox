////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__VECTOR_2__HPP 1
#include <math/preamble.hpp>

namespace yq {
    /*! \brief Vector of 2 dimension(s)
    
        This is a 2 dimensional cartesian vector of the given type.
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Vector2 {
        //! Component data type argument to this structure (ie, template parameter T)
        using component_type = T;

        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector2 unit_x();
        /*! \brief Creates a unit-vector in the $(bit)s dimension.
        */
        static consteval Vector2 unit_y();

        //! Component for the $(bit)s dimension.
        T       x;
        //! Component for the $(bit)s dimension.
        T       y;;
        
        //! Equality operator (using default)
        constexpr bool operator==(const Vector2&) const noexcept = default;

        constexpr operator glm::vec<2, T, glm::defaultp>() const noexcept
        {
            return { x, y  };
        }
    };

    YQ_IEEE754_1(Vector2)
    
    /*! \brief Creates a $(N)d dimensioal vector
    
        Helper function to create a $(N) dimensional cartesian vector where the component type is deduced from
        the first argument.
    */
    template <typename T>
    constexpr Vector2<T> vector(T x, std::type_identity_t<T> y)
    {
        return {x,y};
    }
    
    template <typename T, glm::qualifier Q>
    constexpr Vector2<T> vector(const glm::vec<2,T,Q>& v)
    {
        return { v.x, v.y };
    }


    template <typename T>
    consteval Vector2<T> Vector2<T>::unit_x()
    {
        return {one_v<T>,zero_v<T>};
    }

    template <typename T>
    consteval Vector2<T> Vector2<T>::unit_y()
    {
        return {zero_v<T>,one_v<T>};
    }

    constexpr Vector2D operator "" _x2(unsigned long long int v)
    {
        return {(double) v, 0.};
    }

    constexpr Vector2D operator "" _x2(long double v)
    {
        return {(double) v, 0.};
    }

    constexpr Vector2D operator "" _y2(unsigned long long int v)
    {
        return {0., (double) v};
    }

    constexpr Vector2D operator "" _y2(long double v)
    {
        return {0., (double) v};
    }


    YQ_NAN_1(Vector2, Vector2<T>{nan_v<T>, nan_v<T>})
    YQ_ZERO_1(Vector2, Vector2<T>{zero_v<T>, zero_v<T>})
    

    YQ_IS_NAN_1(Vector2, is_nan(v.x) || is_nan(v.y))
    YQ_IS_FINITE_1(Vector2, is_finite(v.x) && is_finite(v.y))
        




}

YQ_TYPE_DECLARE(yq::Vector2D)
YQ_TYPE_DECLARE(yq::Vector2F)
YQ_TYPE_DECLARE(yq::Vector2I)
YQ_TYPE_DECLARE(yq::Vector2U)

