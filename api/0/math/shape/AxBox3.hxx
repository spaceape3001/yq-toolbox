////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the axbox3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <0/math/shape/AxBox3.hpp>
#include <0/math/utility.hpp>
#include <yq/math/errors.hpp>

namespace yq {
    template <typename T>
    constexpr AxBox3<T>::AxBox3(intersect_t, std::initializer_list<Vector3<T>> ls, std::initializer_list<Vector3<T>> hs) noexcept:
        AxBox3(INTERSECT, yq::span(ls), yq::span(hs)) {}

    template <typename T>
    constexpr AxBox3<T>::AxBox3(intersect_t, std::span<const Vector3<T>>ls, std::span<const Vector3<T>>hs) noexcept
    {
        if(!ls.empty()){
            lo.x    = std::max_element(ls.begin(), ls.end(), Vector3<T>::less_x) -> x;
            lo.y    = std::max_element(ls.begin(), ls.end(), Vector3<T>::less_y) -> y;
            lo.z    = std::max_element(ls.begin(), ls.end(), Vector3<T>::less_z) -> z;
        } else {
            lo      = Vector3<T>(ZERO);
        }
        
        if(!hs.empty()){
            hi.x    = std::min_element(hs.begin(), hs.end(), Vector3<T>::less_x) -> x;
            hi.y    = std::min_element(hs.begin(), hs.end(), Vector3<T>::less_y) -> y;
            hi.z    = std::min_element(hs.begin(), hs.end(), Vector3<T>::less_z) -> z;
        } else {
            hi      = Vector3<T>(ZERO);
        }
    }

    template <typename T>
    constexpr AxBox3<T>::AxBox3(sort_t, const Vector3<T>&a, const Vector3<T>& b) noexcept
    {
        std::tie(lo.x, hi.x)    = std::minmax(a.x, b.x);
        std::tie(lo.y, hi.y)    = std::minmax(a.y, b.y);
        std::tie(lo.z, hi.z)    = std::minmax(a.z, b.z);
    }

    template <typename T>
    constexpr AxBox3<T>::AxBox3(union_t, const Vector3<T>&a, const Vector3<T>& b) noexcept : AxBox3(SORT, a, b) {}

    template <typename T>
    constexpr AxBox3<T>::AxBox3(union_t, std::initializer_list<Vector3<T>> list) noexcept : 
        AxBox3(UNION, yq::span(list)){}

    template <typename T>
    constexpr AxBox3<T>::AxBox3(union_t, std::span<const Vector3<T>> data) noexcept
    {
        if(!data.empty()){
            auto [lx, hx] = std::minmax_element(data.begin(), data.end(), Vector3<T>::less_x);
            lo.x = lx->x;
            hi.x = hx->x;

            auto [ly, hy] = std::minmax_element(data.begin(), data.end(), Vector3<T>::less_y);
            lo.y = ly->y;
            hi.y = hy->y;

            auto [lz, hz] = std::minmax_element(data.begin(), data.end(), Vector3<T>::less_z);
            lo.z = lz->z;
            hi.z = hz->z;
        } else {
            lo = hi = Vector3<T>(ZERO);
        }
    }

    template <typename T>
    constexpr AxBox3<T>::AxBox3(union_t, std::initializer_list<Vector3<T>> ls, std::initializer_list<Vector3<T>> hs) noexcept :
        AxBox3(UNION, yq::span(ls), yq::span(hs))
    {}

    template <typename T>
    constexpr AxBox3<T>::AxBox3(union_t, std::span<const Vector3<T>>ls, std::span<const Vector3<T>>hs) noexcept
    {
        if(!ls.empty()){
            lo.x    = std::min_element(ls.begin(), ls.end(), Vector3<T>::less_x) -> x;
            lo.y    = std::min_element(ls.begin(), ls.end(), Vector3<T>::less_y) -> y;
            lo.z    = std::min_element(ls.begin(), ls.end(), Vector3<T>::less_z) -> z;
        } else {
            lo      = Vector3<T>(ZERO);
        }
        
        if(!hs.empty()){
            hi.x    = std::max_element(hs.begin(), hs.end(), Vector3<T>::less_x) -> x;
            hi.y    = std::max_element(hs.begin(), hs.end(), Vector3<T>::less_y) -> y;
            hi.z    = std::max_element(hs.begin(), hs.end(), Vector3<T>::less_z) -> z;
        } else {
            hi      = Vector3<T>(ZERO);
        }
    }

    #ifdef YQ_MATH_SEGMENT3_HPP
    template <typename T>
    constexpr AxBox3<T>::AxBox3(const Segment3<T>&seg) noexcept : AxBox3(seg.bounds()) {}
    #endif

