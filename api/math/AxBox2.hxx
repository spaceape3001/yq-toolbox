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

#include <math/AxBox2.hpp>
#include <math/AxCorners2.hpp>
#include <math/Circle2.hpp>
#include <math/Range.hpp>
#include <math/Size2.hpp>


namespace yq {
    template <typename T>
    constexpr AxBox2<T>::AxBox2(intersection_t, std::initializer_list<Vector2<T>> ls, std::initializer_list<Vector2<T>> hs) noexcept:
        AxBox2(INTERSECT, std::span<const Vector2<T>>(ls.data(), ls.size()), std::span<const Vector2<T>>(hs.data(), hs.size()))
    {}

    template <typename T>
    constexpr AxBox2<T>::AxBox2(intersection_t, std::span<const Vector2<T>>ls, std::span<const Vector2<T>>hs) noexcept
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
    constexpr AxBox2<T>::AxBox2(union_t, std::initializer_list<Vector2<T>> list) noexcept : 
        AxBox2(UNION, std::span<const Vector2<T>>(list.data(), list.size())){}

    template <typename T>
    constexpr AxBox2<T>::AxBox2(union_t, std::span<const Vector2<T>> data) noexcept
    {
        if(!data.empty()){
            auto [lx, hx] = std::minmax_element(data.begin(), data.end(), Vector2<T>::less_x);
            lo.x = lx->x;
            hi.x = hx->x;

            auto [ly, hy] = std::minmax_element(data.begin(), data.end(), Vector2<T>::less_y);
            lo.y = lx->y;
            hi.y = hx->y;
        } else {
            lo = hi  = Vector2<T>(ZERO);
        }
    }

    template <typename T>
    constexpr AxBox2<T>::AxBox2(union_t, std::initializer_list<Vector2<T>> ls, std::initializer_list<Vector2<T>> hs) noexcept :
        AxBox2(UNION, std::span<const Vector2<T>>(ls.data(), ls.size()), std::span<const Vector2<T>>(hs.data(), hs.size()))
    {}

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

    template <typename T>
    constexpr AxBox2<T>::AxBox2(const Circle2<T>& cir) noexcept : AxBox2(cir.bounds())
    {
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
    constexpr Vector2<T>  AxBox2<T>::center() const noexcept
    {
        if constexpr (trait::is_floating_point_v<T>)
            return ieee754_t<T>(0.5)*(lo+hi);
        if constexpr (std::is_integral_v<T>)
            return (lo+hi) / T(2);
        return {};
    }

    template <typename T>
    Circle2<T>          AxBox2<T>::circumcircle() const
    {
        return circle( center(), half_v<T>*span().length() );
    }

    template <typename T>
    constexpr bool          AxBox2<T>::contains(const Vector2<T>& pt) const noexcept
    {
        return (all(lo) <= pt) && (all(pt) <= hi);
    }

    template <typename T>
    constexpr AxCorners2<Vector2<T>>    AxBox2<T>::corners() const noexcept 
    {
        return { 
            southwest(),
            northwest(),
            southeast(),
            northeast()
        };
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
    constexpr Circle2<T>  AxBox2<T>::incircle() const noexcept
    {
        return circle(center(), middivide(span().cmin()));
    }

    template <typename T>
    constexpr bool          AxBox2<T>::is_valid() const noexcept 
    {
        return all(lo) <= hi;
    }
        
    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::northeast() const noexcept { return hi; };

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::northwest() const noexcept { return { lo.x, hi.y}; }
    
    template <typename T>
    constexpr bool          AxBox2<T>::overlaps(const AxBox2<T>& b) noexcept
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

    template <typename T>
    constexpr Size2<T> AxBox2<T>::size() const noexcept 
    {
        auto s = span();
        return Size2<T>{ s.x, s.y, s.z }; 
    }

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::southeast() const noexcept 
    { 
        return Vector2<T>( hi.x, lo.y ); 
    }
    
    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::southwest() const noexcept 
    { 
        return lo; 
    }

    template <typename T>
    constexpr Vector2<T>    AxBox2<T>::span() const noexcept
    {
        return hi - lo;
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
        
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    /*! \brief Creates a 2D axially aligned box from one vector
    */
    template <typename T>
    constexpr AxBox2<T> aabb(const Vector2<T>& a)
    {
        return AxBox2<T>(a);
    }
    
    /*! \brief Creates a 2D axially aligned box from two vectors
    */
    template <typename T>
    constexpr AxBox2<T> aabb(const Vector2<T>& a, const Vector2<T>& b)
    {
        return AxBox2<T>(UNION, a, b);
    }

    /*! \brief Creates a 2D axially aligned box from container of Vector2's
    */
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
    
    /*! \brief Computes the area of a 2D axially aligned bounding box
    */
    template <typename T>
    constexpr square_t<T>   area(const AxBox2<T>& ax) noexcept
    {
        return ax.area();
    }

    /*! \brief Computes the center of a 2D axially aligned box
    */
    template <typename T>
    constexpr Vector2<T>    center(const AxBox2<T>& box) noexcept
    {
        return box.center();
    }

    //! Checks for validity (hi >= lo)
    template <typename T>
    constexpr bool          is_valid(const AxBox2<T>& a) noexcept
    {
        return a.is_valid();
    }

    /*! \brief Computes the perimeter of the box */
    template <typename T>
    constexpr T             perimeter(const AxBox2<T>& ax) noexcept
    {
        return ax.perimeter();
    }

    /*! \brief Returns the span (dimensions) of the box
    */
    template <typename T>
    constexpr Vector2<T>    span(const AxBox2<T>&a) noexcept
    {
        return a.span();
    }
}
