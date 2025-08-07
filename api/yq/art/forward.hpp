////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstddef>
#include <yq/meta/MetaBinder.hpp>
#include <variant>

#ifdef __GNUC__
        //  While the "is hidden" warnings can be nice... it's burdening the
        //  adaptive API
    #pragma GCC diagnostic ignored "-Woverloaded-virtual="
#endif

namespace yq { template <typename> class Ref; }

namespace yq::art {
    class Doc;
    class Obj;
    
    using DocPtr            = Ref<Doc>;
    using DocCPtr           = Ref<const Doc>;
    
    using id_t              = size_t;
    using revision_t        = uint64_t;

    //! To denote an internal doc-scoped ID link to another object (ie, reference, like points)
    struct ID {
        id_t        id  = 0;
        operator id_t() const { return id; }
        constexpr auto operator<=>(const ID&) const noexcept = default;
    };
    
    //! To denote a key-based reference another object (this is user-scoped)
    struct Key {
        std::string     key;
        operator std::string_view() const { return key; }
        constexpr auto operator<=>(const Key&) const noexcept = default;
    };
    
    //! Reference to something else
    using Reference = std::variant<ID,Key>;
    
    class Canvas;   // 2D drawing document
    class Surface;  // 2D "surface" in a 3D environment
}

YQ_TYPE_DECLARE(yq::art::ID)
YQ_TYPE_DECLARE(yq::art::Key)
YQ_TYPE_DECLARE(yq::art::Reference)
