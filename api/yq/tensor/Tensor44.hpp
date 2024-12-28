////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TENSOR_4_4_HPP 1

#include <yq/typedef/tensor44.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/has_identity.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/vector/Vector4.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    /*! \brief 4x4 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor44 {
        //! Component type
        using component_type = T;

        static constexpr const unsigned rows_count  = 4;
        static constexpr const unsigned cols_count  = 4;
        
        T xx, xy, xz, xw;
        T yx, yy, yz, yw;
        T zx, zy, zz, zw;
        T wx, wy, wz, ww;


        constexpr Tensor44() noexcept = default;

        constexpr Tensor44(
            T _xx, T _xy, T _xz, T _xw,
            T _yx, T _yy, T _yz, T _yw,
            T _zx, T _zy, T _zz, T _zw,
            T _wx, T _wy, T _wz, T _ww
        ) noexcept : 
            xx(_xx), xy(_xy), xz(_xz), xw(_xw),
            yx(_yx), yy(_yy), yz(_yz), yw(_yw),
            zx(_zx), zy(_zy), zz(_zz), zw(_zw),
            wx(_wx), wy(_wy), wz(_wz), ww(_ww)
        {
        }
        
        constexpr Tensor44(all_k, T v) : 
            xx(v), xy(v), xz(v), xw(v),
            yx(v), yy(v), yz(v), yw(v),
            zx(v), zy(v), zz(v), zw(v),
            wx(v), wy(v), wz(v), ww(v)
        {
        }
        
        /*! \brief Constructing a view style matrix
        
            This is a utility for constructing a view-style matrix.  
            It allows the 3x3 to be defined, setting the w-column (right), w-row (below) and the ww-component
        */
        explicit constexpr Tensor44(const Tensor33<T>& t33, const Vector3<T>& wCol=ZERO, const Vector3<T>& wRow=ZERO, T ww=one_v<T>) noexcept;

        constexpr Tensor44(columns_k, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) noexcept :
            xx(x.x), xy(y.x), xz(z.x), xw(w.x),
            yx(x.y), yy(y.y), yz(z.y), yw(w.y),
            zx(x.z), zy(y.z), zz(z.z), zw(w.z),
            wx(x.w), wy(y.w), wz(z.w), ww(w.w)
        {
        }

        constexpr Tensor44(diagonal_k, T _xx, T _yy, T _zz, T _ww) noexcept : 
            xx(_xx),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(_yy),  yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(_zz),  zw(zero_v<T>),
            wx(zero_v<T>), wy(zero_v<T>), wz(zero_v<T>), ww(_ww)
        {
        }

        constexpr Tensor44(diagonal_k, const Vector4<T>& v) noexcept : 
            xx(v.x),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(v.y),  yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(v.z),  zw(zero_v<T>),
            wx(zero_v<T>), wy(zero_v<T>), wz(zero_v<T>), ww(v.w)
        {
        }

        consteval Tensor44(identity_k) noexcept : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), xw(zero_v<T>),
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>), yw(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(one_v<T>),  zw(zero_v<T>),
            wx(zero_v<T>), wy(zero_v<T>), wz(zero_v<T>), ww(one_v<T>)
        {
        }

        template <typename=void> requires has_nan_v<T>
        consteval Tensor44(nan_k) noexcept : Tensor44(ALL, nan_v<T>){}

        constexpr Tensor44(rows_k, const Vector4<T>& x, const Vector4<T>& y, const Vector4<T>& z, const Vector4<T>& w) noexcept :
            xx(x.x), xy(x.y), xz(x.z), xw(x.w),
            yx(y.x), yy(y.y), yz(y.z), yw(y.w),
            zx(z.x), zy(z.y), zz(z.z), zw(z.w),
            wx(w.x), wy(w.y), wz(w.z), ww(w.w)
        {
        }

        consteval Tensor44(zero_k) noexcept :Tensor44(ALL, zero_v<T>){} 

        #ifdef YQ_USE_GLM
        template <glm::qualifier Q>
        explicit constexpr Tensor44(const glm::mat<4,4,T,Q>& t) noexcept;
        #endif

        //! Defaulted equality operator
        constexpr bool operator==(const Tensor44&) const noexcept = default;
        
        #ifdef YQ_USE_GLM
        //! Conversion to GLM
        constexpr operator glm::mat<4,4,T,glm::defaultp>() const noexcept ;
        #endif


        //! Positive (affirmation) operator
        constexpr Tensor44      operator+() const noexcept;

        //! Negation operator
        constexpr Tensor44      operator-() const noexcept;
        
        constexpr Tensor44<T>   operator+ (const Tensor44<T> &b) const noexcept;
        Tensor44<T>&            operator+=(const Tensor44<T> &b)  noexcept;
        constexpr Tensor44<T>   operator- (const Tensor44<T> &b)  const noexcept;
        Tensor44<T>&            operator-=(const Tensor44<T> &b)  noexcept;
    
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor44<product_t<T,U>>  operator*(U b) const noexcept;
    
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Tensor44&  operator*=(U b) const noexcept;

        template <typename U>
        Polygon4<product_t<T,U>>  operator*(const Polygon4<U>&) const;
        template <typename U>
        Polyline4<product_t<T,U>>  operator*(const Polyline4<U>&) const;

        template <typename U>
        constexpr Segment4<product_t<T,U>>  operator*(const Segment4<U>&) const noexcept;

        template <typename U>
        constexpr Tensor41<product_t<T,U>> operator*(const Tensor41<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor42<product_t<T,U>> operator*(const Tensor42<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor43<product_t<T,U>> operator*(const Tensor43<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor44<product_t<T,U>> operator*(const Tensor44<U>& b) const noexcept;

        template <typename U>
        Triangle4<product_t<T,U>> operator*(const Triangle4<U>&) const noexcept;

        template <typename U>
        constexpr Vector4<product_t<T,U>> operator*(const Vector4<U>&b) const noexcept;

        template <typename U>
        std::vector<Vector4<product_t<T,U>>>    operator*(std::span<const Vector4<U>> b) const;

        template <typename U>
        requires self_multiply_v<T,U>
        Tensor44& operator*=(const Tensor44<U>& b) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor44<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Tensor44&  operator/=(U b) noexcept;


        //! Takes the transpose
        constexpr Tensor44 transpose() const noexcept;


        //  TODO: 4x4 determinant 
        //  TODO: 4x4 inverse 
        //  TODO: 4x4 eigenvalues, eigenvectors, & eigensystem

        //! \brief Trace of this tensor
        constexpr T     trace() const noexcept;

        //  --------------------------------------------------------
        //  GETTERS

            //! Diagonal of this vector
            constexpr Vector4<T>  diagonal() const noexcept;

            //! X-column of this vector
            constexpr Vector4<T>  x_column() const noexcept;

            //! Y-column of this vector
            constexpr Vector4<T>  y_column() const noexcept;

            //! Z-column of this vector
            constexpr Vector4<T>  z_column() const noexcept;

            //! W-column of this vector
            constexpr Vector4<T>  w_column() const noexcept;

            //! X-row of this vector
            constexpr Vector4<T>  x_row() const noexcept;

            //! Y-row of this vector
            constexpr Vector4<T>  y_row() const noexcept;

            //! Z-row of this vector
            constexpr Vector4<T>  z_row() const noexcept;

            //! W-row of this vector
            constexpr Vector4<T>  w_row() const noexcept;


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the diagonal
            Tensor44&  diagonal(const Vector4<T>& v) noexcept;

            //! Sets the diagonal
            Tensor44&  diagonal(T _xx, T _yy, T _zz, T _ww) noexcept;

            //! Sets the X-column
            Tensor44& x_column(const Vector4<T>& v) noexcept;

            //! Sets the X-column
            Tensor44& x_column(T _xx, T _yx, T _zx, T _wx) noexcept;

            //! Sets the Y-column
            Tensor44& y_column(const Vector4<T>& v) noexcept;

            //! Sets the Y-column
            Tensor44& y_column(T _xy, T _yy, T _zy, T _wy) noexcept;

            //! Sets the Z-column
            Tensor44& z_column(const Vector4<T>& v) noexcept;

            //! Sets the Z-column
            Tensor44& z_column(T _xz, T _yz, T _zz, T _wz) noexcept;

            //! Sets the W-column
            Tensor44& w_column(const Vector4<T>& v) noexcept;

            //! Sets the W-column
            Tensor44& w_column(T _xw, T _yw, T _zw, T _ww) noexcept;

            //! Sets the X-row
            Tensor44& x_row(const Vector4<T>& v) noexcept;

            //! Sets the X-row
            Tensor44& x_row(T _xx, T _xy, T _xz, T _xw) noexcept;

            //! Sets the Y-row
            Tensor44& y_row(const Vector4<T>& v) noexcept;

            //! Sets the Y-row
            Tensor44& y_row(T _yx, T _yy, T _yz, T _yw) noexcept;

            //! Sets the Z-row
            Tensor44& z_row(const Vector4<T>& v) noexcept;

            //! Sets the Z-row
            Tensor44& z_row(T _zx, T _zy, T _zz, T _zw) noexcept;

            //! Sets the W-row
            Tensor44& w_row(const Vector4<T>& v) noexcept;

            //! Sets the W-row
            Tensor44& w_row(T _wx, T _wy, T _wz, T _ww) noexcept;
    
        //  --------------------------------------------------------
        //  AllComponents Adapters

            /*! Adds a value to all the elements
            */
            constexpr Tensor44 all_add(T b) const noexcept;
            
            //! Decrements all elements
            Tensor44&   all_decrement(T) noexcept;

            //! Increments all elements
            Tensor44&   all_increment(T) noexcept;

            /*! \brief Subtracts value from all elements
            */
            constexpr Tensor44 all_subtract(T b) const noexcept;
            

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
            constexpr bool all_test(const Tensor44& b, Pred pred) const noexcept;

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
            constexpr bool any_test(const Tensor44& b, Pred pred) const noexcept;
            
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

            static bool less_xx( const Tensor44& a, const Tensor44& b) { return a.xx < b.xx; }
            static bool less_xy( const Tensor44& a, const Tensor44& b) { return a.xy < b.xy; }
            static bool less_xz( const Tensor44& a, const Tensor44& b) { return a.xz < b.xz; }
            static bool less_xw( const Tensor44& a, const Tensor44& b) { return a.xw < b.xw; }

            static bool less_yx( const Tensor44& a, const Tensor44& b) { return a.yx < b.yx; }
            static bool less_yy( const Tensor44& a, const Tensor44& b) { return a.yy < b.yy; }
            static bool less_yz( const Tensor44& a, const Tensor44& b) { return a.yz < b.yz; }
            static bool less_yw( const Tensor44& a, const Tensor44& b) { return a.yw < b.yw; }

            static bool less_zx( const Tensor44& a, const Tensor44& b) { return a.zx < b.zx; }
            static bool less_zy( const Tensor44& a, const Tensor44& b) { return a.zy < b.zy; }
            static bool less_zz( const Tensor44& a, const Tensor44& b) { return a.zz < b.zz; }
            static bool less_zw( const Tensor44& a, const Tensor44& b) { return a.zw < b.zw; }

            static bool less_wx( const Tensor44& a, const Tensor44& b) { return a.x < b.x; }
            static bool less_wy( const Tensor44& a, const Tensor44& b) { return a.y < b.y; }
            static bool less_wz( const Tensor44& a, const Tensor44& b) { return a.z < b.z; }
            static bool less_ww( const Tensor44& a, const Tensor44& b) { return a.w < b.w; }
    };
        
    YQ_IEEE754_1(Tensor44)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates 4x4 tensor from four Vector4 column vectors
    */
    template <typename T>
    constexpr Tensor44<T>  columns(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z, const Vector4<T>&w) noexcept
    {
        return Tensor44<T>(COLUMNS, x, y, z, w);
    }

    /*! \brief Creates 4x4 tensor by specifying diagonal 
    
        This assumes the rest of the components are zero.
    */
    template <typename T>
    constexpr Tensor44<T>  diagonal(const Vector4<T>&v) noexcept
    {
        return Tensor44<T>(DIAGONAL, v);
    }
    
    /*! \brief Creates 4x4 tensor by specifying diagonal
    
        This assumes the rest of the components are zero.
    */
    template <typename T>
    constexpr Tensor44<T>  diagonal(T x, std::type_identity_t<T> y, std::type_identity_t<T> z, std::type_identity_t<T> w) noexcept
    {
        return Tensor44<T>(DIAGONAL, x, y, z, w);
    }

    /*! \brief Creates 4x4 tensor by specifying the rows
    */
    template <typename T>
    constexpr Tensor44<T>  rows(const Vector4<T>&x, const Vector4<T>&y, const Vector4<T>&z, const Vector4<T>&w) noexcept
    {
        return Tensor44<T>(ROWS, x, y, z, w);
    }

    #ifdef YQ_USE_GLM
    /*! \brief Creates 4x4 tensor from the GLM equivalent
    */
    template <typename T, glm::qualifier Q>
    constexpr Tensor44<T> tensor(const glm::mat<4,4,T,Q>& t) noexcept;
    #endif
    
    YQ_IDENTITY_1(Tensor44, Tensor44<T>(IDENTITY))
    YQ_NAN_1(Tensor44, Tensor44<T>(NAN))
    YQ_ZERO_1(Tensor44, Tensor44<T>(ZERO))


    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor44
    template <typename T>
    AllComponents<Tensor44<T>>   all(Tensor44<T>& val);

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor44
    template <typename T>
    AllComponents<const Tensor44<T>>   all(const Tensor44<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Tensor44<T>>   elem(Tensor44<T>& val);

    template <typename T>
    ElemComponents<const Tensor44<T>>   elem(const Tensor44<T>& val);
    #endif

    template <typename T>
    AnyComponents<Tensor44<T>>   any(Tensor44<T>& val);

    template <typename T>
    AnyComponents<const Tensor44<T>>   any(const Tensor44<T>& val);
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor44, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) && is_finite(v.xw) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) && is_finite(v.yw) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz) && is_finite(v.zw) &&
        is_finite(v.wx) && is_finite(v.wy) && is_finite(v.wz) && is_finite(v.ww)
    )
    
    YQ_IS_NAN_1(Tensor44,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) || is_nan(v.xw) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) || is_nan(v.yw) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz) || is_nan(v.zw) ||
        is_nan(v.wx) || is_nan(v.wy) || is_nan(v.wz) || is_nan(v.ww)
    )

    //! Transpose of given tensor
    template <typename T>
    constexpr Tensor44<T>  transpose(const Tensor44<T>&ten) noexcept;

