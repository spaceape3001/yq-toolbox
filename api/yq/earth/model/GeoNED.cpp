////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GeoNED.hpp"

#include <yq/coord/Geodetic2.hpp>
#include <yq/coord/Geodetic3.hpp>
#include <yq/coord/ecef/ECEFAcceleration.hpp>
#include <yq/coord/ecef/ECEFOrientation.hpp>
#include <yq/coord/ecef/ECEFPosition.hpp>
#include <yq/coord/ecef/ECEFTensor.hpp>
#include <yq/coord/ecef/ECEFVector.hpp>
#include <yq/math/trigonometry.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>

#include <numbers>

YQ_OBJECT_IMPLEMENT(yq::GeoNED)

namespace yq {
    static constexpr const Tensor33D    kENUT{
        0., 1., 0.,
        1., 0., 0.,
        0., 0., -1.
    };

    static const Quaternion3D           kENUQ    = quaternion(kENUT);

    void GeoNED::init_meta()
    {
        auto w = writer<GeoNED>();
        w.description("Flat Earth Model (North East Down)");
    }

    GeoNED::GeoNED(const GeoNEDConfig& cfg) : m_center(cfg.center), m_gravity(cfg.gravity)
    {
        m_curvature.latitude    = m_radius.value;
        m_curvature.longitude   = m_radius.value * cos(cfg.center.latitude);
        m_iCurvature.latitude   = 1./m_curvature.latitude;
        m_iCurvature.longitude  = 1./m_curvature.longitude;
        name(SET, cfg.name);
    }
    
    GeoNED::~GeoNED()
    {
    }

    Meter   GeoNED::altitude(const ECEFPosition&ecef) const
    {
        return -ecef.z;
    }
    
    ECEFVector  GeoNED::down(const Geodetic2R&) const 
    {
        return ECEFVector(Z,1.);
    }
    
    ECEFVector  GeoNED::down(const Geodetic2R&, unit::Meter) const 
    {
        return ECEFVector(Z,1.);
    }
    
    ECEFVector  GeoNED::down(const Geodetic3RM&) const 
    {
        return ECEFVector(Z,1.);
    }
    
    ECEFVector  GeoNED::down(const ECEFPosition&) const 
    {
        return ECEFVector(Z,1.);
    }

    ECEFVector  GeoNED::east(const Geodetic2R&) const
    {
        return ECEFVector(Y, 1.);
    }
    
    ECEFVector  GeoNED::east(const Geodetic2R&, unit::Meter) const
    {
        return ECEFVector(Y, 1.);
    }
    
    ECEFVector  GeoNED::east(const Geodetic3RM&) const
    {
        return ECEFVector(Y, 1.);
    }
    
    ECEFVector  GeoNED::east(const ECEFPosition&) const
    {
        return ECEFVector(Y, 1.);
    }

    Geodetic3RM GeoNED::geodetic(const ECEFPosition&ecef) const 
    {
        return Geodetic3RM{
            .latitude   = m_center.latitude + ecef.x * m_iCurvature.latitude,
            .longitude  = m_center.longitude + ecef.y * m_iCurvature.longitude,
            .altitude   = -ecef.z
        };
    }
    
    Geodetic2R  GeoNED::geodetic2(const ECEFPosition&ecef) const 
    {
        return Geodetic2R{
            .latitude   = m_center.latitude + ecef.x * m_iCurvature.latitude,
            .longitude  = m_center.longitude + ecef.y * m_iCurvature.longitude
        };
    }

    unit::MeterPerSecond²   GeoNED::gravity(const Geodetic2R&) const
    {
        return m_gravity;
    }
    
    unit::MeterPerSecond²   GeoNED::gravity(const Geodetic2R&, unit::Meter) const
    {
        return m_gravity;
    }
    
    unit::MeterPerSecond²   GeoNED::gravity(const Geodetic3RM&) const
    {
        return m_gravity;
    }
    
    unit::MeterPerSecond²   GeoNED::gravity(const ECEFPosition&) const
    {
        return m_gravity;
    }

    ECEFAcceleration        GeoNED::gravity(vector_k, const Geodetic2R&) const
    {
        return ECEFAcceleration(Z, m_gravity);
    }
    
    ECEFAcceleration        GeoNED::gravity(vector_k, const Geodetic2R&, unit::Meter) const
    {
        return ECEFAcceleration(Z, m_gravity);
    }
    
    ECEFAcceleration        GeoNED::gravity(vector_k, const Geodetic3RM&) const
    {
        return ECEFAcceleration(Z, m_gravity);
    }
    
    ECEFAcceleration        GeoNED::gravity(vector_k, const ECEFPosition&) const
    {
        return ECEFAcceleration(Z, m_gravity);
    }
    
    ECEFVector              GeoNED::north(const Geodetic2R&) const
    {
        return ECEFVector(X, 1.);
    }
    
    ECEFVector              GeoNED::north(const Geodetic2R&, Meter) const
    {
        return ECEFVector(X, 1.);
    }
    
    ECEFVector              GeoNED::north(const Geodetic3RM&) const
    {
        return ECEFVector(X, 1.);
    }
    
    ECEFVector              GeoNED::north(const ECEFPosition&) const
    {
        return ECEFVector(X, 1.);
    }

    Quaternion3D    GeoNED::orientation(quaternion_k, enu_k, const Geodetic2R&) const
    {
        return kENUQ;
    }
    