    #ifdef YQ_MATH_SPHERE3_HPP
    template <typename T>
    constexpr AxBox3<T>::AxBox3(const Sphere3<T>& sph) noexcept : AxBox3(sph.bounds()) {}
    #endif

    #ifdef YQ_MATH_TRIANGLE3_HPP
    template <typename T>
    constexpr AxBox3<T>::AxBox3(const Triangle3<T>&tri) noexcept : AxBox3(tri.bounds()) {}
    #endif

    #ifdef YQ_MATH_TETRAHEDRON3_HPP
    template <typename T>
    constexpr AxBox3<T>::AxBox3(const Tetrahedron3<T>&tetra) noexcept : AxBox3(tetra.bounds()) {}
    #endif

    template <typename T>
    AxBox3<T>  AxBox3<T>::operator+() const noexcept
    {
        return *this;
    }

    template <typename T>
    AxBox3<T>  AxBox3<T>::operator-() const noexcept
    {
        return AxBox3<T>(-hi, -lo);
    }

    template <typename T>
    AxBox3<T>  AxBox3<T>::operator+(const Vector3<T>&b) const noexcept
    {
        return AxBox3<T>(lo+b, hi+b);
    }

    template <typename T>
    AxBox3<T>& AxBox3<T>::operator+=(const Vector3<T>&b) noexcept
    {
        lo += b;
        hi += b;
        return *this;
    }

    template <typename T>
    AxBox3<T>  AxBox3<T>::operator-(const Vector3<T>&b) const noexcept
    {
        return AxBox3<T>(lo-b, hi-b);
    }

