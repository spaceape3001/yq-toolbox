////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Range.hpp>
#include <math/Vector1.hpp>
#include <math/Size1.hpp>
#include <math/AxCorners1.hpp>

namespace yq {

    /*! \brief Axially aligned box in 1 dimension(s).
    
        \note default construction does not enforce that lo <= hi
    */
    template <typename T>
    struct AxBox1 {
    
        //! Component type (ie, capture our argument)
        using component_type    = T;
        
        //! Our low corner 
        Vector1<T>  lo;
        
        //! Our high corner
        Vector1<T>  hi;
        
        constexpr AxBox1() noexcept = default;
        explicit constexpr AxBox1(const Vector1<T>& a) noexcept : lo(a), hi(a) {}
        constexpr AxBox1(const Vector1<T>& _lo, const Vector1<T>& _hi) noexcept : lo(_lo), hi(_hi) {}
        constexpr AxBox1(intersect_t, std::initializer_list<Vector1<T>>, std::initializer_list<Vector1<T>>) noexcept;
        constexpr AxBox1(intersect_t, std::span<const Vector1<T>>, std::span<const Vector1<T>>) noexcept;
        constexpr AxBox1(sort_t, const Vector1<T>&a, const Vector1<T>& b) noexcept;
        constexpr AxBox1(union_t, const Vector1<T>&a, const Vector1<T>& b) noexcept;
        constexpr AxBox1(union_t, std::initializer_list<Vector1<T>>) noexcept;
        constexpr AxBox1(union_t, std::span<const Vector1<T>>) noexcept;
        constexpr AxBox1(union_t, std::initializer_list<Vector1<T>>, std::initializer_list<Vector1<T>>) noexcept;
        constexpr AxBox1(union_t, std::span<const Vector1<T>>, std::span<const Vector1<T>>) noexcept;
        
        template <typename=void> requires has_nan_v<T>
        consteval AxBox1(nan_t) : AxBox1(Vector1<T>(NAN)) {}
        consteval AxBox1(zero_t) : AxBox1(Vector1<T>(ZERO)) {}
        
        explicit constexpr AxBox1(const Segment1<T>&) noexcept;

        
        //! Defaulted equatlity operator
        constexpr bool operator==(const AxBox1&) const noexcept = default;

        AxBox1  operator+() const noexcept;
        AxBox1  operator-() const noexcept;

        AxBox1  operator+(const Vector1<T>&) const noexcept;
        AxBox1& operator+=(const Vector1<T>&) noexcept;
        AxBox1  operator-(const Vector1<T>&) const noexcept;
        AxBox1& operator-=(const Vector1<T>&) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        AxBox1<product_t<T,U>> operator*(U) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        AxBox1& operator*=(U) noexcept;
        
        template <typename U>
        requires is_arithmetic_v<U>
        AxBox1<quotient_t<T,U>> operator/(U) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
        AxBox1& operator/=(U) noexcept;
        


        /*! \brief Union of two AABBs
        */
        constexpr AxBox1<T> operator|(const AxBox1<T>&b) const noexcept;

        constexpr AxBox1<T> operator|(const Vector1<T>&b) const noexcept;

        //! Union in a box
        AxBox1& operator|=(const AxBox1& b) noexcept;

        //! Unions in a vector
        AxBox1& operator|=(const Vector1<T>& b) noexcept;

        /*! \brief Intersection of two AABBs
        */
        constexpr AxBox1<T> operator&(const AxBox1<T>&b) const noexcept;

        //! Intersection into self 
        AxBox1& operator&=(const AxBox1& b) noexcept;

        /*! \brief Computes the center of a 1D axially aligned box
        */
        constexpr Vector1<T> center() const noexcept;

        constexpr Data1<Side>       classify(const Vector1<T>&) const noexcept;

        constexpr Side              classify_x(T) const noexcept;
        constexpr Side              classify_x(const Vector1<T>&) const noexcept;

        /*! \brief Checks if the point is inside (or touching) the box
        */
        constexpr bool contains(const Vector1<T>& pt) const noexcept;

        /*! \brief Returns the enumerated corners of the box
        */
        constexpr AxCorners1<Vector1<T>>  corners() const noexcept;

        /*! \brief Returns the enumerated corners of the box
        */
        constexpr AxCorners1<Vector1<T>>  corners(T adjust) const noexcept;

        //! Distance to box (zero if inside)
        T                       distance(const Vector1<T>&) const;
        
        //! Distance² to box (zero if inside)
        constexpr square_t<T>   distance²(const Vector1<T>&) const noexcept;

