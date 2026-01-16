////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Expect.hpp>

namespace yq {
    template <typename> class Ref;
    
    class GManifest;
    using GManifestPtr     = Ref<GManifest>;
    using GManifestCPtr    = Ref<const GManifest>;
    
    using gmanifest_ptr_x = Expect<GManifestPtr>;
}
