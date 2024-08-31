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
#include <0/basic/IgCase.hpp>
#include <0/basic/LogFwd.hpp>
#include <0/basic/RevIgCase.hpp>

#include <yq/keywords.hpp>
#include <yq/config/string.hpp>
#include <yq/config/json_fwd.hpp>
#include <yq/config/xml_fwd.hpp>
#include <yq/trait/product.hpp>
#include <yq/trait/quotient.hpp>

#define YQ_CPPSTRING(...) #__VA_ARGS__

using namespace std::literals::chrono_literals;

namespace yq {
    // switching to u32-strings (eventually)
    using string_t      = std::u32string;
    using string_view_t = std::u32string_view;
    

    class Any;
    class ByteArray;
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

        // COLLECTIONS
    template <typename I, uint8_t N, bool ORIGIN, bool GHOST> struct ArrayConfig;
    
    template <typename I> using BasicAC1    = ArrayConfig<I, 1, false, false>;
    template <typename I> using BasicAC2    = ArrayConfig<I, 2, false, false>;
    template <typename I> using BasicAC3    = ArrayConfig<I, 3, false, false>;
    template <typename I> using BasicAC4    = ArrayConfig<I, 4, false, false>;
    template <typename I> using BasicAC5    = ArrayConfig<I, 5, false, false>;
    template <typename I> using BasicAC6    = ArrayConfig<I, 6, false, false>;
    
    template <typename I> using GhostAC1    = ArrayConfig<I, 1, true, true>;
    template <typename I> using GhostAC2    = ArrayConfig<I, 2, true, true>;
    template <typename I> using GhostAC3    = ArrayConfig<I, 3, true, true>;
    template <typename I> using GhostAC4    = ArrayConfig<I, 4, true, true>;
    template <typename I> using GhostAC5    = ArrayConfig<I, 5, true, true>;
    template <typename I> using GhostAC6    = ArrayConfig<I, 6, true, true>;
    
    template <typename I> using OriginAC1   = ArrayConfig<I, 1, true, false>;
    template <typename I> using OriginAC2   = ArrayConfig<I, 2, true, false>;
    template <typename I> using OriginAC3   = ArrayConfig<I, 3, true, false>;
    template <typename I> using OriginAC4   = ArrayConfig<I, 4, true, false>;
    template <typename I> using OriginAC5   = ArrayConfig<I, 5, true, false>;
    template <typename I> using OriginAC6   = ArrayConfig<I, 6, true, false>;
    
    template <typename DATA, typename COORDSYS> class Array;
    
    template <typename T, typename I=unsigned int> using Array1 = Array<T, BasicAC1<I>>;
    template <typename T, typename I=unsigned int> using Array2 = Array<T, BasicAC2<I>>;
    template <typename T, typename I=unsigned int> using Array3 = Array<T, BasicAC3<I>>;
    template <typename T, typename I=unsigned int> using Array4 = Array<T, BasicAC4<I>>;
    template <typename T, typename I=unsigned int> using Array5 = Array<T, BasicAC5<I>>;
    template <typename T, typename I=unsigned int> using Array6 = Array<T, BasicAC6<I>>;

    template <typename T, typename I=int> using ZArray1 = Array<T, OriginAC1<I>>;
    template <typename T, typename I=int> using ZArray2 = Array<T, OriginAC2<I>>;
    template <typename T, typename I=int> using ZArray3 = Array<T, OriginAC3<I>>;
    template <typename T, typename I=int> using ZArray4 = Array<T, OriginAC4<I>>;
    template <typename T, typename I=int> using ZArray5 = Array<T, OriginAC5<I>>;
    template <typename T, typename I=int> using ZArray6 = Array<T, OriginAC6<I>>;

    template <typename T, typename I=int> using ZGArray1 = Array<T, GhostAC1<I>>;
    template <typename T, typename I=int> using ZGArray2 = Array<T, GhostAC2<I>>;
    template <typename T, typename I=int> using ZGArray3 = Array<T, GhostAC3<I>>;
    template <typename T, typename I=int> using ZGArray4 = Array<T, GhostAC4<I>>;
    template <typename T, typename I=int> using ZGArray5 = Array<T, GhostAC5<I>>;
    template <typename T, typename I=int> using ZGArray6 = Array<T, GhostAC6<I>>;


    template <typename T> class Deque;
    template <typename E, typename V> class EnumMap;
    template <typename K, typename V>   class Hash;
    template <typename> class List;
    template <typename K, typename V, typename C=std::less<K>> class Map;
    template <typename K, typename V, typename C=std::less<K>> class MultiMap;
    template <typename T, typename C=std::less<T>> class Set;
    template <typename T> struct Span;
    template <typename T> class Stack;
    template <typename T> class Vector;


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

