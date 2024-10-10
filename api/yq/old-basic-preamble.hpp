////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#error "Discontinue use"

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

#include <yq-toolbox/basic/128-bit.hpp>
#include <yq-toolbox/basic/Expect.hpp>
#include <yq-toolbox/text/IgCase.hpp>
#include <yq-toolbox/basic/LogFwd.hpp>
#include <yq-toolbox/text/RevIgCase.hpp>
#include <yq/typedef/expected.hpp>
#include <yq/typedef/int_range.hpp>
#include <yq/typedef/result.hpp>
#include <yq/typedef/string_initlists.hpp>
#include <yq/typedef/string_maps.hpp>
#include <yq/typedef/string_pairs.hpp>
#include <yq/typedef/string_sets.hpp>
#include <yq/typedef/string_vectors.hpp>
#include <yq/typedef/url.hpp>
#include <yq-toolbox/macro/cppstring.hpp>
#include <yq-toolbox/macro/make_version.hpp>
#include <yq/trait/numbers.hpp>
#include <yq/typedef/any.hpp>

#include <yq-toolbox/keywords.hpp>
#include <yq-toolbox/config/string.hpp>
#include <yq-toolbox/container/forward.hpp>
#include <yq-toolbox/meta/forward.hpp>


using namespace std::literals::chrono_literals;

namespace yq {

    class BasicApp;
    class DelayInit;
    
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



        //  Common permutations (Qt will go away...eventually)

    
    using char32_set_t				= std::unordered_set<char32_t>;




        // TODO move these to use std::filesystem::path
    #if defined(__APPLE__) || defined(WIN32)
        using PathSet   = StringSet;
    #elif defined(__linux__) || defined(__unix__)
        using PathSet   = Set<std::string>;
    #endif
    
    
    
    //! Used for detection of overrides
    struct disabled {};
    struct disabled_t {};

}

