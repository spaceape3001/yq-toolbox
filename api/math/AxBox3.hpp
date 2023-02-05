////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <math/preamble.hpp>
#include <math/Range.hpp>
#include <math/Vector3.hpp>
#include <math/AxCorners3.hpp>

namespace yq {

    /*! \brief Axially aligned box in 3 dimension(s).

        Note, lo vs hi isn't enforced, however it's expected that lo < hi, which 
        is what "is_valid" will check.
    */
    template <typename T>
    struct AxBox3 {
    
        //! Component type (capturing the template argument)
        using component_type   = T;
        
        //! Low corner
        Vector3<T>  lo;
        
        //! High corner
        Vector3<T>  hi;
        
        constexpr AxBox3() noexcept = default;
        explicit constexpr AxBox3(const Vector3<T>& a) noexcept : lo(a), hi(a) {}
        constexpr AxBox3(const Vector3<T>& _lo, const Vector3<T>& _hi) noexcept : lo(_lo), hi(_hi) {}
        constexpr AxBox3(intersect_t, std::initializer_list<Vector3<T>>, std::initializer_list<Vector3<T>>) noexcept;
        constexpr AxBox3(intersect_t, std::span<const Vector3<T>>, std::span<const Vector3<T>>) noexcept;
        constexpr AxBox3(sort_t, const Vector3<T>&a, const Vector3<T>& b) noexcept;
        constexpr AxBox3(union_t, const Vector3<T>&a, const Vector3<T>& b) noexcept;
        constexpr AxBox3(union_t, std::initializer_list<Vector3<T>>) noexcept;
        constexpr AxBox3(union_t, std::span<const Vector3<T>>) noexcept;
        constexpr AxBox3(union_t, std::initializer_list<Vector3<T>>, std::initializer_list<Vector3<T>>) noexcept;
        constexpr AxBox3(union_t, std::span<const Vector3<T>>, std::span<const Vector3<T>>) noexcept;

        template <typename=void> requires trait::has_nan_v<T>
        consteval AxBox3(nan_t) : AxBox3(Vector3<T>(NAN)) {}
        consteval AxBox3(zero_t) : AxBox3(Vector3<T>(ZERO)) {}

        explicit constexpr AxBox3(const Segment3<T>&) noexcept;
        explicit constexpr AxBox3(const Triangle3<T>&) noexcept;

        //! Equality operator (defaulted);
        constexpr bool operator==(const AxBox3&) const noexcept = default;

        AxBox3  operator+() const noexcept;
        AxBox3  operator-() const noexcept;

        AxBox3  operator+(const Vector3<T>&) const noexcept;
        AxBox3& operator+=(const Vector3<T>&) noexcept;
        AxBox3  operator-(const Vector3<T>&) const noexcept;
        AxBox3& operator-=(const Vector3<T>&) noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        AxBox3<product_t<T,U>> operator*(U) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_mul_v<T,U>)
        AxBox3& operator*=(U) noexcept;
        
        template <typename U>
        requires trait::is_arithmetic_v<U>
        AxBox3<quotient_t<T,U>> operator/(U) const noexcept;

        template <typename U>
        requires (trait::is_arithmetic_v<U> && trait::self_div_v<T,U>)
        AxBox3& operator/=(U) noexcept;
        

        /*! \brief Union of two AABBs
        */
        constexpr AxBox3<T> operator|(const AxBox3<T>&b) const noexcept;

        constexpr AxBox3<T> operator|(const Vector3<T>&b) const noexcept;

        //! Union in a box
        AxBox3& operator|=(const AxBox3& b) noexcept;

        //! Unions in a vector
        AxBox3& operator|=(const Vector3<T>& b) noexcept;

        /*! \brief Intersection of two AABBs
        */
        constexpr AxBox3<T> operator&(const AxBox3<T>&b) const noexcept;

        //! Intersection into self 
        AxBox3& operator&=(const AxBox3& b) noexcept;

        /*! \brief Computes the center of a 3D axially aligned box
        */
        constexpr Vector3<T>      center() const noexcept;

        /*! \brief Checks if the point is inside (or touching) the box
        */
        constexpr bool contains(const Vector3<T>& pt) const noexcept;

        /*! \brief Returns ALL the corners of the box 
        */
        constexpr AxCorners3<Vector3<T>>  corners() const noexcept;

        /*! \brief Checks for full occlusion
        
            A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
            \param[in] Big   The "bigger" box, if eclipsed
            \param[in] Small The "smaller" box, if eclipsed
        */
        constexpr bool eclipses(const AxBox3<T>& b) const noexcept;

        //! Returns a fixed copy of the box (assuming it's possible to do)
        constexpr AxBox3 fixed() const noexcept;