    using any_x             = Expect<Any>;
    using boolean_x         = Expect<bool>;
    using double_x          = Expect<double>;
    using float_x           = Expect<float>;
    using int_x             = Expect<int>;
    using integer_x         = Expect<int>;
    using int8_x            = Expect<int8_t>;
    using int16_x           = Expect<int16_t>;
    using int32_x           = Expect<int32_t>;
    using int64_x           = Expect<int64_t>;
    using int128_x          = Expect<int128_t>;
    using short_x           = Expect<short>;
    using size_x            = Expect<size_t>;
    using string_x          = Expect<std::string>;
    using string_view_x     = Expect<std::string_view>;
    //using string_map_x      = Expect<StringMap>;
    //using string_set_x      = Expect<StringSet>;
    using uint8_x           = Expect<uint8_t>;
    using uint16_x          = Expect<uint16_t>;
    using uint32_x          = Expect<uint32_t>;
    using uint64_x          = Expect<uint64_t>;
    using uint128_x         = Expect<uint128_t>;
    using unsigned_x        = Expect<unsigned int>;
    using ushort_x          = Expect<unsigned short>;
    using u32string_x       = Expect<std::u32string>;
    using wstring_x         = Expect<std::wstring>;

        // INT RANGES
    using SSizeRange        = IntRange<ssize_t>;
    using SizeRange         = IntRange<size_t>;

        // CHARACTER SEQUQNCE
    using CharPSeq          = std::initializer_list<const char*>;

        // NOT A NUMBER
    static constexpr double   NaN     = std::numeric_limits<double>::quiet_NaN();
    static constexpr float    NaNf    = std::numeric_limits<float>::quiet_NaN();

    static constexpr double   INF     = std::numeric_limits<double>::infinity();
    static constexpr float    INFf    = std::numeric_limits<float>::infinity();


    using any_error_t           = std::pair<Any, std::error_code>;
    using any_span_t            = std::span<Any>;
    using const_any_span_t      = std::span<const Any>;


        //  Common permutations (Qt will go away...eventually)
    using StringMap             = Map<std::string,std::string,IgCase>;
    using StringViewMap         = Map<std::string_view,std::string_view,IgCase>;
    using StringMultiMap        = MultiMap<std::string,std::string,IgCase>;
    using StringSet             = Set<std::string,IgCase>;
    using StringViewSet         = Set<std::string_view,IgCase>;
    using StringPair            = std::pair<std::string,std::string>;
    using StringIntPair         = std::pair<std::string,int>;
    using StringViewMultiMap    = MultiMap<std::string_view,std::string_view,IgCase>;
    using StringViewVector      = Vector<std::string_view>;
    using PathVector            = Vector<std::filesystem::path>;

    using StringAnyMap          = Map<std::string,Any,IgCase>;
    using StringAnyMultiMap     = MultiMap<std::string,Any,IgCase>;

    using string_pair_t         = std::pair<std::string,std::string>;
    using string_int_pair_t     = std::pair<std::string,int>;

    using string_any_map_t      = std::map<std::string,Any,IgCase>;
    using string_any_pair_t     = std::pair<std::string,Any>;

    using string_map_t          = std::map<std::string,std::string,IgCase>;
    using string_set_t          = std::set<std::string,IgCase>;
    using string_vector_t       = std::vector<std::string>;
    
    using string_view_pair_t    = std::pair<std::string_view,std::string_view>;
    using string_view_set_t     = std::set<std::string_view,IgCase>;
    using string_view_vector_t  = std::vector<std::string_view>;
    using path_vector_t         = std::vector<std::filesystem::path>;

    using string_view_initializer_list_t       = std::initializer_list<std::string_view>;

    using U32StringViewSet      = Set<std::u32string_view, IgCase>;
    
    using char32_set_t				= std::unordered_set<char32_t>;

    using u32string_pair_t         = std::pair<std::u32string,std::u32string>;
    using u32string_int_pair_t     = std::pair<std::u32string,int>;

    using u32string_any_map_t      = std::map<std::u32string,Any,IgCase>;
    using u32string_any_pair_t     = std::pair<std::u32string,Any>;

    using u32string_map_t          = std::map<std::u32string,std::u32string,IgCase>;
    using u32string_set_t          = std::set<std::u32string,IgCase>;
    using u32string_vector_t       = std::vector<std::u32string>;

    using u32string_view_pair_t    = std::pair<std::u32string_view,std::u32string_view>;
    using u32string_view_set_t     = std::set<std::u32string_view,IgCase>;
    using u32string_view_vector_t  = std::vector<std::u32string_view>;

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

    

    template<class T, typename U>
    size_t member_offset(U T::* member)
    {
        //  UGLY hack to get an offset for a member pointer
        //  credit to https://stackoverflow.com/questions/5617251/offset-of-pointer-to-member
        //  top answer
        return reinterpret_cast<size_t>(&(reinterpret_cast<T*>((void*) 0)->*member));
    }    

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

    template <typename T, typename Allocator>
    constexpr std::span<const T> span(const std::vector<T,Allocator>& data) noexcept
    {
        return data;
    }

    template <typename T, size_t N>
    constexpr std::span<const T> span(const std::array<T, N>& data) noexcept
    {
        return std::span<const T>(data.data(), N);
    }

    class Stream;


    //! The reasonable maximum for a raw null terminated string... anything else should be in a string view (at least)
    static constexpr const uint64_t         MAX_NULL_TERM       = 8192;

}

