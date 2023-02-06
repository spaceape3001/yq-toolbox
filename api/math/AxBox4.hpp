////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Range.hpp>
#include <math/Size4.hpp>
#include <math/Vector4.hpp>
#include <math/AxCorners4.hpp>

namespace yq {

    /*! \brief Axially aligned box in 4 dimension(s).
    */
    template <typename T>
    struct AxBox4 {
        //! Component type (ie, the argument)
        using component_type    = T;
        
        //! Low corner
        Vector4<T>  lo;

        //! High corner
        Vector4<T>  hi;
        
        constexpr AxBox4() noexcept = default;
        explicit constexpr AxBox4(const Vector4<T>& a)  noexcept: lo(a), hi(a) {}
        constexpr AxBox4(const Vector4<T>& _lo, const Vector4<T>& _hi)  noexcept: lo(_lo), hi(_hi) {}
        constexpr AxBox4(intersect_t, std::initializer_list<Vector4<T>>, std::initializer_list<Vector4<T>>) noexcept;
        constexpr AxBox4(intersect_t, std::span<const Vector4<T>>, std::span<const Vector4<T>>) noexcept;
        constexpr AxBox4(sort_t, const Vector4<T>&a, const Vector4<T>& b) noexcept;
        constexpr AxBox4(union_t, const Vector4<T>&a, const Vector4<T>& b) noexcept;
        constexpr AxBox4(union_t, std::initializer_list<Vector4<T>>) noexcept;
        constexpr AxBox4(union_t, std::span<const Vector4<T>>) noexcept;
        constexpr AxBox4(union_t, std::initializer_list<Vector4<T>>, std::initializer_list<Vector4<T>>) noexcept;
        constexpr AxBox4(union_t, std::span<const Vector4<T>>, std::span<const Vector4<T>>) noexcept;

        template <typename=void> requires trait::has_nan_v<T>
        consteval AxBox4(nan_t) : AxBox4(Vector4<T>(NAN)) {}

        consteval AxBox4(zero_t) : AxBox4(Vector4<T>(ZERO)) {}

        explicit constexpr AxBox4(const Segment4<T>&) noexcept;
        explicit constexpr AxBox4(const Triangle4<T>&) noexcept;

        //! Equality operator (defaulted);
        constexpr bool operator==(const AxBox4&) const noexcept = default;

        AxBox4  operator+() const noexcept;
        AxBox4  operator-() const noexcept;


        AxBox4  operator+(const Vector4<T>&) const noexcept;
        AxBox4& operator+=(const Vector4<T>&) noexcept;
        AxBox4  operator-(const Vector4<T>&) const noexcept;
        AxBox4& operator-=(const Vector4<T>&) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        AxBox4<trait::product_t<T,U>> operator*(U) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        AxBox4& operator*=(U) noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        AxBox4<trait::quotient_t<T,U>> operator/(U) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        AxBox4& operator/=(U) noexcept;
        
        
        /*! \brief Union of two AABBs
        */
        constexpr AxBox4<T> operator|(const AxBox4<T>&b) const noexcept;

        constexpr AxBox4<T> operator|(const Vector4<T>&b) const noexcept;

        //! Union in a box
        AxBox4& operator|=(const AxBox4& b) noexcept;

        //! Unions in a vector
        AxBox4& operator|=(const Vector4<T>& b) noexcept;

        /*! \brief Intersection of two AABBs
        */
        constexpr AxBox4<T> operator&(const AxBox4<T>&b) const noexcept;
        
        //! Intersection into self 
        AxBox4& operator&=(const AxBox4& b) noexcept;

        /*! \brief Computes the center of a 4D axially aligned box
        */
        constexpr Vector4<T>      center() const noexcept;
        
        constexpr Data4<Side>       classify(const Vector4<T>&) const noexcept;

        constexpr Side              classify_w(T) const noexcept;
        constexpr Side              classify_w(const Vector4<T>&) const noexcept;

        constexpr Side              classify_x(T) const noexcept;
        constexpr Side              classify_x(const Vector4<T>&) const noexcept;

        constexpr Side              classify_y(T) const noexcept;
        constexpr Side              classify_y(const Vector4<T>&) const noexcept;

        constexpr Side              classify_z(T) const noexcept;
        constexpr Side              classify_z(const Vector4<T>&) const noexcept;


