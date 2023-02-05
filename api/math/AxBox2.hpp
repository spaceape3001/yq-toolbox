////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Range.hpp>
#include <math/Size2.hpp>
#include <math/Vector2.hpp>
#include <math/AxCorners2.hpp>

namespace yq {

    /*! \brief Axially aligned box in 2 dimension(s).
    
        Note, lo vs hi isn't enforced, however it's expected that lo < hi, which 
        is what "is_valid" will check.
    */
    template <typename T>
    struct AxBox2 {
        //! Component type (ie, the argument)
        using component_type    = T;
        
        Vector2<T>  lo; //!< Lower bounds
        Vector2<T>  hi; //!< Upper bounds
        
        constexpr AxBox2() noexcept = default;
        constexpr AxBox2(const Vector2<T>& a) noexcept : lo(a), hi(a) {}
        constexpr AxBox2(const Vector2<T>& _lo, const Vector2<T>& _hi) noexcept : lo(_lo), hi(_hi) {}
        constexpr AxBox2(intersection_t, std::initializer_list<Vector2<T>>, std::initializer_list<Vector2<T>>) noexcept;
        constexpr AxBox2(intersection_t, std::span<const Vector2<T>>, std::span<const Vector2<T>>) noexcept;
        constexpr AxBox2(sort_t, const Vector2<T>&a, const Vector2<T>& b) noexcept;
        constexpr AxBox2(union_t, const Vector2<T>&a, const Vector2<T>& b) noexcept;
        constexpr AxBox2(union_t, std::initializer_list<Vector2<T>>) noexcept;
        constexpr AxBox2(union_t, std::span<const Vector2<T>>) noexcept;
        constexpr AxBox2(union_t, std::initializer_list<Vector2<T>>, std::initializer_list<Vector2<T>>) noexcept;
        constexpr AxBox2(union_t, std::span<const Vector2<T>>, std::span<const Vector2<T>>) noexcept;
        
        template <typename=void> requires trait::has_nan_v<T>
        consteval AxBox2(nan_t) : AxBox2(Vector2<T>(NAN)) {}

        consteval AxBox2(zero_t) : AxBox2(Vector2<T>(ZERO)) {}

        explicit constexpr AxBox2(const Circle2<T>&) noexcept;
        explicit constexpr AxBox2(const Segment2<T>&) noexcept;
        explicit constexpr AxBox2(const Triangle2<T>&) noexcept;

        //! Equality operator (defaulted)
        constexpr bool operator==(const AxBox2&) const noexcept = default;

        AxBox2  operator+() const noexcept;
        AxBox2  operator-() const noexcept;

        AxBox2  operator+(const Vector2<T>&) const noexcept;
        AxBox2& operator+=(const Vector2<T>&) noexcept;
        AxBox2  operator-(const Vector2<T>&) const noexcept;
        AxBox2& operator-=(const Vector2<T>&) noexcept;

        template <typename U>
        requires trait::is_arithmetic_v<U>
        AxBox2<product_t<T,U>> operator*(U) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        AxBox2& operator*=(U) noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        AxBox2<quotient_t<T,U>> operator/(U) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        AxBox2& operator/=(U) noexcept;
        

        //! Union
        constexpr AxBox2 operator|(const AxBox2<T>&b) const noexcept;

        constexpr AxBox2 operator|(const Vector2<T>&b) const noexcept;

        //! Union in a box
        AxBox2& operator|=(const AxBox2& b) noexcept;

        //! Unions in a vector
        AxBox2& operator|=(const Vector2<T>& b) noexcept;

        //! Intersection 
        constexpr AxBox2 operator&(const AxBox2<T>&b) const noexcept;
        
        //! Intersection into self 
        AxBox2& operator&=(const AxBox2& b) noexcept;
        

        /*! \brief Computes the area
        */
        constexpr square_t<T>               area() const noexcept;

        /*! \brief Computes the center
        */
        constexpr Vector2<T>                center() const noexcept;

        /*! \brief Computes smallest circle that contains the box
            \note The resulting circle will be centered within the box
        */
        Circle2<T>  circumcircle() const;

        /*! \brief Checks if the point is inside (or touching) the box
        */
        constexpr bool          contains(const Vector2<T>& pt) const noexcept;

        /*! \brief Our corners
        */
        constexpr AxCorners2<Vector2<T>>    corners() const noexcept;

        /*! \brief Checks for full occlusion
        
            A small box is "eclipsed" if it's wholy contained (or touching edges) by this box.
            \param[in] Small The "smaller" box, if eclipsed
        */
        constexpr bool          eclipses(const AxBox2<T>& b) const noexcept;

