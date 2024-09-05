////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the axbox2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <yq-toolbox/errors.hpp>
#include <yq-toolbox/shape/AxBox2.hpp>
#include <yq-toolbox/math/utility.hpp>
#include <yq-toolbox/math/Range.hpp>
#include <yq-toolbox/container/initlist_utils.hpp>

namespace yq {
    template <typename T>
    constexpr AxBox2<T>::AxBox2(intersect_t, std::initializer_list<Vector2<T>> ls, std::initializer_list<Vector2<T>> hs) noexcept:
        AxBox2(INTERSECT, yq::span(ls), yq::span(hs)) {}

    template <typename T>
    constexpr AxBox2<T>::AxBox2(intersect_t, std::span<const Vector2<T>>ls, std::span<const Vector2<T>>hs) noexcept
    {
        if(!ls.empty()){
            lo.x    = std::max_element(ls.begin(), ls.end(), Vector2<T>::less_x) -> x;
            lo.y    = std::max_element(ls.begin(), ls.end(), Vector2<T>::less_y) -> y;
        } else {
            lo      = Vector2<T>(ZERO);
        }
        
        if(!hs.empty()){
            hi.x    = std::min_element(hs.begin(), hs.end(), Vector2<T>::less_x) -> x;
            hi.y    = std::min_element(hs.begin(), hs.end(), Vector2<T>::less_y) -> y;
        } else {
            hi      = Vector2<T>(ZERO);
        }
    }

    template <typename T>
    constexpr AxBox2<T>::AxBox2(sort_t, const Vector2<T>&a, const Vector2<T>& b) noexcept
    {
        std::tie(lo.x, hi.x)    = std::minmax(a.x, b.x);
        std::tie(lo.y, hi.y)    = std::minmax(a.y, b.y);
    }

    template <typename T>
    constexpr AxBox2<T>::AxBox2(union_t, const Vector2<T>&a, const Vector2<T>& b) noexcept : AxBox2(SORT, a, b) {}

    template <typename T>
    constexpr AxBox2<T>::AxBox2(union_t, std::initializer_list<Vector2<T>> list) noexcept :  AxBox2(UNION, yq::span(list)){}

    template <typename T>
    constexpr AxBox2<T>::AxBox2(union_t, std::span<const Vector2<T>> data) noexcept
    {
        if(!data.empty()){
            auto [lx, hx] = std::minmax_element(data.begin(), data.end(), Vector2<T>::less_x);
            lo.x = lx->x;
            hi.x = hx->x;

            auto [ly, hy] = std::minmax_element(data.begin(), data.end(), Vector2<T>::less_y);
            lo.y = ly->y;
            hi.y = hy->y;
        } else {
            lo = hi  = Vector2<T>(ZERO);
        }
    }

    template <typename T>
    constexpr AxBox2<T>::AxBox2(union_t, std::initializer_list<Vector2<T>> ls, std::initializer_list<Vector2<T>> hs) noexcept :
        AxBox2(UNION, yq::span(ls), yq::span(hs)) {}

    template <typename T>
    constexpr AxBox2<T>::AxBox2(union_t, std::span<const Vector2<T>>ls, std::span<const Vector2<T>>hs) noexcept
    {
        if(!ls.empty()){
            lo.x    = std::min_element(ls.begin(), ls.end(), Vector2<T>::less_x) -> x;
            lo.y    = std::min_element(ls.begin(), ls.end(), Vector2<T>::less_y) -> y;
        } else {
            lo      = Vector2<T>(ZERO);
        }
        
        if(!hs.empty()){
            hi.x    = std::max_element(hs.begin(), hs.end(), Vector2<T>::less_x) -> x;
            hi.y    = std::max_element(hs.begin(), hs.end(), Vector2<T>::less_y) -> y;
        } else {
            hi      = Vector2<T>(ZERO);
        }
    }

    #ifdef YQ_MATH_CIRCLE2_HPP
    template <typename T>
    constexpr AxBox2<T>::AxBox2(const Circle2<T>& cir) noexcept : AxBox2(cir.bounds())
    {
    }
    #endif

