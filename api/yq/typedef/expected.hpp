////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <yq/core/Expect.hpp>
#include <yq/typedef/128.hpp>
#include <yq/typedef/url.hpp>

namespace yq {
    class Any;
    
    using any_x         = Expect<Any>;
    using boolean_x     = Expect<bool>;
    using double_x      = Expect<double>;
    using float_x       = Expect<float>;
    using int_x         = Expect<int>;
    using integer_x     = Expect<int>;
    using int8_x        = Expect<int8_t>;
    using int16_x       = Expect<int16_t>;
    using int32_x       = Expect<int32_t>;
    using int64_x       = Expect<int64_t>;
    using int128_x      = Expect<int128_t>;
    using short_x       = Expect<short>;
    using size_x        = Expect<size_t>;
    using string_x      = Expect<std::string>;
    using string_view_x = Expect<std::string_view>;
    //using string_map_x  = Expect<StringMap>;
    //using string_set_x  = Expect<StringSet>;
    using uint8_x       = Expect<uint8_t>;
    using uint16_x      = Expect<uint16_t>;
    using uint32_x      = Expect<uint32_t>;
    using uint64_x      = Expect<uint64_t>;
    using uint128_x     = Expect<uint128_t>;
    using unsigned_x    = Expect<unsigned int>;
    using ushort_x      = Expect<unsigned short>;
    using u32string_x   = Expect<std::u32string>;
    using url_x         = Expect<Url>;
    using url_view_x    = Expect<UrlView>;
    using void_ptr_x    = Expect<void*>;
    using wstring_x     = Expect<std::wstring>;
}
