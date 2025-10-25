////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Tangential.hpp"
#include <yq/coord/DValue.hpp>
#include <yq/coord/ecef/ECEFPosition.hpp>
#include <yq/coord/ecef/ECEFVector.hpp>
#include <yq/math/UV.hpp>

namespace yq::tangential {
    TanSurface      surface(const ECEFPosition& ecef)
    {
        double ax  = fabs(ecef.x.value);
        double ay  = fabs(ecef.y.value);
        double az  = fabs(ecef.z.value);
        
        if((ax > ay) && (ax > az)){
            return (ecef.x.value > 0) ? TanSurface::xPositive : TanSurface::xNegative;
        } else if(ay > az){
            return (ecef.y.value > 0) ? TanSurface::yPositive : TanSurface::yNegative;
        } else {
            return (ecef.z.value > 0) ? TanSurface::zPositive : TanSurface::zNegative;
        }
    }
    
    TriTanSurface   surfaces(const ECEFPosition&)
    {
        // TODO 
        return {};
    }

    TanUV           uv_of(TanSurface surf, const ECEFPosition& ecef)
    {
        switch(surf){
        case TanSurface::xPositive:
            return TanUV( ecef.y.value / ecef.x.value, ecef.z.value / ecef.x.value);
        case TanSurface::xNegative:
            return TanUV( ecef.y.value / ecef.x.value, -ecef.z.value / ecef.x.value);
        case TanSurface::yPositive:
            return TanUV( -ecef.x.value / ecef.y.value, ecef.z.value / ecef.y.value);
        case TanSurface::yNegative:
            return TanUV( -ecef.x.value / ecef.y.value, -ecef.z.value / ecef.y.value);
        case TanSurface::zPositive:
            return TanUV( ecef.x.value / ecef.z.value, ecef.y.value / ecef.z.value);
        case TanSurface::zNegative:
            return TanUV( ecef.x.value / ecef.z.value, ecef.y.value / ecef.z.value);
        default:
            return {};
        }
    }

    ECEFVector      outward_directional_vector(TanSurface surf, const TanUV& t)
    {
        switch(surf){
        case TanSurface::xPositive:
            return ECEFVector(  1.0,  t.u,  t.v );
        case TanSurface::xNegative:
            return ECEFVector( -1.0, -t.u,  t.v );
        case TanSurface::yPositive:
            return ECEFVector( -t.u,  1.0,  t.v );
        case TanSurface::yNegative:
            return ECEFVector(  t.u, -1.0,  t.v );
        case TanSurface::zPositive:
            return ECEFVector(  t.u,  t.v,  1.0 );
        case TanSurface::zNegative:
            return ECEFVector( -t.u, -t.v, -1.0 );
        default:
            return {};
        }
    }
}
