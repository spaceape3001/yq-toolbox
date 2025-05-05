////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_MKS_HPP 1

#include <yq/keywords.hpp>
#include <yq/trait/cube.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_sqrt.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/ieee754.hpp>
#include <yq/trait/is_basic_float.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/trait/square.hpp>
#include <yq/core/StreamOps.hpp>

#include <type_traits>

namespace yq {
    template <typename T, typename DIM>
    struct MKS {
        using dimension         = DIM;
        using component_type    = T;
    
        T       value = {};
        
        constexpr MKS() noexcept = default;
        constexpr MKS(T v) noexcept : value(v) {}

        template <typename=void> requires has_nan_v<T>
        consteval MKS(nan_k) noexcept : value(nan_v<T>) {}
        consteval MKS(one_k) noexcept : value(one_v<T>) {}
        consteval MKS(zero_k) noexcept : value(zero_v<T>) {}
        
        template <int N>
        requires std::is_floating_point_v<T>
        auto power() const;
        template <int N>
        requires std::is_floating_point_v<T>
        auto root() const;
        template <int N,int D=1>
        requires std::is_floating_point_v<T>
        auto to() const;
        
        constexpr auto operator<=>(const MKS&) const noexcept = default;
    };
    

    template <typename T, typename DIM>
        template <int N>
        requires std::is_floating_point_v<T>
    auto MKS<T,DIM>::power() const
    {
        return MKS<T, typename DIM::template _pow_<N,1>>{::pow(value, (double)N)};
    }
    
    template <typename T, typename DIM>
        template <int D>
        requires std::is_floating_point_v<T>
    auto MKS<T,DIM>::root() const
    {
        return MKS<T,typename DIM::template _pow_<1,D>>{::pow(value, 1.0 / (double) D)};
    }
    

    template <typename T, typename DIM>
        template <int N,int D>
        requires std::is_floating_point_v<T>
    auto MKS<T,DIM>::to() const
    {
        return MKS<T,typename DIM::template _pow_<N,D>>(::pow(value, (double) N /  (double) D));
    }
    
//  --------------------------------------------------------
//  COMPOSITION

    template <typename T, typename DIM>
    MKS<T,DIM> mks(const MKS<T,DIM>& v)
    {
        return v;
    }

    template <typename T, typename DIM>
    struct nan_eval<MKS<T,DIM>> : public std::true_type {
        static consteval MKS<T,DIM> make()
        {                                                   
            return { nan_v<T> };
        }                                                   
    };

    template <typename T, typename DIM>
    struct zero_eval<MKS<T,DIM>> : public std::true_type {
        static consteval MKS<T,DIM> make()
        {
            return { T{} };
        }
    };
    
//  --------------------------------------------------------
//  GETTERS

//  --------------------------------------------------------
//  SETTERS

//  --------------------------------------------------------
//  BASIC FUNCTIONS

    template <typename T, typename DIM>
    MKS<T,DIM> abs(const MKS<T,DIM>& v)
    {
        return { abs(v.value) };
    }
    
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    auto cbrt(const MKS<T,DIM>& v)
    {
        return MKS<T,typename DIM::template _pow_<1,3>>{cbrt(v.value)};
    }

    template <typename T, typename DIM>
    auto cube(const MKS<T,DIM>& v)
    {
        return MKS<cube_t<T>, typename DIM::template _pow_<3,1>>{ v.value * v.value * v.value };
    }

    template <typename T, typename DIM>
    auto operator^(const MKS<T,DIM>& v,three_k)
    {
        return MKS<cube_t<T>, typename DIM::template _pow_<3,1>>{ v.value * v.value * v.value };
    }

    template <typename T, typename DIM>
    ieee754_t<T> ieee754(const MKS<T,DIM>& v)
    {
        return ieee754(v.value);
    }

    template <typename T, typename DIM>
    bool is_finite(const MKS<T,DIM>& v)
    {
        return is_finite(v.value);
    }

    template <typename T, typename DIM>
    bool is_nan(const MKS<T,DIM>& v)
    {
        return is_nan(v.value);
    }
    
    template <typename T, typename DIM>
    requires has_sqrt_v<T>
    auto sqrt(const MKS<T,DIM>& v)
    {
        auto ret    = sqrt(v.value);
        return MKS<decltype(ret), typename DIM::template _pow_<1,2>>{ ret };
    }

    template <typename T, typename DIM>
    auto square(const MKS<T,DIM>& v)
    {
        return MKS<square_t<T>, typename DIM::template _pow_<2,1>>{ v.value * v.value };
    }

