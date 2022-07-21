////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <chrono>
#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

#include <basic/128-bit.hpp>
#include <basic/IgCase.hpp>
#include <basic/LogFwd.hpp>
#include <basic/RevIgCase.hpp>

#include <nlohmann/json_fwd.hpp>

using namespace std::literals::chrono_literals;
using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;


namespace rapidxml {
    // Forward declarations
    template<class Ch> class xml_node;
    template<class Ch> class xml_attribute;
    template<class Ch> class xml_document;
    template<class Ch> class xml_base;
}

namespace yq {
    class Any;
    class ByteArray;
    class BasicApp;
    class DelayInit;
    class Global;       //  a global property ... effectively
    
    class ArgInfo;
    class GlobalInfo;   // Meta for global
    class Meta;         // base meta 
    class MethodInfo;   // Function call
    class ObjectInfo;   // Obtrusive data type
    class PropertyInfo; // a object property
    class CompoundInfo; // CompoundInfo type (with properties & methods)   
    class TypeInfo;     // Unobtrusive data type
    
    class MetaObject;   // object with meta
    struct Parsed;
    class RefCount;
    class Stream;


        // TEMPLATE CLASS (BY CLASS)
    template <class> class EnumImpl;

        // TEMPLATE CLASSES
    template <typename> class Guarded;
    template <typename> class Ref;
    template <typename> class Touched;
    
        // TEMPLATE STRUCTS
    template <typename> struct IntRange;
    template <typename> struct Result;
    template <typename> struct Span;
    
        // COORDINATES
    template <typename, uint8_t>    struct Coord;
    

    template <typename T> using Coord1 = Coord<T,1>;
    using Coord1I   = Coord1<int>;
    using Coord1U   = Coord1<unsigned int>;
    using Coord1Z   = Coord1<size_t>;

    template <typename T> using Coord2 = Coord<T,2>;
    using Coord2I   = Coord2<int>;
    using Coord2U   = Coord2<unsigned int>;
    using Coord2Z   = Coord2<size_t>;

    template <typename T> using Coord3 = Coord<T,3>;
    using Coord3I   = Coord3<int>;
    using Coord3U   = Coord3<unsigned int>;
    using Coord3Z   = Coord3<size_t>;

    template <typename T> using Coord4 = Coord<T,4>;
    using Coord4I   = Coord4<int>;
    using Coord4U   = Coord4<unsigned int>;
    using Coord4Z   = Coord4<size_t>;

    template <typename T> using Coord5 = Coord<T,5>;
    using Coord5I   = Coord5<int>;
    using Coord5U   = Coord5<unsigned int>;
    using Coord5Z   = Coord5<size_t>;

    template <typename T> using Coord6 = Coord<T,6>;
    using Coord6I   = Coord6<int>;
    using Coord6U   = Coord6<unsigned int>;
    using Coord6Z   = Coord6<size_t>;


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



        //  Common permutations (Qt will go away...eventually)
    using StringMap             = Map<std::string,std::string,IgCase>;
    using StringViewMap         = Map<std::string_view,std::string_view,IgCase>;
    using StringMultiMap        = MultiMap<std::string,std::string,IgCase>;
    using StringSet             = Set<std::string,IgCase>;
    using StringViewSet         = Set<std::string_view,IgCase>;
    using StringPair            = std::pair<std::string,std::string>;
    using StringIntPair         = std::pair<std::string,int>;
    using StringViewMultiMap    = MultiMap<std::string_view,std::string_view,IgCase>;

    using string_map_t          = Map<std::string,std::string,IgCase>;
    using string_set_t          = Set<std::string,IgCase>;
    using string_view_set_t     = Set<std::string_view,IgCase>;

    using string_view_pair_t    = std::pair<std::string_view,std::string_view>;
    using string_view_set_t     = Set<std::string_view,IgCase>;
    using string_view_vector_t  = Vector<std::string_view>;
    using path_vector_t         = Vector<std::filesystem::path>;

        // TODO move these to use std::filesystem::path
    #if defined(__APPLE__) || defined(WIN32)
        using PathSet   = StringSet;
    #elif defined(__linux__) || defined(__unix__)
        using PathSet   = Set<std::string>;
    #endif
    
    template <typename T> struct BasicUrl;
    using UrlView       = BasicUrl<std::string_view>;
    using Url           = BasicUrl<std::string>;
    
    using url_r         = Result<Url>;
    using url_view_r    = Result<UrlView>;

    using std::literals::string_literals::operator""s;
    using std::literals::string_view_literals::operator""sv;
    
    using XmlBase       = rapidxml::xml_base<char>;
    using XmlNode       = rapidxml::xml_node<char>;
    using XmlAttribute  = rapidxml::xml_attribute<char>;
    using XmlDocument   = rapidxml::xml_document<char>;

    using json = nlohmann::json;

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
}


