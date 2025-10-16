////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GeoENU.hpp"

#include <yq/coord/Geodetic2.hpp>
#include <yq/coord/Geodetic3.hpp>
#include <yq/coord/ecef/ECEFAcceleration.hpp>
#include <yq/coord/ecef/ECEFOrientation.hpp>
#include <yq/coord/ecef/ECEFPosition.hpp>
#include <yq/coord/ecef/ECEFTensor.hpp>
#include <yq/coord/ecef/ECEFVector.hpp>
#include <yq/math/trigonometry.hpp>

#include <numbers>

namespace yq {
    static constexpr const Tensor33D    kNEDT{
        0., 1., 0.,
        1., 0., 0.,
        0., 0., -1.
    };

    static const Quaternion3D           kNEDQ    = quaternion(kNEDT);

    GeoENU::GeoENU(const GeoENUConfig& cfg) : m_center(cfg.center), m_gravity(cfg.gravity)
    {
        m_curvature.latitude    = m_radius.value;
        m_curvature.longitude   = m_radius.value * cos(cfg.center.latitude);
        m_iCurvature.latitude   = 1./m_curvature.latitude;
        m_iCurvature.longitude  = 1./m_curvature.longitude;
        name(SET, cfg.name);
    }
    
    GeoENU::~GeoENU()
    {
    }

    Meter   GeoENU::altitude(const ECEFPosition&ecef) const
    {
        return ecef.z;
    }
    
    ECEFVector  GeoENU::down(const Geodetic2R&) const 
    {
        return ECEFVector(Z,-1.);
    }
    
    ECEFVector  GeoENU::down(const Geodetic2R&, unit::Meter) const 
    {
        return ECEFVector(Z,-1.);
    }
    
    ECEFVector  GeoENU::down(const Geodetic3RM&) const 
    {
        return ECEFVector(Z,-1.);
    }
    
    ECEFVector  GeoENU::down(const ECEFPosition&) const 
    {
        return ECEFVector(Z,-1.);
    }

    ECEFVector  GeoENU::east(const Geodetic2R&) const
    {
        return ECEFVector(X, 1.);
    }
    
    ECEFVector  GeoENU::east(const Geodetic2R&, unit::Meter) const
    {
        return ECEFVector(X, 1.);
    }
    
    ECEFVector  GeoENU::east(const Geodetic3RM&) const
    {
        return ECEFVector(X, 1.);
    }
    
    ECEFVector  GeoENU::east(const ECEFPosition&) const
    {
        return ECEFVector(X, 1.);
    }

    Geodetic3RM GeoENU::geodetic(const ECEFPosition&ecef) const 
    {
        return Geodetic3RM{
            .latitude   = m_center.latitude + ecef.y * m_iCurvature.latitude,
            .longitude  = m_center.longitude + ecef.x * m_iCurvature.longitude,
            .altitude   = ecef.z
        };
    }
    
    Geodetic2R  GeoENU::geodetic2(const ECEFPosition&ecef) const 
    {
        return Geodetic2R{
            .latitude   = m_center.latitude + ecef.y * m_iCurvature.latitude,
            .longitude  = m_center.longitude + ecef.x * m_iCurvature.longitude
        };
    }

    unit::MeterPerSecond²   GeoENU::gravity(const Geodetic2R&) const
    {
        return m_gravity;
    }
    
    unit::MeterPerSecond²   GeoENU::gravity(const Geodetic2R&, unit::Meter) const
    {
        return m_gravity;
    }
    
    unit::MeterPerSecond²   GeoENU::gravity(const Geodetic3RM&) const
    {
        return m_gravity;
    }
    
    unit::MeterPerSecond²   GeoENU::gravity(const ECEFPosition&) const
    {
        return m_gravity;
    }

    ECEFAcceleration        GeoENU::gravity(vector_k, const Geodetic2R&) const
    {
        return ECEFAcceleration(Z, -m_gravity);
    }
    
    ECEFAcceleration        GeoENU::gravity(vector_k, const Geodetic2R&, unit::Meter) const
    {
        return ECEFAcceleration(Z, -m_gravity);
    }
    
    ECEFAcceleration        GeoENU::gravity(vector_k, const Geodetic3RM&) const
    {
        return ECEFAcceleration(Z, -m_gravity);
    }
    
    ECEFAcceleration        GeoENU::gravity(vector_k, const ECEFPosition&) const
    {
        return ECEFAcceleration(Z, -m_gravity);
    }
    
    ECEFVector              GeoENU::north(const Geodetic2R&) const
    {
        return ECEFVector(Y, 1.);
    }
    
    ECEFVector              GeoENU::north(const Geodetic2R&, Meter) const
    {
        return ECEFVector(Y, 1.);
    }
    
    ECEFVector              GeoENU::north(const Geodetic3RM&) const
    {
        return ECEFVector(Y, 1.);
    }
    
    ECEFVector              GeoENU::north(const ECEFPosition&) const
    {
        return ECEFVector(Y, 1.);
    }

    Quaternion3D    GeoENU::orientation(quaternion_k, enu_k, const Geodetic2R&) const
    {
        return IDENTITY;
    }
    
    Quaternion3D    GeoENU::orientation(quaternion_k, enu_k, const Geodetic2R&, unit::Meter) const
    {
        return IDENTITY;
    }
    
