////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TENSOR_4_3_HPP 1

#include <yq/typedef/tensor43.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/has_identity.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/vector/Vector3.hpp>
#include <yq/vector/Vector4.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    /*! \brief 4x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor43 {
        //! Component type (captures template parameter)
        using component_type = T;
        
        static constexpr const unsigned rows_count  = 4;
        static constexpr const unsigned cols_count  = 3;

        T xx, xy, xz;
        T yx, yy, yz;
        T zx, zy, zz;
        T wx, wy, wz;

        constexpr Tensor43() noexcept = default;

        constexpr Tensor43(
            T _xx, T _xy, T _xz,
            T _yx, T _yy, T _yz,
            T _zx, T _zy, T _zz,
            T _wx, T _wy, T _wz
        ) : 
            xx(_xx), xy(_xy), xz(_xz), 
            yx(_yx), yy(_yy), yz(_yz), 
            zx(_zx), zy(_zy), zz(_zz), 
            wx(_wx), wy(_wy), wz(_wz)
        {
        }
        
        constexpr Tensor43(all_t, T v) : 
            xx(v), xy(v), xz(v),
            yx(v), yy(v), yz(v),
            zx(v), zy(v), zz(v),
            wx(v), wy(v), wz(v)
        {
        }

        constexpr Tensor43(columns_t, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z) noexcept :
            xx(x.x), xy(y.x), xz(z.x), 
            yx(x.y), yy(y.y), yz(z.y), 
            zx(x.z), zy(y.z), zz(z.z), 
            wx(x.w), wy(y.w), wz(z.w)
        {
        }

        consteval Tensor43(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), 
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>), 
            zx(zero_v<T>), zy(zero_v<T>), zz(one_v<T>),  
            wx(zero_v<T>), wy(zero_v<T>), wz(zero_v<T>) 
        {
        }

        template <typename=void> requires has_nan_v<T>
        consteval Tensor43(nan_t) : Tensor43(ALL, nan_v<T>) {}

        constexpr Tensor43(rows_t, const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z, const Vector3<T>& w) :
            xx(x.x), xy(x.y), xz(x.z),
            yx(y.x), yy(y.y), yz(y.z),
            zx(z.x), zy(z.y), zz(z.z),
            wx(w.x), wy(w.y), wz(w.z)
        {
        }

        consteval Tensor43(zero_t) : Tensor43(ALL, zero_v<T>) {}

        #ifdef YQ_USE_GLM
        template <glm::qualifier Q>
        explicit constexpr Tensor43(const glm::mat<4,3,T,Q>& t) noexcept;
        #endif

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor43&) const noexcept = default;

        #ifdef YQ_USE_GLM
        //! Conversion to GLM
        constexpr operator glm::mat<4,3,T,glm::defaultp>() const noexcept ;
        #endif

        //! Positive (affirmation) operator
        constexpr Tensor43  operator+() const noexcept;

        //! Negation operator
        constexpr Tensor43  operator-() const noexcept;

        constexpr Tensor43   operator+ (const Tensor43 &b)  const noexcept;
        Tensor43&            operator+=(const Tensor43 &b)  noexcept;
        constexpr Tensor43   operator- (const Tensor43 &b)  const noexcept;
        Tensor43&            operator-=(const Tensor43 &b)  noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor43<product_t<T,U>>  operator*(U b) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Tensor43&  operator*=(U b) noexcept;

        template <typename U>
        Polygon4<product_t<T,U>>  operator*(const Polygon3<U>&) const;
        template <typename U>
        Polyline4<product_t<T,U>>  operator*(const Polyline3<U>&) const;

        template <typename U>
        constexpr Segment4<product_t<T,U>>  operator*(const Segment3<U>&) const noexcept;

        template <typename U>
        constexpr Tensor41<product_t<T,U>> operator*(const Tensor31<U>& b) const noexcept;

        template <typename U>
        constexpr Tensor42<product_t<T,U>> operator*(const Tensor32<U>& b) const noexcept;

        template <typename U>
        constexpr Tensor43<product_t<T,U>> operator*(const Tensor33<U>& b) const noexcept;

        template <typename U>
        constexpr Tensor44<product_t<T,U>> operator*(const Tensor34<U>& b) const noexcept;

        template <typename U>
        requires self_multiply_v<T,U>
        Tensor43& operator*=(const Tensor33<U>& b) noexcept;

        template <typename U>
        Triangle4<product_t<T,U>> operator*(const Triangle3<U>&) const noexcept;

        template <typename U>
        constexpr Vector4<product_t<T,U>> operator*(const Vector3<U>&b) const noexcept;

        template <typename U>
        std::vector<Vector4<product_t<T,U>>>    operator*(std::span<const Vector3<U>> b) const;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor43<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Tensor43&  operator/=(U b) noexcept;

        constexpr Tensor34<T>   transpose() const noexcept;


        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this tensor
            constexpr Vector4<T>  x_column() const noexcept;

            //! Y-column of this tensor
            constexpr Vector4<T>  y_column() const noexcept;

            //! Z-column of this tensor
            constexpr Vector4<T>  z_column() const noexcept;
            
            //! X-row of this tensor
            constexpr Vector3<T>  x_row() const noexcept;

            //! Y-row of this tensor
            constexpr Vector3<T>  y_row() const noexcept;

            //! Z-row of this tensor
            constexpr Vector3<T>  z_row() const noexcept;

            //! W-row of this tensor
            constexpr Vector3<T>  w_row() const noexcept;
    

        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column
            Tensor43& x_column(const Vector4<T>& v) noexcept;

            //! Sets the X-column
            Tensor43& x_column(T _xx, T _yx, T _zx, T _wx) noexcept;

            //! Sets the Y-column
            Tensor43& y_column(const Vector4<T>& v) noexcept;

            //! Sets the Y-column
            Tensor43& y_column(T _xy, T _yy, T _zy, T _wy) noexcept;

            //! Sets the Z-column
            Tensor43& z_column(const Vector4<T>& v) noexcept;

            //! Sets the Z-column
            Tensor43& z_column(T _xz, T _yz, T _zz, T _wz) noexcept;

            //! Sets the X-row
            Tensor43& x_row(const Vector3<T>& v) noexcept;

            //! Sets the X-row
            Tensor43& x_row(T _xx, T _xy, T _xz) noexcept;

            //! Sets the Y-row
            Tensor43& y_row(const Vector3<T>& v) noexcept;

            //! Sets the Y-row
            Tensor43& y_row(T _yx, T _yy, T _yz) noexcept;

            //! Sets the Z-row
            Tensor43& z_row(const Vector3<T>& v) noexcept;

            //! Sets the Z-row
            Tensor43& z_row(T _zx, T _zy, T _zz) noexcept;

            //! Sets the W-row
            Tensor43& w_row(const Vector3<T>& v) noexcept;

            //! Sets the W-row
            Tensor43& w_row(T _wx, T _wy, T _wz) noexcept;

        //  --------------------------------------------------------
        //  AllComponents Adapters

            /*! Adds a value to all the elements
            */
            constexpr Tensor43 all_add(T b) const noexcept;
            
            //! Decrements all elements
            Tensor43&   all_decrement(T) noexcept;

            //! Increments all elements
            Tensor43&   all_increment(T) noexcept;

            /*! \brief Subtracts value from all elements
            */
            constexpr Tensor43 all_subtract(T b) const noexcept;
            

            /*! Tests every element
                
                This applies the given test to every component, 
                returns TRUE if all tests are true.
                \note y, z, w component tests may be skipped if the x-component test fails.
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool all_test(Pred pred) const noexcept;

            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if all tests are true.
                \note y, z, w component tests may be skipped if the x-component test fails.
                \param[in] b The other vector
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool all_test(const Tensor43& b, Pred pred) const noexcept;

            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if all tests are true.
                \note y, z, w component tests may be skipped if the x-component test fails.
                \param[in] b The other value
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool all_test(T b, Pred pred) const noexcept;

        //  --------------------------------------------------------
        //  AnyComponents Adapters
            
            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if any test is true.
                \note y, z, w component tests may be skipped if the x-component test passes.
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool any_test(Pred pred) const noexcept;
            
            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if any test is true.
                \note y, z, w component tests may be skipped if the x-component test passes.
                \param[in] b The other vector
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool any_test(const Tensor43& b, Pred pred) const noexcept;
            
            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if any test is true.
                \note y, z, w component tests may be skipped if the x-component test passes.
                \param[in] b The other value
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool any_test(T b, Pred pred) const noexcept;

        //  --------------------------------------------------------
        //  COMPARISONS

            static bool less_xx( const Tensor43& a, const Tensor43& b) { return a.xx < b.xx; }
            static bool less_xy( const Tensor43& a, const Tensor43& b) { return a.xy < b.xy; }
            static bool less_xz( const Tensor43& a, const Tensor43& b) { return a.xz < b.xz; }

            static bool less_yx( const Tensor43& a, const Tensor43& b) { return a.yx < b.yx; }
            static bool less_yy( const Tensor43& a, const Tensor43& b) { return a.yy < b.yy; }
            static bool less_yz( const Tensor43& a, const Tensor43& b) { return a.yz < b.yz; }

            static bool less_zx( const Tensor43& a, const Tensor43& b) { return a.zx < b.zx; }
            static bool less_zy( const Tensor43& a, const Tensor43& b) { return a.zy < b.zy; }
            static bool less_zz( const Tensor43& a, const Tensor43& b) { return a.zz < b.zz; }

            static bool less_wx( const Tensor43& a, const Tensor43& b) { return a.x < b.x; }
            static bool less_wy( const Tensor43& a, const Tensor43& b) { return a.y < b.y; }
            static bool less_wz( const Tensor43& a, const Tensor43& b) { return a.z < b.z; }
    };

    YQ_IEEE754_1(Tensor43)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates 4x3 tensor by specifying the columns
    */
    template <typename T>
    constexpr Tensor43<T>  columns(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z) noexcept
    {
        return Tensor43<T>(COLUMNS, x, y, z);
    }

    /*! \brief Creates 4x3 tensor by specifying the rows
    */
    template <typename T>
    constexpr Tensor43<T>  rows(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z, const Vector3<T>&w) noexcept
    {
        return Tensor43<T>(ROWS, x, y, z, w);
    }
    
    YQ_IDENTITY_1(Tensor43, Tensor43<T>(IDENTITY))
    YQ_NAN_1(Tensor43, Tensor43<T>(NAN))
    YQ_ZERO_1(Tensor43, Tensor43<T>(ZERO))
    
    template <typename T>
    constexpr Tensor34<T>  transpose(const Tensor43<T>&v);

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor43
    template <typename T>
    AllComponents<Tensor43<T>>   all(Tensor43<T>& val);

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor43
    template <typename T>
    AllComponents<const Tensor43<T>>   all(const Tensor43<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Tensor43<T>>   elem(Tensor43<T>& val);

    template <typename T>
    ElemComponents<const Tensor43<T>>   elem(const Tensor43<T>& val);
    #endif

    template <typename T>
    AnyComponents<Tensor43<T>>   any(Tensor43<T>& val);

    template <typename T>
    AnyComponents<const Tensor43<T>>   any(const Tensor43<T>& val);
    


//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor43, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz) &&
        is_finite(v.wx) && is_finite(v.wy) && is_finite(v.wz)
    )
    
    YQ_IS_NAN_1(Tensor43,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz) ||
        is_nan(v.wx) || is_nan(v.wy) || is_nan(v.wz)
    )

//  --------------------------------------------------------
//  GETTERS

    //! X-column of given tensor
    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor43<T>&ten)  noexcept;

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor43<T>&ten)  noexcept;

    //! Z-column of given tensor
    template <typename T>
    constexpr Vector4<T>  z_column(const Tensor43<T>&ten)  noexcept;

    //! X-row of given tensor
    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor43<T>&ten) noexcept;

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor43<T>&ten) noexcept;

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector3<T>  z_row(const Tensor43<T>&ten) noexcept;

    //! W-row of given tensor
    template <typename T>
    constexpr Vector3<T>  w_row(const Tensor43<T>&ten) noexcept;



//  --------------------------------------------------------
//  ADDITION



//  --------------------------------------------------------
//  SUBTRACTION

    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor43<product_t<T,U>>  operator*(T a, const Tensor43<T>& b) noexcept;
    


//  --------------------------------------------------------
//  DIVISION



//  --------------------------------------------------------
//  OTIMES PRODUCT


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor43D)
YQ_TYPE_DECLARE(yq::Tensor43F)
YQ_TYPE_DECLARE(yq::Tensor43I)
YQ_TYPE_DECLARE(yq::Tensor43U)

