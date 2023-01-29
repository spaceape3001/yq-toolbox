////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

/* 
    This is the template IMPLEMENTATION of the vector2 code.  Include this
    *IF* you need the operator and it's not yet available as explicit 
    template instantiation.  
*/

#include "Bivector2.hpp"
#include "Multivector2.hpp"

#include <math/Tensor21.hpp>
#include <math/Tensor22.hpp>
#include <math/Tensor23.hpp>
#include <math/Tensor24.hpp>

#include <math/Vector1.hpp>
#include <math/Vector2.hpp>
#include <math/Vector3.hpp>
#include <math/Vector4.hpp>

#include <math/trig.hpp>
#include <math/Units.hpp>


namespace yq {
    template <typename T>
    constexpr Vector2<T>::operator glm::vec<2, T, glm::defaultp>() const noexcept
    {
        return glm::vec<2, T, glm::defaultp>( x, y );
    }

    //! Negation (negative) operator
    template <typename T>
    constexpr Vector2<T> Vector2<T>::operator-() const noexcept
    {
        return Vector2(-x,-y);
    }

    template <typename T>
    Vector2<quotient_t<T,T>> Vector2<T>::operator~() const
    {
        auto l = one_v<T>/length();
        return Vector2<quotient_t<T,T>>(x*l, y*l);
    }

    template <typename T>
    constexpr square_t<T> Vector2<T>::operator^(two_t) const noexcept
    {
        return x*x + y*y;
    }    

    template <typename T>
    constexpr Multivector2<T> Vector2<T>::operator+(T b) const noexcept
    {
        return Multivector2<T>(
            b, 
            x, y, 
            {} 
        );
    }
    
    template <typename T>
    constexpr Multivector2<T> Vector2<T>::operator+(const Bivector2<T>& b) const noexcept
    {
        return Multivector2<T>(
            {}, 
            x, y, 
            b.xy 
        );
    }
    
    template <typename T>
    constexpr Multivector2<T> Vector2<T>::operator+(const Multivector2<T>& b) const noexcept
    {
        return Multivector2<T>(
            b.a, 
            x+b.x, y+b.y,
            b.xy
        );
    }


    template <typename T>
    constexpr Vector2<T> Vector2<T>::operator+(const Vector2& b) const noexcept
    {
        return Vector2(x+b.x, y+b.y);
    }
    
    template <typename T>
    Vector2<T>& Vector2<T>::operator+=(const Vector2& b) noexcept
    {
        x += b.x;
        y += b.y;
        return *this;
    }

    template <typename T>
    constexpr Multivector2<T> Vector2<T>::operator-(T b) const noexcept
    {
        return { 
            -b, 
            x, y, 
            {} 
        };
    }
    
    template <typename T>
    constexpr Multivector2<T> Vector2<T>::operator-(const Bivector2<T>& b) const noexcept
    {
        return { 
            {}, 
            x, y, 
            -b.xy 
        };
    }
    
    template <typename T>
    constexpr Multivector2<T> Vector2<T>::operator-(const Multivector2<T>& b) const noexcept
    {
        return { 
            -b.a, 
            x-b.x, y-b.y,
            -b.xy
        };
    }

    template <typename T>
    constexpr Vector2<T> Vector2<T>::operator-(const Vector2& b) const noexcept
    {
        return Vector2(x-b.x, y-b.y);
    }

