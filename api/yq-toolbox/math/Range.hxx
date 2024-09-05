////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the Range code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include "Range.hpp"

#include <yq-toolbox/math/Side.hpp>
#include <yq-toolbox/trait/has_one.hpp>

namespace yq {
    template <typename T>
    constexpr Side     _classify(T v, T lo, T hi) noexcept
    {
        auto lc = v <=> lo;
        auto hc = v <=> hi;
    
        static_assert(std::is_same_v<decltype(lc),decltype(hc)>);

        if constexpr ( std::is_same_v<decltype(lc), std::strong_ordering> ){
            switch(lc){
            case std::strong_ordering::less:
                switch(hc){
                case std::strong_ordering::less:
                    return Side::BELOW;
                case std::strong_ordering::equal:   
                    return Side::ERROR | Side::BELOW | Side::HIGH;
                case std::strong_ordering::greater: 
                    return Side::ERROR | Side::BELOW | Side::ABOVE;
                default:
                    return Side::ERROR;
                }
                break;
            case std::strong_ordering::equal:
                switch(hc){
                case std::strong_ordering::less:
                    return Side::LOW;
                case std::strong_ordering::equal:
                    return Side::LOW | Side::HIGH;
                case std::strong_ordering::greater:
                    return Side::ERROR | Side::LOW | Side::ABOVE;
                default:
                    return Side::ERROR;
                }
                break;
            case std::strong_ordering::greater:
                switch(hc){
                case std::strong_ordering::less:
                    return Side::MIDDLE;
                case std::strong_ordering::equal:
                    return Side::HIGH;
                case std::strong_ordering::greater:
                    return Side::ABOVE;
                default:
                    return Side::ERROR;
                }
                break;
            default:
                return Side::ERROR;
            }
        } else if constexpr ( std::is_same_v<decltype(lc), std::weak_ordering> ){
            switch(lc){
            case std::weak_ordering::less:
                switch(hc){
                case std::weak_ordering::less:
                    return Side::BELOW;
                case std::weak_ordering::equivalent:
                    return Side::ERROR | Side::BELOW | Side::HIGH;
                case std::weak_ordering::greater:
                    return Side::ERROR | Side::BELOW | Side::ABOVE;
                default:
                    return Side::ERROR;
                }
                break;
            case std::weak_ordering::equivalent:
                switch(hc){
                case std::weak_ordering::less:
                    return Side::LOW;
                case std::weak_ordering::equivalent:
                    return Side::LOW | Side::HIGH;
                case std::weak_ordering::greater:
                    return Side::ERROR | Side::LOW | Side::ABOVE;
                default:
                    return Side::ERROR;
                }
                break;
            case std::weak_ordering::greater:
                switch(hc){
                case std::weak_ordering::less:
                    return Side::MIDDLE;
                case std::weak_ordering::equivalent:
                    return Side::HIGH;
                case std::weak_ordering::greater:
                    return Side::ABOVE;
                default:
                    return Side::ERROR;
                }
                break;
            default:
                return Side::ERROR;
            }
        } else if constexpr ( std::is_same_v<decltype(lc), std::partial_ordering>){
            switch(lc){
            case std::partial_ordering::less:
                switch(hc){
                case std::partial_ordering::less:
                    return Side::BELOW;
                case std::partial_ordering::equivalent:
                    return Side::ERROR | Side::BELOW | Side::HIGH;
                case std::partial_ordering::greater:
                    return Side::ERROR | Side::BELOW | Side::ABOVE;
                case std::partial_ordering::unordered:
                    return Side::UNKNOWN | Side::BELOW;
                default:
                    return Side::ERROR;
                }
                break;
            case std::partial_ordering::equivalent:
                switch(hc){
                case std::partial_ordering::less:
                    return Side::LOW;
                case std::partial_ordering::equivalent:
                    return Side::LOW | Side::HIGH;
                case std::partial_ordering::greater:
                    return Side::ERROR | Side::LOW | Side::ABOVE;
                case std::partial_ordering::unordered:
                    return Side::UNKNOWN | Side::LOW;
                default:
                    return Side::ERROR;
                }
                break;
            case std::partial_ordering::greater:
                switch(hc){
                case std::partial_ordering::less:
                    return Side::MIDDLE;
                case std::partial_ordering::equivalent:
                    return Side::HIGH;
                case std::partial_ordering::greater:
                    return Side::ABOVE;
                case std::partial_ordering::unordered:
                    return Side::MIDDLE | Side::UNKNOWN;
                default:
                    return Side::ERROR;
                }
                break;
            case std::partial_ordering::unordered:
                switch(hc){
                case std::partial_ordering::less:
                    return Side::UNKNOWN | Side::MIDDLE;
                case std::partial_ordering::equivalent:
                    return Side::UNKNOWN | Side::HIGH;
                case std::partial_ordering::greater:
                    return Side::UNKNOWN | Side::ABOVE;
                case std::partial_ordering::unordered:
                    return Side::UNKNOWN | Side::MIDDLE | Side::UNKNOWN;
                default:
                    return Side::UNKNOWN | Side::ERROR;
                }
                break;
            default:
                return Side::ERROR;
            }
        }
        return Side::ERROR;
    }

