////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_TENSOR_2_3_HPP 1

#include <yq/typedef/tensor23.hpp>

#include <yq/keywords.hpp>
#include <yq/trait/has_identity.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/vector/Vector2.hpp>
#include <yq/vector/Vector3.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    /*! \brief 2x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor23 {
    
        //! Component type (captures template parameter)
        using component_type = T;

        static constexpr const unsigned rows_count  = 2;
        static constexpr const unsigned cols_count  = 3;


        T xx, xy, xz;
        T yx, yy, yz;


        constexpr Tensor23() noexcept = default;

        constexpr Tensor23(
            T _xx, T _xy, T _xz,
            T _yx, T _yy, T _yz
        ) : 
            xx(_xx), xy(_xy), xz(_xz), 
            yx(_yx), yy(_yy), yz(_yz)
        {
        }
        
        constexpr Tensor23(all_k, T v) : 
            xx(v), xy(v), xz(v),
            yx(v), yy(v), yz(v)
        {
        }

        constexpr Tensor23(columns_t, const Vector2<T>& x, const Vector2<T>& y, const Vector2<T>& z) noexcept :
            xx(x.x), xy(y.x), xz(z.x), 
            yx(x.y), yy(y.y), yz(z.y)
        {
        }


        consteval Tensor23(identity_k) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), 
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>)
        {
        }

        template <typename=void> requires has_nan_v<T>
        consteval Tensor23(nan_t) : Tensor23(ALL, nan_v<T>) {}

        constexpr Tensor23(rows_t, const Vector3<T>& x, const Vector3<T>& y) :
            xx(x.x), xy(x.y), xz(x.z),
            yx(y.x), yy(y.y), yz(y.z)
        {
        }

        consteval Tensor23(zero_k) : Tensor23(ALL, zero_v<T>) {}
        
        #ifdef YQ_USE_GLM
        template <glm::qualifier Q>
        explicit constexpr Tensor23(const glm::mat<2,3,T,Q>& t) noexcept;
        #endif
        
        //! Defaulted equality operator
        constexpr bool operator==(const Tensor23&) const noexcept = default;

        #ifdef YQ_USE_GLM
        //! Creates a GLM matrix
        constexpr operator glm::mat<2,3,T,glm::defaultp>() const noexcept;
        #endif

        //! Positive (affirmation) oeprator
        constexpr Tensor23      operator+() const noexcept;

        //! Negation
        constexpr Tensor23      operator-() const noexcept;
        
        constexpr Tensor23      operator+ (const Tensor23 &b) const noexcept;
        Tensor23&               operator+=(const Tensor23 &b) noexcept;
        constexpr Tensor23      operator- (const Tensor23 &b) const noexcept;
        Tensor23&               operator-=(const Tensor23 &b) noexcept;

        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor23<product_t<T,U>>  operator*(U b) const noexcept;
        
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Tensor23&  operator*=(U b) noexcept;

        template <typename U>
        Polygon2<product_t<T,U>>  operator*(const Polygon3<U>&) const;
        template <typename U>
        Polyline2<product_t<T,U>>  operator*(const Polyline3<U>&) const;

        template <typename U>
        constexpr Segment2<product_t<T,U>>  operator*(const Segment3<U>&) const noexcept;

        template <typename U>
        constexpr Tensor21<product_t<T,U>> operator*(const Tensor31<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor22<product_t<T,U>> operator*(const Tensor32<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor23<product_t<T,U>> operator*(const Tensor33<U>& b) const noexcept;
        template <typename U>
        constexpr Tensor24<product_t<T,U>> operator*(const Tensor34<U>& b) const noexcept;

        template <typename U>
        requires self_multiply_v<T,U>
        Tensor23& operator*=(const Tensor33<U>& b) noexcept;

        template <typename U>
        Triangle2<product_t<T,U>> operator*(const Triangle3<U>&) const noexcept;

        template <typename U>
        constexpr Vector2<product_t<T,U>> operator*(const Vector3<U>&b) const noexcept;

        template <typename U>
        std::vector<Vector2<product_t<T,U>>>    operator*(std::span<const Vector3<U>> b) const;
        
        template <typename U>
        requires is_arithmetic_v<U>
        constexpr Tensor23<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Tensor23&  operator/=(U b) noexcept;

        constexpr Tensor32<T> transpose() const noexcept;


        //  --------------------------------------------------------
        //  GETTERS

            //! X-column of this tensor
            constexpr Vector2<T>  x_column() const noexcept;

            //! Y-column of this tensor
            constexpr Vector2<T>  y_column() const noexcept;

            //! Z-column of this tensor
            constexpr Vector2<T>  z_column() const noexcept;

            //! X-row of this tensor
            constexpr Vector3<T>  x_row() const noexcept;

            //! Y-row of this tensor
            constexpr Vector3<T>  y_row() const noexcept;


        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the X-column of this tensor
            Tensor23& x_column(const Vector2<T>& v);

            //! Sets the X-column of this tensor
            Tensor23& x_column(T _xx, T _yx);

            //! Sets the Y-column of this tensor
            Tensor23& y_column(const Vector2<T>& v);

            //! Sets the Y-column of this tensor
            Tensor23& y_column(T _xy, T _yy);

            //! Sets the Z-column of this tensor
            Tensor23& z_column(const Vector2<T>& v);

            //! Sets the Z-column of this tensor
            Tensor23& z_column(T _xz, T _yz);

            //! Sets the X-row of this tensor
            Tensor23& x_row(const Vector3<T>& v);

            //! Sets the X-row of this tensor
            Tensor23& x_row(T _xx, T _xy, T _xz);

            //! Sets the Y-row of this tensor
            Tensor23& y_row(const Vector3<T>& v);

            //! Sets the Y-row of this tensor
            Tensor23& y_row(T _yx, T _yy, T _yz);


        //  --------------------------------------------------------
        //  AllComponents Adapters

            /*! Adds a value to all the elements
            */
            constexpr Tensor23 all_add(T b) const noexcept;
            
            //! Decrements all elements
            Tensor23&   all_decrement(T) noexcept;

            //! Increments all elements
            Tensor23&   all_increment(T) noexcept;

            /*! \brief Subtracts value from all elements
            */
            constexpr Tensor23 all_subtract(T b) const noexcept;
            

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
            constexpr bool all_kest(const Tensor23& b, Pred pred) const noexcept;

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
            constexpr bool any_kest(const Tensor23& b, Pred pred) const noexcept;
            
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

            static bool less_xx( const Tensor23& a, const Tensor23& b) { return a.xx < b.xx; }
            static bool less_xy( const Tensor23& a, const Tensor23& b) { return a.xy < b.xy; }
            static bool less_xz( const Tensor23& a, const Tensor23& b) { return a.xz < b.xz; }

            static bool less_yx( const Tensor23& a, const Tensor23& b) { return a.yx < b.yx; }
            static bool less_yy( const Tensor23& a, const Tensor23& b) { return a.yy < b.yy; }
            static bool less_yz( const Tensor23& a, const Tensor23& b) { return a.yz < b.yz; }

    };

    YQ_IEEE754_1(Tensor23)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 2x3 tensor by columns
    */
    template <typename T>
    constexpr Tensor23<T>  columns(const Vector2<T>&x, const Vector2<T>&y, const Vector2<T>&z)
    {
        return Tensor23<T>(COLUMNS, x, y, z);
    }

    /*! \brief Create 2x3 tensor by rows
    */
    template <typename T>
    constexpr Tensor23<T>  rows(const Vector3<T>&x, const Vector3<T>&y)
    {
        return Tensor23<T>(ROWS, x, y);
    }
    
    YQ_IDENTITY_1(Tensor23, Tensor23<T>(IDENTITY))
    YQ_NAN_1(Tensor23, Tensor23<T>(NAN))
    YQ_ZERO_1(Tensor23, Tensor23<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor23, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz)
    )
    
    YQ_IS_NAN_1(Tensor23,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz)
    )

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor23
    template <typename T>
    AllComponents<Tensor23<T>>   all(Tensor23<T>& val);

    //! All components adapter
    //! Use this to activate the "all" component adapters in tensor23
    template <typename T>
    AllComponents<const Tensor23<T>>   all(const Tensor23<T>& val);
    
    #if 0
    template <typename T>
    ElemComponents<Tensor23<T>>   elem(Tensor23<T>& val);

    template <typename T>
    ElemComponents<const Tensor23<T>>   elem(const Tensor23<T>& val);
    #endif

    template <typename T>
    AnyComponents<Tensor23<T>>   any(Tensor23<T>& val);

    template <typename T>
    AnyComponents<const Tensor23<T>>   any(const Tensor23<T>& val);

    template <typename T>
    constexpr Tensor32<T>  transpose(const Tensor23<T>&v);

//  --------------------------------------------------------
//  GETTERS

    //! Gets the X-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  x_column(const Tensor23<T>&ten);

    //! Gets the Y-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  y_column(const Tensor23<T>&ten);

    //! Gets the Z-column of the provided tensor
    template <typename T>
    constexpr Vector2<T>  z_column(const Tensor23<T>&ten);

    //! Gets the X-row of the provided tensor
    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor23<T>&ten);

    //! Gets the Y-row of the provided tensor
    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor23<T>&ten);



//  --------------------------------------------------------
//  ADDITION

//  --------------------------------------------------------
//  SUBTRACTION

//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr Tensor23<product_t<T,U>>  operator*(T a, const Tensor23<U>& b);
    

//  --------------------------------------------------------
//  DIVISION



//  --------------------------------------------------------
//  OTIMES PRODUCT


//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

}

YQ_TYPE_DECLARE(yq::Tensor23D)
YQ_TYPE_DECLARE(yq::Tensor23F)
YQ_TYPE_DECLARE(yq::Tensor23I)
YQ_TYPE_DECLARE(yq::Tensor23U)