    template <typename T>
    Vector2<T>& Vector2<T>::operator-=(const Vector2& b) noexcept
    {
        x -= b.x;
        y -= b.y;
        return *this;
    }


    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U>)
    constexpr Vector2<product_t<T,U>> Vector2<T>::operator*(U b) const noexcept
    {
        return Vector2<product_t<T,U>>(x*b, y*b);
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
    Vector2<T>& Vector2<T>::operator*=(U b) noexcept
    {
        x *= b;
        y *= b;
        return *this;
    }
    
    template <typename T>
        template <typename U>
    constexpr Vector1<product_t<T,U>> Vector2<T>::operator*(const Tensor21<U>&b) const noexcept
    {
        return Vector1<product_t<T,U>>(
            x*b.xx + y*b.yx
        );
    }

    template <typename T>
        template <typename U>
    constexpr Vector2<product_t<T,U>> Vector2<T>::operator*(const Tensor22<U>&b) const noexcept
    {
        return Vector2<product_t<T,U>>(
            x*b.xx + y*b.yx,
            x*b.xy + y*b.yy
        );
    }

    template <typename T>
        template <typename U>
    requires trait::self_mul_v<T,U>
    Vector2<T>&  Vector2<T>::operator*=(const Tensor22<U>&b) noexcept
    {
        *this = *this * b;
        return *this;
    }

    template <typename T>
        template <typename U>
    constexpr Vector3<product_t<T,U>> Vector2<T>::operator*(const Tensor23<U>&b) const noexcept
    {
        return Vector3<product_t<T,U>>(
            x*b.xx + y*b.yx,
            x*b.xy + y*b.yy,
            x*b.xz + y*b.yz
        );
    }

    template <typename T>
        template <typename U>
    constexpr Vector4<product_t<T,U>> Vector2<T>::operator*(const Tensor24<U>&b) const noexcept
    {
        return Vector4<product_t<T,U>>(
            x*b.xx + y*b.yx,
            x*b.xy + y*b.yy,
            x*b.xz + y*b.yz,
            x*b.xw + y*b.yw
        );
    }


    template <typename T>
        template <typename U>
    constexpr Multivector2<product_t<T,U>> Vector2<T>::operator*(const Vector2<U>&b) const noexcept
    {
        return Multivector2<product_t<T,U>>( x*b.x+y*b.y, 0., 0., x*b.y-y*b.x );
    }

    template <typename T>
        template <typename U>
    constexpr product_t<T,U> Vector2<T>::operator DOT (const Vector2<U>&b) const noexcept
    {
        return x*b.x + y*b.y;
    }

    template <typename T>
        template <typename U>
    constexpr product_t<T,U> Vector2<T>::operator CROSS (const Vector2<U>&b) const noexcept
    {
        return x*b.y-y*b.x;
    }

    template <typename T>
        template <typename U>
    constexpr product_t<T,U> Vector2<T>::operator INNER (const Vector2<U>&b) const noexcept
    {
        return x*b.x + y*b.y;
    }

    template <typename T>
        template <typename U>
    constexpr Bivector2<product_t<T,U>> Vector2<T>::operator OUTER (const Vector2<U>& b) const noexcept
    {
        return Bivector2<product_t<T,U>>( x*b.y-y*b.x );
    }


    template <typename T>
        template <typename U>
    constexpr Tensor21<product_t<T,U>> Vector2<T>::operator OTIMES(const Vector1<U>&b) const noexcept
    {
        return Tensor21<product_t<T,U>>(
            x+b.x,
            y+b.x
        );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor22<product_t<T,U>> Vector2<T>::operator OTIMES(const Vector2<U>&b) const noexcept
    {
        return Tensor22<product_t<T,U>>(
            x+b.x, x+b.y,
            y+b.x, y+b.y
        );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor23<product_t<T,U>> Vector2<T>::operator OTIMES(const Vector3<U>&b) const noexcept
    {
        return Tensor23<product_t<T,U>>(
            x+b.x, x+b.y, x+b.z,
            y+b.x, y+b.y, y+b.z
        );
    }

    template <typename T>
        template <typename U>
    constexpr Tensor24<product_t<T,U>> Vector2<T>::operator OTIMES(const Vector4<U>&b) const noexcept
    {
        return Tensor24<product_t<T,U>>(
            x+b.x, x+b.y, x+b.z, x+b.w,
            y+b.x, y+b.y, y+b.z, y+b.w
        );
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U>)
    constexpr  Vector2<quotient_t<T,U>> Vector2<T>::operator/(U b) const noexcept
    {
        return Vector2<product_t<T,U>>(x / b, y / b);
    }

    template <typename T>
        template <typename U>
    requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
    Vector2<T>& Vector2<T>::operator/=(U b) noexcept
    {
        x /= b;
        y /= b;
        return *this;
    }

    //! Division of left vector by the right
    template <typename T>
        template <typename U>
    constexpr Multivector2<quotient_t<T,U>>   Vector2<T>::operator/ (const Vector2<U>&b) const noexcept
    {
        return (*this * b) / b.length²();
    }

    //! Union
    template <typename T>
    constexpr AxBox2<T> Vector2<T>::operator|(const AxBox2<T>&b) const noexcept
    {
        return AxBox2<T>(UNION, {*this, b.lo, b.hi});
    }

    template <typename T>
    constexpr AxBox2<T> Vector2<T>::operator|(const Vector2&b) const noexcept
    {
        return AxBox2<T>(UNION, *this, b);
    }

    template <typename T>
    constexpr Vector2<T> Vector2<T>::all_add(T b) const noexcept
    {
        return Vector2( x+b, y+b );
    }
    
    template <typename T>
    constexpr Vector2<T> Vector2<T>::all_subtract(T b) const noexcept
    {
        return Vector2( x-b, x-b );
    }

    template <typename T>
    constexpr T     Vector2<T>::cmax() const noexcept
    {
        return max(x, y);
    }

    template <typename T>
    constexpr T     Vector2<T>::cmin() const noexcept
    {
        return min(x, y);
    }

    template <typename T>
    constexpr square_t<T>     Vector2<T>::cproduct() const noexcept
    {
        return x*y;
    }

    template <typename T>
    constexpr T   Vector2<T>::csum() const noexcept
    {
        return x + y;
    }

    template <typename T>
    constexpr Vector2<T>   Vector2<T>::eabs() const noexcept
    {
        return Vector2( abs(x), abs(y) );
    }

    template <typename T>
        template <typename U>
    constexpr Vector2<quotient_t<T,U>>    Vector2<T>::ediv(const Vector2<U>&b) const noexcept
    {
        return Vector2<quotient_t<T,U>>(x/b.x, y/b.y);
    }

    template <typename T>
    constexpr Vector2<T>   Vector2<T>::emax(const Vector2&b) const noexcept
    {
        return Vector2(max(x, b.x), max(y, b.y));
    }

    template <typename T>
    constexpr Vector2<T>   Vector2<T>::emax(T b) const noexcept
    {
        return Vector2(max(x, b), max(y, b));
    }

    template <typename T>
    constexpr Vector2<T>   Vector2<T>::emin(const Vector2&b) const noexcept
    {
        return Vector2(min(x, b.x), min(y, b.y));
    }

    template <typename T>
    constexpr Vector2<T>   Vector2<T>::emin(T b) const noexcept
    {
        return Vector2(min(x, b), min(y, b));
    }

    template <typename T>
        template <typename U>
    constexpr Vector2<product_t<T,U>>    Vector2<T>::emul(const Vector2<U>&b) const noexcept
    {
        return Vector2<product_t<T,U>>(x*b.x, y*b.y);
    }

    template <typename T>
    constexpr square_t<T> Vector2<T>::length²() const noexcept
    {
        return x*x + y*y;
    }    
    
    template <typename T>
    T       Vector2<T>::length() const
    {
        if constexpr (trait::has_sqrt_v<square_t<T>>)
            return sqrt(length²());
        return {};
    }

    template <typename T>
    constexpr Vector3<T> Vector2<T>::z(T _z) const noexcept
    {
        return Vector3<T>( x, y, _z );
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    //! Adds scalar with vector
    template <typename T>
    constexpr Multivector2<T> operator+(T a, const Vector2<T>& b) noexcept
    {
        return Multivector2<T>(
            a, 
            b.x, b.y, 
            {} 
        );
    }

    //! Subtracts vector from scalar
    template <typename T>
    constexpr Multivector2<T> operator-(T a, const Vector2<T>& b) noexcept
    {
        return Multivector2<T>(
            a, 
            -b.x, -b.y, 
            {} 
        );
    }

    template <typename T, typename U>
    requires (trait::is_arithmetic_v<T>)
    constexpr Vector2<product_t<T,U>> operator*(T a, const Vector2<U>&b) noexcept
    {
        return Vector2<product_t<T,U>>(a*b.x, a*b.y);
    }

    template <typename T, typename U>
    requires (trait::is_arithmetic_v<T>)
    constexpr  Vector2<quotient_t<T,U>> operator/(T a, const  Vector2<U>&b) noexcept
    {
        return (a*b) / b.length²();
    }

    template <typename T>
    constexpr Vector2<T>   abs_elem(const Vector2<T>&a) noexcept
    {
        return a.eabs();
    }

    template <typename T>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian       angle(const Vector2<T>&a, const Vector2<T>& b)
    {
        return acos( std::clamp<T>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }


    template <typename T, typename DIM1, typename DIM2>
    requires (std::is_floating_point_v<T> && trait::has_sqrt_v<T>)
    Radian      angle(const Vector2<MKS<T,DIM1>>&a, const Vector2<MKS<T,DIM2>>& b)
    {
        using one_t = MKS<T,dim::None>;
        return acos( std::clamp<one_t>( (a*b)/(length(a)*length(b)), -one_v<T>, one_v<T>));
    }

    //! Creates a two dimension unit vector
    //!
    //! \param az   Counter-clockwise angle from +x
    inline Vector2D     ccw(Radian az)
    {
        return Vector2D(cos(az), sin(az) );
    }

    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector2<T>& a)
    {
        return atan(a.y, a.x);
    }

    /*! \brief Counter clockwise (euler) angle
    
        Computes the euler angle of the vector, ie, counter-clockwise from the +X axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    Radian   ccw(const Vector2<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }

    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector2<T>& a)
    {
        return atan(a.y, a.x);
    }

    /*! \brief Clockwise angle
    
        Computes the angle of the vector from the +Y axis.
    */
    template <typename T, typename DIM>
    requires std::is_floating_point_v<T>
    MKS<T,dim::Angle>   clockwise(const Vector2<MKS<T,DIM>>& a)
    {
        return atan(a.y, a.x);
    }

    //! Creates a two dimension unit vector
    //!
    //! \param az    Clockwise angle from +y
    inline Vector2D     clockwise(Radian az)
    {
        return Vector2D( sin(az), cos(az) );
    }

    template <typename T>
    constexpr T             component_max(const Vector2<T>&a) noexcept
    {
        return a.cmax();
    }

    template <typename T>
    constexpr T             component_min(const Vector2<T>&a) noexcept
    {
        return a.cmin();
    }

    template <typename T>
    constexpr square_t<T>     component_product(const Vector2<T>& a) noexcept
    {
        return a.cproduct();
    }

    template <typename T>
    constexpr T   component_sum(const Vector2<T>& a) noexcept
    {
        return a.csum();
    }

    /*! \brief "Delta Area"
    
        This is a building block for triangle & polygon area code, computes the "delta area" between two points
        (almost the same as area(aabb(a,b)) but can be negative.)
    */
    template <typename T>
    constexpr square_t<T>    delta_area(const Vector2<T>&a, const Vector2<T>& b) noexcept
    {
        return (b-a).cproduct();
    }

    /*! \brief "Point area" of the points
    
        This is a helper to area and other functions, 
        simply does an "area" of the point deltas, 
        no sign correction, no scaling.
    */
    template <typename T>
    square_t<T>    delta_area(const std::span<Vector2<T>>& vertex)
    {
        if(vertex.empty())
            return square_t<T>{};

        size_t  n   = vertex.size();
        square_t<T> ret = delta_area(vertex[n-1],vertex[0]);
        --n;
        for(size_t i=0;i<n;++n)
            ret += delta_area(vertex[i], vertex[i+1]);
        return ret;
    }

    template <typename T, typename U>
    constexpr Vector2<quotient_t<T,U>>    div_elem(const Vector2<T>&a, const Vector2<U>&b) noexcept
    {
        return a.ediv(b);
    }


    template <typename T, typename R>
    bool is_close(const R& compare, const Vector2<T>& actual, const Vector2<T>& expected)
    {
        return compare(length(actual-expected), length(expected));
    }

    template <typename T, typename R>
    bool is_close(const R& compare, const Vector2<T>& actual, std::type_identity_t<T> x, std::type_identity_t<T> y)
    {
        return is_close(compare, actual, Vector2<T>(x, y) );
    }

    /*! \brief Square of the vector's length
    
        This returns the SQUARE of the given vector's length.
    */
    template <typename T>
    constexpr square_t<T> length²(const Vector2<T>& vec) noexcept
    {
        return vec.length²();
    }    

    /*! \brief Length of the vector
        
        This returns the length of the given vector.
    */
    template <typename T>
    requires trait::has_sqrt_v<T>
    auto    length(const Vector2<T>& a)
    {
        return sqrt(length²(a));
    }

    template <typename T>
    constexpr Vector2<T>   max_elem(const Vector2<T>&a, const Vector2<T>&b) noexcept
    {
        return a.emax(b);
    }

    template <typename T>
    constexpr Vector2<T>   min_elem(const Vector2<T>&a, const Vector2<T>&b) noexcept
    {
        return a.emin(b);
    }

    /*! \brief Mid-way divide two vectors
    */
    template <typename T>
    constexpr Vector2<T>  midvector(const Vector2<T>& a, const Vector2<T>& b) noexcept
    {
        if constexpr (has_ieee754_v<T>)
            return ieee754_t<T>(0.5)*(a+b);
        else if constexpr (std::is_integral_v<T>)
            return (a+b) / T(2);
        else
            return {};
    }

    template <typename T, typename U>
    constexpr Vector2<product_t<T,U>>    mul_elem(const Vector2<T>&a, const Vector2<U>&b) noexcept
    {
        return a.emul(b);
    }
}