        /*! \brief Checks for full occlusion
        
            A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
            \param[in] b     The "smaller" box, if eclipsed
        */
        constexpr bool eclipses(const AxBox1<T>& b) const noexcept;
        
        //! Returns a fixed copy of the box (assuming it's possible to do)
        constexpr AxBox1    fixed() const noexcept;
        
        constexpr Vector1<T>    h() const noexcept;
        constexpr Vector1<T>    h(T adjust) const noexcept;

        /*! \brief Inflates the box
        
            This inflates a VALID box by the specified amount.  Negatives will shrink, invalids 
            will remain invalid.
        
        */
        constexpr AxBox1    inflate(T) const noexcept;

        /*! \brief Inflates the box
        
            This guards against invalid boxes, by first fixing it, and second, limiting any shrinkage to 
            half the minimum dimension of the box (ie, it'll be zero-thickness if the limit is activated)
        */
        constexpr AxBox1    inflate(guard_t, T) const noexcept;

        /*! \brief Tests for a valid box */
        constexpr bool    is_valid() const noexcept;
        
        constexpr Vector1<T>    l() const noexcept;
        constexpr Vector1<T>    l(T adjust) const noexcept;
        
        //! Minimum inflation number on a valid box to keep it from going invalid
        constexpr T min_inflate() const noexcept;

        /*! \brief Checks for any overlap
        
            This returns TRUE if *ANY* part of the boxes overlap (or touch)
        */
        constexpr bool overlaps(const AxBox1<T>& b) const noexcept;

        /*! \brief Projects a local [0,1] coordinate to a global coordinate
        
            \param[in] bx   The axially aligned box
            \return The global coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector1<T>   project(const Vector1<T>& v) const noexcept;
        
        /*! \brief Shrinks the box
        */
        constexpr AxBox1<T> shrink(T amt) const noexcept;
        
        constexpr Size1<T> size() const noexcept ;

        /*! \brief Span (dimensions) of this box
        */
        constexpr Vector1<T>    span() const noexcept;
        
        /*! \brief Span (dimensions) of this box
        
            This guards against negative values (ie, takes absolute value)
        */
        constexpr Vector1<T>    span(guard_t) const noexcept;


        /*! \brief Projects a global coordinate to a local [0,1] coordinate
            \param[in] v    The global coordinate
            \return The local coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector1<T>   unproject(const Vector1<T>& v) const noexcept;
        
        //! Tests this box for validness
        constexpr bool          valid() const noexcept ;

        /*! \brief Returns the x-range of the box
        */
        constexpr Range<T>  x_range() const noexcept;
    };
    
    YQ_IEEE754_1(AxBox1)
    YQ_INTEGER_1(AxBox1)
    YQ_IS_INTEGER_1(AxBox1)
    
    /*! \brief Creates an axially alligned box from one corner vertex
    */
    template <typename T>
    constexpr AxBox1<T> aabb(const Vector1<T>& a) noexcept;

    /*! \brief Creates an axially alligned box from two corner vertices
    */
    template <typename T>
    constexpr AxBox1<T> aabb(const Vector1<T>& a, const Vector1<T>& b) noexcept;

    /*! \brief Creates a 3D axially aligned box from container of Vector2's
    */
    template <typename T>
    AxBox1<T> aabb(const std::vector<Vector1<T>>& vals);


    YQ_NAN_1(AxBox1, AxBox1<T>(NAN));
    YQ_ZERO_1(AxBox1, AxBox1<T>(ZERO));

    YQ_IS_FINITE_1( AxBox1, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox1, is_nan(v.lo) || is_nan(v.hi))


    /*! \brief Computes the center of a 1D axially aligned box
    */
    template <typename T>
    constexpr Vector1<T> center(const AxBox1<T>& box)  noexcept;

    //! Computes the centroid of the given box (same as the center)
    template <typename T>
    Vector1<T>  centroid(const AxBox1<T>& box);

    /*! \brief Tests for a valid box */
    template <typename T>
    constexpr bool    is_valid(const AxBox1<T>& box) noexcept;

    //! Computes the span for a given box
    template <typename T>
    constexpr Vector1<T>    span(const AxBox1<T>&box) noexcept;
}

YQ_TYPE_DECLARE(yq::AxBox1D)
YQ_TYPE_DECLARE(yq::AxBox1F)
YQ_TYPE_DECLARE(yq::AxBox1I)
YQ_TYPE_DECLARE(yq::AxBox1U)

