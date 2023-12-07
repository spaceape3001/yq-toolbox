////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#define YQ_MATH_AXBOX1_HPP 1


#include <math/preamble.hpp>
#include <math/vector/Vector1.hpp>

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
        
        //! Default constructor
        constexpr AxBox1() noexcept = default;
        
        /*! \brief Initializing constructor with ONE value
        
            This constructor initializes BOTH lo and hi with the same value.  
            This will technically be a valid axbox with zero span.
        */
        explicit constexpr AxBox1(const Vector1<T>& a) noexcept : lo(a), hi(a) {}
        
        /*! \brief Initializing constructor with TWO values
        
            This constructor initializes the box as specified.  
            
            \note This result may be an invalid box with negative spans.
        */
        constexpr AxBox1(const Vector1<T>& _lo, const Vector1<T>& _hi) noexcept : lo(_lo), hi(_hi) {}
        
        /*! \brief Construct as an intersection of points
        
            This takes the smallest box from the given low and high values.
            
            \note This result may be an invalid box if *ANY* lows have components higher than a corresponding high value

            \param[in] low Low values
            \param[in] high High values
        */
        constexpr AxBox1(intersect_t, std::initializer_list<Vector1<T>> low, std::initializer_list<Vector1<T>> high) noexcept;

        /*! \brief Construct as an intersection of points
        
            This takes the smallest box from the given low and high values.
            
            \note This result may be an invalid box if *ANY* lows have components higher than a corresponding high value

            \param[in] low Low values
            \param[in] high High values
        */
        constexpr AxBox1(intersect_t, std::span<const Vector1<T>> low, std::span<const Vector1<T>> high) noexcept;
        
        /*! \brief Construct a box using the two points
        
            This ensures lo <= hi (unless infinite/nan)
        */
        constexpr AxBox1(sort_t, const Vector1<T>&a, const Vector1<T>& b) noexcept;

        /*! \brief Construct a box as a union of two points
        
            This ensures lo <= hi (unless infinite/nan)
        */
        constexpr AxBox1(union_t, const Vector1<T>&a, const Vector1<T>& b) noexcept;
        
        /*! \brief Construct a box as a union of multiple points
        
            This returns the bounding box of *ALL* the given points
        */
        constexpr AxBox1(union_t, std::initializer_list<Vector1<T>>) noexcept;

        /*! \brief Construct a box as a union of multiple points
        
            This returns the bounding box of *ALL* the given points
        */
        constexpr AxBox1(union_t, std::span<const Vector1<T>>) noexcept;
        
        /*! \brief Construct a box as a union of multiple points
        
            This constructor segregates the set of low and high points.
            
            \note It's possible to construct an invalid box if all the low points are above the high points.
            
            \param[in] low Low values
            \param[in] high High values
        */
        constexpr AxBox1(union_t, std::initializer_list<Vector1<T>> low, std::initializer_list<Vector1<T>> high) noexcept;

        /*! \brief Construct a box as a union of multiple points
        
            This constructor segregates the set of low and high points.
            
            \note It's possible to construct an invalid box if all the low points are above the high points.
            
            \param[in] low Low values
            \param[in] high High values
        */
        constexpr AxBox1(union_t, std::span<const Vector1<T>> low, std::span<const Vector1<T>> high) noexcept;
        
        //! Box of not-a-numbers
        template <typename=void> requires has_nan_v<T>
        consteval AxBox1(nan_t) : AxBox1(Vector1<T>(NAN)) {}
        
        //! Zero box
        consteval AxBox1(zero_t) : AxBox1(Vector1<T>(ZERO)) {}
        
        //! Constructs from a segment
        explicit constexpr AxBox1(const Segment1<T>&) noexcept;

        //! Converts to another compatible AxBox type
        template <typename U>
        requires std::is_nothrow_convertible_v<T,U>
        explicit constexpr operator AxBox1<U>() const noexcept
        {
            return { (Vector1<U>) lo, (Vector1<U>) hi };
        }
        
        template <typename U>
        requires (std::is_convertible_v<T,U> && !std::is_nothrow_convertible_v<T,U>)
        explicit constexpr operator AxBox1<U>() const 
        {
            return { (Vector1<U>) lo, (Vector1<U>) hi };
        }
        
        //! Defaulted equatlity operator
        constexpr bool operator==(const AxBox1&) const noexcept = default;

        //! Positive (affirmative) operator
        AxBox1  operator+() const noexcept;
        
        //! Negation operator
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
        
        //! Lower "corner" of the box
        constexpr Vector1<T>    l() const noexcept;
        
        /*! \brief Lower adjusted corner of the box
        
            This adjusts the corner outward by the specified amount, assuming it's a valid box
        */
        constexpr Vector1<T>    l(T adjust) const noexcept;

        //! Length of this box
        constexpr T             length() const noexcept;
        
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
        
        //! Size (dimensions) of this box
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

    template <typename T, typename U>
    requires is_arithmetic_v<T>
    constexpr AxBox1<product_t<T,U>> operator*(T a, const AxBox1<U>&b) noexcept;


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

    //! Length of the given box
    template <typename T>
    constexpr T         length(const AxBox1<T>&) noexcept;

    //! Computes the span for a given box
    template <typename T>
    constexpr Vector1<T>    span(const AxBox1<T>&box) noexcept;

    //! Streaming helper (assuming debug-like output)
    template <typename S, typename T>
    S&  as_stream(S& s, const AxBox1<T>& v);
    
    //! Streams box to a text-like stream
    template <typename T>
    Stream& operator<<(Stream&s, const AxBox1<T>& v);

    //! Streams to a log stream
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream& s, const AxBox1<T>& v);
}

YQ_TYPE_DECLARE(yq::AxBox1D)
YQ_TYPE_DECLARE(yq::AxBox1F)
YQ_TYPE_DECLARE(yq::AxBox1I)
YQ_TYPE_DECLARE(yq::AxBox1U)

