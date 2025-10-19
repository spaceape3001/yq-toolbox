////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/earth/wgs84.hpp>
#include <yq/earth/model/GeoEllipsoid.hpp>

//  Using NGA.STND.0036_1.0.0_WGS84, dated 2014-07-08 (EPOCH 2005)

namespace yq {
    const GeoModel&     wgs84()
    {
        static const GeoEllipsoidConfig    kWGS84_2005{
            .semimajor  = { 6378137.0 },
            .flattening = 1. / 298.257223563,
            .ω          = { 7.292115e-5 },
            .μ          = { 3.986004418e14 },
            .ge         = { 9.7803253359 },
            .gp         = { 9.8321849379 }
        };
        
        static const GeoEllipsoid           sPlanet(kWGS84_2005);
        return sPlanet;
    }
}
