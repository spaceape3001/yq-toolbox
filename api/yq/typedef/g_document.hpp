////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Expect.hpp>

namespace yq {
    template <typename> class Ref;
}

namespace yq::graph {
    class GDocument;
    using GDocumentPtr     = Ref<GDocument>;
    using GDocumentCPtr    = Ref<const GDocument>;
    
    using gdocument_ptr_x = Expect<GDocumentPtr>;
}
