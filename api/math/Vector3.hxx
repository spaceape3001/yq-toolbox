////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the vector3 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/AxBox3.hpp>
#include <math/Bivector3.hpp>
#include <math/Multivector3.hpp>
#include <math/Polygon3.hpp>
#include <math/Polyline3.hpp>
#include <math/Segment3.hpp>
#include <math/Size3.hpp>
#include <math/Trivector3.hpp>

#include <math/Tensor31.hpp>
#include <math/Tensor32.hpp>
#include <math/Tensor33.hpp>
#include <math/Tensor34.hpp>

#include <math/Vector1.hpp>
#include <math/Vector2.hpp>
#include <math/Vector3.hpp>
#include <math/Vector4.hpp>

#include <math/Units.hpp>
#include <math/trig.hpp>
#include <math/utility.hpp>

#include <basic/Stream.hpp>
#include <basic/Logging.hpp>

#include <math/AllComponents.hpp>
#include <math/AnyComponents.hpp>


namespace yq {
    template <typename T>
    constexpr Vector3<T>::Vector3(const Size3<T>&v) noexcept : Vector3(v.x, v.y, v.z)
    {
    }

    #ifdef YQ_USE_GLM
    template <typename T>
    constexpr Vector3<T>::operator glm::vec<3, T, glm::defaultp>() const noexcept
    {
        return glm::vec<3, T, glm::defaultp>( x, y, z );
    }
    #endif

    template <typename T>
    constexpr Vector3<T> Vector3<T>::operator-() const noexcept
    {
        return Vector3(-x,-y,-z);
    }

    template <typename T>
    Vector3<quotient_t<T,T>> Vector3<T>::operator~() const
    {
        auto l = one_v<T>/length();
        return Vector3<quotient_t<T,T>>(x*l, y*l, z*l);
    }

