////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/typedef/ecef.hpp>
#include <yq/typedef/tangential.hpp>
#include <yq/coord/tan/TanSurface.hpp>

namespace yq {

    //! Helpers for a tangential earth coordinate system
    namespace tangential {
        struct TriTanSurface {
            TanSurface  primary;        //!< Surface the position is on
            TanSurface  secondary;      //!< Second closest (important for edges)
            TanSurface  tertiary;       //!< Third closest (important for near corners)
        };
    
        // Surface we're on
        TanSurface      surface(const ECEFPosition&);
        TriTanSurface   surfaces(const ECEFPosition&);
        
        TanUV           uv_of(TanSurface, const ECEFPosition&);
        
        //! Outward Directional vector 
        //! \note This will *NOT* be of unit length... if that's necessary, caller does normalization
        ECEFVector      outward_directional_vector(TanSurface, const TanUV&);
    }

    class TanDomain {
    public:
        using keyword_t   = tangential_k;
        
        TanSurface      surface;
    };
}