        /*! \brief Checks for full occlusion
        
            A small box is "eclipsed" if it's wholy contained (or touching edges) by this box.
            \param[in] Small The "smaller" box, if eclipsed
        */
        constexpr bool          eclipses(const Circle2<T>& b) const noexcept;

        //! Returns a fixed copy of the box (assuming it's possible to do)
        constexpr AxBox2 fixed() const noexcept;

        /*! \brief Computes largest circle that's inside the box
            \note The resulting circle will be centered within the box
        */
        constexpr Circle2<T>  incircle() const noexcept;

        //! Tests this box for validness
        constexpr bool          is_valid() const noexcept;
            
        //! Returns the northeast corner of the box
        constexpr Vector2<T>    northeast() const noexcept;

        //! Returns the northwest corner of the box
        constexpr Vector2<T>    northwest() const noexcept;
        
        /*! \brief Checks for any overlap
        
            This returns TRUE if *ANY* part of the boxes overlap (or touch)
        */
        constexpr bool          overlaps(const AxBox2<T>& b) noexcept;

        /*! \brief Computes the perimeter of the box */
        constexpr T             perimeter() const noexcept;

        /*! \brief Projects a local [0,1] coordinate to a global coordinate based on the provided axially aligned box
        
            \param[in] v    The local coordinate
            \return The global coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector2<T>    project(const Vector2<T>& v) const noexcept;

        /*! \brief Returns the size of the box
        */
        constexpr Size2<T> size() const noexcept;


        //! Returns the southeast corner of the box
        constexpr Vector2<T>    southeast() const noexcept;
        
        //! Returns the southwest corner of the box
        constexpr Vector2<T>    southwest() const noexcept;

        /*! \brief Returns the span (dimensions) of the box
        */
        constexpr Vector2<T>    span() const noexcept;
        

        /*! \brief Projects a global coordinate to a local [0,1] coordinate for the axially aligned box

            \param[in] bx   The axially aligned box
            \param[in] v    The global coordinate
            \return The local coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector2<T>   unproject(const Vector2<T>& v) const noexcept;

        //! Tests this box for validness
        constexpr bool          valid() const noexcept;

        //! X Range of the box
        constexpr Range<T>      x_range() const noexcept;
        
        //! X size of the box
        constexpr T             x_size() const noexcept;
        
        //! Y Range of the box
        constexpr Range<T>      y_range() const noexcept;
        
        //! Y size of the box
        constexpr T             y_size() const noexcept;
    };

    YQ_IEEE754_1(AxBox2)

//  --------------------------------------------------------
//  COMPOSITION

    /*! \brief Creates a 2D axially aligned box from one vector
    */
    template <typename T>
    constexpr AxBox2<T> aabb(const Vector2<T>& a);
    
    /*! \brief Creates a 2D axially aligned box from two vectors
    */
    template <typename T>
    constexpr AxBox2<T> aabb(const Vector2<T>& a, const Vector2<T>& b);

    /*! \brief Creates a 2D axially aligned box from container of Vector2's
    */
    template <typename T>
    AxBox2<T> aabb(const std::vector<Vector2<T>>& vals);

    YQ_NAN_1(AxBox2, AxBox2<T>(NAN));
    YQ_ZERO_1(AxBox2, AxBox2<T>(ZERO));

    YQ_IS_FINITE_1( AxBox2, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox2, is_nan(v.lo) || is_nan(v.hi))


    /*! \brief Computes the area of a 2D axially aligned bounding box
    */
    template <typename T>
    constexpr square_t<T>   area(const AxBox2<T>& ax) noexcept;

    /*! \brief Computes the center of a 2D axially aligned box
    */
    template <typename T>
    constexpr Vector2<T>    center(const AxBox2<T>& box) noexcept;

    /*! \brief Computes smallest circle containing the given box
    
        \note The resulting circle will be centered within the box
    */
    template <typename T>
    Circle2<T>    circumcircle(const AxBox2<T>& box);

    /*! \brief Computes biggest circle within the bounding box
    
        \note The resulting circle will be centered within the box
    */
    template <typename T>
    constexpr Circle2<T>    incircle(const AxBox2<T>& box) noexcept;

    //! Checks for validity (hi >= lo)
    template <typename T>
    constexpr bool          is_valid(const AxBox2<T>& a) noexcept;

    /*! \brief Computes the perimeter of the box */
    template <typename T>
    constexpr T             perimeter(const AxBox2<T>& ax) noexcept;

    /*! \brief Returns the span (dimensions) of the box
    */
    template <typename T>
    constexpr Vector2<T>    span(const AxBox2<T>&a) noexcept;
}

YQ_TYPE_DECLARE(yq::AxBox2D)
YQ_TYPE_DECLARE(yq::AxBox2F)
YQ_TYPE_DECLARE(yq::AxBox2I)
YQ_TYPE_DECLARE(yq::AxBox2U)

