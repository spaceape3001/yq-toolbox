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

namespace yq {
    class XGDocument;
    using XGDocumentPtr     = Ref<XGDocument>;
    using XGDocumentCPtr    = Ref<const XGDocument>;
    
    using xg_document_ptr_x = Expect<XGDocumentPtr>;
}
