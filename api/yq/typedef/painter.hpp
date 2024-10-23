////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <memory>

namespace yq {
    class Painter;
    class Painter2;
    template <class> class Paint2;
    
    using PainterSPtr   = std::shared_ptr<Painter>;
    using Painter2SPtr  = std::shared_ptr<Painter2>;
    template <typename C> using Paint2SPtr = std::shared_ptr<Paint2<C>>;
}
