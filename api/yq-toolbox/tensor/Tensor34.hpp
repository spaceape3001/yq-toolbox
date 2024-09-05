////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TENSOR_3_4_HPP 1

#include <yq-toolbox/typedef/tensor34.hpp>

#include <yq-toolbox/keywords.hpp>
#include <yq-toolbox/trait/has_identity.hpp>
#include <yq-toolbox/trait/product.hpp>
#include <yq-toolbox/trait/quotient.hpp>
#include <yq-toolbox/trait/self_divide.hpp>
#include <yq-toolbox/trait/self_multiply.hpp>
#include <yq-toolbox/vector/Vector3.hpp>
#include <yq-toolbox/vector/Vector4.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    /*! \brief 3x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor34 {
        //! Component type (captures template parameter)
        using component_type = T;
        
        static constexpr const unsigned rows_count  = 3;
        static constexpr const unsigned cols_count  = 4;

        T xx, xy, xz, xw;
        T yx, yy, yz, yw;
        T zx, zy, zz, zw;

        constexpr Tensor34() noexcept = default;

        constexpr Tensor34(
            T _xx, T _xy, T _xz, T _xw,
            T _yx, T _yy, T _yz, T _yw,
            T _zx, T _zy, T _zz, T _zw
        ) : 
            xx(_xx), xy(_xy), xz(_xz), xw(_xw),
            yx(_yx), yy(_yy), yz(_yz), yw(_yw),
            zx(_zx), zy(_zy), zz(_zz), zw(_zw)
        {
        }

        constexpr Tensor34(all_t, T v) : 
            xx(v), xy(v), xz(v), xw(v),
            yx(v), yy(v), yz(v), yw(v),
            zx(v), zy(v), zz(v), zw(v)
        {
        }
        
        constexpr Tensor34(columns_t, const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z, const Vector3<T>& w) :
            xx(x.x), xy(y.x), xz(z.x), xw(w.x),
            yx(x.y), yy(y.y), yz(z.y), yw(w.y),
            zx(x.z), zy(y.z), zz(z.z), zw(w.z)
        {
        }

        consteval Tensor34(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(one_v<T>),  zw(zero_v<T>)
        {
        }

        template <typename=void> requires has_nan_v<T>
        consteval Tensor34(nan_t) : 
            xx(nan_v<T>), xy(nan_v<T>), xz(nan_v<T>), xw(nan_v<T>),
            yx(nan_v<T>), yy(nan_v<T>), yz(nan_v<T>), yw(nan_v<T>),
            zx(nan_v<T>), zy(nan_v<T>), zz(nan_v<T>), zw(nan_v<T>)
        {
        }

        constexpr Tensor34(rows_t, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) :
            xx(x.x), xy(x.y), xz(x.z), xw(x.w),
            yx(y.x), yy(y.y), yz(y.z), yw(y.w),
            zx(z.x), zy(z.y), zz(z.z), zw(z.w)
        {
        }

        consteval Tensor34(zero_t) : 
            xx(zero_v<T>), xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(zero_v<T>), yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(zero_v<T>), zw(zero_v<T>)
        {
        }

        #ifdef YQ_USE_GLM
        template <glm::qualifier Q>
        explicit constexpr Tensor34(const glm::mat<3,4,T,Q>& t) noexcept;
        #endif

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor34&) const noexcept = default;

        #ifdef YQ_USE_GLM
        constexpr operator glm::mat<3,4,T,glm::defaultp>() const noexcept;
        #endif
        
        //! Positive (affirmation) operator
        constexpr Tensor34<T>   operator+() const noexcept;

        //! Negation operator
        constexpr Tensor34<T>   operator-() const noexcept;

        constexpr Tensor34<T>   operator+ (const Tensor34<T> &b)  const noexcept;
        Tensor34&               operator+=(const Tensor34<T> &b)  noexcept;

        constexpr Tensor34<T>   operator- (const Tensor34<T> &b)  const noexcept;
        Tensor34&               operator-=(const Tensor34<T> &b)  noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor34<product_t<T,U>>  operator*(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Tensor34&  operator*=(U b) noexcept;

        template <typename U>
        Polygon3<product_t<T,U>>  operator*(const Polygon4<U>&) const;
        template <typename U>
        Polyline3<product_t<T,U>>  operator*(const Polyline4<U>&) const;

        template <typename U>
        constexpr Segment3<product_t<T,U>>  operator*(const Segment4<U>&) const noexcept;
        
        template <typename U>
        constexpr Tensor31<product_t<T,U>> operator*(const Tensor41<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor32<product_t<T,U>> operator*(const Tensor42<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor33<product_t<T,U>> operator*(const Tensor43<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor34<product_t<T,U>> operator*(const Tensor44<U>& b) const noexcept;

        template <typename U>
        requires self_multiply_v<T,U>
        Tensor34& operator*=(const Tensor44<U>& b) noexcept;

        template <typename U>
        Triangle3<product_t<T,U>> operator*(const Triangle4<U>&) const noexcept;

        template <typename U>
        constexpr Vector3<product_t<T,U>> operator*(const Vector4<U>&b) const noexcept;

        template <typename U>
        std::vector<Vector3<product_t<T,U>>>    operator*(std::span<const Vector4<U>> b) const;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor34<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Tensor34&  operator/=(U b) noexcept;

        constexpr Tensor43<T>   transpose() const noexcept;

        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this tensor
            constexpr Vector3<T>  x_column() const noexcept;

            //! Y-column of this tensor
            constexpr Vector3<T>  y_column() const noexcept;

            //! Z-column of this tensor
            constexpr Vector3<T>  z_column() const noexcept;

            //! W-column of this tensor
            constexpr Vector3<T>  w_column() const noexcept;

            //! X-row of this tensor
            constexpr Vector4<T>  x_row() const noexcept;

            //! Y-row of this tensor
            constexpr Vector4<T>  y_row() const noexcept;

            //! Z-row of this tensor
            constexpr Vector4<T>  z_row() const noexcept;


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column
            Tensor34<T>& x_column(const Vector3<T>& v) noexcept;

            //! Sets the X-column
            Tensor34<T>& x_column(T _xx, T _yx, T _zx) noexcept;

            //! Sets the Y-column
            Tensor34<T>& y_column(const Vector3<T>& v) noexcept;

            //! Sets the Y-column
            Tensor34<T>& y_column(T _xy, T _yy, T _zy) noexcept;

            //! Sets the Z-column
            Tensor34<T>& z_column(const Vector3<T>& v) noexcept;

            //! Sets the Z-column
            Tensor34<T>& z_column(T _xz, T _yz, T _zz) noexcept;

            //! Sets the W-column
            Tensor34<T>& w_column(const Vector3<T>& v) noexcept;

            //! Sets the W-column
            Tensor34<T>& w_column(T _xw, T _yw, T _zw) noexcept;

            //! Sets the X-row
            Tensor34<T>& x_row(const Vector4<T>& v) noexcept;

            //! Sets the X-row
            Tensor34<T>& x_row(T _xx, T _xy, T _xz, T _xw) noexcept;

            //! Sets the Y-row
            Tensor34<T>& y_row(const Vector4<T>& v) noexcept;

            //! Sets the Y-row
            Tensor34<T>& y_row(T _yx, T _yy, T _yz, T _yw) noexcept;

            //! Sets the Z-row
            Tensor34<T>& z_row(const Vector4<T>& v) noexcept;

            //! Sets the Z-row
            Tensor34<T>& z_row(T _zx, T _zy, T _zz, T _zw) noexcept;

        //  --------------------------------------------------------
        //  AllComponents Adapters

            /*! Adds a value to all the elements
            */
            constexpr Tensor34 all_add(T b) const noexcept;
            
            //! Decrements all elements
            Tensor34&   all_decrement(T) noexcept;

            //! Increments all elements
            Tensor34&   all_increment(T) noexcept;

            /*! \brief Subtracts value from all elements
            */
            constexpr Tensor34 all_subtract(T b) const noexcept;
            

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
            constexpr bool all_test(const Tensor34& b, Pred pred) const noexcept;

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
            constexpr bool any_test(const Tensor34& b, Pred pred) const noexcept;
            
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

            static bool less_xx( const Tensor34& a, const Tensor34& b) { return a.xx < b.xx; }
            static bool less_xy( const Tensor34& a, const Tensor34& b) { return a.xy < b.xy; }
            static bool less_xz( const Tensor34& a, const Tensor34& b) { return a.xz < b.xz; }
            static bool less_xw( const Tensor34& a, const Tensor34& b) { return a.xw < b.xw; }

            static bool less_yx( const Tensor34& a, const Tensor34& b) { return a.yx < b.yx; }
            static bool less_yy( const Tensor34& a, const Tensor34& b) { return a.yy < b.yy; }
            static bool less_yz( const Tensor34& a, const Tensor34& b) { return a.yz < b.yz; }
            static bool less_yw( const Tensor34& a, const Tensor34& b) { return a.yw < b.yw; }

            static bool less_zx( const Tensor34& a, const Tensor34& b) { return a.zx < b.zx; }
            static bool less_zy( const Tensor34& a, const Tensor34& b) { return a.zy < b.zy; }
            static bool less_zz( const Tensor34& a, const Tensor34& b) { return a.zz < b.zz; }
            static bool less_zw( const Tensor34& a, const Tensor34& b) { return a.zw < b.zw; }

    };

    YQ_IEEE754_1(Tensor34)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 3x4 tensor by columns
    */
    template <typename T>
    constexpr Tensor34<T>  columns(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z, const Vector3<T>&w) noexcept
    {
        return Tensor34<T>(COLUMNS, x, y, z, w);
    }

    /*! \brief Create 3x4 tensor by rows
    */
    template <typename T>
    constexpr Tensor34<T>  rows(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z) noexcept
    {
        return Tensor34<T>(ROWS, x, y, z);
    }
    
    YQ_IDENTITY_1(Tensor34, Tensor34<T>(ZERO))
    YQ_NAN_1(Tensor34, Tensor34<T>(NAN))
    YQ_ZERO_1(Tensor34, Tensor34<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor34, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) && is_finite(v.yw) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz) && is_finite(v.zw)
    )
    
    YQ_IS_NAN_1(Tensor34,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) || is_nan(v.yw) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz) || is_nan(v.zw)
    )


    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor34
    template <typename T>
    AllComponents<Tensor34<T>>   all(Tensor34<T>& val);

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor34
    template <typename T>
    AllComponents<const Tensor34<T>>   all(const Tensor34<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Tensor34<T>>   elem(Tensor34<T>& val);

    template <typename T>
    ElemComponents<const Tensor34<T>>   elem(const Tensor34<T>& val);
    #endif

    template <typename T>
    AnyComponents<Tensor34<T>>   any(Tensor34<T>& val);

    template <typename T>
    AnyComponents<const Tensor34<T>>   any(const Tensor34<T>& val);
    

    template <typename T>
    constexpr Tensor43<T>  transpose(const Tensor34<T>&v);

//  --------------------------------------------------------
//  GETTERS

    //! X-column of given tensor
    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor34<T>&ten)  noexcept;

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector3<T>  y_column(const Tensor34<T>&ten) noexcept;

    //! Z-column of given tensor
    template <typename T>
    constexpr Vector3<T>  z_column(const Tensor34<T>&ten)  noexcept;

    //! W-column of given tensor
    template <typename T>
    constexpr Vector3<T>  w_column(const Tensor34<T>&ten)  noexcept;

    //! X-row of given tensor
    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor34<T>&ten) noexcept;

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor34<T>&ten) noexcept;

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector4<T>  z_row(const Tensor34<T>&ten) noexcept;



//  --------------------------------------------------------
//  ADDITION



//  --------------------------------------------------------
//  SUBTRACTION

    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor34<product_t<T,U>>  operator*(T a, const Tensor34<U>& b) noexcept;
    
    



//  --------------------------------------------------------
//  DIVISION

//  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor34D)
YQ_TYPE_DECLARE(yq::Tensor34F)
YQ_TYPE_DECLARE(yq::Tensor34I)
YQ_TYPE_DECLARE(yq::Tensor34U)

