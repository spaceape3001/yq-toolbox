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

namespace yq::xg {
    class XGManifest;
    using XGManifestPtr     = Ref<XGManifest>;
    using XGManifestCPtr    = Ref<const XGManifest>;
    
    using xg_manifest_ptr_x = Expect<XGManifestPtr>;
}
