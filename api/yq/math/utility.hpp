////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/*
    This file is for those odd small utilities, ones that had been being crammed
    into preamble.hpp but shouldn't...
*/

#include <yq/keywords.hpp>
#include <yq/trait/can_add.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/ieee754.hpp>
#include <yq/trait/is_arithmetic.hpp>
#include <yq/trait/is_floating_point.hpp>
#include <yq/trait/square.hpp>
#include <cmath>
#include <initializer_list>
#include <span>
#include <utility>
#include <vector>

namespace yq {

    template <typename F, typename S>
    S       greatest(const std::pair<F,S>& a, const std::pair<F,S>& b)
    {
        if(a.first >= b.first)
            return a.second;
        else
            return b.second;
    }

    template <typename F, typename S>
    S       greatest(const std::pair<F,S>& a, const std::pair<F,S>& b, const std::pair<F,S>& c)
    {
        if(c.first >= std::max(a.first, b.first))
            return c.second;
        else if(b.first >= std::max(a.first, c.first))
            return b.second;
        else
            return a.second;
    }


    inline int   iround(double v)
    {
        return (int)(std::round(v)+std::copysign(0.1,v));
    }

    inline int   iceil(double r)
    {
        return (int)(ceil(r)+std::copysign(0.1,r));
    }

    inline int   itrunc(double r)
    {
        return (int)(trunc(r)+std::copysign(0.1,r));
    }

    inline int   ifloor(double r)
    {
        return (int)(floor(r)+std::copysign(0.1,r));
    }

    template <typename T, typename R>
    requires is_arithmetic_v<T>
    bool is_close(const R& compare, T actual, T expected)
    {
        return compare(actual - expected, expected);
    }
    
    /*! \brief Mid-way divide two numbers
    */
    template <typename T>
    constexpr T     middivide(T a, T b=T{}) noexcept
    {
        if constexpr (has_ieee754_v<T>)
            return ieee754_t<T>(0.5)*(a+b);
        else if constexpr (std::is_integral_v<T>)
            return (a+b) / T(2);
        else
            return {};
    }

    template <typename T>
    constexpr T   positive(T b) noexcept
    {
        return (b >= zero_v<T>) ? b : -b;
    }

    template <typename T>
    constexpr T   negative(T b) noexcept
    {
        return (b >= zero_v<T>) ? -b : b;
    }
    
    template <typename T>
    requires is_arithmetic_v<T>
    constexpr square_t<T>    operator^(T v, two_k) noexcept
    {
        return v*v;
    }

    template <typename T>
    requires has_nan_v<T>
    T  antinan(std::initializer_list<T> data, T def=zero_v<T>)
    {
        for(T t : data){
            if(!is_nan(t))
                return t;
        }
        return def;
    }
    
    template <typename T>
    requires can_add_v<T>
    constexpr T   sum(std::span<const T> data) noexcept
    {
        T   ret = zero_v<T>;
        for(const T& v : data)
            ret += v;
        return ret;
    }

    template <typename T>
    requires can_add_v<T>
    constexpr T   sum(std::initializer_list<T> data) noexcept
    {
        return sum(span(data));
    }
    
    template <typename T, typename Pred>
    constexpr auto   transform(std::span<const T> input, Pred pred) noexcept -> std::vector<decltype(pred(T()))> 
    {
        std::vector<decltype(pred(T()))>    ret;
        ret.reserve(input.size());
        for(const T& t : input)
            ret.push_back(pred(t));
        return ret;
    }

    template <typename T>
    square_t<T>  sum(square_k, std::span<const T> values)
    {
        static_assert(is_floating_point_v<T>, "Needs to be a floating point type");
        square_t<T>   ret{};
        for(const T& v : values)
            ret += v*v;
        return ret;
    }

    template <typename T>
    square_t<T>  sum(square_k, std::span<const T> values, T bias)
    {
        static_assert(is_floating_point_v<T>, "Needs to be a floating point type");
        square_t<T>   ret{};
        for(const T& v : values){
            T w = v - bias;
            ret += w*w;
        }
        return ret;
    }

    template <typename T>
    T       average(std::span<const T> values)
    {
        static_assert(is_floating_point_v<T>, "Needs to be a floating point type");
        if(values.empty())
            return T{};
        return sum(values) / ieee754_t<T>(values.size());
    }
}

