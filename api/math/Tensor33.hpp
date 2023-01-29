////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ__API__MATH__TENSOR_3_3__HPP 1
#include <math/preamble.hpp>
#include <math/trig.hpp>
#include <math/Vector3.hpp>

namespace yq {
    /*! \brief 3x3 second order tensor (ie a matrix)
    
        \tparam[T]  Data type to be used, recommended to be arithmetic in nature
    */
    template <typename T>
    struct Tensor33 {
    
        //! Component type (captures the template parameter)
        using component_type = T;
        
        static constexpr const unsigned rows_count  = 3;
        static constexpr const unsigned cols_count  = 3;

        T xx, xy, xz;
        T yx, yy, yz;
        T zx, zy, zz;


        constexpr Tensor33() noexcept = default;

        constexpr Tensor33(
            T _xx, T _xy, T _xz,
            T _yx, T _yy, T _yz,
            T _zx, T _zy, T _zz
        ) : 
            xx(_xx), xy(_xy), xz(_xz), 
            yx(_yx), yy(_yy), yz(_yz), 
            zx(_zx), zy(_zy), zz(_zz)
        {
        }
        
        constexpr Tensor33(all_t, T v) : 
            xx(v), xy(v), xz(v),
            yx(v), yy(v), yz(v),
            zx(v), zy(v), zz(v)
        {
        }

        constexpr Tensor33(columns_t, const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z) noexcept :
            xx(x.x), xy(y.x), xz(z.x), 
            yx(x.y), yy(y.y), yz(z.y), 
            zx(x.z), zy(y.z), zz(z.z)
        {
        }

        constexpr Tensor33(diagonal_t, T _xx, T _yy, T _zz) : 
            xx(_xx),  xy(zero_v<T>), xz(zero_v<T>),
            yx(zero_v<T>), yy(_yy),  yz(zero_v<T>),
            zx(zero_v<T>), zy(zero_v<T>), zz(_zz)
        {
        }

        constexpr Tensor33(diagonal_t, const Vector3<T>& v) : 
            xx(v.x),  xy(zero_v<T>), xz(zero_v<T>), 
            yx(zero_v<T>), yy(v.y),  yz(zero_v<T>), 
            zx(zero_v<T>), zy(zero_v<T>), zz(v.z)
        {
        }

        consteval Tensor33(identity_t) : 
            xx(one_v<T>),  xy(zero_v<T>), xz(zero_v<T>), 
            yx(zero_v<T>), yy(one_v<T>),  yz(zero_v<T>), 
            zx(zero_v<T>), zy(zero_v<T>), zz(one_v<T>)
        {
        }

        consteval Tensor33(nan_t) : Tensor33(ALL, nan_v<T>) {}

        constexpr Tensor33(rows_t, const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z) :
            xx(x.x), xy(x.y), xz(x.z),
            yx(y.x), yy(y.y), yz(y.z),
            zx(z.x), zy(z.y), zz(z.z)
        {
        }

        consteval Tensor33(zero_t) : Tensor33(ALL, zero_v<T>) {}
        
        template <glm::qualifier Q>
        explicit constexpr Tensor33(const glm::mat<3,3,T,Q>& t) noexcept;

                //! Default equality operator
        constexpr bool operator==(const Tensor33&) const noexcept = default;

        //! Creates a GLM matrix
        constexpr operator glm::mat<3,3,T,glm::defaultp>() const noexcept;

        //! Positive (affirmation) operator
        constexpr Tensor33  operator+() const noexcept;

        //! Negation operator
        constexpr Tensor33  operator-() const noexcept;

        constexpr Tensor33   operator+ (const Tensor33 &b) const noexcept;
        Tensor33&            operator+=(const Tensor33 &b) noexcept;

