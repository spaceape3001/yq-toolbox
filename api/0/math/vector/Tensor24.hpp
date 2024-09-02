////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TENSOR_2_4_HPP 1
#include <0/math/preamble.hpp>
#include <0/math/vector/Vector2.hpp>
#include <0/math/vector/Vector4.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

namespace yq {
    /*! \brief 2x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor24 {
    
        //! Component type
        using component_type = T;

        static constexpr const unsigned rows_count  = 2;
        static constexpr const unsigned cols_count  = 4;

        T xx, xy, xz, xw;
        T yx, yy, yz, yw;

        constexpr Tensor24() noexcept = default;

        constexpr Tensor24(
            T _xx, T _xy, T _xz, T _xw,
            T _yx, T _yy, T _yz, T _yw
        ) : 
            xx(_xx), xy(_xy), xz(_xz), xw(_xw),
            yx(_yx), yy(_yy), yz(_yz), yw(_yw)
        {
        }
        
        constexpr Tensor24(all_t, T v) : 
            xx(v), xy(v), xz(v), xw(v),
            yx(v), yy(v), yz(v), yw(v)
        {
        }

        constexpr Tensor24(columns_t, const Vector2<T>& x, const Vector2<T>& y, const Vector2<T>& z, const Vector2<T>& w) :
            xx(x.x), xy(y.x), xz(z.x), xw(w.x),
            yx(x.y), yy(y.y), yz(z.y), yw(w.y)
        {
        }

        consteval Tensor24(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>), yw(zero_v<T>)
        {
        }

        template <typename=void> requires has_nan_v<T>
        consteval Tensor24(nan_t) : Tensor24(ALL, nan_v<T>) {}

        constexpr Tensor24(rows_t, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) :
            xx(x.x), xy(x.y), xz(x.z), xw(x.w),
            yx(y.x), yy(y.y), yz(y.z), yw(y.w)
        {
        }

        consteval Tensor24(zero_t) : Tensor24(ALL, zero_v<T>) {}

        #ifdef YQ_USE_GLM
        template <glm::qualifier Q>
        explicit constexpr Tensor24(const glm::mat<2,4,T,Q>& t) noexcept;
        #endif

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor24&) const noexcept = default;

        #ifdef YQ_USE_GLM
        constexpr operator glm::mat<2,4,T,glm::defaultp>() const noexcept;
        #endif

        //! Positive (affirmation) operator
        constexpr Tensor24      operator+() const noexcept;

        //! Negation
        constexpr Tensor24      operator-() const noexcept;
        
        constexpr Tensor24      operator+ (const Tensor24 &b) const noexcept;
        Tensor24&               operator+=(const Tensor24 &b) noexcept;
        constexpr Tensor24      operator- (const Tensor24 &b) const noexcept;
        Tensor24&               operator-=(const Tensor24 &b) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor24<product_t<T,U>>  operator*(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Tensor24<T>&  operator*=(U b) noexcept;

        template <typename U>
        Polygon2<product_t<T,U>>  operator*(const Polygon4<U>&) const;
        template <typename U>
        Polyline2<product_t<T,U>>  operator*(const Polyline4<U>&) const;

        template <typename U>
        constexpr Segment2<product_t<T,U>>  operator*(const Segment4<U>&) const noexcept;

        template <typename U>
        constexpr Tensor21<product_t<T,U>> operator*(const Tensor41<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor22<product_t<T,U>> operator*(const Tensor42<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor23<product_t<T,U>> operator*(const Tensor43<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor24<product_t<T,U>> operator*(const Tensor44<U>& b) const noexcept;

        template <typename U>
        Triangle2<product_t<T,U>> operator*(const Triangle4<U>&) const noexcept;

        template <typename U>
        constexpr Vector2<product_t<T,U>> operator*(const Vector4<U>&b) const noexcept;

        template <typename U>
        std::vector<Vector2<product_t<T,U>>>    operator*(std::span<const Vector4<U>> b) const;

        template <typename U>
        requires self_multiply_v<T,U>
        Tensor24<T>& operator*=(const Tensor44<U>& b) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor24<quotient_t<T,U>>  operator/(U b) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Tensor24<T>&  operator/=(U b) noexcept;
        
        constexpr Tensor42<T> transpose() const noexcept;

        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this tensor
            constexpr Vector2<T>  x_column() const noexcept;

            //! Y-column of this tensor
            constexpr Vector2<T>  y_column() const noexcept;

            //! Z-column of this tensor
            constexpr Vector2<T>  z_column() const noexcept;

            //! W-column of this tensor
            constexpr Vector2<T>  w_column() const noexcept;

            //! X-row of this tensor
            constexpr Vector4<T>  x_row() const noexcept;

            //! Y-row of this tensor
            constexpr Vector4<T>  y_row() const noexcept;


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the x-column of this tensor
            Tensor24& x_column(const Vector2<T>& v);

            //! Sets the x-column of this tensor
            Tensor24& x_column(T _xx, T _yx);

            //! Sets the y-column of this tensor
            Tensor24& y_column(const Vector2<T>& v);

            //! Sets the y-column of this tensor
            Tensor24& y_column(T _xy, T _yy);

            //! Sets the z-column of this tensor
            Tensor24& z_column(const Vector2<T>& v);

            //! Sets the z-column of this tensor
            Tensor24& z_column(T _xz, T _yz);

            //! Sets the w-column of this tensor
            Tensor24& w_column(const Vector2<T>& v);

            //! Sets the w-column of this tensor
            Tensor24& w_column(T _xw, T _yw);

            //! Sets the x-row of this tensor
            Tensor24& x_row(const Vector4<T>& v);

            //! Sets the x-row of this tensor
            Tensor24& x_row(T _xx, T _xy, T _xz, T _xw);

            //! Sets the y-row of this tensor
            Tensor24& y_row(const Vector4<T>& v);

            //! Sets the y-row of this tensor
            Tensor24& y_row(T _yx, T _yy, T _yz, T _yw);


        //  --------------------------------------------------------
        //  AllComponents Adapters

            /*! Adds a value to all the elements
            */
            constexpr Tensor24 all_add(T b) const noexcept;
            
