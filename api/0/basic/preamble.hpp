////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <array>
#include <chrono>
#include <expected>
#include <filesystem>
#include <initializer_list>
#include <map>
#include <set>
#include <span>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_set>
#include <vector>

#include <yq/basic/128-bit.hpp>
#include <yq/basic/Expect.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/basic/LogFwd.hpp>
#include <yq/text/RevIgCase.hpp>
#include <yq/typedef/expected.hpp>
#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/string_pairs.hpp>
#include <yq/typedef/string_sets.hpp>
#include <yq/typedef/string_vectors.hpp>
#include <yq/macro/cppstring.hpp>
#include <yq/trait/numbers.hpp>

#include <yq/keywords.hpp>
#include <yq/config/string.hpp>
#include <yq/container/forward.hpp>


using namespace std::literals::chrono_literals;

namespace yq {

    class Any;
    class BasicApp;
    class DelayInit;
    class Global;       //  a global property ... effectively
    
    class ArgInfo;
    class ConstructorInfo;
    class GlobalInfo;   // Meta for global
    class Meta;         // base meta 
    class MethodInfo;   // Function call
    class ObjectInfo;   // Obtrusive data type
    class OperatorInfo;
    class PropertyInfo; // a object property
    class CompoundInfo; // CompoundInfo type (with properties & methods)   
    class TypeInfo;     // Unobtrusive data type
    
    class MetaObject;   // object with meta
    struct Parsed;
    class RefCount;
    class Stream;
    struct MaybeCase;

        // TEMPLATE CLASS (BY CLASS)
    template <class> class EnumImpl;

        // TEMPLATE CLASSES
    template <typename> class Guarded;
    template <typename> class Ref;
    template <typename> class Touched;
    
        // TEMPLATE STRUCTS
    template <typename> struct Created;
    template <typename> struct IntRange;
    template <typename> struct Result;
    template <typename> struct Span;

        // RESULTS
    
    using any_r             = Result<Any>;
    using boolean_r         = Result<bool>;
    using double_r          = Result<double>;
    using float_r           = Result<float>;
    using int_r             = Result<int>;
    using integer_r         = Result<int>;
    using int8_r            = Result<int8_t>;
    using int16_r           = Result<int16_t>;
    using int32_r           = Result<int32_t>;
    using int64_r           = Result<int64_t>;
    using int128_r          = Result<int128_t>;
    using short_r           = Result<short>;
    using size_r            = Result<size_t>;
    using string_r          = Result<std::string>;
    using string_view_r     = Result<std::string_view>;
    //using string_map_r      = Result<StringMap>;
    //using string_set_r      = Result<StringSet>;
    using uint8_r           = Result<uint8_t>;
    using uint16_r          = Result<uint16_t>;
    using uint32_r          = Result<uint32_t>;
    using uint64_r          = Result<uint64_t>;
    using uint128_r         = Result<uint128_t>;
    using unsigned_r        = Result<unsigned int>;
    using ushort_r          = Result<unsigned short>;
    using u32string_r       = Result<std::u32string>;
    using wstring_r         = Result<std::wstring>;

        // INT RANGES
    using SSizeRange        = IntRange<ssize_t>;
    using SizeRange         = IntRange<size_t>;

        // CHARACTER SEQUQNCE
    using CharPSeq          = std::initializer_list<const char*>;

        // NOT A NUMBER

    using any_error_t           = std::pair<Any, std::error_code>;
    using any_span_t            = std::span<Any>;
    using const_any_span_t      = std::span<const Any>;


        //  Common permutations (Qt will go away...eventually)
    using PathVector            = Vector<std::filesystem::path>;



    using path_vector_t         = std::vector<std::filesystem::path>;

    using string_view_initializer_list_t       = std::initializer_list<std::string_view>;

    
    using char32_set_t				= std::unordered_set<char32_t>;





    using u32string_view_initializer_list_t       = std::initializer_list<std::u32string_view>;

    using any_stack_t               = Stack<Any>;

        // TODO move these to use std::filesystem::path
    #if defined(__APPLE__) || defined(WIN32)
        using PathSet   = StringSet;
    #elif defined(__linux__) || defined(__unix__)
        using PathSet   = Set<std::string>;
    #endif
    
    template <typename T> struct BasicUrl;
    using UrlView       = BasicUrl<std::string_view>;
    using Url           = BasicUrl<std::string>;
    using Url32         = BasicUrl<std::u32string>;
    using Url32View     = BasicUrl<std::u32string_view>;
    
    using url_r         = Result<Url>;
    using url_view_r    = Result<UrlView>;


    #define YQ_MAKE_VERSION(major, minor, patch) ((((uint32_t)(major)) << 22) | (((uint32_t)(minor)) << 12) | ((uint32_t)(patch)))
    
    template <typename T>
    void    steal(T*& ptr, T*& other)
    {
        ptr     = other;
        other   = nullptr;
    }
    
    //! Used for detection of overrides
    struct disabled {};
    struct disabled_t {};


    class Stream;
}

