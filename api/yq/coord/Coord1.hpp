////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/coord1.hpp>

#include <yq/keywords.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/is_arithmetic.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>
#include <yq/trait/self_divide.hpp>
#include <yq/trait/self_multiply.hpp>

namespace log4cpp { class CategoryStream; }

namespace yq {
    template <typename> struct AllComponents;
    template <typename> struct AnyComponents;

    class Stream;

    /*! \brief One dimensional coordinate
    
        This is expanded in one diemnsion for the one-dimensional coordinate.
    */
    template <typename T>
    struct Coord<T,1> {
    
        //! Component type
        using component_type    = T;
        
        //! Number of dimensions
        static constexpr const uint8_t  DIMS    = 1;
        
        //! Data (I-value)
        T       i;

        //! Default constructor
        constexpr Coord() noexcept = default;
        
        //! Initializing constructor
        constexpr Coord(T _i) noexcept : 
            i(_i)  {}
            
        //! All components to given value
        constexpr Coord(all_k, T _v) noexcept : Coord<T,1>(_v) {}
        
        //! Zero initializes
        constexpr Coord(zero_k) noexcept : Coord<T,1>(ALL, zero_v<T>) {}

        //! Defaulted spaceship  operator
        constexpr auto operator<=>(const Coord&) const noexcept = default;

        //! Conversion operator to other 1-dimensional coordinates
        template <typename U>
        requires (!std::is_same_v<T,U>)
        explicit constexpr operator Coord<U,1>() const noexcept
        {
            return { (U) i };
        }

        //! Allows for uniform coordinate assignment.
        Coord& operator=(T v)
        {
            i = v;
            return *this;
        }
        
        constexpr Coord operator+() const noexcept;
        constexpr Coord operator-() const noexcept;
        constexpr Coord operator+(const Coord& b) const noexcept;
        constexpr Coord operator-(const Coord& b) const noexcept;
        
        Coord& operator+=(const Coord&) noexcept;
        Coord& operator-=(const Coord&) noexcept;

        //! Scales the coordinate
        template <typename U>
            requires is_arithmetic_v<U>
        constexpr Coord1<product_t<T,U>> operator*(U b) const noexcept;
        
        //! Self-scale the coordinate
        template <typename U>
            requires (is_arithmetic_v<U> && self_multiply_v<T,U>)
        Coord& operator*=(U b) noexcept;

        //! Multiplies two coordinates together, term by term
        template <typename U>
        constexpr Coord1<product_t<T,U>> operator*(const Coord1<U>& b) const noexcept;
        
        //! Self-Multiplies left coordinate with right, term by term
        template <typename U>
            requires self_multiply_v<T,U>
        Coord& operator*=(const Coord1<U>& b) noexcept;

        //! Reduces the cooordinate, returns result
        template <typename U>
            requires is_arithmetic_v<U>
        constexpr Coord1<quotient_t<T,U>> operator/(U b) const noexcept;

        //! Reduces the cooordinate in place, returns result
        template <typename U>
            requires (is_arithmetic_v<U> && self_divide_v<T,U>)
        Coord& operator/=(U b) noexcept;

        //! Divides two coordinates, term by term
        template <typename U>
        constexpr Coord1<quotient_t<T,U>> operator/(const Coord1<U>& b) const noexcept;

        //! Self divides left coordinate by right
        template <typename U>
            requires self_divide_v<T,U>
        Coord& operator/=(const Coord1<U>& b) noexcept;

        template <typename S>
        S&  stream(S&) const;


            //  ===================================================================================================
            //  AllComponents Adapters
            //  ===================================================================================================

        /*! Adds a value to all the elements
        */
        constexpr Coord all_add(T b) const noexcept;
        
        //! Decrement all elements
        Coord&    all_decrement(T b) noexcept;

        //! Increment all elements
        Coord&    all_increment(T b) noexcept;

        /*! \brief Subtracts value from all elements
        */
        constexpr Coord all_subtract(T b) const noexcept;

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
        constexpr bool all_test(const Coord& b, Pred pred) const noexcept;

        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if all tests are true.
            \note y, z, w component tests may be skipped if the x-component test fails.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool all_test(T b, Pred pred) const noexcept;

            //  ===================================================================================================
            //  AnyComponents Adapters
            //  
            //  The following all_test() are for the AllComponents Adapters, to apply the test on ALL components,
            //  returning true if all elements are successful
            //  ===================================================================================================
        
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
        constexpr bool any_test(const Coord& b, Pred pred) const noexcept;
        
        /*! Tests every element
            This applies the given test to every component, 
            returns TRUE if any test is true.
            \note y, z, w component tests may be skipped if the x-component test passes.
            \param[in] b The other value
            \param[in] pred The predicate (your test)
        */
        template <typename Pred>
        constexpr bool any_test(T b, Pred pred) const noexcept;
    };

    YQ_NAN_1(Coord1, Coord1<T>( nan_v<T> ))
    YQ_IS_NAN_1(Coord1, is_nan(v.i) )
    YQ_IS_FINITE_1(Coord1, is_finite(v.i) )
    YQ_ZERO_1(Coord1, Coord1<T>( zero_v<T> ))

    //  --------------------------------------------------------
    //  COMPOSITION

    /*! \brief Composes a one dimensional coordinate from arguments */
    template <typename T>
    constexpr Coord1<T>    coord(T i) noexcept
    {
        return { i };
    }
    
    /*! \brief Construct a uniform 1-dimensional coordinate */
    template <typename T>
    constexpr Coord1<T>    coord1(T i)
    {
        return { i };
    }

    //  --------------------------------------------------------
    //  BASIC FUNCTIONS

    /*! \brief Max of two coordinates, done by element */
    template <typename T>
    constexpr Coord1<T> max(const Coord1<T>&a, const Coord1<T>& b);

    /*! \brief Min of two coordinates, done by element */
    template <typename T>
    constexpr Coord1<T> min(const Coord1<T>&a, const Coord1<T>& b);

    /*! \brief Product of the components */
    template <typename T>
    constexpr T product(const Coord1<T>& a);

    /*! \brief Sum of the components */
    template <typename T>
    constexpr T sum(const Coord1<T>& a);


    //  --------------------------------------------------------

    //! All components adapter
    //! Use this to activate the "all" component adapters in coord1
    template <typename T>
    AllComponents<Coord1<T>>   all(Coord1<T>& val);

    //! All components adapter
    //! Use this to activate the "all" component adapters in coord1
    template <typename T>
    AllComponents<const Coord1<T>>   all(const Coord1<T>& val);

    template <typename T>
    AnyComponents<Coord1<T>>   any(Coord1<T>& val);

    template <typename T>
    AnyComponents<const Coord1<T>>   any(const Coord1<T>& val);


    //! Scale the coordinate
    template <typename T, typename U>
        requires is_arithmetic_v<T>
    constexpr Coord1<product_t<T,U>> operator*(T a, const Coord1<U>&b);

    
    //! Helper to stream out a coordinate
    template <typename T>
    Stream& operator<<(Stream&, const Coord1<T>&);

    //! Helper to log out a coordinate
    template <typename T>
    log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const Coord1<T>&);
}

YQ_TYPE_DECLARE(yq::Coord1D);
YQ_TYPE_DECLARE(yq::Coord1F);
YQ_TYPE_DECLARE(yq::Coord1I);
YQ_TYPE_DECLARE(yq::Coord1U);
YQ_TYPE_DECLARE(yq::Coord1Z);

