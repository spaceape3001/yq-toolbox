////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the vector4 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include <math/AxBox4.hpp>
#include <math/Bivector4.hpp>
#include <math/Multivector4.hpp>
#include <math/Quadvector4.hpp>
#include <math/Segment4.hpp>
#include <math/Trivector4.hpp>

#include <math/Tensor41.hpp>
#include <math/Tensor42.hpp>
#include <math/Tensor43.hpp>
#include <math/Tensor44.hpp>

#include <math/Vector1.hpp>
#include <math/Vector2.hpp>
#include <math/Vector3.hpp>
#include <math/Vector4.hpp>

#include <math/trig.hpp>
#include <math/Units.hpp>

namespace yq {
    template <typename T>
    constexpr Vector4<T>::operator glm::vec<4, T, glm::defaultp>() const noexcept
    {
        return glm::vec<4, T, glm::defaultp>( x, y, z, w );
    }

    template <typename T>
    constexpr Vector4<T> Vector4<T>::operator-() const noexcept
    {
        return Vector4(-x,-y,-z,-w);
    }

    template <typename T>
    Vector4<quotient_t<T,T>> Vector4<T>::operator~() const
    {
        auto l = one_v<T>/length();
        return Vector4(x*l, y*l, z*l, w*l);
    }

    template <typename T>
    constexpr square_t<T> Vector4<T>::operator^(two_t) const noexcept
    {
        return x*x + y*y + z*z + w*w;
    }    

    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator+(T b) const noexcept
    {
        return Multivector4<T>(
            b, 
            x, y, z, w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }

    template <typename T>
    constexpr AxBox4<T> Vector4<T>::operator+(const AxBox4<T>&b) const noexcept
    {
        return AxBox4<T>(*this + b.lo, *this + b.hi);
    }

    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator+(const Bivector4<T>&b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            x, y, z, w, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }

    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator+(const Multivector4<T>&b) const noexcept
    {
        return Multivector4<T>(
            b.a, 
            x+b.x, y+b.y, z+b.z, w+b.w, 
            b.xy, b.yz, b.zw, b.wx, b.xz, b.yw,
            b.xyz, b.yzw, b.zwx, b.wxy,
            b.xyzw
        );
    }

    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator+(const Quadvector4<T>&b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            x, y, z, w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xyzw
        );
    }

