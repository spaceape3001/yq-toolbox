////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <yq-toolbox/basic/128-bit.hpp>
#include <yq/typedef/url.hpp>

namespace yq {
    class Any;

    using any_opt             = std::optional<Any>;
    using boolean_opt         = std::optional<bool>;
    using double_opt          = std::optional<double>;
    using float_opt           = std::optional<float>;
    using int_opt             = std::optional<int>;
    using integer_opt         = std::optional<int>;
    using int8_opt            = std::optional<int8_t>;
    using int16_opt           = std::optional<int16_t>;
    using int32_opt           = std::optional<int32_t>;
    using int64_opt           = std::optional<int64_t>;
    using int128_opt          = std::optional<int128_t>;
    using short_opt           = std::optional<short>;
    using size_opt            = std::optional<size_t>;
    using string_opt          = std::optional<std::string>;
    using string_view_opt     = std::optional<std::string_view>;
    //using string_map_opt      = std::optional<StringMap>;
    //using string_set_opt      = std::optional<StringSet>;
    using uint8_opt           = std::optional<uint8_t>;
    using uint16_opt          = std::optional<uint16_t>;
    using uint32_opt          = std::optional<uint32_t>;
    using uint64_opt          = std::optional<uint64_t>;
    using uint128_opt         = std::optional<uint128_t>;
    using unsigned_opt        = std::optional<unsigned int>;
    using ushort_opt          = std::optional<unsigned short>;
    using u32string_opt       = std::optional<std::u32string>;
    using url_opt             = std::optional<Url>;
    using url_view_opt        = std::optional<UrlView>;
    using wstring_opt         = std::optional<std::wstring>;
}