    template <typename T>
    constexpr square_t<T> Vector3<T>::operator^(two_t) const noexcept
    {
        return x*x + y*y + z*z;
    }    

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator+(T b) const noexcept
    {
        return Multivector3<T>(
            b, 
            x, y, z,
            zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }

    template <typename T>
    constexpr AxBox3<T> Vector3<T>::operator+(const AxBox3<T>&b) const noexcept
    {
        return AxBox3<T>(*this + b.lo, *this + b.hi);
    }

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator+(const Bivector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            zero_v<T>, 
            x, y, z,
            b.xy, b.yz, b.zx,
            zero_v<T> 
        );
    }

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator+(const Multivector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            b.a, 
            x+b.x, y+b.y, z+b.z, 
            b.xy, b.yz, b.zx,
            b.xyz
        );
    }

    template <typename T>
    Polygon3<T> Vector3<T>::operator+(const Polygon3<T>&b) const
    {
        return Polygon3<T>(*this + b.vertex);
    }

    template <typename T>
    Polyline3<T> Vector3<T>::operator+(const Polyline3<T>&b) const
    {
        return Polygon3<T>(*this - b.vertex);
    }

    template <typename T>
    constexpr Segment3<T> Vector3<T>::operator+(const Segment3<T>&rhs) const noexcept
    {
        return Segment3<T>( *this + rhs.a, *this + rhs.b );
    }

    template <typename T>
    constexpr Sphere3<T> Vector3<T>::operator+(const Sphere3<T>&b) const noexcept
    {
        return Sphere3<T>(*this + b.point, b.radius);
    }

    template <typename T>
    constexpr Triangle3<T> Vector3<T>::operator+(const Triangle3<T>&rhs) const noexcept
    {
        return Triangle3<T>(*this+rhs.a, *this+rhs.b, *this+rhs.c);
    }

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator+(const Trivector3<T>& b) const noexcept
    {
        return Multivector3<T>( 
            zero_v<T>, 
            x, y, z,
            zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xyz
        );
    }
    
    template <typename T>
    constexpr Vector3<T> Vector3<T>::operator+(const Vector3& b) const noexcept
    {
        return Vector3(x+b.x, y+b.y, z+b.z);
    }

    template <typename T>
    Vector3<T>& Vector3<T>::operator+=(const Vector3& b) noexcept
    {
        x += b.x;
        y += b.y;
        z += b.z;
        return *this;
    }
    
    template <typename T>
    std::vector<Vector3<T>> Vector3<T>::operator+(std::span<const Vector3>bs) const 
    {
        return transform(bs, [&](const Vector3<T>& b) -> Vector3<T> {
            return *this + b;
        });
    }

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator-(T b) const noexcept
    {
        return Multivector3<T>(
            -b, 
            x, y, z,
            zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }

    template <typename T>
    constexpr AxBox3<T> Vector3<T>::operator-(const AxBox3<T>&b) const noexcept
    {
        return AxBox3<T>(*this - b.hi, *this - b.lo);
    }

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator-(const Bivector3<T>& b) const noexcept
    {
        return Multivector3<T>( 
            zero_v<T>, 
            x, y, z,
            -b.xy, -b.yz, -b.zx,
            zero_v<T> 
        );
    }

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator-(const Multivector3<T>& b) const noexcept
    {
        return Multivector3<T>(
            -b.a, 
            x-b.x, y-b.y, z-b.z, 
            -b.xy, -b.yz, -b.zx,
            -b.xyz
        );
    }

    template <typename T>
    Polygon3<T> Vector3<T>::operator-(const Polygon3<T>&b) const
    {
        return Polygon3<T>(*this - b.vertex);
    }

    template <typename T>
    Polyline3<T> Vector3<T>::operator-(const Polyline3<T>&b) const
    {
        return Polygon3<T>(*this - b.vertex);
    }

    template <typename T>
    constexpr Segment3<T> Vector3<T>::operator-(const Segment3<T>&rhs) const noexcept
    {
        return Segment3<T>( *this - rhs.a, *this - rhs.b );
    }

    template <typename T>
    constexpr Sphere3<T> Vector3<T>::operator-(const Sphere3<T>&b) const noexcept
    {
        return Sphere3<T>(*this - b.point, b.radius);
    }

    template <typename T>
    constexpr Triangle3<T> Vector3<T>::operator-(const Triangle3<T>&rhs) const noexcept
    {
        return Triangle3<T>(*this-rhs.a, *this-rhs.b, *this-rhs.c);
    }

    template <typename T>
    constexpr Multivector3<T> Vector3<T>::operator-(const Trivector3<T>& b) const noexcept
    {
        return Multivector3<T>( 
            zero_v<T>, 
            x, y, z,
            zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xyz
        );
    }

    template <typename T>
    constexpr Vector3<T> Vector3<T>::operator-(const Vector3& b) const noexcept
    {
        return Vector3(x-b.x, y-b.y, z-b.z);
    }

    template <typename T>
    Vector3<T>& Vector3<T>::operator-=(const Vector3& b) noexcept
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }

    template <typename T>
    std::vector<Vector3<T>> Vector3<T>::operator-(std::span<const Vector3>bs) const
    {
        return transform(bs, [&](const Vector3<T>& b) -> Vector3<T> {
            return *this - b;
        });
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U>)
    constexpr Vector3<product_t<T,U>> Vector3<T>::operator*(U b) const noexcept
    {
        return Vector3<product_t<T,U>>(x*b, y*b, z*b);
    }

    template <typename T>
        template <typename U>
    requires (is_arithmetic_v<U> && self_mul_v<T,U>)
    Vector3<T>& Vector3<T>::operator*=(U b) noexcept
    {
        x *= b;
        y *= b;
        z *= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Vector1<product_t<T,U>> Vector3<T>::operator*(const Tensor31<U>&b) const noexcept
    {
        return Vector1<product_t<T,U>>(
            x*b.xx + y*b.yx + z*b.zx
        );
    }

    template <typename T>
        template <typename U>
    constexpr Vector2<product_t<T,U>> Vector3<T>::operator*(const Tensor32<U>&b) const noexcept
    {
        return Vector2<product_t<T,U>>(
            x*b.xx + y*b.yx + z*b.zx,
            x*b.xy + y*b.yy + z*b.zy
        );
    }

    template <typename T>
        template <typename U>
    constexpr Vector3<product_t<T,U>> Vector3<T>::operator*(const Tensor33<U>&b) const noexcept
    {
        return Vector3<product_t<T,U>>(
            x*b.xx + y*b.yx + z*b.zx,
            x*b.xy + y*b.yy + z*b.zy,
            x*b.xz + y*b.yz + z*b.zz
        );
    }

    template <typename T>
        template <typename U>
    constexpr Vector4<product_t<T,U>> Vector3<T>::operator*(const Tensor34<U>&b) const noexcept
    {
        return Vector4<product_t<T,U>>(
            x*b.xx + y*b.yx + z*b.zx,
            x*b.xy + y*b.yy + z*b.zy,
            x*b.xz + y*b.yz + z*b.zz,
            x*b.xw + y*b.yw + z*b.zw
        );
    }

    template <typename T>
        template <typename U>
    requires (self_mul_v<T,U>)
    Vector3<T>& Vector3<T>::operator*=(const Tensor33<U>&b) noexcept
    {
        *this   = *this * b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Multivector3<product_t<U,T>> Vector3<T>::operator*(const Vector3<U>&b) const noexcept
    {
        return Multivector3<product_t<U,T>>(
            x*b.x+y*b.y+z*b.z, 
            0., 0., 0., 
            x*b.y-y*b.x, y*b.z-z*b.y, z*b.x-x*b.z,
            0.
        );
    }

    template <typename T>
        template <typename U>
    constexpr product_t<T,U> Vector3<T>::operator DOT (const Vector3<U>&b) const noexcept
    {
        return x*b.x + y*b.y + z*b.z;
    }


    template <typename T>
        template <typename U>
    constexpr product_t<T,U> Vector3<T>::operator INNER (const Vector3<U>&b) const noexcept
    {
        return x*b.x + y*b.y + z*b.z;
    }

    template <typename T>
        template <typename U>
    constexpr Vector3<product_t<T,U>> Vector3<T>::operator CROSS (const Vector3<U>&b) const noexcept
    {
        return Vector3<product_t<T,U>>(
            y*b.z-z*b.y, 
            z*b.x-x*b.z, 
            x*b.y-y*b.x 
        );
    }

    template <typename T>
        template <typename U>
    constexpr Bivector3<product_t<T,U>> Vector3<T>::operator OUTER (const Vector3<U>& b) noexcept
    {
        return Bivector3<product_t<T,U>>( x*b.y-y*b.x, y*b.z-z*b.y, z*b.x-x*b.z );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor31<product_t<T,U>> Vector3<T>::operator OTIMES(const Vector1<U>&b) const noexcept
    {
        return Tensor31<product_t<T,U>>(
            x+b.x,
            y+b.x,
            z+b.x
        );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor32<product_t<T,U>> Vector3<T>::operator OTIMES(const Vector2<U>&b) const noexcept
    {
        return Tensor32<product_t<T,U>> (
            x+b.x, x+b.y,
            y+b.x, y+b.y,
            z+b.x, z+b.y
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor33<product_t<T,U>> Vector3<T>::operator OTIMES(const Vector3<U>&b) const noexcept
    {
        return Tensor33<product_t<T,U>>(
            x+b.x, x+b.y, x+b.z,
            y+b.x, y+b.y, y+b.z,
            z+b.x, z+b.y, z+b.z
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor34<product_t<T,U>> Vector3<T>::operator OTIMES(const Vector4<U>&b) const noexcept
    {
        return Tensor34<product_t<T,U>>(
            x+b.x, x+b.y, x+b.z, x+b.w,
            y+b.x, y+b.y, y+b.z, y+b.w,
            z+b.x, z+b.y, z+b.z, z+b.w
        );
    }

    template <typename T>
        template <typename U>
    requires (std::is_arithmetic_v<U>)
    constexpr  Vector3<quotient_t<T,U>> Vector3<T>::operator/(U b) const noexcept
    {
        return Vector3<quotient_t<T,U>>(x / b, y / b, z / b);
    }

    template <typename T>
        template <typename U>
    requires (std::is_arithmetic_v<U> && self_div_v<T,U>)
    Vector3<T>& Vector3<T>::operator/=(U b) noexcept
    {
        x /= b;
        y /= b;
        z /= b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Multivector3<quotient_t<T,U>>   Vector3<T>::operator/ (const Vector3<U>&b) const noexcept
    {
        return (*this * b) / b.length²();
    }

    template <typename T>
    constexpr AxBox3<T> Vector3<T>::operator|(const AxBox3<T>& b) const noexcept
    {
        return AxBox3<T>(UNION, { *this, b.lo, b.hi });
    }

    template <typename T>
    constexpr AxBox3<T> Vector3<T>::operator|(const Vector3&b) const noexcept
    {
        return AxBox3<T>(UNION, *this, b);
    }

    template <typename T>
    constexpr Vector3<T> Vector3<T>::all_add(T b) const noexcept
    {
        return { x+b, y+b, z+b };
    }

    template <typename T>
    Vector3<T>&    Vector3<T>::all_decrement(T b) noexcept
    {
        x -= b;
        y -= b;
        z -= b;
        return *this;
    }

    template <typename T>
    Vector3<T>&    Vector3<T>::all_increment(T b) noexcept
    {
        x += b;
        y += b;
        z += b;
        return *this;
    }
    
    template <typename T>
    constexpr Vector3<T> Vector3<T>::all_subtract(T b) const noexcept
    {
        return { x-b, y-b, z-b };
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Vector3<T>::all_test(Pred pred) const noexcept
    {
        return pred(x) && pred(y) && pred(z);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Vector3<T>::all_test(const Vector3& b, Pred pred) const noexcept
    {
        return pred(x, b.x) && pred(y, b.y) && pred(z, b.z);
    }

    template <typename T>
        template <typename Pred>
    constexpr bool Vector3<T>::all_test(T b, Pred pred) const noexcept
    {
        return pred(x, b) && pred(y, b) && pred(z, b);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Vector3<T>::any_test(Pred pred) const noexcept
    {
        return pred(x) || pred(y) || pred(z);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Vector3<T>::any_test(const Vector3& b, Pred pred) const noexcept
    {
        return pred(x, b.x) || pred(y, b.y) || pred(z, b.z);
    }
    
    template <typename T>
        template <typename Pred>
    constexpr bool Vector3<T>::any_test(T b, Pred pred) const noexcept
    {
        return pred(x, b) || pred(y, b) || pred(z, b);
    }
    
    template <typename T>
        template <typename R>
    bool Vector3<T>::close(const Vector3& expected, const R& compare) const
    {
        return compare(length(*this-expected), length(expected));
    }

    template <typename T>
    constexpr T Vector3<T>::cmax() const noexcept
    {
        return max(max(x, y), z);
    }

    template <typename T>
    constexpr T Vector3<T>::cmin() const noexcept
    {
        return min(min(x, y), z);
    }

    template <typename T>
    constexpr cube_t<T>     Vector3<T>::cproduct() const noexcept
    {
        return x*y*z;
    }
    
    template <typename T>
    constexpr T   Vector3<T>::csum() const noexcept
    {
        return x + y + z;
    }
    
    template <typename T>
    constexpr Vector3<T>   Vector3<T>::eabs() const noexcept
    {
        return Vector3<T>( abs(x), abs(y), abs(z) );
    }

    template <typename T>
        template <typename U>
    constexpr Vector3<quotient_t<T,U>>    Vector3<T>::ediv(const Vector3<U>&b) const noexcept
    {
        return Vector3<quotient_t<T,U>>( x/b.x, y/b.y, z/b.z );
    }

    template <typename T>
    constexpr Vector3<T>   Vector3<T>::emax(const Vector3&b) const noexcept
    {
        return Vector3<T>(max(x, b.x), max(y, b.y), max(z, b.z));
    }

    template <typename T>
    constexpr Vector3<T>   Vector3<T>::emin(const Vector3&b) const noexcept
    {
        return Vector3<T>(min(x, b.x), min(y, b.y), min(z, b.z));
    }    

    template <typename T>
        template <typename U>
    constexpr Vector3<product_t<T,U>>    Vector3<T>::emul(const Vector3<U>&b) const noexcept
    {
        return Vector3<product_t<T,U>>(x*b.x, y*b.y, z*b.z);
    }

    template <typename T>
    constexpr square_t<T> Vector3<T>::length²() const noexcept
    {
        return x*x + y*y + z*z;
    }    
    
    template <typename T>
    T       Vector3<T>::length() const
    {
        if constexpr (has_sqrt_v<square_t<T>>)
            return sqrt(length²());
        return zero_v<T>;
    }

    template <typename T>
    Vector2<T>  Vector3<T>::xy() const
    {
        return Vector2<T>(x,y);
    }

    template <typename T>
    Vector2<T>  Vector3<T>::yz() const
    {
        return Vector2<T>(y,z);
    }

    template <typename T>
    Vector2<T>  Vector3<T>::zx() const
    {
        return Vector2<T>(z,x);
    }


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    template <typename T>
    constexpr Multivector3<T> operator+(T a, const Vector3<T>& b) noexcept
    {
        return Multivector3<T>(
            a, 
            b.x, b.y, b.z, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }

    template <typename T>
    std::vector<Vector3<T>>   operator+(std::span<Vector3<T>>as, Vector3<T>b)
    {
        return transform(as, [&](const Vector3<T>&a) -> Vector3<T> {
            return a + b;
        });
    }

    template <typename T>
    constexpr Multivector3<T> operator-(T a, const Vector3<T>& b) noexcept
    {
        return Multivector3<T>(
            a, 
            -b.x, -b.y, -b.z, 
            zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }

    template <typename T>
    std::vector<Vector3<T>>   operator-(std::span<Vector3<T>>as, Vector3<T>b)
    {
        return transform(as, [&](const Vector3<T>&a) -> Vector3<T> {
            return a - b;
        });
    }


    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    constexpr Vector3<product_t<T,U>> operator*(T a, const Vector3<U>&b) noexcept
    {
        return Vector3<product_t<T,U>>(a*b.x, a*b.y, a*b.z);
    }

    template <typename T, typename U>
    requires (is_arithmetic_v<T>)
    std::vector<Vector3<product_t<T,U>>>   operator*(T a, std::span<Vector3<U>>bs)
    {
        return transform(bs, [&](const Vector3<U>&b) -> Vector3<product_t<T,U>> {
            return a * b;
        });
    }

    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector3<product_t<T,U>>>   operator*(std::span<Vector3<T>>as, U b)
    {
        return transform(as, [&](const Vector3<T>&a) -> Vector3<product_t<T,U>> {
            return a * b;
        });
    }

    template <typename T, typename U>
    std::vector<Vector1<product_t<T,U>>> operator*(std::span<const Vector3<T>>as, const Tensor31<U>&b)
    {
        return transform(as, [&](const Vector3<T>&v) -> Vector1<product_t<T,U>>{
            return v * b;
        });
    }
    
    template <typename T, typename U>
    std::vector<Vector2<product_t<T,U>>> operator*(std::span<const Vector3<T>>as, const Tensor32<U>&b)
    {
        return transform(as, [&](const Vector3<T>&v) -> Vector2<product_t<T,U>>{
            return v * b;
        });
    }

    template <typename T, typename U>
    std::vector<Vector3<product_t<T,U>>> operator*(std::span<const Vector3<T>>as, const Tensor33<U>&b)
    {
        return transform(as, [&](const Vector3<T>&v) -> Vector3<product_t<T,U>>{
            return v * b;
        });
    }
    
    template <typename T, typename U>
    std::vector<Vector4<product_t<T,U>>> operator*(std::span<const Vector3<T>>as, const Tensor34<U>&b)
    {
        return transform(as, [&](const Vector3<T>&v) -> Vector4<product_t<T,U>>{
            return v * b;
        });
    }

    template <typename T, typename U>
    requires (std::is_arithmetic_v<T>)
    constexpr  Vector3<quotient_t<T,U>> operator/(T a, const  Vector3<U>&b) noexcept
    {
        return (a*b) / b.length²();
    }

    template <typename T, typename U>
    requires (is_arithmetic_v<U>)
    std::vector<Vector3<quotient_t<T,U>>>   operator/(std::span<Vector3<T>>as, U b)
    {
        return transform(as, [&](const Vector3<T>&a) -> Vector3<quotient_t<T,U>> {
            return a / b;
        });
    }

    template <typename T>
    constexpr Vector3<T>   abs_elem(const Vector3<T>&a) noexcept
    {
        return a.eabs();
    }


    template <typename T>
    AllComponents<Vector3<T>>   all(Vector3<T>& val)
    {
        return { val };
    }
    
    template <typename T>
    AllComponents<const Vector3<T>>   all(const Vector3<T>& val)
    {
        return { val };
    }

    template <typename T>
    requires (std::is_floating_point_v<T> && has_sqrt_v<T>)
    Radian              angle(const Vector3<T>&a, const Vector3<T>& b)
    {
        return acos( std::clamp<T>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }
    
    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && has_sqrt_v<T>)
    Radian             angle(const Vector3<MKS<T,DIM1>>&a, const Vector3<MKS<T,DIM2>>& b)
    {
        using one_t = MKS<T,dim::None>;
        return acos( std::clamp<one_t>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }

    template <typename T>
    AnyComponents<Vector3<T>>   any(Vector3<T>& val)
    {
        return { val };
    }

    template <typename T>
    AnyComponents<const Vector3<T>>   any(const Vector3<T>& val)
    {
        return { val };
    }

    inline  Vector3D    ccw(Radian az, Radian el)
    {
        double  c  = cos(el);
        return Vector3D( c*cos(az), c*sin(az), sin(el) );
    }
    
    template <typename T>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector3<T>& a)
    {
        return atan(a.y, a.x);
    }

    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector3<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }

    inline Vector3D     clockwise(Radian az, Radian el)
    {
        double  c  = cos(el);
        return Vector3D(  c*sin(az), c*cos(az), sin(el) );
    }
    

    template <typename T>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector3<T>& a)
    {
        return atan(a.y, a.x);
    }

    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector3<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }

    template <typename T>
    constexpr T             component_max(const Vector3<T>&a) noexcept
    {
        return a.cmax();
    }

    template <typename T>
    constexpr T             component_min(const Vector3<T>&a) noexcept
    {
        return a.cmin();
    }

    template <typename T>
    constexpr cube_t<T>       component_product(const Vector3<T>& a) noexcept
    {
        return a.cproduct();
    }
    
    template <typename T>
    constexpr T   component_sum(const Vector3<T>& a) noexcept
    {
        return a.csum();
    }

    #if 0
    template <typename T>
    ElemComponents<Vector3<T>>   elem(Vector3<T>& val)
    {
        return { val };
    }

    template <typename T>
    ElemComponents<const Vector3<T>>   elem(const Vector3<T>& val)
    {
        return { val };
    }
    #endif

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector3<T>& actual, const Vector3<T>& expected)
    {
        return compare(length(actual-expected), expected.length());
    }
    
    template <typename T, typename R>
    bool is_close(const R& compare, const Vector3<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y, std::type_identity_t<T> z)
    {
        return is_close(compare, actual, Vector3<T>(x, y, z) );
    }

    template <typename T>
    constexpr square_t<T> length²(const Vector3<T>& a) noexcept
    {
        return a.length²();
    }    
    
    template <typename T>
    T       length(const Vector3<T>& a)
    {
        return a.length();
    }
    
    template <typename T>
    constexpr Vector3<T>   max_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept
    {
        return a.emax(b);
    }

    template <typename T>
    constexpr Vector3<T>   max_elem(std::initializer_list<Vector3<T>> vs) noexcept
    {
        return max_elem(std::span<const Vector3<T>>(vs.data(), vs.size()));
    }

    template <typename T>
    constexpr Vector3<T>   max_elem(std::span<const Vector3<T>>vs) noexcept
    {
        if(vs.empty())
            return Vector3<T>(NAN);
        return Vector3<T>(
            std::max_element(vs.begin(), vs.end(), Vector3<T>::less_x) -> x,
            std::max_element(vs.begin(), vs.end(), Vector3<T>::less_y) -> y,
            std::max_element(vs.begin(), vs.end(), Vector3<T>::less_z) -> z
        );
    }

    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr Vector3<T>     midvector(const Vector3<T>& a, const Vector3<T>& b) noexcept
    {
        if constexpr (has_ieee754_v<T>)
            return ieee754_t<T>(0.5)*(a+b);
        else if constexpr (std::is_integral_v<T>)
            return (a+b) / T(2);
        else
            return Vector3<T>(ZERO);
    }

    template <typename T>
    constexpr Vector3<T>   min_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept
    {
        return a.emin(b);
    }    

    template <typename T>
    constexpr Vector3<T>   min_elem(std::initializer_list<Vector3<T>>vs) noexcept
    {
        return min_elem(std::span<const Vector3<T>>(vs.data(), vs.size()));
    }

    template <typename T>
    constexpr Vector3<T>   min_elem(std::span<const Vector3<T>>vs) noexcept
    {
        if(vs.empty())
            return Vector3<T>(NAN);
        return Vector3<T>(
            std::min_element(vs.begin(), vs.end(), Vector3<T>::less_x) -> x,
            std::min_element(vs.begin(), vs.end(), Vector3<T>::less_y) -> y,
            std::min_element(vs.begin(), vs.end(), Vector3<T>::less_z) -> z
        );
    }

    template <typename T, typename U>
    constexpr Vector3<product_t<T,U>>    mul_elem(const Vector3<T>&a, const Vector3<T>&b) noexcept
    {
        return a.emul(b);
    }

    template <typename T>
    constexpr Vector2<T> xy( const Vector3<T>& a) noexcept
    {
        return Vector2<T>( a.x, a.y );
    }

    template <typename T>
    constexpr Vector3<T> xy( const Vector2<T>& a, std::type_identity_t<T> z) noexcept
    {
        return Vector3<T>( a.x, a.y, z );
    }


    template <typename S, typename T>
    S&  as_stream(S& s, const Vector3<T>& v)
    {
        return s << "(" << v.x << "," << v.y << "," << v.z << ")";
    }
    
    template <typename T>
    Stream& operator<<(Stream&s, const Vector3<T>& v)
    {
        return as_stream(s, v);
    }

    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const Vector3<T>& v)
    {
        return as_stream(s, v);
    }
}