    #ifdef YQ_MATH_POLYGON2_HPP
    template <typename T>
    constexpr AxBox2<T>::AxBox2(const Polygon2<T>&p) noexcept : AxBox2(p.bounds()) {}
    #endif

    #ifdef YQ_MATH_POLYLINE2_HPP
    template <typename T>
    constexpr AxBox2<T>::AxBox2(const Polyline2<T>&p) noexcept : AxBox2(p.bounds()) {}
    #endif
    
    #ifdef YQ_MATH_SEGMENT2_HPP
    template <typename T>
    constexpr AxBox2<T>::AxBox2(const Segment2<T>&seg) noexcept : AxBox2<T>(seg.bounds()) {}
    #endif

    #ifdef YQ_MATH_TRIANGLE2_HPP
    template <typename T>
    constexpr AxBox2<T>::AxBox2(const Triangle2<T>&tri) noexcept : AxBox2<T>(tri.bounds()) {}
    #endif

    template <typename T>
    AxBox2<T>  AxBox2<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    AxBox2<T>  AxBox2<T>::operator-() const noexcept
    {
        return AxBox2<T>(-hi, -lo);
    }

    template <typename T>
    AxBox2<T>  AxBox2<T>::operator+(const Vector2<T>&b) const noexcept
    {
        return AxBox2<T>(lo+b, hi+b);
    }

    template <typename T>
    AxBox2<T>& AxBox2<T>::operator+=(const Vector2<T>&b) noexcept
    {
        lo += b;
        hi += b;
        return *this;
    }

    template <typename T>
    AxBox2<T>  AxBox2<T>::operator-(const Vector2<T>&b) const noexcept
    {
        return AxBox2<T>(lo-b, hi-b);
    }

