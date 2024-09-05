////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <initializer_list>
#include <span>
#include <yq-toolbox/trait/has_equality.hpp>

namespace yq {
    template <typename T>
    bool    is_in(T val, std::initializer_list<T> vals)
    {
        static_assert(has_equality_v<T>, "Type needs to have an equality operator!");
        for(auto& t : vals)
            if(val == t)
                return true;
        return false;
    }

    //! creates a span from an initializer list
    template <typename T>
    constexpr std::span<const T> span(const std::initializer_list<T>& data) noexcept
    {
        return std::span<const T>(data.begin(), data.end());
    }

    template <typename T>
    constexpr std::span<const T> span(const std::initializer_list<const T>& data) noexcept
    {
        return std::span<const T>(data.begin(), data.end());
    }

}