            //! Decrements all elements
            Tensor24&   all_decrement(T) noexcept;

            //! Increments all elements
            Tensor24&   all_increment(T) noexcept;

            /*! \brief Subtracts value from all elements
            */
            constexpr Tensor24 all_subtract(T b) const noexcept;
            

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
            constexpr bool all_test(const Tensor24& b, Pred pred) const noexcept;

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
            constexpr bool any_test(const Tensor24& b, Pred pred) const noexcept;
            
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

            static bool less_xx( const Tensor24& a, const Tensor24& b) { return a.xx < b.xx; }
            static bool less_xy( const Tensor24& a, const Tensor24& b) { return a.xy < b.xy; }
            static bool less_xz( const Tensor24& a, const Tensor24& b) { return a.xz < b.xz; }
            static bool less_xw( const Tensor24& a, const Tensor24& b) { return a.xw < b.xw; }

            static bool less_yx( const Tensor24& a, const Tensor24& b) { return a.yx < b.yx; }
            static bool less_yy( const Tensor24& a, const Tensor24& b) { return a.yy < b.yy; }
            static bool less_yz( const Tensor24& a, const Tensor24& b) { return a.yz < b.yz; }
            static bool less_yw( const Tensor24& a, const Tensor24& b) { return a.yw < b.yw; }

    };

    YQ_IEEE754_1(Tensor24)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 2x4 tensor by columns
    */
    template <typename T>
    constexpr Tensor24<T>  columns(const Vector2<T>&x, const Vector2<T>&y, const Vector2<T>&z, const Vector2<T>&w)
    {
        return Tensor24<T>(COLUMNS, x, y, z, w);
    }

    /*! \brief Create 2x4 tensor by rows
    */
    template <typename T>
    constexpr Tensor24<T>  rows(const Vector4<T>&x, const Vector4<T>&y)
    {
        return Tensor24<T>(ROWS, x, y );
    }
    
    YQ_IDENTITY_1(Tensor24, Tensor24<T>(IDENTITY))
    YQ_NAN_1(Tensor24,Tensor24<T>(NAN))
    YQ_ZERO_1(Tensor24, Tensor24<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor24, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) && is_finite(v.yw)
    )
    
    YQ_IS_NAN_1(Tensor24,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) || is_nan(v.yw)
    )

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor24
    template <typename T>
    AllComponents<Tensor24<T>>   all(Tensor24<T>& val);

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor24
    template <typename T>
    AllComponents<const Tensor24<T>>   all(const Tensor24<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Tensor24<T>>   elem(Tensor24<T>& val);

    template <typename T>
    ElemComponents<const Tensor24<T>>   elem(const Tensor24<T>& val);
    #endif

    template <typename T>
    AnyComponents<Tensor24<T>>   any(Tensor24<T>& val);

    template <typename T>
    AnyComponents<const Tensor24<T>>   any(const Tensor24<T>& val);
    
    
    template <typename T>
    constexpr Tensor42<T>  transpose(const Tensor24<T>&v);

//  --------------------------------------------------------
//  GETTERS

    //! Gets the x-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor24<T>&ten);

    //! Gets the y-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor24<T>&ten);

    //! Gets the z-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  z_column(const Tensor24<T>&ten);

    //! Gets the w-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  w_column(const Tensor24<T>&ten);

    //! Gets the x-row of the provided tensor
    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor24<T>&ten);

    //! Gets the y-row of the provided tensor
    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor24<T>&ten);

//  --------------------------------------------------------
//  --------------------------------------------------------

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor24<product_t<T,U>>  operator*(T a, const Tensor24<U>& b);


}

YQ_TYPE_DECLARE(yq::Tensor24D)
YQ_TYPE_DECLARE(yq::Tensor24F)
YQ_TYPE_DECLARE(yq::Tensor24I)
YQ_TYPE_DECLARE(yq::Tensor24U)

