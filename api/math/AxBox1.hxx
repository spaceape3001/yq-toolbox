////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the axbox1 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/AxBox1.hpp>
#include <math/utility.hpp>
#include <math/errors.hpp>

namespace yq {
    template <typename T>
    constexpr AxBox1<T>::AxBox1(intersect_t, std::initializer_list<Vector1<T>> ls, std::initializer_list<Vector1<T>> hs) noexcept:
        AxBox1(INTERSECT, span(ls), span(hs)) {}

    template <typename T>
    constexpr AxBox1<T>::AxBox1(intersect_t, std::span<const Vector1<T>>ls, std::span<const Vector1<T>>hs) noexcept
    {
        if(!ls.empty()){
            lo.x    = std::max_element(ls.begin(), ls.end(), Vector1<T>::less_x) -> x;
        } else {
            lo      = Vector1<T>(ZERO);
        }
        
        if(!hs.empty()){
            hi.x    = std::min_element(hs.begin(), hs.end(), Vector1<T>::less_x) -> x;
        } else {
            hi      = Vector1<T>(ZERO);
        }
    }

    template <typename T>
    constexpr AxBox1<T>::AxBox1(sort_t, const Vector1<T>&a, const Vector1<T>& b) noexcept
    {
        std::tie(lo.x, hi.x)    = std::minmax(a.x, b.x);
    }

    template <typename T>
    constexpr AxBox1<T>::AxBox1(union_t, const Vector1<T>&a, const Vector1<T>& b) noexcept : AxBox1(SORT, a, b) {}

    template <typename T>
    constexpr AxBox1<T>::AxBox1(union_t, std::initializer_list<Vector1<T>> list) noexcept : 
        AxBox1(UNION, span(list)){}

    template <typename T>
    constexpr AxBox1<T>::AxBox1(union_t, std::span<const Vector1<T>> data) noexcept
    {
        if(!data.empty()){
            auto [lx, hx] = std::minmax_element(data.begin(), data.end(), Vector1<T>::less_x);
            lo.x = lx->x;
            hi.x = hx->x;
        } else {
            lo = hi = Vector1<T>(ZERO);
        }
    }

    template <typename T>
    constexpr AxBox1<T>::AxBox1(union_t, std::initializer_list<Vector1<T>> ls, std::initializer_list<Vector1<T>> hs) noexcept :
        AxBox1(UNION, span(ls), span(hs)) {}

    template <typename T>
    constexpr AxBox1<T>::AxBox1(union_t, std::span<const Vector1<T>>ls, std::span<const Vector1<T>>hs) noexcept
    {
        if(!ls.empty()){
            lo.x    = std::min_element(ls.begin(), ls.end(), Vector1<T>::less_x) -> x;
        } else {
            lo      = Vector1<T>(ZERO);
        }
        
        if(!hs.empty()){
            hi.x    = std::max_element(hs.begin(), hs.end(), Vector1<T>::less_x) -> x;
        } else {
            hi      = Vector1<T>(ZERO);
        }
    }

    #ifdef YQ_MATH_SEGMENT1_HPP
    template <typename T>
    constexpr AxBox1<T>::AxBox1(const Segment1<T>&seg) noexcept : AxBox1<T>(seg.bounds()) {}
    #endif

    template <typename T>
    AxBox1<T>  AxBox1<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    AxBox1<T>  AxBox1<T>::operator-() const noexcept
    {
        return AxBox1<T>(-hi, -lo);
    }

    template <typename T>
    AxBox1<T>  AxBox1<T>::operator+(const Vector1<T>&b) const noexcept
    {
        return AxBox1<T>(lo+b, hi+b);
    }

    template <typename T>
    AxBox1<T>& AxBox1<T>::operator+=(const Vector1<T>&b) noexcept
    {
        lo += b;
        hi += b;
        return *this;
    }

    template <typename T>
    AxBox1<T>  AxBox1<T>::operator-(const Vector1<T>&b) const noexcept
    {
        return AxBox1<T>(lo-b, hi-b);
    }

