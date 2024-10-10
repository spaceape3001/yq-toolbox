////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/core/IntRange.hpp>
#include <cassert>
#include <type_traits>
#include <algorithm>

namespace yq {
    using std::min;
    using std::max;

    template <typename T, uint8_t N> struct Coord;
    
    /*! \brief Gets the specified coordinate dimension index
    
        \tparam T   index type to the coordinate
        \tparam N   number of dimensions 
        \param c    Coordinate itself
        \param i    integer index of the dimension to get
        \return the coordinate's index value for the given index
    */
    template <typename T, uint8_t N>
    constexpr T   get(const Coord<T,N>& c, uint8_t i)
    {
        assert(i<N);
        return ((const T*)&c)[i];
    }

    /*! \brief Editable reference the specified coordinate dimension index
    
        \tparam T   index type to the coordinate
        \tparam N   number of dimensions 
        \param c    Coordinate itself
        \param i    integer index of the dimension to get
        \return REFERENCE to the coordinate's index value for the given index
    */
    template <typename T, uint8_t N>
    constexpr T&  edit(Coord<T,N>& c, uint8_t i)
    {
        assert(i<N);
        return ((T*)&c)[i];
    }

    /*! \brief Sets the specified coordinate value
    
        \tparam T   index type to the coordinate
        \tparam N   number of dimensions 
        \param c    Coordinate itself to be set
        \param i    integer index of the dimension to get
        \param v    integer value to set
    */
    template <typename T, uint8_t N>
    void set (Coord<T,N>& c, uint8_t i, T v)
    {
        assert(i<N);
        edit(c,i) = v;
    }

    namespace trait {
        template <typename> struct is_coord : std::false_type {};
        template <typename T, uint8_t N>
        struct is_coord<Coord<T,N>> : std::true_type {};
        
        /*! \brief Trait to test for a coordinate based type
        */
        template <typename T>
        inline constexpr bool is_coord_v = is_coord<T>::value;
    }
    
    /*! \brief Positive operator
    */
    template <typename T, uint8_t N>
    constexpr Coord<T,N>  operator+(const Coord<T,N>& a) noexcept
    {
        return a;
    }
    
    /*! \brief Returns N for the number of dimensions
        
        Used in templated code to return the dimensions of the object
    */
    template <typename T, uint8_t N>
    consteval uint8_t dims(const Coord<T,N>&) noexcept
    {
        return N;
    }
    
    /*! \brief Returns a collection of ranges, one per dimension, going from a to b
    
        This returns an integer range, one per dimension, that'll go from a to b.
    */
    template <typename T, uint8_t N>
    requires std::is_integral_v<T>
    constexpr Coord<IntRange<T>,N>  range(const Coord<T,N>&a, const Coord<T,N>&b)
    {
        union {
            IntRange<T> values[N];
            Coord<IntRange<T>,N>    ret;
        };
        for(uint8_t n=0;n<N;++n)
            values[n]  = range(get(a, n), get(b,n));
        return ret;
    }
    
    
    /*! \brief Check if all elements are greater 
    
        This compares the elements and returns TRUE if ALL elements of LHS are greater to RHS.
        
        \param[in] lhs  Left hand argument
        \param[in] rhs  Right hand argument
        return TRUE if all elements are lhs > rhs
    */
    template <typename T, uint8_t N>
    constexpr bool  all_greater(const Coord<T,N>& lhs, const Coord<T,N>& rhs)
    {
        for(uint8_t n=0;n<N;++n)
            if(get(lhs,n) <= get(rhs,n))
                return false;
        return true;
    }

    /*! \brief Check if all elements are greater or equal
    
        This compares the elements and returns TRUE if ALL elements of LHS are greater or equal to RHS.
        
        \param[in] lhs  Left hand argument
        \param[in] rhs  Right hand argument
        return TRUE if all elements are lhs >= rhs
    */
    template <typename T, uint8_t N>
    constexpr bool  all_greater_equal(const Coord<T,N>& lhs, const Coord<T,N>& rhs)
    {
        for(uint8_t n=0;n<N;++n)
            if(get(lhs,n) < get(rhs,n))
                return false;
        return true;
    }

    
    /*! \brief Check if all elements are less
    
        This compares the elements and returns TRUE if ALL elements of LHS are less to RHS.
        
        \param[in] lhs  Left hand argument
        \param[in] rhs  Right hand argument
        return TRUE if all elements are lhs < rhs
    */
    template <typename T, uint8_t N>
    constexpr bool  all_less(const Coord<T,N>& lhs, const Coord<T,N>& rhs)
    {
        for(uint8_t n=0;n<N;++n)
            if(get(lhs,n) >= get(rhs,n))
                return false;
        return true;
    }

    
    /*! \brief Check if all elements are lesser or equal
    
        This compares the elements and returns TRUE if ALL elements of LHS are lesser or equal to RHS.
        
        \param[in] lhs  Left hand argument
        \param[in] rhs  Right hand argument
        return TRUE if all elements are lhs <= rhs
    */
    template <typename T, uint8_t N>
    constexpr bool  all_less_equal(const Coord<T,N>& lhs, const Coord<T,N>& rhs)
    {
        for(uint8_t n=0;n<N;++n)
            if(get(lhs,n) > get(rhs,n))
                return false;
        return true;
    }

    
    /*! \brief Check if any elements are greater 
    
        This compares the elements and returns TRUE if ANY element of LHS are greater to RHS.
        
        \param[in] lhs  Left hand argument
        \param[in] rhs  Right hand argument
        return TRUE if any elements are lhs > rhs
    */
    template <typename T, uint8_t N>
    constexpr bool  any_greater(const Coord<T,N>& lhs, const Coord<T,N>& rhs)
    {
        for(uint8_t n=0;n<N;++n)
            if(get(lhs,n) > get(rhs,n))
                return true;
        return false;
    }
    
    /*! \brief Check if any elements are greater or equal
    
        This compares the elements and returns TRUE if ANY element of LHS are greater or equal to RHS.
        
        \param[in] lhs  Left hand argument
        \param[in] rhs  Right hand argument
        return TRUE if any elements are lhs >= rhs
    */
    template <typename T, uint8_t N>
    constexpr bool  any_greater_equal(const Coord<T,N>& lhs, const Coord<T,N>& rhs)
    {
        for(uint8_t n=0;n<N;++n)
            if(get(lhs,n) >= get(rhs,n))
                return true;
        return false;
    }

    /*! \brief Check if any elements are lesser
    
        This compares the elements and returns TRUE if ANY element of LHS are less than RHS.
        
        \param[in] lhs  Left hand argument
        \param[in] rhs  Right hand argument
        return TRUE if any elements are lhs < rhs
    */
    template <typename T, uint8_t N>
    constexpr bool  any_less(const Coord<T,N>& lhs, const Coord<T,N>& rhs)
    {
        for(uint8_t n=0;n<N;++n)
            if(get(lhs,n) < get(rhs,n))
                return true;
        return false;
    }

    /*! \brief Check if any elements are lesser or equal
    
        This compares the elements and returns TRUE if ANY element of LHS are lessor or equal to RHS.
        
        \param[in] lhs  Left hand argument
        \param[in] rhs  Right hand argument
        return TRUE if any elements are lhs <= rhs
    */
    template <typename T, uint8_t N>
    constexpr bool  any_less_equal(const Coord<T,N>& lhs, const Coord<T,N>& rhs)
    {
        for(uint8_t n=0;n<N;++n)
            if(get(lhs,n) <= get(rhs,n))
                return true;
        return false;
    }
}