//  --------------------------------------------------------
//  GETTERS

    //! Diagonal of given tensor
    template <typename T>
    constexpr Vector4<T>  diagonal(const Tensor44<T>&ten) noexcept;

    //! X-column of given tensor
    template <typename T>
    constexpr Vector4<T>  x_column(const Tensor44<T>&ten)  noexcept;

    //! Y-column of given tensor
    template <typename T>
    constexpr Vector4<T>  y_column(const Tensor44<T>&ten)  noexcept;

    //! Z-column of given tensor
    template <typename T>
    constexpr Vector4<T>  z_column(const Tensor44<T>&ten)  noexcept;

    //! W-column of given tensor
    template <typename T>
    constexpr Vector4<T>  w_column(const Tensor44<T>&ten)  noexcept;

    //! X-row of given tensor
    template <typename T>
    constexpr Vector4<T>  x_row(const Tensor44<T>&ten) noexcept;

    //! Y-row of given tensor
    template <typename T>
    constexpr Vector4<T>  y_row(const Tensor44<T>&ten) noexcept;

    //! Z-row of given tensor
    template <typename T>
    constexpr Vector4<T>  z_row(const Tensor44<T>&ten) noexcept;

    //! W-row of given tensor
    template <typename T>
    constexpr Vector4<T>  w_row(const Tensor44<T>&ten) noexcept;


//  --------------------------------------------------------
//  ADDITION


//  --------------------------------------------------------
//  SUBTRACTION

    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor44<product_t<T,U>>  operator*(T a, const Tensor44<U>& b) noexcept;
    


//  --------------------------------------------------------
//  DIVISION



//  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS


    //  TODO: 4x4 determinant 
    //  TODO: 4x4 inverse 
    //  TODO: 4x4 eigenvalues, eigenvectors, & eigensystem

    /*! \brief Trace of the given 4 x 4 tensor
    
        \param[in] a    Tensor to take the trace of
    */
    template <typename T>
    constexpr T     trace(const Tensor44<T>& ten) noexcept;

}

YQ_TYPE_DECLARE(yq::Tensor44D)
YQ_TYPE_DECLARE(yq::Tensor44F)
YQ_TYPE_DECLARE(yq::Tensor44I)
YQ_TYPE_DECLARE(yq::Tensor44U)