    Quaternion3D    GeoNED::orientation(quaternion_k, enu_k, const Geodetic2R&, unit::Meter) const
    {
        return kENUQ;
    }
    
    Quaternion3D    GeoNED::orientation(quaternion_k, enu_k, const Geodetic3RM&) const
    {
        return kENUQ;
    }
    
    Quaternion3D    GeoNED::orientation(quaternion_k, enu_k, const ECEFPosition&) const
    {
        return kENUQ;
    }

    Quaternion3D    GeoNED::orientation(quaternion_k, ned_k, const Geodetic3RM&) const
    {
        return IDENTITY;
    }
    
    Quaternion3D    GeoNED::orientation(quaternion_k, ned_k, const Geodetic2R&) const
    {
        return IDENTITY;
    }
    
    Quaternion3D    GeoNED::orientation(quaternion_k, ned_k, const Geodetic2R&, unit::Meter) const
    {
        return IDENTITY;
    }
    
    Quaternion3D    GeoNED::orientation(quaternion_k, ned_k, const ECEFPosition&) const
    {
        return IDENTITY;
    }
    

    Tensor33D       GeoNED::orientation(tensor_k, enu_k, const Geodetic2R&) const
    {
        return kENUT;
    }
    
    Tensor33D       GeoNED::orientation(tensor_k, enu_k, const Geodetic2R&, unit::Meter) const
    {
        return kENUT;
    }
    
    Tensor33D       GeoNED::orientation(tensor_k, enu_k, const Geodetic3RM&) const
    {
        return kENUT;
    }
    
    Tensor33D       GeoNED::orientation(tensor_k, enu_k, const ECEFPosition&) const
    {
        return kENUT;
    }

    Tensor33D       GeoNED::orientation(tensor_k, ned_k, const Geodetic2R&) const
    {
        return IDENTITY;
    }
    
    Tensor33D       GeoNED::orientation(tensor_k, ned_k, const Geodetic2R&, unit::Meter) const
    {
        return IDENTITY;
    }
    
    Tensor33D       GeoNED::orientation(tensor_k, ned_k, const Geodetic3RM&) const
    {
        return IDENTITY;
    }
    
    Tensor33D       GeoNED::orientation(tensor_k, ned_k, const ECEFPosition&) const
    {
        return IDENTITY;
    }
    
    ECEFPosition    GeoNED::position(const Geodetic3RM&geo) const 
    {
        return ECEFPosition(
            (geo.latitude-m_center.latitude) * m_curvature.latitude,
            (geo.longitude-m_center.longitude) * m_curvature.longitude,
            -geo.altitude
        );
    }
    
    ECEFPosition    GeoNED::position(const Geodetic2R& geo) const 
    {
        return ECEFPosition(
            (geo.latitude-m_center.latitude) * m_curvature.latitude,
            (geo.longitude-m_center.longitude) * m_curvature.longitude,
            0._m
        );
    }
    
    ECEFPosition    GeoNED::position(const Geodetic2R& geo, unit::Meter z) const 
    {
        return ECEFPosition(
            (geo.latitude-m_center.latitude) * m_curvature.latitude,
            (geo.longitude-m_center.longitude) * m_curvature.longitude,
            -z
        );
    }

    Meter   GeoNED::radius(const Geodetic2R&) const
    {
        return m_radius;
    }
    
    Meter   GeoNED::radius(const Geodetic2R&, unit::Meter) const 
    {
        return m_radius;
    }
    
    Meter   GeoNED::radius(const Geodetic3RM&) const 
    {
        return m_radius;
    }
    
    Meter   GeoNED::radius(const ECEFPosition&) const 
    {
        return m_radius;
    }
    
        
    ECEFVector  GeoNED::south(const Geodetic2R&) const 
    {
        return ECEFVector(X, -1.);
    }
    
    ECEFVector  GeoNED::south(const Geodetic2R&, unit::Meter) const 
    {
        return ECEFVector(X, -1.);
    }
    
    ECEFVector  GeoNED::south(const Geodetic3RM&) const 
    {
        return ECEFVector(X, -1.);
    }
    
    ECEFVector  GeoNED::south(const ECEFPosition&) const
    {
        return ECEFVector(X, -1.);
    }
    
    ECEFVector  GeoNED::up(const Geodetic2R&) const 
    {
        return ECEFVector(Z, -1.);
    }
    
    ECEFVector  GeoNED::up(const Geodetic2R&, unit::Meter) const 
    {
        return ECEFVector(Z, -1.);
    }
    
    ECEFVector  GeoNED::up(const Geodetic3RM&) const 
    {
        return ECEFVector(Z, -1.);
    }
    
    ECEFVector  GeoNED::up(const ECEFPosition&) const
    {
        return ECEFVector(Z, -1.);
    }
    
    ECEFVector  GeoNED::west(const Geodetic2R&) const
    {
        return ECEFVector(Y, -1.);
    }
    
    ECEFVector  GeoNED::west(const Geodetic2R&, unit::Meter) const 
    {
        return ECEFVector(Y, -1.);
    }

    ECEFVector  GeoNED::west(const Geodetic3RM&) const 
    {
        return ECEFVector(Y, -1.);
    }

    ECEFVector  GeoNED::west(const ECEFPosition&) const
    {
        return ECEFVector(Y, -1.);
    }

}