    template <typename T>
    AxBox3<T>& AxBox3<T>::operator-=(const Vector3<T>&b) noexcept
    {
        lo -= b;
        hi -= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    AxBox3<product_t<T,U>> AxBox3<T>::operator*(U b) const noexcept
    {
        if(b >= zero_v<U>)
            return AxBox3<product_t<T,U>>(lo*b,hi*b);
        else
            return AxBox3<product_t<T,U>>(hi*b,lo*b);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    AxBox3<T>& AxBox3<T>::operator*=(U b) noexcept
    {
        *this = *this * b;
        return *this;
    }
        
    template <typename T>
        template <typename U>
    requires is_arithmetic_v<U>
    AxBox3<quotient_t<T,U>> AxBox3<T>::operator/(U b) const noexcept
    {
        if(b >= zero_v<U>)
            return AxBox3<quotient_t<T,U>>(lo/b,hi/b);
        else
            return AxBox3<quotient_t<T,U>>(hi/b,lo/b);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_div_v<T,U>)
    AxBox3<T>& AxBox3<T>::operator/=(U b) noexcept
    {
        *this = *this / b;
        return *this;
    }
        

    template <typename T>
    constexpr AxBox3<T> AxBox3<T>::operator|(const AxBox3<T>&b) const noexcept
    {
        return AxBox3(UNION, {lo, hi, b.lo, b.hi});
    }

    template <typename T>
    constexpr AxBox3<T> AxBox3<T>::operator|(const Vector3<T>&b) const noexcept
    {
        return AxBox3(UNION, {lo, hi, b});
    }

    template <typename T>
    AxBox3<T>& AxBox3<T>::operator|=(const AxBox3& b) noexcept
    {
        *this   = *this | b;
        return *this;
    }

    template <typename T>
    AxBox3<T>& AxBox3<T>::operator|=(const Vector3<T>& b) noexcept
    {
        *this   = *this | b;
        return *this;
    }

    template <typename T>
    constexpr AxBox3<T> AxBox3<T>::operator&(const AxBox3<T>&b) const noexcept
    {
        return AxBox3(INTERSECT, {lo, b.lo}, {hi, b.hi});
    }

    template <typename T>
    AxBox3<T>& AxBox3<T>::operator&=(const AxBox3& b)  noexcept
    {
        *this = *this & b;
        return *this;
    }


    template <typename T>
    constexpr Vector3<T>      AxBox3<T>::center() const noexcept
    {
        if constexpr (is_floating_point_v<T>)
            return ieee754_t<T>(0.5)*(lo+hi);
        if constexpr (std::is_integral_v<T>)
            return (lo+hi) / T(2);
        return {};
    }

    #ifdef YQ_MATH_SPHERE3_HPP
    template <typename T>
    constexpr Sphere3<T>        AxBox3<T>::circumsphere() const noexcept
    {
        return Sphere3<T>( center(), half_v<T>*span().length() );
    }
    #endif

    #if defined(YQ_MATH_DATA3_HPP) && defined(YQ_MATH_SIDE_HPP)
    template <typename T>
    constexpr Data3<Side>       AxBox3<T>::classify(const Vector3<T>&v) const noexcept
    {
        return Data3<Side>( classify_x(v.x), classify_y(v.y), classify_z(v.z), classify_w(v.w) );
    }
    #endif

    #ifdef YQ_MATH_SIDE_HPP
    template <typename T>
    constexpr Side              AxBox3<T>::classify_x(T v) const noexcept
    {
        return _classify(v, lo.x, hi.x);
    }
    #endif

    #ifdef YQ_MATH_SIDE_HPP
    template <typename T>
    constexpr Side              AxBox3<T>::classify_x(const Vector3<T>&v) const noexcept
    {
        return classify_x(v.x);
    }
    #endif

    #ifdef YQ_MATH_SIDE_HPP
    template <typename T>
    constexpr Side              AxBox3<T>::classify_y(T v) const noexcept
    {
        return _classify(v, lo.y, hi.y);
    }
    #endif

    #ifdef YQ_MATH_SIDE_HPP
    template <typename T>
    constexpr Side              AxBox3<T>::classify_y(const Vector3<T>&v) const noexcept
    {
        return classify_y(v.y);
    }
    #endif

    #ifdef YQ_MATH_SIDE_HPP
    template <typename T>
    constexpr Side              AxBox3<T>::classify_z(T v) const noexcept
    {
        return _classify(v, lo.z, hi.z);
    }
    #endif

    #ifdef YQ_MATH_SIDE_HPP
    template <typename T>
    constexpr Side              AxBox3<T>::classify_z(const Vector3<T>&v) const noexcept
    {
        return classify_z(v.z);
    }
    #endif

    template <typename T>
    constexpr bool AxBox3<T>::contains(const Vector3<T>& pt) const noexcept
    {
        return (all(lo) <= pt) && (all(pt) <= hi);
    }

    #ifdef YQ_MATH_AXCORNERS3_HPP
    template <typename T>
    constexpr AxCorners3<Vector3<T>>  AxBox3<T>::corners() const noexcept
    {
        return AxCorners3<Vector3<T>>(
            lll(),
            llh(),
            lhl(),
            lhh(),
            hll(),
            hlh(),
            hhl(),
            hhh()
        );
    }
    #endif

    #ifdef YQ_MATH_AXCORNERS3_HPP
    template <typename T>
    constexpr AxCorners3<Vector3<T>>    AxBox3<T>::corners(T adjust) const noexcept
    {
        return inflate(adjust).corners();
    }
    #endif

    template <typename T>
    T                       AxBox3<T>::distance(const Vector3<T>&v) const
    {
        if constexpr ( has_sqrt_v<T> )
            return sqrt(distance²(v));
        return zero_v<T>;
    }
    
    template <typename T>
    constexpr square_t<T>   AxBox3<T>::distance²(const Vector3<T>&v) const noexcept
    {
        return 
            (_gap(v.x, lo.x, hi.x)^²) +
            (_gap(v.y, lo.y, hi.y)^²) +
            (_gap(v.z, lo.z, hi.z)^²)
        ;
    }

    template <typename T>
    constexpr bool AxBox3<T>::eclipses(const AxBox3<T>& b) const noexcept
    {
        return (all(lo) <= b.lo) && (all(b.hi) <= hi);
    }

    template <typename T>
    constexpr AxBox3<T> AxBox3<T>::fixed() const noexcept
    {
        return AxBox3(UNION, lo, hi);
    }

    template <typename T>
    template <typename>
    requires is_floating_point_v<T>
    Expect<unity_t<T>>    AxBox3<T>::fraction_x(T x) const noexcept
    {
        if(hi.x == lo.x)
            return errors::degenerate_dimension();
        return (x-lo.x) / (hi.x-lo.x);
    }

    template <typename T>
    template <typename>
    requires is_floating_point_v<T>
    Expect<unity_t<T>>    AxBox3<T>::fraction_x(T x, T ep) const noexcept
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
    Expect<unity_t<T>>    AxBox3<T>::fraction_y(T y) const noexcept
    {
        if(hi.y == lo.y)
            return errors::degenerate_dimension();
        return (y-lo.y) / (hi.y-lo.y);
    }

    template <typename T>
    template <typename>
    requires is_floating_point_v<T>
    Expect<unity_t<T>>    AxBox3<T>::fraction_y(T y, T ep) const noexcept
    {
        if(hi.y - lo.y < ep){
            if(hi.y < lo.y)
                return errors::invalid_box();
            return errors::degenerate_dimension();
        }
        return (y-lo.y) / (hi.y-lo.y);
    }

    template <typename T>
    template <typename>
    requires is_floating_point_v<T>
    Expect<unity_t<T>>    AxBox3<T>::fraction_z(T z) const noexcept
    {
        if(hi.z == lo.z)
            return errors::degenerate_dimension();
        return (z-lo.z) / (hi.z-lo.z);
    }

    template <typename T>
    template <typename>
    requires is_floating_point_v<T>
    Expect<unity_t<T>>    AxBox3<T>::fraction_z(T z, T ep) const noexcept
    {
        if(hi.z - lo.z < ep){
            if(hi.z < lo.z)
                return errors::invalid_box();
            return errors::degenerate_dimension();
        }
        return (z-lo.z) / (hi.z-lo.z);
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::hhh() const noexcept
    {
        return hi;
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::hhh(T adjust) const noexcept
    {
        return Vector3(hi.x+adjust,hi.y+adjust,hi.z+adjust);
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::hhl() const noexcept
    {
        return Vector3(hi.x, hi.y, lo.z);
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::hhl(T adjust) const noexcept
    {
        return Vector3(hi.x+adjust,hi.y+adjust,lo.z-adjust);
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::hlh() const noexcept
    {
        return Vector3(hi.x, lo.y, hi.z);
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::hlh(T adjust) const noexcept
    {
        return Vector3(hi.x+adjust,lo.y-adjust,hi.z+adjust);
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::hll() const noexcept
    {
        return Vector3(hi.x, lo.y, lo.z);
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::hll(T adjust) const noexcept
    {
        return Vector3(hi.x+adjust,lo.y-adjust,lo.z-adjust);
    }


    template <typename T>
    constexpr AxBox3<T>    AxBox3<T>::inflate(T d) const noexcept
    {
        return AxBox3(all(lo) - d, all(hi) + d);
    }

    template <typename T>
    constexpr AxBox3<T>    AxBox3<T>::inflate(guard_t, T d) const noexcept
    {
        AxBox3  bx  = fixed();
        return bx.inflate(std::max(d, bx.min_inflate()));
    }

    #ifdef YQ_MATH_SPHERE3_HPP
    template <typename T>
    constexpr Sphere3<T>    AxBox3<T>::insphere() const noexcept
    {
        return Sphere3<T>(center(), middivide(span().cmin()));
    }
    #endif

    template <typename T>
    constexpr bool    AxBox3<T>::is_valid() const noexcept
    {
        return all(lo) <= hi;
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::lhh() const noexcept
    {
        return Vector3<T>(lo.x, hi.y, hi.z);
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::lhh(T adjust) const noexcept
    {
        return Vector3<T>(lo.x-adjust, hi.y+adjust, hi.z+adjust);
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::lhl() const noexcept
    {
        return Vector3<T>(lo.x, hi.y, lo.z);
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::lhl(T adjust) const noexcept
    {
        return Vector3<T>(lo.x-adjust, hi.y+adjust, lo.z-adjust);
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::llh() const noexcept
    {
        return Vector3<T>(lo.x, lo.y, hi.z);
    }
    

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::llh(T adjust) const noexcept
    {
        return Vector3<T>(lo.x-adjust, lo.y-adjust, hi.z+adjust);
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::lll() const noexcept
    {
        return lo;
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::lll(T adjust) const noexcept
    {
        return Vector3<T>(lo.x-adjust, lo.y-adjust, lo.z-adjust);
    }

    template <typename T>
    constexpr T AxBox3<T>::min_inflate() const noexcept
    {
        return -midspan(span().cmin());
    }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::northeast_bottom() const noexcept
    {
        return hhl();
   }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::northeast_top() const noexcept
    {
        return hhh();
    }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::northwest_bottom() const noexcept
    {
        return lhl();
    }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::northwest_top() const noexcept
    {
        return llh();
    }

    template <typename T>
    constexpr bool AxBox3<T>::overlaps(const AxBox3<T>& b) const noexcept
    {
        return (all(lo) <= b.hi) && (all(b.lo) <= hi);
    }

    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    constexpr Vector3<T>   AxBox3<T>::project(const Vector3<T>& v) const noexcept
    {
        return (one_v<Vector3<T>>-v).emul(lo) + v.emul(hi);
    }

    #ifdef YQ_MATH_SIZE3_HPP
    template <typename T>
    constexpr Size3<T> AxBox3<T>::size() const noexcept 
    {
        auto s = span();
        return Size3<T>{ s.x, s.y, s.z }; 
    }
    #endif

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::southeast_bottom() const noexcept
    {
        return hll();
    }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::southeast_top() const noexcept
    {
        return hlh();
    }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::southwest_bottom() const noexcept
    {
        return lll();
    }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::southwest_top() const noexcept
    {
        return llh();
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::span() const noexcept
    {
        return hi - lo;
    }


    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::span(guard_t) const noexcept
    {
        return span().eabs();
    }

    template <typename T>
    constexpr square_t<T>    AxBox3<T>::surface_area() const noexcept
    {
        Vector3<T>  del     = hi - lo;
        return 2.0 * ((del.x*del.y)+(del.y*del.z)+(del.z*del.x));
    }


    template <typename T>
    template <typename>
    requires std::is_floating_point_v<T>
    constexpr Vector3<T>   AxBox3<T>::unproject(const Vector3<T>& v) const noexcept
    {
        return div_elem(v-lo, hi-lo);
    }

    template <typename T>
    constexpr bool          AxBox3<T>::valid() const noexcept 
    {
        return all(lo) <= hi;
    }

    template <typename T>
    constexpr cube_t<T>       AxBox3<T>::volume() const noexcept
    {
        return span().cproduct();
    }

    template <typename T>
    constexpr cube_t<T>       AxBox3<T>::volume(guard_t) const noexcept
    {
        return abs(volume());
    }

    #ifdef YQ_MATH_RANGE_HPP
    template <typename T>
    constexpr Range<T>  AxBox3<T>::x_range() const noexcept
    {
        return range(lo.x, hi.x);
    }

    template <typename T>
    constexpr Range<T>  AxBox3<T>::y_range() const noexcept
    {
        return range(lo.y, hi.y);
    }

    template <typename T>
    constexpr Range<T>  AxBox3<T>::z_range() const noexcept
    {
        return range(lo.z, hi.z);
    }
    #endif
        
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr AxBox3<product_t<T,U>> operator*(T a, const AxBox3<U>& b) noexcept
    {
        if(a >= zero_v<T>)
            return AxBox3<product_t<T,U>>(a*b.lo, a*b.hi);
        else
            return AxBox3<product_t<T,U>>(a*b.hi, a*b.lo);
    }


    template <typename T>
    constexpr AxBox3<T> aabb(const Vector3<T>& a) noexcept
    {
        return AxBox3<T>(a);
    }

    template <typename T>
    constexpr AxBox3<T> aabb(const Vector3<T>& a, const Vector3<T>& b) noexcept
    {
        return AxBox3<T>(UNION, a, b);
    }

    template <typename T>
    AxBox3<T> aabb(const std::vector<Vector3<T>>& vals)
    {
        switch(vals.size()){
        case 0:
            return AxBox3<T>(ZERO);
        case 1:
            return AxBox3<T>(vals[0]);
        case 2:
            return AxBox3<T>(UNION, vals[0],vals[1]);
        default:
            break;
        }

        return AxBox3<T>(UNION, vals);
    }
    

    template <typename T>
    constexpr Vector3<T>      center(const AxBox3<T>& box) noexcept
    {
        return box.center();
    }

    template <typename T>
    Vector3<T>  centroid(const AxBox3<T>& box)
    {
        return box.center();
    }

    template <typename T>
    constexpr bool    is_valid(const AxBox3<T>& box) noexcept
    {
        return box.is_valid();
    }


    template <typename T>
    constexpr Vector3<T>    span(const AxBox3<T>&box) noexcept
    {
        return box.span();
    }

    template <typename T>
    constexpr square_t<T>    surface_area(const AxBox3<T>& box) noexcept
    {
        return box.surface_area();
    }

    template <typename T>
    constexpr cube_t<T>       volume(const AxBox3<T>& box) noexcept
    {
        return box.volume();
    }    

    template <typename S, typename T>
    S&  as_stream(S& s, const AxBox3<T>& v)
    {
        return s << "[(" << v.lo.x << ":" << v.hi.x << ")x(" 
                         << v.lo.y << ":" << v.hi.y << ")x(" 
                         << v.lo.z << ":" << v.hi.z << ")]";
    }
    
    #ifdef YQ_BASIC_STREAM_HPP_
    template <typename T>
    Stream& operator<<(Stream&s, const AxBox3<T>& v)
    {
        return as_stream(s, v);
    }
    #endif

    #ifdef _LOG4CPP_CATEGORYSTREAM_HH
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const AxBox3<T>& v)
    {
        return as_stream(s, v);
    }
    #endif
}