    template <typename T>
    constexpr T         _gap(T v, T lo, T hi) noexcept
    {
        if(lo <= v)
            return v - lo;
        if(v <= hi)
            return hi - v;
        return zero_v<T>;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    constexpr Range<T>::Range(intersect_t, std::initializer_list<T> ls, std::initializer_list<T> hs) :
        Range(INTERSECT, std::span<const T>(ls.data(), ls.size()), std::span<const T>(hs.data(), hs.size())){}

    template <typename T>
    constexpr Range<T>::Range(intersect_t, std::span<const T>ls, std::span<const T> hs)
    {
       if(!ls.empty()){
            lo      = *std::max_element(ls.begin(), ls.end());
        } else {
            lo      = zero_v<T>;
        }
        
        if(!hs.empty()){
            hi.x    = *std::min_element(hs.begin(), hs.end());
        } else {
            hi      = zero_v<T>;
        }
     }

    template <typename T>
    constexpr Range<T>::Range(sort_t, T a, T b) noexcept 
    {
        std::tie(lo, hi)    = std::minmax(a, b);
    }
    
    template <typename T>
    constexpr Range<T>::Range(union_t, T a, T b) noexcept : Range(SORT, a, b) {}
    
    template <typename T>
    constexpr Range<T>::Range(union_t, std::initializer_list<T> vs) : 
        Range(UNION, std::span<const T>(vs.data(), vs.size())) {}

    template <typename T>
    constexpr Range<T>::Range(union_t, std::span<const T> data)
    {
        if(!data.empty()){
            auto [l, h] = std::minmax_element(data.begin(), data.end());
            lo = *l;
            hi = *h;
        } else {
            lo = hi = zero_v<T>;
        }
    }

    template <typename T>
    constexpr Range<T>::Range(union_t, std::initializer_list<T> ls, std::initializer_list<T> hs) :
        Range(UNION, std::span<const T>(ls.data(), ls.size()), std::span<const T>(hs.data(), hs.size())){}

    template <typename T>
    constexpr Range<T>::Range(union_t, std::span<const T>ls, std::span<const T> hs)
    {
        if(!ls.empty()){
            lo      = std::min_element(ls.begin(), ls.end());
        } else {
            lo      = zero_v<T>;
        }
        
        if(!hs.empty()){
            hi      = std::max_element(hs.begin(), hs.end());
        } else {
            hi      = zero_v<T>;
        }
    }
    
    template <typename T>
    constexpr Range<T>  Range<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    constexpr Range<T>  Range<T>::operator-() const noexcept
    {
        return Range(-hi, -lo );
    }

    template <typename T>
    constexpr Range<T>  Range<T>::operator+(T b) const noexcept
    {
        return Range( lo+b, hi+b );
    }

    template <typename T>
    Range<T>& Range<T>::operator+=(T b) noexcept
    {
        lo += b;
        hi += b;
        return *this;
    }

    template <typename T>
    constexpr Range<T>  Range<T>::operator+(const Range<T>& b) const noexcept
    {
        return Range(lo+b.lo, hi+b.hi);
    }

    template <typename T>
    Range<T>& Range<T>::operator+=(const Range<T>& b) noexcept
    {
        lo += b.lo;
        hi += b.hi;
        return *this;
    }
    
    template <typename T>
    constexpr Range<T>  Range<T>::operator-(T b) const noexcept
    {
        return Range( lo-b, hi-b );
    }

    template <typename T>
    Range<T>& Range<T>::operator-=(T b) noexcept
    {
        lo -= b;
        hi -= b;
        return *this;
    }

    template <typename T>
    constexpr Range<T>  Range<T>::operator-(const Range<T>& b) const noexcept
    {
        return Range( lo-b.hi, hi-b.lo);
    }

    template <typename T>
    Range<T>& Range<T>::operator-=(const Range<T>& b) noexcept
    {
        *this = *this - b;      // gotta be this way in case somebody does range -= range;
        return *this;
    }


    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Range<product_t<T,U>>    Range<T>::operator*(U b) const noexcept
    {
        if(b >= zero_v<U>)
            return Range<product_t<T,U>>(lo*b, hi*b);
        else
            return Range<product_t<T,U>>(hi*b, lo*b);
    }
    
    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>) 
    Range<T>&    Range<T>::operator*=(U b) noexcept
    {
        *this   = *this * b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Range<product_t<T,U>>   Range<T>::operator*(const Range<U>&b) const noexcept
    {
        return Range<product_t<T,U>>(UNION, {lo*b.lo, lo*b.hi, hi*b.lo, hi*b.hi });
    }

    template <typename T>
        template <typename U>
    requires self_multiply_v<T,U>
    Range<T>&    Range<T>::operator*=(const Range<U>& b) noexcept
    {
        *this  = *this * b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    constexpr Range<quotient_t<T,U>>    Range<T>::operator/(U b) const noexcept
    {
        if(b >= zero_v<U>)
            return Range<quotient_t<T,U>>( lo/b, hi/b);
        else
            return Range<quotient_t<T,U>>( hi/b, lo/b);
    }
    
    template <typename T>
        template <typename U>
    requires (std::is_arithmetic_v<U> && self_divide_v<T,U>) 
    Range<T>&    Range<T>::operator/=(U b) noexcept
    {
        *this   = *this / b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Range<quotient_t<T,U>>   Range<T>::operator/(const Range<U>&b) const noexcept
    {
        return Range<quotient_t<T,U>>(UNION, {lo/b.lo, lo/b.hi, hi/b.lo, hi/b.hi });
    }

    template <typename T>
        template <typename U>
    requires self_divide_v<T,U>
    Range<T>&    Range<T>::operator/=(const Range<U>& b) noexcept
    {
        *this   = *this / b;
        return *this;
    }
    

    template <typename T>
    constexpr Range<T>    Range<T>::operator|(T b) const noexcept
    {
        return Range<T>(std::min(lo, b), std::max(hi, b));
    }

    template <typename T>
    Range<T>&   Range<T>::operator|=(T b) noexcept
    {
        *this = *this | b;
        return *this;
    }
    
    template <typename T>
    constexpr Range<T>  Range<T>::operator|(const Range<T>& b) const noexcept
    {
        return Range<T>(std::min(lo, b.lo), std::max(hi, b.hi));
    }

    template <typename T>
    Range<T>&   Range<T>::operator|=(const Range<T>& b) noexcept
    {
        *this = *this | b;
        return *this;
    }

    template <typename T>
    constexpr Range<T>  Range<T>::operator&(const Range<T>& b) const noexcept
    {
        return Range<T>(std::max(lo, b.lo), std::min(hi, b.hi));
    }

    template <typename T>
    Range<T>&   Range<T>::operator&=(const Range<T>& b) noexcept
    {
        *this = *this & b;
        return *this;
    }
    
    template <typename T>
    constexpr Range<T>  Range<T>::center() const noexcept
    {
        if constexpr (is_floating_point_v<T>)
            return ieee754_t<T>(0.5)*(lo+hi);
        if constexpr (is_integer_v<T>)
            return (lo+hi) / integer_t<T>(2);
        return {};
    }

    template <typename T>
    constexpr Side   Range<T>::classify(T v) const noexcept
    {   
        return _classify(v, lo, hi);
    }

    template <typename T>
    constexpr bool    Range<T>::eclipses(T b) const noexcept
    {
        return (lo <= b) && (b <= hi);
    }

    template <typename T>
    constexpr bool    Range<T>::eclipses(const Range& b) const noexcept
    {
        return (lo <= b.lo) && (b.hi <= hi);
    }
    
    template <typename T>
    constexpr Range<T>     Range<T>::inflate(T v) const noexcept
    {
        return Range(lo-v, hi+v);
    }

    template <typename T>
    constexpr Range<T>     Range<T>::fixed() const noexcept
    {
        return Range(SORT, lo, hi);
    }


    template <typename T>
    constexpr bool    Range<T>::is_valid() const noexcept
    {
        return lo <= hi;
    }

    template <typename T>
        template <typename>
    requires is_floating_point_v<T>
    constexpr T   Range<T>::project(T v) const noexcept
    {
        return (one_v<T>-v)*lo + v*hi;
    }

    template <typename T>
    constexpr T     Range<T>::span() const noexcept
    {
        return hi - lo;
    }

    template <typename T>
        template <typename>
    requires is_floating_point_v<T>
    constexpr T   Range<T>::unproject(T v) const noexcept
    {
        return (v-lo)/(hi-lo);
    }

    template <typename T>
    constexpr bool    Range<T>::valid() const noexcept
    {
        return lo <= hi;
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    constexpr Range<T>  operator+(T a, const Range<T>& b) noexcept
    {
        return Range<T>(a+b.lo, a+b.hi);
    }

    template <typename T>
    constexpr Range<T>  operator-(T a, const Range<T>& b) noexcept
    {
        return Range<T>( a - b.hi, a - b.lo );
    }

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Range<product_t<T,U>>    operator*(T a, const Range<U>& b) noexcept
    {
        if(a >= zero_v<T>)
            return Range<product_t<T,U>>(a*b.lo, a*b.hi);
        else
            return Range<product_t<T,U>>(a*b.hi, a*b.lo);
    }

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Range<product_t<T,U>>    operator/(T a, const Range<U>& b) noexcept
    {
        if(a >= zero_v<T>)
            return range(a/b.hi, a/b.lo);
        else
            return range(a/b.lo, a/b.hi);
    }

    template <typename T>
    constexpr Range<T>    operator|(T a, const Range<T>& b) noexcept
    {
        return Range<T>(std::min(a, b.lo), std::max(a, b.hi));
    }

    template <typename T>
    constexpr Range<T>    center(const Range<T>& a) noexcept
    {
        return a.center();
    }

    template <typename T>
    constexpr T           span(const Range<T>& a) noexcept
    {
        return a.span();
    }
}