        constexpr Tensor33   operator- (const Tensor33 &b) const noexcept;
        Tensor33&            operator-=(const Tensor33 &b) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor33<product_t<T,U>>  operator*(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        Tensor33&  operator*=(U b) noexcept;

        template <typename U>
        constexpr Tensor31<product_t<T,U>> operator*(const Tensor31<U>& b) const noexcept;

        template <typename U>
        constexpr Tensor32<product_t<T,U>> operator*(const Tensor32<U>& b) const noexcept;

        template <typename U>
        constexpr Tensor33<product_t<T,U>> operator*(const Tensor33<U>& b) const noexcept;

        template <typename U>
        constexpr Tensor34<product_t<T,U>> operator*(const Tensor34<U>& b) const noexcept;

        template <typename U>
        requires trait::self_mul_v<T,U>
        Tensor33& operator*=(const Tensor33<U>& b) noexcept;

        template <typename U>
        constexpr Vector3<product_t<T,U>> operator*(const Vector3<U>&b) const noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        constexpr Tensor33<quotient_t<T,U>>  operator/(U b) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        Tensor33&  operator/=(U b) noexcept;

        //! Determinant of this matrix
        constexpr cube_t<T> determinant() const noexcept;
     
        //  TODO: 3x3 eigenvalues, eigenvectors, & eigensystem
        
        
        //! Inverse of this matrix
        constexpr Tensor33<inverse_t<T>> inverse() const noexcept;
        
        /*! \brief Trace of this tensor
        */
        constexpr T     trace() const noexcept;
    
        //! Transpose of this vector
        constexpr Tensor33  transpose() const noexcept;

        //  --------------------------------------------------------
        //  GETTERS

            //! The diagonal of this tensor
            constexpr Vector3<T>  diagonal() const noexcept;

            //! X-column of this tensor
            constexpr Vector3<T>  x_column() const noexcept;

            //! Y-column of this tensor
            constexpr Vector3<T>  y_column() const noexcept;

            //! Z-column of this tensor
            constexpr Vector3<T>  z_column() const noexcept;

            //! X-row of this tensor
            constexpr Vector3<T>  x_row() const noexcept;

            //! Y-row of this tensor
            constexpr Vector3<T>  y_row() const noexcept;

            //! Z-row of this tensor
            constexpr Vector3<T>  z_row() const noexcept;



        //  --------------------------------------------------------
        //  SETTERS

            //! Sets the diagonal
            Tensor33&  diagonal(const Vector3<T>& v);

            //! Sets the diagonal
            Tensor33&  diagonal(T _xx, T _yy, T _zz);

            //! Sets the x-column
            Tensor33& x_column(const Vector3<T>& v);

            //! Sets the x-column
            Tensor33& x_column(T _xx, T _yx, T _zx);

            //! Sets the y-column
            Tensor33& y_column(const Vector3<T>& v);

            //! Sets the y-column
            Tensor33& y_column(T _xy, T _yy, T _zy);

            //! Sets the z-column
            Tensor33& z_column(const Vector3<T>& v);

            //! Sets the z-column
            Tensor33& z_column(T _xz, T _yz, T _zz);

            //! Sets the x-row
            Tensor33& x_row(const Vector3<T>& v);

            //! Sets the x-row
            Tensor33& x_row(T _xx, T _xy, T _xz);

            //! Sets the y-row
            Tensor33& y_row(const Vector3<T>& v);

            //! Sets the y-row
            Tensor33& y_row(T _yx, T _yy, T _yz);

            //! Sets the z-row
            Tensor33& z_row(const Vector3<T>& v);
    
            //! Sets the z-row
            Tensor33& z_row(T _zx, T _zy, T _zz);
    };

    YQ_IEEE754_1(Tensor33)
        
//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Create 3x3 tensor by columns
    */
    template <typename T>
    constexpr Tensor33<T>  columns(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z)
    {
        return Tensor33<T>(COLUMNS, x, y, z);
    }

    /*! \brief Create 3x3 tensor by its diagonal
    */
    template <typename T>
    constexpr Tensor33<T>  diagonal(const Vector3<T>&v)
    {
        return Tensor33<T>(DIAGONAL, v);
    }
    
    /*! \brief Create 3x3 tensor by its diagonal
    */
    template <typename T>
    constexpr Tensor33<T>  diagonal(T x, std::type_identity_t<T> y, std::type_identity_t<T> z)
    {
        return Tensor33<T>(DIAGONAL, x, y, z);
    }

    /*! \brief Create 3x3 tensor by heading-pitch-roll
    
        A traditional rotation matrix in flight sims and other similar ventures, this creates a 3x3
        matrix by specifying it's "heading-pitch-roll".
        
        \param[in] hdg      Yaw or Heading (ie rotation around "Z")
        \param[in] pitch    Pitch up (ie rotation around "Y")
        \param[in] roll     Roll (ie rotation around "X")

        \return 3x3 rotation matrix
    */
    template <typename T>
    Tensor33<T> hpr33(MKS<T,dim::Angle> hdg, MKS<T,dim::Angle> pitch, MKS<T,dim::Angle> roll)
    {
        auto ch = cos(hdg);
        auto sh = sin(hdg);

        auto cp = cos(pitch);
        auto sp = sin(pitch);

        auto cr = cos(roll);
        auto sr = sin(roll);
        
        return {
            ch*cp, sh*cp, -sp,
            ch*sp*sr-sh*cr, sh*sp*sr+ch*cr, cp*sr,
            ch*sp*cr+sh*sr, sh*sp*cr-ch*sr, cp*cr
        };
    }

    //! Creates a matrix that can rotate a vector by the specfied angle
    //! In the counter-clockwise direction
    template <typename T>
    constexpr Tensor33<T>   rotation3X(MKS<T,dim::Angle> r)
    {
        auto c  = cos(r);
        auto s  = sin(r);
        return {
            1., 0., 0.,
            0., c, -s,
            0., s, c
        };
    }