    template <typename T>
    constexpr Segment4<T> Vector4<T>::operator+(const Segment4<T>&rhs) const noexcept
    {
        return Segment4<T>( *this + rhs.a, *this + rhs.b );
    }

    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator+(const Trivector4<T>&b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            x, y, z, w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            b.xyz, b.yzw, b.zwx, b.wxy,
            zero_v<T> 
        );
    }

    template <typename T>
    constexpr Vector4<T> Vector4<T>::operator+(const Vector4& b) const noexcept
    {
        return Vector4(x+b.x, y+b.y, z+b.z, w+b.w);
    }

    template <typename T>
    Vector4<T>& Vector4<T>::operator+=(const Vector4& b) noexcept
    {
        x += b.x;
        y += b.y;
        z += b.z;
        w += b.w;
        return *this;
    }


    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator-(T b) const noexcept
    {
        return Multivector4<T>( 
            -b, 
            x, y, z, w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }

    template <typename T>
    constexpr AxBox4<T> Vector4<T>::operator-(const AxBox4<T>&b) const noexcept
    {
        return AxBox4<T>(*this - b.hi, *this - b.lo);
    }

    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator-(const Bivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            x, y, z, w, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        );
    }

    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator-(const Multivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            -b.a, 
            x-b.x, y-b.y, z-b.z, w-b.w, 
            -b.xy, -b.yz, -b.zw, -b.wx, -b.xz, -b.yw,
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            -b.xyzw
        );
    }

    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator-(const Quadvector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            x, y, z, w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xyzw
        );
    }

    template <typename T>
    constexpr Segment4<T> Vector4<T>::operator-(const Segment4<T>&rhs) const noexcept
    {
        return Segment4<T>( *this - rhs.a, *this - rhs.b );
    }

    template <typename T>
    constexpr Multivector4<T> Vector4<T>::operator-( const Trivector4<T>& b) const noexcept
    {
        return Multivector4<T>(
            zero_v<T>, 
            x, y, z, w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            -b.xyz, -b.yzw, -b.zwx, -b.wxy,
            zero_v<T> 
        );
    }    


    template <typename T>
    constexpr Vector4<T> Vector4<T>::operator-(const Vector4& b) const noexcept
    {
        return Vector4(x-b.x, y-b.y, z-b.z, w-b.w);
    }
    
    template <typename T>
    Vector4<T>& Vector4<T>::operator-=(const Vector4& b) noexcept
    {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        w -= b.w;
        return *this;
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U>)
    constexpr Vector4<product_t<T,U>> Vector4<T>::operator*(U b) const noexcept
    {
        return Vector4<product_t<T,U>>(x*b, y*b, z*b, w*b);
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Vector4<T>& Vector4<T>::operator*=(U b) noexcept
    {
        x *= b;
        y *= b;
        z *= b;
        w *= b;
        return *this;
    }


    template <typename T>
        template <typename U>
    constexpr Vector1<product_t<T,U>> Vector4<T>::operator*(const Tensor41<U>&b) const noexcept
    {
        return Vector1<product_t<T,U>>(
            x*b.xx + y*b.yx + z*b.zx + w*b.wx
        );
    }

    template <typename T>   
        template <typename U>
    constexpr Vector2<product_t<T,U>> Vector4<T>::operator*(const Tensor42<U>&b) const noexcept
    {
        return Vector2<product_t<T,U>>(
            x*b.xx + y*b.yx + z*b.zx + w*b.wx,
            x*b.xy + y*b.yy + z*b.zy + w*b.wy
        );
    }

    template <typename T>
        template <typename U>
    constexpr Vector3<product_t<T,U>> Vector4<T>::operator*(const Tensor43<U>&b) const noexcept
    {
        return Vector3<product_t<T,U>>(
            x*b.xx + y*b.yx + z*b.zx + w*b.wx,
            x*b.xy + y*b.yy + z*b.zy + w*b.wy,
            x*b.xz + y*b.yz + z*b.zz + w*b.wz
        );
    }

    template <typename T>
        template <typename U>
    constexpr Vector4<product_t<T,U>> Vector4<T>::operator*(const Tensor44<U>&b) const noexcept
    {
        return Vector4<product_t<T,U>>(
            x*b.xx + y*b.yx + z*b.zx + w*b.wx,
            x*b.xy + y*b.yy + z*b.zy + w*b.wy,
            x*b.xz + y*b.yz + z*b.zz + w*b.wz,
            x*b.xw + y*b.yw + z*b.zw + w*b.ww
        );
    }

    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Vector4<T>& Vector4<T>::operator*=(const Tensor44<U>& b) noexcept
    {
        *this = *this * b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Multivector4<product_t<T,U>>   Vector4<T>::operator*(const Vector4<U>&b) const noexcept
    {
        return {
            x*b.x+y*b.y+z*b.z+w*b.w, 0., 0., 0., 0.,
            x*b.y-y*b.x, y*b.z-z*b.y, z*b.w-w*b.z, w*b.x-x*b.w, x*b.z-z*b.x, y*b.w-w*b.y,
            0., 0., 0., 0., 0.
        };
    }

    template <typename T>
        template<typename U>
    constexpr product_t<T,U> Vector4<T>::operator DOT (const Vector4<U>&b) const noexcept
    {
        return x*b.x + y*b.y + z*b.z + w*b.w;
    }


    template <typename T>
        template<typename U>
    constexpr product_t<T,U> Vector4<T>::operator INNER (const Vector4<U>&b) const noexcept
    {
        return x*b.x + y*b.y + z*b.z + w*b.w;
    }

    template <typename T>
        template <typename U>
    constexpr Bivector4<product_t<T,U>> Vector4<T>::operator OUTER(const Vector4<U>&b) const noexcept
    {
        return { x*b.y-y*b.x, y*b.z-z*b.y, z*b.w-w*b.z, w*b.x-x*b.w, x*b.z-z*b.x, y*b.w-w*b.y };
    }

    template <typename T>
        template <typename U>
    constexpr Tensor41<product_t<T,U>> Vector4<T>::operator OTIMES(const Vector1<U>&b) const noexcept
    {
        return Tensor41<product_t<T,U>>(
            x+b.x,
            y+b.x,
            z+b.x,
            w+b.x
        );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor42<product_t<T,U>> Vector4<T>::operator OTIMES(const Vector2<U>&b) const noexcept
    {
        return Tensor42<product_t<T,U>>(
            x+b.x, x+b.y,
            y+b.x, y+b.y,
            z+b.x, z+b.y,
            w+b.x, w+b.y
        );
    }
    
    template <typename T>
        template <typename U>
    constexpr Tensor43<product_t<T,U>> Vector4<T>::operator OTIMES(const Vector3<U>&b) const noexcept
    {
        return Tensor43<product_t<T,U>>(
            x+b.x, x+b.y, x+b.z,
            y+b.x, y+b.y, y+b.z,
            z+b.x, z+b.y, z+b.z,
            w+b.x, w+b.y, w+b.z
        );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor44<product_t<T,U>> Vector4<T>::operator OTIMES(const Vector4<U>&b) const noexcept
    {
        return Tensor44<product_t<T,U>>(
            x+b.x, x+b.y, x+b.z, x+b.w,
            y+b.x, y+b.y, y+b.z, y+b.w,
            z+b.x, z+b.y, z+b.z, z+b.w,
            w+b.x, w+b.y, w+b.z, w+b.w
        );
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U>)
    constexpr  Vector4<quotient_t<T,U>> Vector4<T>::operator/(U b) const noexcept
    {
        return Vector4<quotient_t<T,U>>(x / b, y / b, z / b, w / b);
    }
    
    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Vector4<T>& Vector4<T>::operator/=(U b) noexcept
    {
        x /= b;
        y /= b;
        z /= b;
        w /= b;
        return *this;
    }

    /*! Vector/vector division
    
        Yes, legal in geometric algebra!
    */
    template <typename T>
        template <typename U>
    constexpr Multivector4<quotient_t<T,U>>   Vector4<T>::operator/ (const Vector4<U>&b) const noexcept
    {
        return (*this * b) / b.length²();
    }

    template <typename T>
    constexpr AxBox4<T> Vector4<T>::operator|(const AxBox4<T>&b) const noexcept
    {
        return AxBox4<T>(UNION, {*this, b.lo, b.hi});
    }

    template <typename T>
    constexpr AxBox4<T> Vector4<T>::operator|(const Vector4&b) const noexcept
    {
        return AxBox4<T>(UNION, *this, b);
    }
    
    template <typename T>
    constexpr Vector4<T> Vector4<T>::all_add(T b) const noexcept
    {
        return Vector4( x+b, y+b, z+b, w+b );
    }
    
    template <typename T>
    constexpr Vector4<T> Vector4<T>::all_subtract(T b) const noexcept
    {
        return Vector4( x-b, y-b, z-b, w-b );
    }

    template <typename T>
    constexpr T     Vector4<T>::cmax() const noexcept
    {
        return max(max(x, y), max(z, w));
    }

    template <typename T>
    constexpr T     Vector4<T>::cmin() const noexcept
    {
        return min(min(x, y), min(z, w));
    }

    template <typename T>
    constexpr fourth_t<T>   Vector4<T>::cproduct() const noexcept
    {
        return x*y*z*w;
    }

    template <typename T>
    constexpr T             Vector4<T>::csum() const noexcept
    {
        return x + y + z + w;
    }

    template <typename T>
    constexpr Vector4<T>   Vector4<T>::eabs() const noexcept
    {
        return Vector4( abs(x), abs(y), abs(z), abs(w) );
    }

    template <typename T>
        template <typename U>
    constexpr Vector4<quotient_t<T,U>>  Vector4<T>::ediv(const Vector4<U>&b) const noexcept
    {
        return Vector4<quotient_t<T,U>>(x/b.x, y/b.y, z/b.z, w/b.w);
    }

    template <typename T>
    constexpr Vector4<T>   Vector4<T>::emax(const Vector4&b) const noexcept
    {
        return Vector4(max(x, b.x), max(y, b.y), max(z, b.z), max(w, b.w));
    }
    
    template <typename T>
    constexpr Vector4<T>   Vector4<T>::emin(const Vector4&b) const noexcept
    {
        return Vector4(min(x, b.x), min(y, b.y), min(z, b.z), min(w, b.w));
    }

    template <typename T>
        template <typename U>
    constexpr Vector4<product_t<T,U>>   Vector4<T>::emul(const Vector4<U>&b) const noexcept
    {
        return {x*b.x, y*b.y, z*b.z, w*b.w};
    }
        
    template <typename T>
    constexpr square_t<T> Vector4<T>::length²() const noexcept
    {
        return x*x + y*y + z*z + w*w;
    }    

    template <typename T>
    T    Vector4<T>::length() const
    {
        if constexpr (trait::has_sqrt_v<T>)
            return sqrt(length²());
        return {};
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    

    template <typename T>
    constexpr Multivector4<T> operator-(T a, const Vector4<T>& b) noexcept
    {
        return { 
            a, 
            -b.x, -b.y, -b.z, -b.w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        };
    }

    template <typename T>
    constexpr Multivector4<T> operator+(T a, const Vector4<T>& b) noexcept
    {
        return { 
            a, 
            b.x, b.y, b.z, b.w, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T>, zero_v<T>, zero_v<T>, zero_v<T>, 
            zero_v<T> 
        };
    }


    template <typename T, typename U>
    requires (trait::is_arithmetic_v<T>)
    constexpr Vector4<product_t<T,U>> operator*(T a, const Vector4<U>&b) noexcept
    {
        return Vector4<product_t<T,U>>(a*b.x, a*b.y, a*b.z, a*b.w);
    }
    
    template <typename T, typename U>
    requires (trait::is_arithmetic_v<T>)
    constexpr  Vector4<quotient_t<T,U>> operator/(T a, const  Vector4<U>&b) noexcept
    {
        return (a*b) / b.length²();
    }

    
    template <typename T>
    constexpr Vector4<T>   abs_elem(const Vector4<T>&a) noexcept
    {
        return a.eabs();
    }


    template <typename T>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian       angle(const Vector4<T>&a, const Vector4<T>& b)
    {
        return acos( std::clamp<T>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }
    
    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian       angle(const Vector4<MKS<T,DIM1>>&a, const Vector4<MKS<T,DIM2>>& b)
    {
        using one_t = MKS<T,dim::None>;
        return acos( std::clamp<one_t>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }

    template <typename T>
    constexpr T             component_max(const Vector4<T>&a) noexcept
    {
        return a.cmax();
    }

    template <typename T>
    constexpr T             component_min(const Vector4<T>&a) noexcept
    {
        return a.cmin();
    }

    template <typename T>
    constexpr fourth_t<T>     component_product(const Vector4<T>& a) noexcept
    {
        return a.cproduct();
    }

    template <typename T>
    constexpr T   component_sum(const Vector4<T>& a) noexcept
    {
        return a.csum();
    }
    
    template <typename T, typename U>
    constexpr Vector4<quotient_t<T,U>>    div_elem(const Vector4<T>&a, const Vector4<U>&b) noexcept
    {
        return a.ediv(b);
    }


    template <typename T, typename R>
    bool is_close(const R& compare, const Vector4<T>& actual, const Vector4<T>& expected)
    {
        return compare(length(actual-expected), length(expected));
    }
    
    template <typename T, typename R>
    bool is_close(const R& compare, const Vector4<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y, std::type_identity_t<T> z,std::type_identity_t<T>w)
    {
        return is_close(compare, actual, Vector4<T>(x, y, z, w) );
    }

    template <typename T>
    constexpr square_t<T> length²(const Vector4<T>& a) noexcept
    {
        return a.length²();
    }    

    template <typename T>
    auto    length(const Vector4<T>& a)
    {
        return a.length();
    }
    
    template <typename T>
    constexpr Vector4<T>   max_elem(const Vector4<T>&a, const Vector4<T>&b) noexcept
    {
        return a.emax(b);
    }
    
    template <typename T>
    constexpr Vector4<T>   min_elem(const Vector4<T>&a, const Vector4<T>&b) noexcept
    {
        return a.emin(b);
    }

    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr Vector4<T>    midvector(const Vector4<T>& a, const Vector4<T>& b) noexcept
    {
        if constexpr (has_ieee754_v<T>)
            return ieee754_t<T>(0.5)*(a+b);
        else if constexpr (std::is_integral_v<T>)
            return (a+b) / T(2);
        else
            return {};
    }
    
    template <typename T, typename U>
    constexpr Vector4<product_t<T,U>>    mul_elem(const Vector4<T>&a, const Vector4<T>&b) noexcept
    {
        return a.emul(b);
    }


}

