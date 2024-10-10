////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstdint>

namespace yq {

    /*! \brief Enumeration for comparison results */
    #if 0
    YQ_ENUM(Compare, ,
        UNCOMPARABLE   = 0,
        GREATER,
        LESSER,
        EQUAL
    );
    #endif

    enum class Compare : uint8_t {
        UNCOMPARABLE   = 0,
        GREATER,
        LESSER,
        EQUAL
    };

    template <typename T, typename A>
    constexpr Compare chain_compare(const T& lhs, const T& rhs, A a) noexcept
    {
        return a(lhs, rhs);
    }

    template <typename T, typename A, typename ... B>
    constexpr Compare chain_compare(const T& lhs, const T& rhs, A a, B... b) noexcept
    {
        Compare c = a(lhs, rhs);
        if (c == Compare::LESSER)
            return Compare::LESSER;
        if (c == Compare::GREATER)
            return Compare::GREATER;
        return chain_compare(lhs, rhs, b...);
    }

    template <template <typename...> class Tmpl>
    constexpr Compare merge(const Tmpl<Compare>& cs) noexcept
    {
        for(Compare c : cs){
            switch(c){
            case Compare::UNCOMPARABLE:
                return Compare::UNCOMPARABLE;
            case Compare::LESSER:
            case Compare::GREATER:
                return c;
            case Compare::EQUAL:
            default:
                break;
            }
        }
        return Compare::EQUAL;
    }


    /*! \brief Inverts the comparison

    */
    constexpr Compare invert(Compare c)
    {
        switch(c){
        case Compare::EQUAL:
            return Compare::EQUAL;
        case Compare::LESSER:
            return Compare::GREATER;
        case Compare::GREATER:
            return Compare::LESSER;
        case Compare::UNCOMPARABLE:
        default:
            return Compare::UNCOMPARABLE;
        }
    }

    template <typename T>
    constexpr Compare  compare(const T& a, const T& b)
    {
        if(a < b)
            return Compare::LESSER;
        if(b < a)
            return Compare::GREATER;
        return Compare::EQUAL;
    }


    template <typename T>
    constexpr Compare  compare_invert(const T& a, const T& b)
    {
        return invert(compare(a,b));
    }

    template <typename T>
    constexpr bool    is_between(T val, T low, T high)
    {
        return (low <= val) && (val <= high);
    }

    constexpr bool is_equal(Compare c)
    {
        return (c == Compare::EQUAL) ? true : false;
    }

    constexpr bool is_greater(Compare c)
    {
        return (c == Compare::GREATER) ? true : false;
    }

    constexpr bool is_less(Compare c)
    {
        return (c == Compare::LESSER) ? true : false;
    }

    constexpr bool is_less(Compare a, Compare b)
    {
        if(a != Compare::EQUAL)
            return is_less(a);
        return is_less(b);
    }

    constexpr bool is_less(Compare a, Compare b, Compare c)
    {
        if(a != Compare::EQUAL)
            return is_less(a);
        if(b != Compare::EQUAL)
            return is_less(b);
        return is_less(c);
    }

    template <typename T, typename ... A>
    constexpr bool is_less(const T& lhs, const T& rhs, A... a)
    {
        return is_less(chainCompare(lhs, rhs, a...));
    }

    template <typename T, typename ... A>
    constexpr bool is_greater(const T& lhs, const T& rhs, A... a)
    {
        return is_greater(chainCompare(lhs, rhs, a...));
    }

}