    //! Creates a matrix that can rotate a vector by the specfied angle
    //! In the counter-clockwise direction
    template <typename T>
    constexpr Tensor33<T>   rotation3Y(MKS<T,dim::Angle> r)
    {
        auto c  = cos(r);
        auto s  = sin(r);
        return {
            c, 0., -s,
            0., 1., 0.,
            s, 0., c
        };
    }


    //! Creates a matrix that can rotate a vector by the specfied angle
    //! In the counter-clockwise direction
    template <typename T>
    constexpr Tensor33<T>   rotation3Z(MKS<T,dim::Angle> r)
    {
        auto c  = cos(r);
        auto s  = sin(r);
        return {
            1., 0., 0.,
            0., c, -s,
            0., s, c
        };
    }


    /*! \brief Create 3x3 tensor by rows
    */
    template <typename T>
    constexpr Tensor33<T>  rows(const Vector3<T>&x, const Vector3<T>&y, const Vector3<T>&z)
    {
        return Tensor33<T>(ROWS, x, y, z);
    }

    /*! \brief Create 3x3 tensor from GLM
    */
    template <typename T, glm::qualifier Q>
    constexpr Tensor33<T> tensor(const glm::mat<3,3,T,Q>& t)
    {
        return Tensor33<T>(t);
    }
    
    
    YQ_IDENTITY_1(Tensor33, Tensor33<T>(IDENTITY))
    YQ_NAN_1(Tensor33, Tensor33<T>(NAN))
    YQ_ZERO_1(Tensor33, Tensor33<T>(ZERO))
    
//  --------------------------------------------------------
//  BASIC FUNCTIONS


    YQ_IS_FINITE_1(Tensor33, 
        is_finite(v.xx) && is_finite(v.xy) && is_finite(v.xz) &&
        is_finite(v.yx) && is_finite(v.yy) && is_finite(v.yz) &&
        is_finite(v.zx) && is_finite(v.zy) && is_finite(v.zz)
    )
    
    YQ_IS_NAN_1(Tensor33,  
        is_nan(v.xx) || is_nan(v.xy) || is_nan(v.xz) ||
        is_nan(v.yx) || is_nan(v.yy) || is_nan(v.yz) ||
        is_nan(v.zx) || is_nan(v.zy) || is_nan(v.zz)
    )

    //! Transpose of the provided tensor
    template <typename T>
    constexpr Tensor33<T>  transpose(const Tensor33<T>&ten);

//  --------------------------------------------------------
//  GETTERS

    //! Diagonal of provided tensor
    template <typename T>
    constexpr Vector3<T>  diagonal(const Tensor33<T>&ten);

    //! X-column of provided tensor
    template <typename T>
    constexpr Vector3<T>  x_column(const Tensor33<T>&ten);

    //! Y-column of provided tensor
    template <typename T>
    constexpr Vector3<T>  y_column(const Tensor33<T>&ten);

    //! Z-column of provided tensor
    template <typename T>
    constexpr Vector3<T>  z_column(const Tensor33<T>&ten) ;

    //! X-row of provided tensor
    template <typename T>
    constexpr Vector3<T>  x_row(const Tensor33<T>&ten);

    //! Y-row of provided tensor
    template <typename T>
    constexpr Vector3<T>  y_row(const Tensor33<T>&ten);

    //! Z-row of provided tensor
    template <typename T>
    constexpr Vector3<T>  z_row(const Tensor33<T>&ten);



//  --------------------------------------------------------
//  ADDITION


//  --------------------------------------------------------
//  SUBTRACTION
    
//  --------------------------------------------------------
//  MULTIPLICATION

    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr Tensor33<product_t<T,U>>  operator*(T a, const Tensor33<U>& b);
    
    

//  --------------------------------------------------------
//  DIVISION



//  --------------------------------------------------------
//  OTIMES PRODUCT

//  --------------------------------------------------------
//  ADVANCED FUNCTIONS

    //! Determinant of the given tensor
    template <typename T>
    cube_t<T> determinant(const Tensor33<T>& ten);
 
    //  TODO: 3x3 eigenvalues, eigenvectors, & eigensystem
    
    
    //! Inverse of the given tensor
    template <typename T>
    Tensor33<inverse_t<T>> inverse(const Tensor33<T>&ten);
    
    /*! \brief Trace of the 3 x 3 tensor
    
        \param[in] a    Tensor to take the trace of
    */
    template <typename T>
    constexpr T     trace(const Tensor33<T>& ten);
}

YQ_TYPE_DECLARE(yq::Tensor33D)
YQ_TYPE_DECLARE(yq::Tensor33F)
YQ_TYPE_DECLARE(yq::Tensor33I)
YQ_TYPE_DECLARE(yq::Tensor33U)

