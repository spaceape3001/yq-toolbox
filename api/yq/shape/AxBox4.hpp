////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#define YQ_MATH_AXBOX4_HPP 1

#include <yq/typedef/axbox4.hpp>

#include <yq/keywords.hpp>
#include <yq/core/Expect.hpp>
#include <yq/trait/is_floating_point.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>
#include <yq/trait/unity.hpp>
#include <yq/vector/Vector4.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    struct Side;
    template <typename> struct AxCorners4;
    template <typename> struct Data4;
    template <typename> struct Range;

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
        
        //! Default constructor
        constexpr AxBox4() noexcept = default;

        /*! \brief Initializing constructor with ONE value
        
            This constructor initializes BOTH lo and hi with the same value.  
            This will technically be a valid axbox with zero span.
        */
        explicit constexpr AxBox4(const Vector4<T>& a)  noexcept: lo(a), hi(a) {}

        /*! \brief Initializing constructor with TWO values
        
            This constructor initializes the box as specified.  
            
            \note This result may be an invalid box with negative spans.
        */
        constexpr AxBox4(const Vector4<T>& _lo, const Vector4<T>& _hi)  noexcept : lo(_lo), hi(_hi) {}

        /*! \brief Construct as an intersection of points
        
            This takes the smallest box from the given low and high values.
            
            \note This result may be an invalid box if *ANY* lows have components higher than a corresponding high value

            \param[in] low Low values
            \param[in] high High values
        */
        constexpr AxBox4(intersect_t, std::initializer_list<Vector4<T>>, std::initializer_list<Vector4<T>>) noexcept;

        /*! \brief Construct as an intersection of points
        
            This takes the smallest box from the given low and high values.
            
            \note This result may be an invalid box if *ANY* lows have components higher than a corresponding high value

            \param[in] low Low values
            \param[in] high High values
        */
        constexpr AxBox4(intersect_t, std::span<const Vector4<T>>, std::span<const Vector4<T>>) noexcept;

        /*! \brief Construct a box using the two points
        
            This ensures lo <= hi (unless infinite/nan)
        */
        constexpr AxBox4(sort_t, const Vector4<T>&a, const Vector4<T>& b) noexcept;

        /*! \brief Construct a box as a union of two points
        
            This ensures lo <= hi (unless infinite/nan)
        */
        constexpr AxBox4(union_t, const Vector4<T>&a, const Vector4<T>& b) noexcept;

        /*! \brief Construct a box as a union of multiple points
        
            This returns the bounding box of *ALL* the given points
        */
        constexpr AxBox4(union_t, std::initializer_list<Vector4<T>>) noexcept;

        /*! \brief Construct a box as a union of multiple points
        
            This returns the bounding box of *ALL* the given points
        */
        constexpr AxBox4(union_t, std::span<const Vector4<T>>) noexcept;

        /*! \brief Construct a box as a union of multiple points
        
            This constructor segregates the set of low and high points.
            
            \note It's possible to construct an invalid box if all the low points are above the high points.
            
            \param[in] low Low values
            \param[in] high High values
        */
        constexpr AxBox4(union_t, std::initializer_list<Vector4<T>>, std::initializer_list<Vector4<T>>) noexcept;

        /*! \brief Construct a box as a union of multiple points
        
            This constructor segregates the set of low and high points.
            
            \note It's possible to construct an invalid box if all the low points are above the high points.
            
            \param[in] low Low values
            \param[in] high High values
        */
        constexpr AxBox4(union_t, std::span<const Vector4<T>>, std::span<const Vector4<T>>) noexcept;

        //! Box of not-a-numbers
        template <typename=void> requires has_nan_v<T>
        consteval AxBox4(nan_t) : AxBox4(Vector4<T>(NAN)) {}

        //! Zero box
        consteval AxBox4(zero_t) : AxBox4(Vector4<T>(ZERO)) {}

        //! Constructs using the bounding box of the given segment
        explicit constexpr AxBox4(const Segment4<T>&) noexcept;

        //! Constructs using the bounding box of the given sphere
        explicit constexpr AxBox4(const Sphere4<T>&) noexcept;

        //! Constructs using the bounding box of the given triangel
        explicit constexpr AxBox4(const Triangle4<T>&) noexcept;

        //! Converts this box to another box of compatible type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator AxBox4<U>() const noexcept
        {
            return { (Vector4<U>) lo, (Vector4<U>) hi };
        }
        
        //! Converts this box to another box of compatible type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator AxBox4<U>() const 
        {
            return { (Vector4<U>) lo, (Vector4<U>) hi };
        }

        //! Equality operator (defaulted);
        constexpr bool operator==(const AxBox4&) const noexcept = default;

        //! Positive (affirmation) operator
        AxBox4  operator+() const noexcept;
        
        //! Negation operator
        AxBox4  operator-() const noexcept;

        //! Returns a box shifted by the given displacement
        AxBox4  operator+(const Vector4<T>&) const noexcept;
        
        //! Shifts this box by the given displacement
        AxBox4& operator+=(const Vector4<T>&) noexcept;
        
        //! Returns a box shifted opposite the given displacement
        AxBox4  operator-(const Vector4<T>&) const noexcept;
        
        //! Shifts this box opposite the given displacement
        AxBox4& operator-=(const Vector4<T>&) noexcept;

        //! Returns a box scaled by the given factor
        template <typename U>
        requires is_arithmetic_v<U>
        AxBox4<product_t<T,U>> operator*(U) const noexcept;

        //! Scales this box by the given factor
        template <typename U>
        requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        AxBox4& operator*=(U) noexcept;
        
        //! Returns a box reduced by the given divisor
        template <typename U>
        requires is_arithmetic_v<U>
        AxBox4<quotient_t<T,U>> operator/(U) const noexcept;

        //! Reduces this box by the given divisor
        template <typename U>
        requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        AxBox4& operator/=(U) noexcept;
        
        
        /*! \brief Union of two AABBs
        */
        constexpr AxBox4<T> operator|(const AxBox4<T>&b) const noexcept;

        //! Returns a box unioned with this new point
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
        
        //! Minimum sphere needed to contain the box
        constexpr Sphere4<T>        circumsphere() const noexcept;

        //! Classifies the point with respect to the box
        constexpr Data4<Side>       classify(const Vector4<T>&) const noexcept;

        //! Classifies the given W coordinate with respect to the box
        constexpr Side              classify_w(T) const noexcept;

        //! Classifies the vector's W coordinate with respect to the box
        constexpr Side              classify_w(const Vector4<T>&) const noexcept;

        //! Classifies the given X coordinate with respect to the box
        constexpr Side              classify_x(T) const noexcept;

        //! Classifies the vector's X coordinate with respect to the box
        constexpr Side              classify_x(const Vector4<T>&) const noexcept;

        //! Classifies the given Y coordinate with respect to the box
        constexpr Side              classify_y(T) const noexcept;

        //! Classifies the vector's Y coordinate with respect to the box
        constexpr Side              classify_y(const Vector4<T>&) const noexcept;

        //! Classifies the given Z coordinate with respect to the box
        constexpr Side              classify_z(T) const noexcept;

        //! Classifies the vector's Z coordinate with respect to the box
        constexpr Side              classify_z(const Vector4<T>&) const noexcept;


        /*! \brief Checks if the point is inside (or touching) the box
        */
        constexpr bool contains (const Vector4<T>& pt) const noexcept;

        /*! \brief Returns ALL the corners of the box 
        */
        constexpr AxCorners4<Vector4<T>>  corners() const noexcept;

        //! Corners adjusted outward by the given value
        constexpr AxCorners4<Vector4<T>>  corners(T adjust) const noexcept;
        
        //! Distance to box (zero if inside)
        T                       distance(const Vector4<T>&) const;
        
        //! Distance² to box (zero if inside)
        constexpr square_t<T>   distance²(const Vector4<T>&) const noexcept;

        /*! \brief Checks for full occlusion
        
            A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
            \param[in] Big   The "bigger" box, if eclipsed
            \param[in] Small The "smaller" box, if eclipsed
        */
        constexpr bool eclipses(const AxBox4<T>& b) const noexcept;

        //! Returns a fixed copy of the box (assuming it's possible to do)
        constexpr AxBox4 fixed() const noexcept;

        /*! \brief Fraction of the box the given w is positioned
        
            This gives the fractional "w" that the w-value is positioned across the box (lo -> hi)
            
            \param[in] w    W-coordinate to check
            \return the fraction along the box's w-dimension
        */
        //  TODO accommodate integer based T
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<unity_t<T>>    fraction_w(T w) const noexcept;

        /*! \brief Fraction of the box the given w is positioned
        
            This gives the fractional "w" that the w-value is positioned across the box (lo -> hi)
            
            \param[in] w    W-coordinate to check
            \param[in] ep   Epsilon to check the dimensional size
            \return the fraction along the box's w-dimension
            \note The epsilon check will be buggy on invalid boxes!
        */
        //  TODO accommodate integer based T
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<unity_t<T>>    fraction_w(T w, T ep) const noexcept;

        /*! \brief Fraction of the box the given x is positioned
        
            This gives the fractional "x" that the x-value is positioned across the box (lo -> hi)
            
            \param[in] x    x-coordinate to check
            \return the fraction along the box's x-dimension
        */
        //  TODO accommodate integer based T
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<unity_t<T>>    fraction_x(T x) const noexcept;

        /*! \brief Fraction of the box the given x is positioned
        
            This gives the fractional "x" that the x-value is positioned across the box (lo -> hi)
            
            \param[in] x    X-coordinate to check
            \param[in] ep   Epsilon to check the dimensional size
            \return the fraction along the box's x-dimension
            \note The epsilon check will be buggy on invalid boxes!
        */
        //  TODO accommodate integer based T
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<unity_t<T>>    fraction_x(T x, T ep) const noexcept;

        /*! \brief Fraction of the box the given y is positioned
        
            This gives the fractional "y" that the y-value is positioned across the box (lo -> hi)
            
            \param[in] y    Y-coordinate to check
            \return the fraction along the box's y-dimension
        */
        //  TODO accommodate integer based T
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<unity_t<T>>    fraction_y(T y) const noexcept;

        /*! \brief Fraction of the box the given y is positioned
        
            This gives the fractional "y" that the y-value is positioned across the box (lo -> hi)
            
            \param[in] y    Y-coordinate to check
            \param[in] ep   Epsilon to check the dimensional size
            \return the fraction along the box's y-dimension
            \note The epsilon check will be buggy on invalid boxes!
        */
        //  TODO accommodate integer based T
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<unity_t<T>>    fraction_y(T y, T ep) const noexcept;

        /*! \brief Fraction of the box the given z is positioned
        
            This gives the fractional "z" that the z-value is positioned across the box (lo -> hi)
            
            \param[in] z    Z-coordinate to check
            \return the fraction along the box's z-dimension
        */
        //  TODO accommodate integer based T
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<unity_t<T>>    fraction_z(T z) const noexcept;

        /*! \brief Fraction of the box the given z is positioned
        
            This gives the fractional "z" that the z-value is positioned across the box (lo -> hi)
            
            \param[in] z    Z-coordinate to check
            \param[in] ep   Epsilon to check the dimensional size
            \return the fraction along the box's z-dimension
            \note The epsilon check will be buggy on invalid boxes!
        */
        //  TODO accommodate integer based T
        template <typename=void>
        requires is_floating_point_v<T>
        Expect<unity_t<T>>    fraction_z(T z, T ep) const noexcept;

        //! Hi-hi-hi-hi corner of this box
        constexpr Vector4<T>    hhhh() const noexcept;

        //! Hi-hi-hi-hi corner of this box
        constexpr Vector4<T>    hhhh(T adjust) const noexcept;

        //! Hi-hi-hi-lo corner of this box
        constexpr Vector4<T>    hhhl() const noexcept;

        //! Hi-hi-hi-lo corner of this box
        constexpr Vector4<T>    hhhl(T adjust) const noexcept;

        //! Hi-hi-lo-hi corner of this box
        constexpr Vector4<T>    hhlh() const noexcept;

        //! Hi-hi-lo-hi corner of this box
        constexpr Vector4<T>    hhlh(T adjust) const noexcept;

        //! Hi-hi-lo-lo corner of this box
        constexpr Vector4<T>    hhll() const noexcept;

        //! Hi-hi-lo-lo corner of this box
        constexpr Vector4<T>    hhll(T adjust) const noexcept;

        //! Hi-lo-hi-hi corner of this box
        constexpr Vector4<T>    hlhh() const noexcept;

        //! Hi-lo-hi-hi corner of this box
        constexpr Vector4<T>    hlhh(T adjust) const noexcept;

        //! Hi-lo-hi-lo corner of this box
        constexpr Vector4<T>    hlhl() const noexcept;

        //! Hi-lo-hi-lo corner of this box
        constexpr Vector4<T>    hlhl(T adjust) const noexcept;

        //! Hi-lo-lo-hi corner of this box
        constexpr Vector4<T>    hllh() const noexcept;

        //! Hi-lo-lo-hi corner of this box
        constexpr Vector4<T>    hllh(T adjust) const noexcept;

        //! Hi-lo-lo-lo corner of this box
        constexpr Vector4<T>    hlll() const noexcept;

        //! Hi-lo-lo-lo corner of this box
        constexpr Vector4<T>    hlll(T adjust) const noexcept;

        /*! \brief Computes the hyper volume of the box
        */
        constexpr fourth_t<T> hypervolume() const noexcept;

        /*! \brief Computes the hyper volume of the box
        
            \note This instance guards against negative numbers
        */
        constexpr fourth_t<T> hypervolume(guard_t) const noexcept;

        /*! \brief Inflates the box
        
            This inflates the box by the specified amount.  
            \note Negatives will shrink the box, and the shrunken box may be invalid.  Use "shrink" to safeguard.
        */
        constexpr AxBox4    inflate(T) const noexcept;

        /*! \brief Inflates the box
        
            This guards against invalid boxes, by first fixing it, and second, limiting any shrinkage to 
            half the minimum dimension of the box (ie, it'll be zero-thickness if the limit is activated)
        */
        constexpr AxBox4    inflate(guard_t, T) const noexcept;

        //! Largest sphere contained by this box (won't touch all sides)
        constexpr Sphere4<T>    insphere() const noexcept;

        //! Checks for validity (hi >= lo)
        constexpr bool    is_valid() const noexcept;

        //! Lo-hi-hi-hi corner of this box
        constexpr Vector4<T>    lhhh() const noexcept;

        //! Lo-hi-hi-hi corner of this box, adjusted outward by the given amount
        constexpr Vector4<T>    lhhh(T adjust) const noexcept;

        //! Lo-hi-hi-lo corner of this box
        constexpr Vector4<T>    lhhl() const noexcept;

        //! Lo-hi-hi-lo corner of this box, adjusted outward by the given amount
        constexpr Vector4<T>    lhhl(T adjust) const noexcept;

        //! Lo-hi-lo-hi corner of this box
        constexpr Vector4<T>    lhlh() const noexcept;

        //! Lo-hi-lo-hi corner of this box, adjusted outward by the given amount
        constexpr Vector4<T>    lhlh(T adjust) const noexcept;

        //! Lo-hi-lo-lo corner of this box
        constexpr Vector4<T>    lhll() const noexcept;

        //! Lo-hi-lo-lo corner of this box, adjusted outward by the given amount
        constexpr Vector4<T>    lhll(T adjust) const noexcept;

        //! Lo-lo-hi-hi corner of this box
        constexpr Vector4<T>    llhh() const noexcept;

        //! Lo-lo-hi-hi corner of this box, adjusted outward by the given amount
        constexpr Vector4<T>    llhh(T adjust) const noexcept;

        //! Lo-lo-hi-lo corner of this box
        constexpr Vector4<T>    llhl() const noexcept;

        //! Lo-lo-hi-lo corner of this box, adjusted outward by the given amount
        constexpr Vector4<T>    llhl(T adjust) const noexcept;

        //! Lo-lo-lo-hi corner of this box
        constexpr Vector4<T>    lllh() const noexcept;

        //! Lo-lo-lo-hi corner of this box, adjusted outward by the given amount
        constexpr Vector4<T>    lllh(T adjust) const noexcept;

        //! Lo-lo-lo-lo corner of this box
        constexpr Vector4<T>    llll() const noexcept;

        //! Lo-lo-lo-lo corner of this box, adjusted outward by the given amount
        constexpr Vector4<T>    llll(T adjust) const noexcept;

        //! Minimum inflation number on a valid box to keep it from going invalid
        constexpr T min_inflate() const noexcept;

        //! Nearest point (itself if inside)
        //constexpr Vector4<T>    nearest(const Vector4<T>&) const noexcept;

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

        /*! \brief Returns the size of the box
        */
        constexpr Size4<T> size() const noexcept;

        /*! \brief Returns the span (dimensions) of the box
        */
        constexpr Vector4<T>    span() const noexcept;

        /*! \brief Span (dimensions) of this box
        
            This guards against negative values (ie, takes absolute value)
        */
        constexpr Vector4<T>    span(guard_t) const noexcept;

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
    YQ_INTEGER_1(AxBox4)
    
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


    //! Returns a scaled right box by the given left factor
    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr AxBox4<product_t<T,U>> operator*(T a, const AxBox4<U>& b) noexcept;

    /*! \brief Computes the center of a 4D axially aligned box
    */
    template <typename T>
    constexpr Vector4<T>    center(const AxBox4<T>& box) noexcept;


    //! Computes the centroid of the given box (same as the center)
    template <typename T>
    Vector4<T>  centroid(const AxBox4<T>& box);

    /*! \brief Computes the hyper volume of the box
    */
    template <typename T>
    constexpr fourth_t<T>   hypervolume(const AxBox4<T>& box) noexcept;

    //! Checks for validity (hi >= lo)
    template <typename T>
    constexpr bool          is_valid(const AxBox4<T>& box) noexcept;

    /*! \brief Returns the span (dimensions) of the box
    */
    template <typename T>
    constexpr Vector4<T>    span(const AxBox4<T>&box) noexcept;

    //! Streaming assistant to text/debugging style output streams
    template <typename S, typename T>
    S&  as_stream(S& s, const AxBox4<T>& v);
    
    //! Streams to the internal text-based stream
    template <typename T>
    Stream& operator<<(Stream&s, const AxBox4<T>& v);

    //! Streams to a logging stream
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const AxBox4<T>& v);
}


YQ_TYPE_DECLARE(yq::AxBox4D)
YQ_TYPE_DECLARE(yq::AxBox4F)
YQ_TYPE_DECLARE(yq::AxBox4I)
YQ_TYPE_DECLARE(yq::AxBox4U)

