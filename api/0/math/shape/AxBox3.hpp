////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#define YQ_MATH_AXBOX3_HPP 1

#include <0/math/preamble.hpp>
#include <0/math/vector/Vector3.hpp>

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
        
        //! Default constructor
        constexpr AxBox3() noexcept = default;

        /*! \brief Initializing constructor with ONE value
        
            This constructor initializes BOTH lo and hi with the same value.  
            This will technically be a valid axbox with zero span.
        */
        explicit constexpr AxBox3(const Vector3<T>& a) noexcept : lo(a), hi(a) {}

        /*! \brief Initializing constructor with TWO values
        
            This constructor initializes the box as specified.  
            
            \note This result may be an invalid box with negative spans.
        */
        constexpr AxBox3(const Vector3<T>& _lo, const Vector3<T>& _hi) noexcept : lo(_lo), hi(_hi) {}

        /*! \brief Construct as an intersection of points
        
            This takes the smallest box from the given low and high values.
            
            \note This result may be an invalid box if *ANY* lows have components higher than a corresponding high value

            \param[in] low Low values
            \param[in] high High values
        */
        constexpr AxBox3(intersect_t, std::initializer_list<Vector3<T>>, std::initializer_list<Vector3<T>>) noexcept;

        /*! \brief Construct as an intersection of points
        
            This takes the smallest box from the given low and high values.
            
            \note This result may be an invalid box if *ANY* lows have components higher than a corresponding high value

            \param[in] low Low values
            \param[in] high High values
        */
        constexpr AxBox3(intersect_t, std::span<const Vector3<T>>, std::span<const Vector3<T>>) noexcept;

        /*! \brief Construct a box using the two points
        
            This ensures lo <= hi (unless infinite/nan)
        */
        constexpr AxBox3(sort_t, const Vector3<T>&a, const Vector3<T>& b) noexcept;

        /*! \brief Construct a box as a union of two points
        
            This ensures lo <= hi (unless infinite/nan)
        */
        constexpr AxBox3(union_t, const Vector3<T>&a, const Vector3<T>& b) noexcept;

        /*! \brief Construct a box as a union of multiple points
        
            This returns the bounding box of *ALL* the given points
        */
        constexpr AxBox3(union_t, std::initializer_list<Vector3<T>>) noexcept;

        /*! \brief Construct a box as a union of multiple points
        
            This returns the bounding box of *ALL* the given points
        */
        constexpr AxBox3(union_t, std::span<const Vector3<T>>) noexcept;

        /*! \brief Construct a box as a union of multiple points
        
            This constructor segregates the set of low and high points.
            
            \note It's possible to construct an invalid box if all the low points are above the high points.
            
            \param[in] low Low values
            \param[in] high High values
        */
        constexpr AxBox3(union_t, std::initializer_list<Vector3<T>>, std::initializer_list<Vector3<T>>) noexcept;

        /*! \brief Construct a box as a union of multiple points
        
            This constructor segregates the set of low and high points.
            
            \note It's possible to construct an invalid box if all the low points are above the high points.
            
            \param[in] low Low values
            \param[in] high High values
        */
        constexpr AxBox3(union_t, std::span<const Vector3<T>>, std::span<const Vector3<T>>) noexcept;

        //! Box of not-a-numbers
        template <typename=void> requires has_nan_v<T>
        consteval AxBox3(nan_t) : AxBox3(Vector3<T>(NAN)) {}

        //! Zero box
        consteval AxBox3(zero_t) : AxBox3(Vector3<T>(ZERO)) {}

        //! Constructs using the bounding box of the given segment
        explicit constexpr AxBox3(const Segment3<T>&) noexcept;

        //! Constructs using the bounding box of the given sphere
        explicit constexpr AxBox3(const Sphere3<T>&) noexcept;

        //! Constructs using the bounding box of the given triangle
        explicit constexpr AxBox3(const Triangle3<T>&) noexcept;

        //! Constructs using the bounding box of the given tetrahedron
        explicit constexpr AxBox3(const Tetrahedron3<T>&) noexcept;

        //! Converts to another box of compatible type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator AxBox3<U>() const noexcept
        {
            return { (Vector3<U>) lo, (Vector3<U>) hi };
        }
        
        //! Converts to another box of compatible type
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator AxBox3<U>() const 
        {
            return { (Vector3<U>) lo, (Vector3<U>) hi };
        }

        //! Equality operator (defaulted);
        constexpr bool operator==(const AxBox3&) const noexcept = default;

        //! Positive (affirmation) operator
        AxBox3  operator+() const noexcept;
        
        //! Negation operator
        AxBox3  operator-() const noexcept;

        //! Returns a box shifted by the given displacement
        AxBox3  operator+(const Vector3<T>&) const noexcept;
        
        //! Shifts this box by the given displacement
        AxBox3& operator+=(const Vector3<T>&) noexcept;
        
        //! Returns a box shifted opposite to the given displacement
        AxBox3  operator-(const Vector3<T>&) const noexcept;
        
        //! Shifts this box opposite to the given displacement
        AxBox3& operator-=(const Vector3<T>&) noexcept;
        
        //! Returns a box scaled by the given factor
        template <typename U>
        requires is_arithmetic_v<U>
        AxBox3<product_t<T,U>> operator*(U) const noexcept;

        //! Scales this box by the specified amount
        template <typename U>
        requires (is_arithmetic_v<U> && self_mul_v<T,U>)
        AxBox3& operator*=(U) noexcept;
        
        //! Returns a box reduced by the given factor
        template <typename U>
        requires is_arithmetic_v<U>
        AxBox3<quotient_t<T,U>> operator/(U) const noexcept;

        template <typename U>
        requires (is_arithmetic_v<U> && self_div_v<T,U>)
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

        //! Minimum sphere needed to contain the box
        constexpr Sphere3<T>        circumsphere() const noexcept;

        //! Classifies the point with respect to the box
        constexpr Data3<Side>       classify(const Vector3<T>&) const noexcept;

        //! Classifies the given X coordinate with respect to the box
        constexpr Side              classify_x(T) const noexcept;

        //! Classifies the vector's X coordinate with respect to the box
        constexpr Side              classify_x(const Vector3<T>&) const noexcept;

        //! Classifies the given Y coordinate with respect to the box
        constexpr Side              classify_y(T) const noexcept;

        //! Classifies the vector's Y coordinate with respect to the box
        constexpr Side              classify_y(const Vector3<T>&) const noexcept;

        //! Classifies the given Z coordinate with respect to the box
        constexpr Side              classify_z(T) const noexcept;

        //! Classifies the vector's Z coordinate with respect to the box
        constexpr Side              classify_z(const Vector3<T>&) const noexcept;


        /*! \brief Checks if the point is inside (or touching) the box
        */
        constexpr bool contains(const Vector3<T>& pt) const noexcept;

        /*! \brief Returns ALL the corners of the box 
        */
        constexpr AxCorners3<Vector3<T>>  corners() const noexcept;

        //! Corners adjusted outward by the given value
        constexpr AxCorners3<Vector3<T>>  corners(T adjust) const noexcept;

        //! Distance to box (zero if inside)
        T                       distance(const Vector3<T>&) const;
        
        //! Distance² to box (zero if inside)
        constexpr square_t<T>   distance²(const Vector3<T>&) const noexcept;

        /*! \brief Checks for full occlusion
        
            A small box is "eclipsed" if it's wholy contained (or touching edges) of the bigger box.
            \param[in] Big   The "bigger" box, if eclipsed
            \param[in] Small The "smaller" box, if eclipsed
        */
        constexpr bool eclipses(const AxBox3<T>& b) const noexcept;

        //! Returns a fixed copy of the box (assuming it's possible to do)
        constexpr AxBox3 fixed() const noexcept;

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

        //! Hi-hi-hi corner of this box
        constexpr Vector3<T>    hhh() const noexcept;

        //! Hi-hi-hi corner of this box, adjusted outward by the given amount
        constexpr Vector3<T>    hhh(T adjust) const noexcept;

        //! Hi-hi-lo corner of this box
        constexpr Vector3<T>    hhl() const noexcept;

        //! Hi-hi-lo corner of this box, adjusted outward by the given amount
        constexpr Vector3<T>    hhl(T adjust) const noexcept;

        //! Hi-lo-hi corner of this box
        constexpr Vector3<T>    hlh() const noexcept;

        //! Hi-lo-hi corner of this box, adjusted outward by the given amount
        constexpr Vector3<T>    hlh(T adjust) const noexcept;

        //! Hi-lo-li corner of this box
        constexpr Vector3<T>    hll() const noexcept;

        //! Hi-lo-lo corner of this box, adjusted outward by the given amount
        constexpr Vector3<T>    hll(T adjust) const noexcept;

        /*! \brief Inflates the box
        
            This inflates the box by the specified amount.  
            \note Negatives will shrink the box, and the shrunken box may be invalid.
        */
        constexpr AxBox3    inflate(T) const noexcept;

        /*! \brief Inflates the box
        
            This guards against invalid boxes, by first fixing it, and second, limiting any shrinkage to 
            half the minimum dimension of the box (ie, it'll be zero-thickness if the limit is activated)
        */
        constexpr AxBox3    inflate(guard_t, T) const noexcept;
        
        //! Largest sphere contained by this box (won't touch all sides)
        constexpr Sphere3<T>    insphere() const noexcept;

        //! Check for validity
        constexpr bool    is_valid() const noexcept;

        //! Lo-hi-hi corner of this box
        constexpr Vector3<T>    lhh() const noexcept;

        //! Lo-hi-hi corner of this box, adjusted outward by the given amount
        constexpr Vector3<T>    lhh(T adjust) const noexcept;

        //! Lo-hi-lo corner of this box
        constexpr Vector3<T>    lhl() const noexcept;

        //! Lo-hi-lo corner of this box, adjusted outward by the given amount
        constexpr Vector3<T>    lhl(T adjust) const noexcept;

        //! Lo-lo-hi corner of this box
        constexpr Vector3<T>    llh() const noexcept;

        //! Lo-lo-hi corner of this box, adjusted outward by the given amount
        constexpr Vector3<T>    llh(T adjust) const noexcept;

        //! Lo-lo-lo corner of this box
        constexpr Vector3<T>    lll() const noexcept;

        //! Lo-lo-lo corner of this box, adjusted outward by the given amount
        constexpr Vector3<T>    lll(T adjust) const noexcept;

        //! Minimum inflation number on a valid box to keep it from going invalid
        constexpr T min_inflate() const noexcept;

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

        /*! \brief Returns the size of the box
        */
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

        /*! \brief Span (dimensions) of this box
        
            This guards against negative values (ie, takes absolute value)
        */
        constexpr Vector3<T>    span(guard_t) const noexcept;

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

        /*! \brief Computes the volume of the box
            
            \note This one guards against negative volumes (ie, takes the absolute value)
        */
        constexpr cube_t<T>       volume(guard_t) const noexcept;

        //! X Range of the box
        constexpr Range<T>  x_range() const noexcept;

        //! Y Range of the box
        constexpr Range<T>  y_range() const noexcept;

        //! Z Range of the box
        constexpr Range<T>  z_range() const noexcept;

    };

    YQ_IEEE754_1(AxBox3)
    YQ_INTEGER_1(AxBox3)
    YQ_IS_INTEGER_1(AxBox3)
    

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

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr AxBox3<product_t<T,U>> operator*(T a, const AxBox3<U>&b) noexcept;

    /*! \brief Computes the center of a 3D axially aligned box
    */
    template <typename T>
    constexpr Vector3<T>      center(const AxBox3<T>& box) noexcept;

    //! Computes the centroid of the given box (same as the center)
    template <typename T>
    Vector3<T>  centroid(const AxBox3<T>& box);
    
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

    //! Streaming assistant to text/debugging style output streams
    template <typename S, typename T>
    S&  as_stream(S& s, const AxBox3<T>& v);
    
    //! Streams to the internal text-based stream
    template <typename T>
    Stream& operator<<(Stream&s, const AxBox3<T>& v);

    //! Streams to a logging stream
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const AxBox3<T>& v);
}

YQ_TYPE_DECLARE(yq::AxBox3D)
YQ_TYPE_DECLARE(yq::AxBox3F)
YQ_TYPE_DECLARE(yq::AxBox3I)
YQ_TYPE_DECLARE(yq::AxBox3U)