    template <typename T>
    AxBox1<T>& AxBox1<T>::operator-=(const Vector1<T>&b) noexcept
    {
        lo -= b;
        hi -= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    AxBox1<product_t<T,U>> AxBox1<T>::operator*(U b) const noexcept
    {
        if(b >= zero_v<U>)
            return AxBox1<product_t<T,U>>(lo*b,hi*b);
        else
            return AxBox1<product_t<T,U>>(hi*b,lo*b);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    AxBox1<T>& AxBox1<T>::operator*=(U b) noexcept
    {
        *this = *this * b;
        return *this;
    }
        
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    AxBox1<quotient_t<T,U>> AxBox1<T>::operator/(U b) const noexcept
    {
        if(b >= zero_v<U>)
            return AxBox1<quotient_t<T,U>>(lo/b,hi/b);
        else
            return AxBox1<quotient_t<T,U>>(hi/b,lo/b);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    AxBox1<T>& AxBox1<T>::operator/=(U b) noexcept
    {
        *this = *this / b;
        return *this;
    }
        

    template <typename T>
    constexpr AxBox1<T> AxBox1<T>::operator|(const AxBox1<T>&b) const noexcept
    {
        return AxBox1(UNION, {lo, hi, b.lo, b.hi});
    }

    template <typename T>
    constexpr AxBox1<T> AxBox1<T>::operator|(const Vector1<T>&b) const noexcept
    {
        return AxBox1(UNION, {lo, hi, b});
    }

    template <typename T>
    AxBox1<T>& AxBox1<T>::operator|=(const AxBox1& b) noexcept
    {
        *this   = *this | b;
        return *this;
    }

    template <typename T>
    AxBox1<T>& AxBox1<T>::operator|=(const Vector1<T>& b) noexcept
    {
        *this   = *this | b;
        return *this;
    }

    template <typename T>
    constexpr AxBox1<T> AxBox1<T>::operator&(const AxBox1<T>&b) const noexcept
    {
        return AxBox1(INTERSECT, {lo, b.lo}, {hi, b.hi});
    }

    template <typename T>
    AxBox1<T>& AxBox1<T>::operator&=(const AxBox1& b) noexcept
    {
        *this = *this & b;
        return *this;
    }

    template <typename T>
    constexpr Vector1<T> AxBox1<T>::center() const noexcept
    {
        if constexpr (is_floating_point_v<T>)
            return ieee754_t<T>(0.5)*(lo+hi);
        if constexpr (std::is_integral_v<T>)
            return (lo+hi) / T(2);
        return {};
    }

    #if defined(YQ_MATH_DATA1_HPP) && defined(YQ_MATH_SIDE_HPP)
    template <typename T>
    constexpr Data1<Side>       AxBox1<T>::classify(const Vector1<T>&v) const noexcept
    {
        return Data1<Side>( classify_x(v.x), classify_y(v.y), classify_z(v.z), classify_w(v.w) );
    }
    #endif
    
    
    #ifdef YQ_MATH_SIDE_HPP
    template <typename T>
    constexpr Side              AxBox1<T>::classify_x(T v) const noexcept
    {
        return _classify(v, lo.x, hi.x);
    }
    #endif

    #ifdef YQ_MATH_SIDE_HPP
    template <typename T>
    constexpr Side              AxBox1<T>::classify_x(const Vector1<T>&v) const noexcept
    {
        return classify_x(v.x);
    }
    #endif

    template <typename T>
    constexpr bool AxBox1<T>::contains(const Vector1<T>& pt) const noexcept
    {
        return (all(lo) <= pt) && (all(pt) <= hi);
    }

    #ifdef YQ_MATH_AXCORNERS1_HPP
    template <typename T>
    constexpr AxCorners1<Vector1<T>>  AxBox1<T>::corners() const noexcept
    {
        return AxCorners1<Vector1<T>>( 
            l(),
            h()
        );
    }
    #endif

    #ifdef YQ_MATH_AXCORNERS1_HPP
    template <typename T>
    constexpr AxCorners1<Vector1<T>>    AxBox1<T>::corners(T adjust) const noexcept
    {
        return inflate(adjust).corners();
    }
    #endif

    template <typename T>
    T                       AxBox1<T>::distance(const Vector1<T>&v) const
    {
        if constexpr ( has_abs_v<T> )
            return abs(_gap(v.x, lo.x, hi.x));
        if constexpr ( has_sqrt_v<T> )
            return sqrt(distance²(v));
        return zero_v<T>;
    }
    
    template <typename T>
    constexpr square_t<T>   AxBox1<T>::distance²(const Vector1<T>&v) const noexcept
    {
        return 
            (_gap(v.x, lo.x, hi.x)^²)
        ;
    }

    template <typename T>
    constexpr bool AxBox1<T>::eclipses(const AxBox1<T>& b) const noexcept
    {
        return (all(lo) <= b.lo) && (all(b.hi) <= hi);
    }

    template <typename T>
    constexpr AxBox1<T> AxBox1<T>::fixed() const noexcept
    {
        return AxBox1(UNION, lo, hi);
    }

    template <typename T>
    template <typename>
    requires is_floating_point_v<T>
    Expect<unity_t<T>> AxBox1<T>::fraction_x(T x) const noexcept
    {
        if(hi.x == lo.x)
            return errors::degenerate_dimension();
        return (x-lo.x) / (hi.x-lo.x);
    }

    template <typename T>
    template <typename>
    requires is_floating_point_v<T>
    Expect<unity_t<T>> AxBox1<T>::fraction_x(T x, T ep) const noexcept
    {
        if(hi.x - lo.x < ep){
            if(hi.x < lo.x)
                return errors::invalid_box();
            return errors::degenerate_dimension();
        }
        return (x-lo.x) / (hi.x-lo.x) ;
    }
    
    template <typename T>
    constexpr Vector1<T>   AxBox1<T>::h() const noexcept
    {
        return hi;
    }

    template <typename T>
    constexpr Vector1<T>    AxBox1<T>::h(T adjust) const noexcept
    {
        return Vector1<T>(hi.x+adjust);
    }

    template <typename T>
    constexpr AxBox1<T>    AxBox1<T>::inflate(T d) const noexcept
    {
        return AxBox1(all(lo) - d, all(hi) + d);
    }

    template <typename T>
    constexpr AxBox1<T>    AxBox1<T>::inflate(guard_t, T d) const noexcept
    {
        AxBox1  bx  = fixed();
        return bx.inflate(std::max(d, bx.min_inflate()));
    }

    template <typename T>
    constexpr bool    AxBox1<T>::is_valid() const noexcept
    {
        return all(lo) <= hi;
    }

    template <typename T>
    constexpr Vector1<T>   AxBox1<T>::l() const noexcept
    {
        return lo;
    }

    template <typename T>
    constexpr Vector1<T>    AxBox1<T>::l(T adjust) const noexcept
    {
        return Vector1<T>(lo.x-adjust);
    }

    template <typename T>
    constexpr T AxBox1<T>::length() const noexcept
    {
        return hi.x - lo.x;
    }

    template <typename T>
    constexpr T AxBox1<T>::min_inflate() const noexcept
    {
        return -midspan(span().cmin());
    }

    template <typename T>
    constexpr bool AxBox1<T>::overlaps(const AxBox1<T>& b) const noexcept
    {
        return (all(lo) <= b.hi) && (all(b.lo) <= hi);
    }

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    constexpr Vector1<T>   AxBox1<T>::project(const Vector1<T>& v) const noexcept
    {
        return (one_v<Vector1<T>>-v).emul(lo) + v.emul(hi);
    }
    
    #ifdef YQ_MATH_SIZE1_HPP
    template <typename T>
    constexpr Size1<T> AxBox1<T>::size() const noexcept 
    {
        auto s = span();
        return Size1<T>{ s.x }; 
    }
    #endif

    template <typename T>
    constexpr Vector1<T>    AxBox1<T>::span() const noexcept
    {
        return hi - lo;
    }

    template <typename T>
    constexpr Vector1<T>    AxBox1<T>::span(guard_t) const noexcept
    {
        return span().eabs();
    }

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    constexpr Vector1<T>   AxBox1<T>::unproject(const Vector1<T>& v) const noexcept
    {
        return div_elem(v-lo, hi-lo);
    }

    template <typename T>
    constexpr bool          AxBox1<T>::valid() const noexcept 
    {
        return all(lo) <= hi;
    }

    #ifdef YQ_MATH_RANGE_HPP
    template <typename T>
    constexpr Range<T>  AxBox1<T>::x_range() const noexcept
    {
        return range(lo.x, hi.x);
    }
    #endif
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr AxBox1<product_t<T,U>> operator*(T a, const AxBox1<U>& b) noexcept
    {
        if(a >= zero_v<T>)
            return AxBox1<product_t<T,U>>(a*b.lo, a*b.hi);
        else
            return AxBox1<product_t<T,U>>(a*b.hi, a*b.lo);
    }

    template <typename T>
    constexpr AxBox1<T> aabb(const Vector1<T>& a) noexcept
    {
        return AxBox1<T>(a);
    }

    template <typename T>
    constexpr AxBox1<T> aabb(const Vector1<T>& a, const Vector1<T>& b) noexcept
    {
        return AxBox1<T>(UNION, a, b);
    }

    template <typename T>
    AxBox1<T> aabb(const std::vector<Vector1<T>>& vals)
    {
        switch(vals.size()){
        case 0:
            return AxBox1<T>(ZERO);
        case 1:
            return AxBox1<T>(vals[0]);
        case 2:
            return AxBox1<T>(UNION, vals[0],vals[1]);
        default:
            break;
        }

        return AxBox1<T>(vals);
    }

    template <typename T>
    constexpr Vector1<T> center(const AxBox1<T>& box)  noexcept
    {
        return box.center();
    }

    template <typename T>
    Vector1<T>  centroid(const AxBox1<T>& box)
    {
        return box.center();
    }

    template <typename T>
    constexpr bool    is_valid(const AxBox1<T>& box) noexcept
    {
        return box.is_valid();
    }

    template <typename T>
    constexpr T         length(const AxBox1<T>&box) noexcept
    {
        return box.length();
    }

    template <typename T>
    constexpr Vector1<T>    span(const AxBox1<T>&box) noexcept
    {
        return box.span();
    }

    template <typename S, typename T>
    S&  as_stream(S& s, const AxBox1<T>& v)
    {
        return s << "[(" << v.lo.x << ":" << v.hi.x << ")]";
    }
    
    #ifdef YQ_BASIC_STREAM_HPP_
    template <typename T>
    Stream& operator<<(Stream&s, const AxBox1<T>& v)
    {
        return as_stream(s, v);
    }
    #endif

    #ifdef _LOG4CPP_CATEGORYSTREAM_HH
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const AxBox1<T>& v)
    {
        return as_stream(s, v);
    }
    #endif
}
