////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Expect.hpp>

namespace yq {
    template <typename> class Ref;
    
    class Symbol;
    using SymbolPtr     = Ref<Symbol>;
    using SymbolCPtr    = Ref<const Symbol>;
    
    using symbol_ptr_x = Expect<SymbolPtr>;
}