    template <typename T, typename DIM>
    auto operator^(const MKS<T,DIM>& v, two_k)
    {
        return MKS<square_t<T>, typename DIM::template _pow_<2,1>>{ v.value * v.value };
    }

//  --------------------------------------------------------
//  POSITIVE

    template <typename T, typename DIM>
    MKS<T,DIM> operator+(const MKS<T,DIM>& a)
    {
        return a;
    }


//  --------------------------------------------------------
//  NEGATIVE

    template <typename T, typename DIM>
    MKS<T,DIM> operator-(const MKS<T,DIM>& a)
    {
        return { -a.value };
    }

//  --------------------------------------------------------
//  NORMALIZATION


//  --------------------------------------------------------
//  ADDITION

    template <typename T, typename DIM>
    MKS<T,DIM> operator+(const MKS<T,DIM>& a, const MKS<T,DIM>& b)
    {
        return { a.value + b.value };
    }

    template <typename T, typename DIM>
    MKS<T,DIM>& operator+=(MKS<T,DIM>& a, const MKS<T,DIM>& b)
    {
        a.value += b.value;
        return a;
    }

//  --------------------------------------------------------
//  SUBTRACTION

    template <typename T, typename DIM>
    MKS<T,DIM> operator-(const MKS<T,DIM>& a, const MKS<T,DIM>& b)
    {
        return { a.value - b.value };
    }

    template <typename T, typename DIM>
    MKS<T,DIM>& operator-=(MKS<T,DIM>& a, const MKS<T,DIM>& b)
    {
        a.value -= b.value;
        return a;
    }


//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename DIM>
    requires is_basic_float_v<T>
    MKS<T,DIM> operator*(T a, const MKS<T,DIM>& b)
    {
        return { a * b.value };
    }
    
    template <typename T, typename DIM>
    requires is_basic_float_v<T>
    MKS<T,DIM> operator*(const MKS<T,DIM>& a, T  b)
    {
        return { a.value * b };
    }
    
    template <typename T, typename DIM>
    requires is_basic_float_v<T>
    MKS<T,DIM>& operator*=(MKS<T,DIM>& a, T  b)
    {
        a.value *= b;
        return a;
    }

    template <typename T, typename U, typename DIMT, typename DIMU>
    MKS<product_t<T,U>,typename DIMT::template _mult_<DIMU>> operator*(const MKS<T,DIMT>& a, const MKS<U,DIMU>& b)
    {
        return { a.value * b.value };
    }
    

//  --------------------------------------------------------
//  DIVISION

    template <typename T, typename DIM>
    requires is_basic_float_v<T>
    MKS<T,typename DIM::template _pow_<-1,1>> operator/(T a, const MKS<T,DIM>& b)
    {
        return { a / b.value };
    }
    
    template <typename T, typename DIM>
    requires is_basic_float_v<T>
    MKS<T,DIM> operator/(const MKS<T,DIM>& a, T  b)
    {
        return { a.value / b };
    }
    
    template <typename T, typename DIM>
    requires is_basic_float_v<T>
    MKS<T,DIM>& operator/=(MKS<T,DIM>& a, T  b)
    {
        a.value /= b;
        return a;
    }

    template <typename T, typename U, typename DIMT, typename DIMU>
    MKS<quotient_t<T,U>,typename DIMT::template _div_<DIMU>> operator/(const MKS<T,DIMT>& a, const MKS<U,DIMU>& b)
    {
        return { a.value / b.value };
    }

//  --------------------------------------------------------
//  DOT PRODUCT


//  --------------------------------------------------------
//  INNER PRODUCT


//  --------------------------------------------------------
//  OUTER PRODUCT


///  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  PROJECTIONS

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    template <typename T, typename DIM, typename R>
    bool is_close(const R& compare, MKS<T,DIM> actual, MKS<T,DIM> expected)
    {
        return compare(actual.value - expected.value, expected.value);
    }

    template <typename T, typename DIM, typename R>
    bool is_close(const R& compare, MKS<T,DIM> actual, std::type_identity_t<T> v)
    {
        return is_close(compare, actual, MKS<T,DIM>{v});
    }

//  --------------------------------------------------------
//  CONDITIONAL INCLUDES
    
//  --------------------------------------------------------
//  STREAMING
    
    template <typename T, typename DIM>
    Stream& operator<<(Stream& stream, const MKS<T,DIM>& v)
    {
        return stream << v.value;
    }
}
