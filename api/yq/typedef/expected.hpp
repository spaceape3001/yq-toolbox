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
#include <yq/typedef/rgb.hpp>
#include <yq/typedef/rgba.hpp>

namespace yq {
    class Any;
    class Meta;
    class Object;
    class ObjectMeta;
    class TypeMeta;
    
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
    using meta_x        = Expect<const Meta*>;
    using object_meta_x = Expect<const ObjectMeta*>;
    using object_ptr_x  = Expect<Object*>;
    using object_cptr_x = Expect<const Object*>;
    using rgb3f_x       = Expect<RGB3F>;
    using rgb3u8_x      = Expect<RGB3U8>;
    using rgba4f_x      = Expect<RGBA4F>;
    using rgba4u8_x     = Expect<RGBA4U8>;
    using short_x       = Expect<short>;
    using size_x        = Expect<size_t>;
    using string_x      = Expect<std::string>;
    using string_view_x = Expect<std::string_view>;
    //using string_map_x  = Expect<StringMap>;
    //using string_set_x  = Expect<StringSet>;
    using type_meta_x   = Expect<const TypeMeta*>;
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
    using void_cptr_x   = Expect<const void*>;
    using wstring_x     = Expect<std::wstring>;
}
