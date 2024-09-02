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
#include <yq/typedef/int_range.hpp>
#include <yq/typedef/result.hpp>
#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/string_pairs.hpp>
#include <yq/typedef/string_sets.hpp>
#include <yq/typedef/string_vectors.hpp>
#include <yq/typedef/url.hpp>
#include <yq/macro/cppstring.hpp>
#include <yq/macro/make_version.hpp>
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
    template <typename> struct Span;

        // RESULTS
    

        // INT RANGES

        // CHARACTER SEQUQNCE
    using CharPSeq          = std::initializer_list<const char*>;

        // NOT A NUMBER

    using any_error_t           = std::pair<Any, std::error_code>;
    using any_span_t            = std::span<Any>;
    using const_any_span_t      = std::span<const Any>;


        //  Common permutations (Qt will go away...eventually)
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