    Quaternion3D    GeoENU::orientation(quaternion_k, enu_k, const Geodetic3RM&) const
    {
        return IDENTITY;
    }
    
    Quaternion3D    GeoENU::orientation(quaternion_k, enu_k, const ECEFPosition&) const
    {
        return IDENTITY;
    }

    Quaternion3D    GeoENU::orientation(quaternion_k, ned_k, const Geodetic3RM&) const
    {
        return kNEDQ;
    }
    
    Quaternion3D    GeoENU::orientation(quaternion_k, ned_k, const Geodetic2R&) const
    {
        return kNEDQ;
    }
    
    Quaternion3D    GeoENU::orientation(quaternion_k, ned_k, const Geodetic2R&, unit::Meter) const
    {
        return kNEDQ;
    }
    
    Quaternion3D    GeoENU::orientation(quaternion_k, ned_k, const ECEFPosition&) const
    {
        return kNEDQ;
    }
    

    Tensor33D       GeoENU::orientation(tensor_k, enu_k, const Geodetic2R&) const
    {
        return IDENTITY;
    }
    
    Tensor33D       GeoENU::orientation(tensor_k, enu_k, const Geodetic2R&, unit::Meter) const
    {
        return IDENTITY;
    }
    
    Tensor33D       GeoENU::orientation(tensor_k, enu_k, const Geodetic3RM&) const
    {
        return IDENTITY;
    }
    
    Tensor33D       GeoENU::orientation(tensor_k, enu_k, const ECEFPosition&) const
    {
        return IDENTITY;
    }

    Tensor33D       GeoENU::orientation(tensor_k, ned_k, const Geodetic2R&) const
    {
        return kNEDT;
    }
    
    Tensor33D       GeoENU::orientation(tensor_k, ned_k, const Geodetic2R&, unit::Meter) const
    {
        return kNEDT;
    }
    
    Tensor33D       GeoENU::orientation(tensor_k, ned_k, const Geodetic3RM&) const
    {
        return kNEDT;
    }
    
    Tensor33D       GeoENU::orientation(tensor_k, ned_k, const ECEFPosition&) const
    {
        return kNEDT;
    }
    
    ECEFPosition    GeoENU::position(const Geodetic3RM&geo) const 
    {
        return ECEFPosition(
            (geo.longitude-m_center.longitude) * m_curvature.longitude,
            (geo.latitude-m_center.latitude) * m_curvature.latitude,
            geo.altitude
        );
    }
    
    ECEFPosition    GeoENU::position(const Geodetic2R& geo) const 
    {
        return ECEFPosition(
            (geo.longitude-m_center.longitude) * m_curvature.longitude,
            (geo.latitude-m_center.latitude) * m_curvature.latitude,
            0._m
        );
    }
    
    ECEFPosition    GeoENU::position(const Geodetic2R& geo, unit::Meter z) const 
    {
        return ECEFPosition(
            (geo.longitude-m_center.longitude) * m_curvature.longitude,
            (geo.latitude-m_center.latitude) * m_curvature.latitude,
            z
        );
    }

    Meter   GeoENU::radius(const Geodetic2R&) const
    {
        return m_radius;
    }
    
    Meter   GeoENU::radius(const Geodetic2R&, unit::Meter) const 
    {
        return m_radius;
    }
    
    Meter   GeoENU::radius(const Geodetic3RM&) const 
    {
        return m_radius;
    }
    
    Meter   GeoENU::radius(const ECEFPosition&) const 
    {
        return m_radius;
    }
    
        
    ECEFVector  GeoENU::south(const Geodetic2R&) const 
    {
        return ECEFVector(Y, -1.);
    }
    
    ECEFVector  GeoENU::south(const Geodetic2R&, unit::Meter) const 
    {
        return ECEFVector(Y, -1.);
    }
    
    ECEFVector  GeoENU::south(const Geodetic3RM&) const 
    {
        return ECEFVector(Y, -1.);
    }
    
    ECEFVector  GeoENU::south(const ECEFPosition&) const
    {
        return ECEFVector(Y, -1.);
    }
    
    ECEFVector  GeoENU::up(const Geodetic2R&) const 
    {
        return ECEFVector(Z, 1.);
    }
    
    ECEFVector  GeoENU::up(const Geodetic2R&, unit::Meter) const 
    {
        return ECEFVector(Z, 1.);
    }
    
    ECEFVector  GeoENU::up(const Geodetic3RM&) const 
    {
        return ECEFVector(Z, 1.);
    }
    
    ECEFVector  GeoENU::up(const ECEFPosition&) const
    {
        return ECEFVector(Z, 1.);
    }
    
    ECEFVector  GeoENU::west(const Geodetic2R&) const
    {
        return ECEFVector(X, -1.);
    }
    
    ECEFVector  GeoENU::west(const Geodetic2R&, unit::Meter) const 
    {
        return ECEFVector(X, -1.);
    }

    ECEFVector  GeoENU::west(const Geodetic3RM&) const 
    {
        return ECEFVector(X, -1.);
    }

    ECEFVector  GeoENU::west(const ECEFPosition&) const
    {
        return ECEFVector(X, -1.);
    }

}
