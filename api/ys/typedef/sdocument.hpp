////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <memory>

namespace yq::spatial {
    class SDocument;
    using SDocumentSPtr   = std::shared_ptr<SDocument>;
    using SDocumentSCPtr  = std::shared_ptr<const SDocument>;
    using SDocumentUPtr   = std::unique_ptr<SDocument>;
    using SDocumentUCPtr  = std::unique_ptr<const SDocument>;
}