        //! Check for validity
        constexpr bool    is_valid() const noexcept;

       /*! \brief Returns the north east bottom corner
        */
        constexpr Vector3<T>  northeast_bottom() const noexcept;

        /*! \brief Returns the north east top corner
        */
        constexpr Vector3<T>  northeast_top() const noexcept;

        /*! \brief Returns the north west bottom corner
        */
        constexpr Vector3<T>  northwest_bottom() const noexcept;

        /*! \brief Returns the north west top corner
        */
        constexpr Vector3<T>  northwest_top() const noexcept;

        /*! \brief Checks for any overlap
        
            This returns TRUE if *ANY* part of the boxes overlap (or touch)
        */
        constexpr bool overlaps(const AxBox3<T>& b) const noexcept;

        /*! \brief Projects a local [0,1] coordinate to a global coordinate based on the provided axially aligned box
        
            \param[in] v    The local coordinate
            \return The global coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector3<T>   project(const Vector3<T>& v) const noexcept;

        constexpr Size3<T> size() const noexcept ;

        /*! \brief Returns the south east bottom corner
        */
        constexpr Vector3<T>  southeast_bottom() const noexcept;

        /*! \brief Returns the south east top corner
        */
        constexpr Vector3<T>  southeast_top() const noexcept;

        /*! \brief Returns the south west bottom corner
        */
        constexpr Vector3<T>  southwest_bottom() const noexcept;

        /*! \brief Returns the south west top corner
        */
        constexpr Vector3<T>  southwest_top() const noexcept;

        /*! \brief Returns the span (dimensions) of the box
        */
        constexpr Vector3<T>    span() const noexcept;

        /*! \brief Computes the surface area of a 3D axially aligned bounding box
        */
        constexpr square_t<T>    surface_area() const noexcept;


        /*! \brief Projects a global coordinate to a local [0,1] coordinate for the axially aligned box

            \param[in] v    The global coordinate
            \return The local coordinate
        */
        template <typename=void>
        requires std::is_floating_point_v<T>
        constexpr Vector3<T>   unproject(const Vector3<T>& v) const noexcept;

        //! Tests this box for validness
        constexpr bool          valid() const noexcept ;

        /*! \brief Computes the volume of the box
        */
        constexpr cube_t<T>       volume() const noexcept;

        //! X Range of the box
        constexpr Range<T>  x_range() const noexcept;

        //! Y Range of the box
        constexpr Range<T>  y_range() const noexcept;

        //! Z Range of the box
        constexpr Range<T>  z_range() const noexcept;

    };

    YQ_IEEE754_1(AxBox3)
    

    /*! \brief Creates a 3D axially aligned box from one vector
    */
    template <typename T>
    constexpr AxBox3<T> aabb(const Vector3<T>& a) noexcept;

    /*! \brief Creates a 3D axially aligned box from two vectors
    */
    template <typename T>
    constexpr AxBox3<T> aabb(const Vector3<T>& a, const Vector3<T>& b) noexcept;

    /*! \brief Creates a 3D axially aligned box from container of Vector2's
    */
    template <typename T>
    AxBox3<T> aabb(const std::vector<Vector3<T>>& vals);

    YQ_NAN_1(AxBox3, AxBox3<T>(NAN));
    YQ_ZERO_1(AxBox3, AxBox3<T>(ZERO));

    YQ_IS_FINITE_1( AxBox3, is_finite(v.lo) && is_finite(v.hi))
    YQ_IS_NAN_1(AxBox3, is_nan(v.lo) || is_nan(v.hi))


    /*! \brief Computes the center of a 3D axially aligned box
    */
    template <typename T>
    constexpr Vector3<T>      center(const AxBox3<T>& box) noexcept;

    //! Checks for validity (hi >= lo)
    template <typename T>
    constexpr bool    is_valid(const AxBox3<T>& box) noexcept;


    /*! \brief Returns the span (dimensions) of the box
    */
    template <typename T>
    constexpr Vector3<T>    span(const AxBox3<T>&box) noexcept;

    /*! \brief Computes the surface area of a 3D axially aligned bounding box
    */
    template <typename T>
    constexpr square_t<T>    surface_area(const AxBox3<T>& box) noexcept;

    /*! \brief Computes the volume of the box
    */
    template <typename T>
    constexpr cube_t<T>       volume(const AxBox3<T>& box) noexcept;

}

YQ_TYPE_DECLARE(yq::AxBox3D)
YQ_TYPE_DECLARE(yq::AxBox3F)
YQ_TYPE_DECLARE(yq::AxBox3I)
YQ_TYPE_DECLARE(yq::AxBox3U)

