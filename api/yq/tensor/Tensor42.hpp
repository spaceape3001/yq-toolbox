////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TENSOR_4_2_HPP 1

#include <yq/typedef/tensor42.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/has_identity.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/vector/Vector4.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    /*! \brief 4x2 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor42 {
        //! Component type (captures template parameter)
        using component_type = T;
        
        static constexpr const unsigned rows_count  = 4;
        static constexpr const unsigned cols_count  = 2;

        T xx, xy;
        T yx, yy;
        T zx, zy;
        T wx, wy;


        constexpr Tensor42() noexcept = default;

        constexpr Tensor42(
            T _xx, T _xy, 
            T _yx, T _yy, 
            T _zx, T _zy, 
            T _wx, T _wy
        ) : 
            xx(_xx), xy(_xy),
            yx(_yx), yy(_yy),
            zx(_zx), zy(_zy),
            wx(_wx), wy(_wy)
        {
        }
        
        constexpr Tensor42(all_k, T v) : 
            xx(v), xy(v),
            yx(v), yy(v),
            zx(v), zy(v),
            wx(v), wy(v)
        {
        }

        constexpr Tensor42(columns_t, const Vector4<T>& x, const Vector4<T>& y) noexcept :
            xx(x.x), xy(y.x), 
            yx(x.y), yy(y.y), 
            zx(x.z), zy(y.z), 
            wx(x.w), wy(y.w)
        {
        }

        consteval Tensor42(identity_k) : 
            xx(one_v<T>),  xy(zero_v<T>), 
            yx(zero_v<T>), yy(one_v<T>),  
            zx(zero_v<T>), zy(zero_v<T>), 
            wx(zero_v<T>), wy(zero_v<T>)
        {
        }

        template <typename=void> requires has_nan_v<T>
        consteval Tensor42(nan_t) : Tensor42(ALL, nan_v<T>) {}

        constexpr Tensor42(rows_t, const Vector2<T>& x, const Vector2<T>& y, const Vector2<T>& z, const Vector2<T>& w) :
            xx(x.x), xy(x.y), 
            yx(y.x), yy(y.y), 
            zx(z.x), zy(z.y), 
            wx(w.x), wy(w.y)
        {
        }

        consteval Tensor42(zero_k) : Tensor42(ALL, zero_v<T>) {}

        #ifdef YQ_USE_GLM
        template <glm::qualifier Q>
        explicit constexpr Tensor42(const glm::mat<4,2,T,Q>& t) noexcept;;
        #endif

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor42&) const noexcept = default;

        #ifdef YQ_USE_GLM
        //! Conversion to GLM
        constexpr operator glm::mat<4,2,T,glm::defaultp>() const noexcept ;
        #endif

        //! Positive (affirmation) operator
        constexpr Tensor42<T>  operator+() const noexcept;

        //! Negation operator
        constexpr Tensor42<T>  operator-() const noexcept;

        constexpr Tensor42<T>   operator+ (const Tensor42<T> &b) const noexcept;
        Tensor42<T>&            operator+=(const Tensor42<T> &b)  noexcept;
        constexpr Tensor42<T>   operator- (const Tensor42<T> &b) const noexcept;
        Tensor42<T>&            operator-=(const Tensor42<T> &b)  noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor42<product_t<T,U>>  operator*(U b) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Tensor42&    operator*=(U b) noexcept;
        
        template <typename U>
        Polygon4<product_t<T,U>>  operator*(const Polygon2<U>&) const;
        template <typename U>
        Polyline4<product_t<T,U>>  operator*(const Polyline2<U>&) const;

        template <typename U>
        constexpr Segment4<product_t<T,U>>  operator*(const Segment2<U>&) const noexcept;

        template <typename U>
        constexpr Tensor41<product_t<T,U>> operator*(const Tensor21<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor42<product_t<T,U>> operator*(const Tensor22<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor43<product_t<T,U>> operator*(const Tensor23<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor44<product_t<T,U>> operator*(const Tensor24<U>& b) const noexcept;

        template <typename U>
        requires self_multiply_v<T,U>
        Tensor42& operator*=(const Tensor22<U>& b) noexcept;

        template <typename U>
        Triangle4<product_t<T,U>> operator*(const Triangle2<U>&) const noexcept;

        template <typename U>
        constexpr Vector4<product_t<T,U>> operator*(const Vector2<U>&b) const noexcept;
    
        template <typename U>
        std::vector<Vector4<product_t<T,U>>>    operator*(std::span<const Vector2<U>> b) const;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor42<quotient_t<T,U>>  operator/(U b) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Tensor42&   operator/=(U b) noexcept;

        constexpr Tensor24<T>   transpose() const noexcept;

        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this tensor
            constexpr Vector4<T>  x_column() const noexcept;

            //! Y-column of this tensor
            constexpr Vector4<T>  y_column() const noexcept;

            //! X-row of this tensor
            constexpr Vector2<T>  x_row() const noexcept;

            //! Y-row of this tensor
            constexpr Vector2<T>  y_row() const noexcept;

            //! Z-row of this tensor
            constexpr Vector2<T>  z_row() const noexcept;

            //! W-row of this tensor
            constexpr Vector2<T>  w_row() const noexcept;


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets x-column
            Tensor42& x_column(const Vector4<T>& v) noexcept;

            //! Sets x-column
            Tensor42& x_column(T _xx, T _yx, T _zx, T _wx) noexcept;

            //! Sets y-column
            Tensor42& y_column(const Vector4<T>& v) noexcept;

            //! Sets y-column
            Tensor42& y_column(T _xy, T _yy, T _zy, T _wy) noexcept;

            //! Sets x-row
            Tensor42& x_row(const Vector2<T>& v) noexcept;

            //! Sets x-row
            Tensor42& x_row(T _xx, T _xy) noexcept;

            //! Sets y-row
            Tensor42& y_row(const Vector2<T>& v) noexcept;

            //! Sets y-row
            Tensor42& y_row(T _yx, T _yy) noexcept;

            //! Sets z-row
            Tensor42& z_row(const Vector2<T>& v) noexcept;

            //! Sets z-row
            Tensor42& z_row(T _zx, T _zy) noexcept;

            //! Sets z-row
            Tensor42& w_row(const Vector2<T>& v) noexcept;

            //! Sets z-row
            Tensor42& w_row(T _wx, T _wy) noexcept;


        //  --------------------------------------------------------
        //  AllComponents Adapters

            /*! Adds a value to all the elements
            */
            constexpr Tensor42 all_add(T b) const noexcept;
            
            //! Decrements all elements
            Tensor42&   all_decrement(T) noexcept;

            //! Increments all elements
            Tensor42&   all_increment(T) noexcept;

            /*! \brief Subtracts value from all elements
            */
            constexpr Tensor42 all_subtract(T b) const noexcept;
            

            /*! Tests every element
                
                This applies the given test to every component, 
                returns TRUE if all tests are true.
                \note y, z, w component tests may be skipped if the x-component test fails.
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool all_kest(Pred pred) const noexcept;

            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if all tests are true.
                \note y, z, w component tests may be skipped if the x-component test fails.
                \param[in] b The other vector
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool all_kest(const Tensor42& b, Pred pred) const noexcept;

            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if all tests are true.
                \note y, z, w component tests may be skipped if the x-component test fails.
                \param[in] b The other value
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool all_kest(T b, Pred pred) const noexcept;

        //  --------------------------------------------------------
        //  AnyComponents Adapters
            
            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if any test is true.
                \note y, z, w component tests may be skipped if the x-component test passes.
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool any_kest(Pred pred) const noexcept;
            
            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if any test is true.
                \note y, z, w component tests may be skipped if the x-component test passes.
                \param[in] b The other vector
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool any_kest(const Tensor42& b, Pred pred) const noexcept;
            
            /*! Tests every element
                This applies the given test to every component, 
                returns TRUE if any test is true.
                \note y, z, w component tests may be skipped if the x-component test passes.
                \param[in] b The other value
                \param[in] pred The predicate (your test)
            */
            template <typename Pred>
            constexpr bool any_kest(T b, Pred pred) const noexcept;

        //  --------------------------------------------------------
        //  COMPARISONS

            static bool less_xx( const Tensor42& a, const Tensor42& b) { return a.xx < b.xx; }
            static bool less_xy( const Tensor42& a, const Tensor42& b) { return a.xy < b.xy; }

            static bool less_yx( const Tensor42& a, const Tensor42& b) { return a.yx < b.yx; }
            static bool less_yy( const Tensor42& a, const Tensor42& b) { return a.yy < b.yy; }

            static bool less_zx( const Tensor42& a, const Tensor42& b) { return a.zx < b.zx; }
            static bool less_zy( const Tensor42& a, const Tensor42& b) { return a.zy < b.zy; }

            static bool less_wx( const Tensor42& a, const Tensor42& b) { return a.x < b.x; }
            static bool less_wy( const Tensor42& a, const Tensor42& b) { return a.y < b.y; }
    };

    YQ_IEEE754_1(Tensor42)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 4x2 tensor by columns
    */
    template <typename T>
    constexpr Tensor42<T>  columns(const Vector4<T>&x, const Vector4<T>&y) noexcept
    {
        return Tensor42<T>(COLUMNS, x, y);
    }

    /*! \brief Create 4x2 tensor by rows
    */
    template <typename T>
    constexpr Tensor42<T>  rows(const Vector2<T>&x, const Vector2<T>&y, const Vector2<T>&z, const Vector2<T>&w) noexcept
    {
        return Tensor42<T>(ROWS, x, y, z, w);
    }
    
    YQ_IDENTITY_1(Tensor42, Tensor42<T>(IDENTITY))
    YQ_NAN_1(Tensor42, Tensor42<T>(NAN))
    YQ_ZERO_1(Tensor42, Tensor42<T>(ZERO))
    
    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor42
    template <typename T>
    AllComponents<Tensor42<T>>   all(Tensor42<T>& val);

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor42
    template <typename T>
    AllComponents<const Tensor42<T>>   all(const Tensor42<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Tensor42<T>>   elem(Tensor42<T>& val);

    template <typename T>
    ElemComponents<const Tensor42<T>>   elem(const Tensor42<T>& val);
    #endif

    template <typename T>
    AnyComponents<Tensor42<T>>   any(Tensor42<T>& val);

    template <typename T>
    AnyComponents<const Tensor42<T>>   any(const Tensor42<T>& val);
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor42, 
        is_finite(v.xx) && is_finite(v.xy) &&
        is_finite(v.yx) && is_finite(v.yy) &&
        is_finite(v.zx) && is_finite(v.zy) &&
        is_finite(v.wx) && is_finite(v.wy)
    )
    
    YQ_IS_NAN_1(Tensor42,  
        is_nan(v.xx) || is_nan(v.xy) ||
        is_nan(v.yx) || is_nan(v.yy) ||
        is_nan(v.zx) || is_nan(v.zy) ||
        is_nan(v.wx) || is_nan(v.wy)
    )

    template <typename T>
    constexpr Tensor24<T>  transpose(const Tensor42<T>&v);

//  --------------------------------------------------------
//  GETTERS

    //! X-column of given tensor
    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor42<T>&ten)  noexcept;

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor42<T>&ten)  noexcept;

    //! X-row of given tensor
    template <typename T>
    constexpr Vector2<T>  x_row(const Tensor42<T>&ten) noexcept;

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector2<T>  y_row(const Tensor42<T>&ten) noexcept;

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector2<T>  z_row(const Tensor42<T>&ten) noexcept;

    //! W-row of given tensor
    template <typename T>
    constexpr Vector2<T>  w_row(const Tensor42<T>&ten) noexcept;



//  --------------------------------------------------------
//  ADDITION

//  --------------------------------------------------------
//  SUBTRACTION

//  --------------------------------------------------------
//  MULTIPLICATION

//  --------------------------------------------------------
//  DIVISION

//  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor42D)
YQ_TYPE_DECLARE(yq::Tensor42F)
YQ_TYPE_DECLARE(yq::Tensor42I)
YQ_TYPE_DECLARE(yq::Tensor42U)

