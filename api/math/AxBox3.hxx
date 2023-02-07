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

#include <math/AxBox3.hpp>
#include <math/AxCorners3.hpp>
#include <math/Data3.hpp>
#include <math/Range.hpp>
#include <math/Side.hpp>
#include <math/Size3.hpp>

namespace yq {
    template <typename T>
    constexpr AxBox3<T>::AxBox3(intersect_t, std::initializer_list<Vector3<T>> ls, std::initializer_list<Vector3<T>> hs) noexcept:
        AxBox3(INTERSECT, std::span<const Vector3<T>>(ls.data(), ls.size()), std::span<const Vector3<T>>(hs.data(), hs.size()))
    {}

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
        AxBox3(UNION, std::span<const Vector3<T>>(list.data(), list.size())){}

    template <typename T>
    constexpr AxBox3<T>::AxBox3(union_t, std::span<const Vector3<T>> data) noexcept
    {
        if(!data.empty()){
            auto [lx, hx] = std::minmax_element(data.begin(), data.end(), Vector3<T>::less_x);
            lo.x = lx->x;
            hi.x = hx->x;

            auto [ly, hy] = std::minmax_element(data.begin(), data.end(), Vector3<T>::less_y);
            lo.y = lx->y;
            hi.y = hx->y;

            auto [lz, hz] = std::minmax_element(data.begin(), data.end(), Vector3<T>::less_z);
            lo.z = lx->z;
            hi.z = hx->z;
        } else {
            lo = hi = Vector3<T>(ZERO);
        }
    }

    template <typename T>
    constexpr AxBox3<T>::AxBox3(union_t, std::initializer_list<Vector3<T>> ls, std::initializer_list<Vector3<T>> hs) noexcept :
        AxBox3(UNION, std::span<const Vector3<T>>(ls.data(), ls.size()), std::span<const Vector3<T>>(hs.data(), hs.size()))
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

    template <typename T>
    constexpr AxBox3<T>::AxBox3(const Segment3<T>&seg) noexcept : AxBox3(seg.bounds()) {}

    template <typename T>
    constexpr AxBox3<T>::AxBox3(const Sphere3<T>& sph) noexcept : AxBox3(sph.bounds()) {}

    template <typename T>
    constexpr AxBox3<T>::AxBox3(const Triangle3<T>&tri) noexcept : AxBox3(tri.bounds()) {}

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
    requires trait::is_arithmetic_v<U>
    AxBox3<trait::product_t<T,U>> AxBox3<T>::operator*(U b) const noexcept
    {
        if(b >= zero_v<U>)
            return AxBox3<trait::product_t<T,U>>(lo*b,hi*b);
        else
            return AxBox3<trait::product_t<T,U>>(hi*b,lo*b);
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    AxBox3<T>& AxBox3<T>::operator*=(U b) noexcept
    {
        *this = *this * b;
        return *this;
    }
        
    template <typename T>
        template <typename U>
    requires trait::is_arithmetic_v<U>
    AxBox3<trait::quotient_t<T,U>> AxBox3<T>::operator/(U b) const noexcept
    {
        if(b >= zero_v<U>)
            return AxBox3<trait::quotient_t<T,U>>(lo/b,hi/b);
        else
            return AxBox3<trait::quotient_t<T,U>>(hi/b,lo/b);
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
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
        if constexpr (trait::is_floating_point_v<T>)
            return ieee754_t<T>(0.5)*(lo+hi);
        if constexpr (std::is_integral_v<T>)
            return (lo+hi) / T(2);
        return {};
    }

    template <typename T>
    constexpr Data3<Side>       AxBox3<T>::classify(const Vector3<T>&v) const noexcept
    {
        return Data3<Side>( classify_x(v.x), classify_y(v.y), classify_z(v.z), classify_w(v.w) );
    }

    template <typename T>
    constexpr Side              AxBox3<T>::classify_x(T v) const noexcept
    {
        return _classify(v, lo.x, hi.x);
    }

    template <typename T>
    constexpr Side              AxBox3<T>::classify_x(const Vector3<T>&v) const noexcept
    {
        return classify_x(v.x);
    }

    template <typename T>
    constexpr Side              AxBox3<T>::classify_y(T v) const noexcept
    {
        return _classify(v, lo.y, hi.y);
    }

    template <typename T>
    constexpr Side              AxBox3<T>::classify_y(const Vector3<T>&v) const noexcept
    {
        return classify_y(v.y);
    }

    template <typename T>
    constexpr Side              AxBox3<T>::classify_z(T v) const noexcept
    {
        return _classify(v, lo.z, hi.z);
    }

    template <typename T>
    constexpr Side              AxBox3<T>::classify_z(const Vector3<T>&v) const noexcept
    {
        return classify_z(v.z);
    }

    template <typename T>
    constexpr bool AxBox3<T>::contains(const Vector3<T>& pt) const noexcept
    {
        return (all(lo) <= pt) && (all(pt) <= hi);
    }

    template <typename T>
    constexpr AxCorners3<Vector3<T>>  AxBox3<T>::corners() const noexcept
    {
        return { 
            lo,
            { lo.x, lo.y, hi.z  }, 
            { lo.x, hi.y, lo.z  }, 
            { lo.x, hi.y, hi.z  }, 
            { hi.x, lo.y, lo.z  }, 
            { hi.x, lo.y, hi.z  }, 
            { hi.x, hi.y, lo.z  }, 
            hi
        };
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
    constexpr bool    AxBox3<T>::is_valid() const noexcept
    {
        return all(lo) <= hi;
    }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::northeast_bottom() const noexcept
    {
        return { hi.x, hi.y, lo.z };
   }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::northeast_top() const noexcept
    {
        return hi;
    }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::northwest_bottom() const noexcept
    {
        return { lo.x, hi.y, lo.z };
    }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::northwest_top() const noexcept
    {
        return { lo.x, hi.y, hi.z };
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

    template <typename T>
    constexpr Size3<T> AxBox3<T>::size() const noexcept 
    {
        auto s = span();
        return Size3<T>{ s.x, s.y, s.z }; 
    }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::southeast_bottom() const noexcept
    {
        return { hi.x, lo.y, lo.z };
    }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::southeast_top() const noexcept
    {
        return { hi.x, lo.y, hi.z };
    }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::southwest_bottom() const noexcept
    {
        return lo;
    }

    template <typename T>
    constexpr Vector3<T>  AxBox3<T>::southwest_top() const noexcept
    {
        return { lo.x, lo.y, hi.z };
    }

    template <typename T>
    constexpr Vector3<T>    AxBox3<T>::span() const noexcept
    {
        return hi - lo;
    }

    template <typename T>
    constexpr trait::square_t<T>    AxBox3<T>::surface_area() const noexcept
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
    constexpr trait::cube_t<T>       AxBox3<T>::volume() const noexcept
    {
        return span().cproduct();
    }

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
        
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr AxBox3<trait::product_t<T,U>> operator*(T a, const AxBox3<U>& b) noexcept
    {
        if(a >= zero_v<T>)
            return AxBox3<trait::product_t<T,U>>(a*b.lo, a*b.hi);
        else
            return AxBox3<trait::product_t<T,U>>(a*b.hi, a*b.lo);
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
    constexpr trait::square_t<T>    surface_area(const AxBox3<T>& box) noexcept
    {
        return box.surface_area();
    }

    template <typename T>
    constexpr trait::cube_t<T>       volume(const AxBox3<T>& box) noexcept
    {
        return box.volume();
    }    
}