        /*! \brief Checks if the point is inside (or touching) the box
        */
        constexpr bool contains (const Vector4<T>& pt) const noexcept;

        /*! \brief Returns ALL the corners of the box 
        */
        constexpr AxCorners4<Vector4<T>>  corners() const noexcept;
        
        /*! \brief Checks for full occlusion
        
            A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
            \param[in] Big   The "bigger" box, if eclipsed
            \param[in] Small The "smaller" box, if eclipsed
        */
        constexpr bool eclipses(const AxBox4<T>& b) const noexcept;

        //! Returns a fixed copy of the box (assuming it's possible to do)
        constexpr AxBox4 fixed() const noexcept;

        /*! \brief Computes the hyper volume of the box
        */
        constexpr trait::fourth_t<T> hypervolume() const noexcept;

        //! Checks for validity (hi >= lo)
        constexpr bool    is_valid() const noexcept;

        /*! \brief Checks for any overlap
        
            This returns TRUE if *ANY* part of the boxes overlap (or touch)
        */
        constexpr bool overlaps(const AxBox4<T>& b) const noexcept;
        
        /*! \brief Projects a local [0,1] coordinate to a global coordinate based on the provided axially aligned box
        
            \param[in] bx   The axially aligned box
            \param[in] v    The local coordinate
            \return The global coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector4<T>   project(const Vector4<T>& v) const noexcept;

        constexpr Size4<T> size() const noexcept;

        /*! \brief Returns the span (dimensions) of the box
        */
        constexpr Vector4<T>    span() const noexcept;

        /*! \brief Projects a global coordinate to a local [0,1] coordinate for the axially aligned box

            \param[in] bx   The axially aligned box
            \param[in] v    The global coordinate
            \return The local coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector4<T>   unproject(const Vector4<T>& v) const noexcept;

        //! Tests this box for validness
        constexpr bool          valid() const noexcept;

        //! W Range of the box
        constexpr Range<T>  w_range() const noexcept;

        //! X Range of the box
        constexpr Range<T>  x_range() const noexcept;

        //! Y Range of the box
        constexpr Range<T>  y_range() const noexcept;

        //! Z Range of the box
        constexpr Range<T>  z_range() const noexcept;
    };
    
    YQ_IEEE754_1(AxBox4)
    
    /*! \brief Creates a 4D axially aligned box from one vector
    */
    template <typename T>
    constexpr AxBox4<T> aabb(const Vector4<T>& a) noexcept;

    /*! \brief Creates a 4D axially aligned box from two vectors
    */
    template <typename T>
    constexpr AxBox4<T> aabb(const Vector4<T>& a, const Vector4<T>& b) noexcept;

    /*! \brief Creates a 4D axially aligned box from container of Vector4's
    */
    template <typename T>
    AxBox4<T> aabb(const std::vector<Vector4<T>>& vals);

    YQ_NAN_1(AxBox4, AxBox4<T>(NAN));
    YQ_ZERO_1(AxBox4, AxBox4<T>(ZERO));

    YQ_IS_FINITE_1( AxBox4, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox4, is_nan(v.lo) || is_nan(v.hi))


    template <typename T, typename U>
    requires trait::is_arithmetic_v<T>
    constexpr AxBox4<trait::product_t<T,U>> operator*(T a, const AxBox4<U>& b) noexcept;

    /*! \brief Computes the center of a 4D axially aligned box
    */
    template <typename T>
    constexpr Vector4<T>    center(const AxBox4<T>& box) noexcept;

    /*! \brief Computes the hyper volume of the box
    */
    template <typename T>
    constexpr trait::fourth_t<T>   hypervolume(const AxBox4<T>& box) noexcept;

    //! Checks for validity (hi >= lo)
    template <typename T>
    constexpr bool          is_valid(const AxBox4<T>& box) noexcept;

    /*! \brief Returns the span (dimensions) of the box
    */
    template <typename T>
    constexpr Vector4<T>    span(const AxBox4<T>&box) noexcept;
}

YQ_TYPE_DECLARE(yq::AxBox4D)
YQ_TYPE_DECLARE(yq::AxBox4F)
YQ_TYPE_DECLARE(yq::AxBox4I)
YQ_TYPE_DECLARE(yq::AxBox4U)

