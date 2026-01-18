////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Expect.hpp>

namespace yq {
    template <typename> class Ref;
    
    class SymbolLibrary;
    using SymbolLibraryPtr     = Ref<SymbolLibrary>;
    using SymbolLibraryCPtr    = Ref<const SymbolLibrary>;
    
    using symbol_library_ptr_x = Expect<SymbolLibraryPtr>;
}
