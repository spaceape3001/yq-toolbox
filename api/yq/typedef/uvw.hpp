////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace yq {
    template <typename> struct UVW;
    
    using UVW3D                  = UVW<double>;
    using UVW3F                  = UVW<float>;
    using UVW3I                  = UVW<int>;
    using UVW3U                  = UVW<unsigned>;
}