    template <typename T>
    AxBox2<T>& AxBox2<T>::operator-=(const Vector2<T>&b) noexcept
    {
        lo -= b;
        hi -= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    AxBox2<product_t<T,U>> AxBox2<T>::operator*(U b) const noexcept
    {
        if(b >= zero_v<U>)
            return AxBox2<product_t<T,U>>(lo*b,hi*b);
        else
            return AxBox2<product_t<T,U>>(hi*b,lo*b);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
    AxBox2<T>& AxBox2<T>::operator*=(U b) noexcept
    {
        *this = *this * b;
        return *this;
    }
        
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    AxBox2<quotient_t<T,U>> AxBox2<T>::operator/(U b) const noexcept
    {
        if(b >= zero_v<U>)
            return AxBox2<quotient_t<T,U>>(lo/b,hi/b);
        else
            return AxBox2<quotient_t<T,U>>(hi/b,lo/b);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_divide_v<T,U>)
    AxBox2<T>& AxBox2<T>::operator/=(U b) noexcept
    {
        *this = *this / b;
        return *this;
    }
        

    template <typename T>
    constexpr AxBox2<T> AxBox2<T>::operator|(const AxBox2<T>&b) const noexcept
    {
        return AxBox2(UNION, {lo, hi, b.lo, b.hi});
    }

    template <typename T>
    constexpr AxBox2<T> AxBox2<T>::operator|(const Vector2<T>&b) const noexcept
    {
        return AxBox2(UNION, {lo, hi, b});
    }

    template <typename T>
    AxBox2<T>& AxBox2<T>::operator|=(const AxBox2& b) noexcept
    {
        *this   = *this | b;
        return *this;
    }

    template <typename T>
    AxBox2<T>& AxBox2<T>::operator|=(const Vector2<T>& b) noexcept
    {
        *this   = *this | b;
        return *this;
    }

    template <typename T>
    constexpr AxBox2<T> AxBox2<T>::operator&(const AxBox2<T>&b) const noexcept
    {
        return AxBox2(INTERSECT, {lo, b.lo}, {hi, b.hi});
    }

    template <typename T>
    AxBox2<T>& AxBox2<T>::operator&=(const AxBox2& b) noexcept
    {
        *this = *this & b;
        return *this;
    }

    template <typename T>
    constexpr square_t<T> AxBox2<T>::area() const noexcept
    {
        return span().cproduct();
    }

    template <typename T>
    constexpr square_t<T> AxBox2<T>::area(guard_t) const noexcept
    {
        return abs(area());
    }

    template <typename T>
    constexpr Vector2<T>  AxBox2<T>::center() const noexcept
    {
        if constexpr (is_floating_point_v<T>)
            return ieee754_t<T>(0.5)*(lo+hi);
        if constexpr (std::is_integral_v<T>)
            return (lo+hi) / T(2);
        return {};
    }

    #ifdef YQ_MATH_CIRCLE2_HPP
    template <typename T>
    Circle2<T>          AxBox2<T>::circumcircle() const
    {
        return Circle2<T>( center(), half_v<T>*span().length() );
    }
    #endif
    
    #if defined(YQ_MATH_DATA2_HPP) && defined(YQ_MATH_SIDE_HPP)
    template <typename T>
    constexpr Data2<Side>       AxBox2<T>::classify(const Vector2<T>&v) const noexcept
    {
        return Data2<Side>( classify_x(v.x), classify_y(v.y), classify_z(v.z), classify_w(v.w) );
    }
    #endif

    #ifdef YQ_MATH_SIDE_HPP
    template <typename T>
    constexpr Side              AxBox2<T>::classify_x(T v) const noexcept
    {
        return _classify(v, lo.x, hi.x);
    }

    template <typename T>
    constexpr Side              AxBox2<T>::classify_x(const Vector2<T>&v) const noexcept
    {
        return classify_x(v.x);
    }

    template <typename T>
    constexpr Side              AxBox2<T>::classify_y(T v) const noexcept
    {
        return _classify(v, lo.y, hi.y);
    }

    template <typename T>
    constexpr Side              AxBox2<T>::classify_y(const Vector2<T>&v) const noexcept
    {
        return classify_y(v.y);
    }
    #endif

    template <typename T>
    constexpr bool          AxBox2<T>::contains(const Vector2<T>& pt) const noexcept
    {
        return (all(lo) <= pt) && (all(pt) <= hi);
    }

    #ifdef YQ_MATH_AXCORNERS2_HPP
    template <typename T>
    constexpr AxCorners2<Vector2<T>>    AxBox2<T>::corners() const noexcept 
    {
        return AxCorners2<Vector2<T>>(
            ll(),
            lh(),
            hl(),
            hh()
        );
    }
    #endif

    #ifdef YQ_MATH_AXCORNERS2_HPP
    template <typename T>
    constexpr AxCorners2<Vector2<T>>    AxBox2<T>::corners(T adjust) const noexcept
    {
        return inflate(adjust).corners();
    }
    #endif

    template <typename T>
    T                       AxBox2<T>::distance(const Vector2<T>&v) const
    {
        if constexpr ( has_sqrt_v<T> )
            return sqrt(distance²(v));
        return zero_v<T>;
    }
    
    template <typename T>
    constexpr square_t<T>   AxBox2<T>::distance²(const Vector2<T>&v) const noexcept
    {
        return 
            (_gap(v.x, lo.x, hi.x)^²) +
            (_gap(v.y, lo.y, hi.y)^²)
        ;
    }

    template <typename T>
    constexpr bool          AxBox2<T>::eclipses(const AxBox2<T>& b) const noexcept
    {
        return (all(lo) <= b.lo) && (all(b.hi) <= hi);
    }

    template <typename T>
    constexpr bool        AxBox2<T>::eclipses(const Circle2<T>& b) const noexcept
    {
        return eclipses(b.bounds());
    }

    template <typename T>
    constexpr AxBox2<T> AxBox2<T>::fixed() const noexcept
    {
        return AxBox2(UNION, lo, hi);
    }

    template <typename T>
    template <typename>
    requires is_floating_point_v<T>
    Expect<unity_t<T>> AxBox2<T>::fraction_x(T x) const noexcept
    {
        if(hi.x == lo.x)
            return errors::degenerate_dimension();
        return (x-lo.x) / (hi.x-lo.x);
    }

    template <typename T>
    template <typename>
    requires is_floating_point_v<T>
    Expect<unity_t<T>> AxBox2<T>::fraction_x(T x, T ep) const noexcept
    {
        if(hi.x - lo.x < ep){
            if(hi.x < lo.x)
                return errors::invalid_box();
            return errors::degenerate_dimension();
        }
        return (x-lo.x) / (hi.x-lo.x);
    }

    template <typename T>
    template <typename>
    requires is_floating_point_v<T>
    Expect<unity_t<T>> AxBox2<T>::fraction_y(T y) const noexcept
    {
        if(hi.y == lo.y)
            return errors::degenerate_dimension();
        return (y-lo.y) / (hi.y-lo.y);
    }

    template <typename T>
    template <typename>
    requires is_floating_point_v<T>
    Expect<unity_t<T>> AxBox2<T>::fraction_y(T y, T ep) const noexcept
    {
        if(hi.y - lo.y < ep){
            if(hi.y < lo.y)
                return errors::invalid_box();
            return errors::degenerate_dimension();
        }
        return (y-lo.y) / (hi.y-lo.y);
    }

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::hh() const noexcept
    {
        return hi;
    }

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::hh(T adjust) const noexcept
    {
        return Vector2<T>(hi.x+adjust, hi.adjust);
    }
    
    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::hh(guard_t) const noexcept
    {
        return hi.emax(lo);
    }

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::hl() const noexcept
    {
        return Vector2<T>(hi.x, lo.y);
    }
    

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::hl(T adjust) const noexcept
    {
        return Vector2<T>(hi.x+adjust, lo.y-adjust);
    }

    #ifdef YQ_MATH_CIRCLE2_HPP
    template <typename T>
    constexpr Circle2<T>  AxBox2<T>::incircle() const noexcept
    {
        return Circle2<T>(center(), middivide(span().cmin()));
    }
    #endif

    template <typename T>
    constexpr AxBox2<T>    AxBox2<T>::inflate(T d) const noexcept
    {
        return AxBox2(all(lo) - d, all(hi) + d);
    }

    template <typename T>
    constexpr AxBox2<T>    AxBox2<T>::inflate(guard_t, T d) const noexcept
    {
        AxBox2  bx  = fixed();
        return bx.inflate(std::max(d, bx.min_inflate()));
    }

    template <typename T>
    constexpr bool          AxBox2<T>::is_valid() const noexcept 
    {
        return all(lo) <= hi;
    }

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::lh() const noexcept
    {
        return Vector2<T>(lo.x, hi.y);
    }

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::lh(T adjust) const noexcept
    {
        return Vector2<T>(lo.x-adjust, hi.y+adjust);
    }
    

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::ll() const noexcept
    {
        return lo;
    }
    

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::ll(T adjust) const noexcept
    {
        return Vector2<T>(lo.x-adjust, lo.y-adjust);
    }
        
    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::ll(guard_t) const noexcept
    {
        return lo.emin(hi);
    }

    template <typename T>
    constexpr T AxBox2<T>::min_inflate() const noexcept
    {
        return -midspan(span().cmin());
    }

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::northeast() const noexcept 
    { 
        return hh(); 
    }

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::northwest() const noexcept 
    { 
        return lh(); 
    }
    
    template <typename T>
    constexpr bool          AxBox2<T>::overlaps(const AxBox2<T>& b) const noexcept
    {
        return (all(lo) <= b.hi) && (all(b.lo) <= hi);
    }    

    template <typename T>
    constexpr T             AxBox2<T>::perimeter() const noexcept
    {
        return T(2) * (hi-lo).csum();
    }

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    constexpr Vector2<T>    AxBox2<T>::project(const Vector2<T>& v) const noexcept
    {
        return (Vector2<T>(ONE)-v).emul(lo) + v.emul(hi);
    }

    #ifdef YQ_MATH_SIZE2_HPP
    template <typename T>
    constexpr Size2<T> AxBox2<T>::size() const noexcept 
    {
        return Size2<T>(span());
    }

    template <typename T>
    constexpr Size2<T> AxBox2<T>::size(guard_t) const noexcept
    {   
        return Size2<T>(span(GUARD));
    }
    #endif

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::southeast() const noexcept 
    { 
        return hl();
    }
    
    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::southwest() const noexcept 
    { 
        return ll(); 
    }

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::span() const noexcept
    {
        return hi - lo;
    }
    

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::span(guard_t) const noexcept
    {
        return span().eabs();
    }

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    constexpr Vector2<T>   AxBox2<T>::unproject(const Vector2<T>& v) const noexcept
    {
        return div_elem(v-lo, span());
    }

    template <typename T>
    constexpr bool          AxBox2<T>::valid() const noexcept 
    {
        return all(lo) <= hi;
    }

    template <typename T>
    constexpr Range<T>      AxBox2<T>::x_range() const noexcept
    { 
        return { lo.x, hi.x }; 
    }
    
    template <typename T>
    constexpr T             AxBox2<T>::x_size() const noexcept 
    { 
        return hi.x - lo.x; 
    }
    
    #ifdef YQ_MATH_RANGE_HPP
    template <typename T>
    constexpr Range<T>      AxBox2<T>::y_range() const noexcept 
    { 
        return { lo.y, hi.y }; 
    }
    
    template <typename T>
    constexpr T             AxBox2<T>::y_size() const noexcept 
    { 
        return hi.y - lo.y; 
    }
    #endif
        
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr AxBox2<product_t<T,U>> operator*(T a, const AxBox2<U>& b) noexcept
    {
        if(a >= zero_v<T>)
            return AxBox2<product_t<T,U>>(a*b.lo, a*b.hi);
        else
            return AxBox2<product_t<T,U>>(a*b.hi, a*b.lo);
    }

    template <typename T>
    constexpr AxBox2<T> aabb(const Vector2<T>& a)
    {
        return AxBox2<T>(a);
    }

    template <typename T>
    constexpr AxBox2<T> aabb(const Vector2<T>& a, const Vector2<T>& b)
    {
        return AxBox2<T>(UNION, a, b);
    }

    template <typename T>
    AxBox2<T> aabb(const std::vector<Vector2<T>>& vals)
    {
        switch(vals.size()){
        case 0:
            return {};
        case 1:
            return AxBox2<T>(vals[0]);
        case 2:
            return AxBox2<T>(UNION, vals[0],vals[1]);
        default:
            break;
        }

        return AxBox2<T>(UNION, vals);
    }
    
    template <typename T>
    constexpr square_t<T>   area(const AxBox2<T>& ax) noexcept
    {
        return ax.area();
    }

    template <typename T>
    constexpr Vector2<T>    center(const AxBox2<T>& box) noexcept
    {
        return box.center();
    }

    template <typename T>
    Vector2<T>  centroid(const AxBox2<T>& box)
    {
        return box.center();
    }

    #ifdef YQ_MATH_CIRCLE2_HPP
    template <typename T>
    Circle2<T>    circumcircle(const AxBox2<T>& box) 
    {
        return box.circumcircle();
    }
    #endif
    
    
    #ifdef YQ_MATH_CIRCLE2_HPP
    template <typename T>
    constexpr Circle2<T>    incircle(const AxBox2<T>& box) noexcept
    {
        return box.incircle();
    }
    #endif

    template <typename T>
    constexpr bool          is_valid(const AxBox2<T>& a) noexcept
    {
        return a.is_valid();
    }

    template <typename T>
    constexpr T             perimeter(const AxBox2<T>& ax) noexcept
    {
        return ax.perimeter();
    }

    template <typename T>
    constexpr Vector2<T>    span(const AxBox2<T>&a) noexcept
    {
        return a.span();
    }

    template <typename S, typename T>
    S&  as_stream(S& s, const AxBox2<T>& v)
    {
        return s << "[(" << v.lo.x << ":" << v.hi.x << ")x(" 
                         << v.lo.y << ":" << v.hi.y << ")]";
    }
    
    #ifdef YQ_BASIC_STREAM_HPP_
    template <typename T>
    Stream& operator<<(Stream&s, const AxBox2<T>& v)
    {
        return as_stream(s, v);
    }
    #endif

    #ifdef _LOG4CPP_CATEGORYSTREAM_HH
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const AxBox2<T>& v)
    {
        return as_stream(s, v);
    }
    #endif
}
