////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GeoSpheroid.hpp"
#include <yq/coord/Geodetic2.hpp>
#include <yq/coord/Geodetic3.hpp>
#include <yq/coord/ecef/ECEFAcceleration.hpp>
#include <yq/coord/ecef/ECEFOrientation.hpp>
#include <yq/coord/ecef/ECEFPosition.hpp>
#include <yq/coord/ecef/ECEFTensor.hpp>
#include <yq/coord/ecef/ECEFVector.hpp>
#include <yq/math/trigonometry.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>
#include <yq/vector/Quaternion3.hxx>
#include <yq/vector/Vector3.hxx>

YQ_OBJECT_IMPLEMENT(yq::GeoSpheroid)

namespace yq {
    void GeoSpheroid::init_meta()
    {
        auto w = writer<GeoSpheroid>();
        w.description("Spheroid Earth Model (no flattening)");
    }

    GeoSpheroid::GeoSpheroid(const GeoSpheroidConfig& options) : m_gravity(options.gravity), m_radius(options.radius)
    {
        m_radius²   = m_radius * m_radius;
    }
    
    GeoSpheroid::~GeoSpheroid()
    {
    }

    unit::Meter    GeoSpheroid::altitude(const ECEFPosition&ecef) const
    {
        return ecef.length() - m_radius;
    }

    ECEFVector     GeoSpheroid::down(unit::Radian la, unit::Radian lo) const
    {
        double cla  = cos(la);
        return ECEFVector( -cos(lo) * cla, -sin(lo) * cla, -sin(la));
    }

    ECEFVector     GeoSpheroid::down(const Geodetic2R& geo) const
    {
        return down(geo.latitude, geo.longitude);
    }
    
    ECEFVector     GeoSpheroid::down(const Geodetic2R& geo, unit::Meter) const
    {
        return down(geo.latitude, geo.longitude);
    }
    
    ECEFVector     GeoSpheroid::down(const Geodetic3RM&geo) const
    {
        return down(geo.latitude, geo.longitude);
    }
    
    ECEFVector     GeoSpheroid::down(const ECEFPosition& ecef) const
    {
        // TODO... needs a vector constructor/conversion overload
        //return ECEFVector(~-ecef);
        return down(geodetic(ecef));
    }

    ECEFVector     GeoSpheroid::east(unit::Radian lo) const
    {
        return ECEFVector( -sin(lo), cos(lo), 0. );
    }
    
    ECEFVector     GeoSpheroid::east(const Geodetic2R&geo) const
    {
        return east(geo.longitude);
    }
    
    ECEFVector     GeoSpheroid::east(const Geodetic2R& geo, unit::Meter) const
    {
        return east(geo.longitude);
    }
    
    ECEFVector     GeoSpheroid::east(const Geodetic3RM& geo) const
    {
        return east(geo.longitude);
    }
    
    ECEFVector     GeoSpheroid::east(const ECEFPosition& ecef) const
    {
        return ECEFVector(~Vector3D( -ecef.y.value, ecef.x.value, 0. ));
    }

    Geodetic3RM    GeoSpheroid::geodetic(const ECEFPosition&ecef) const
    {
        return {
            .latitude   = atan(ecef.z, sqrt(ecef.x*ecef.x+ecef.y*ecef.y)),
            .longitude  = atan(ecef.y, ecef.x),
            .altitude   = ecef.length() - m_radius
        };
    }
    
    Geodetic2R     GeoSpheroid::geodetic2(const ECEFPosition&ecef) const
    {
        return {
            .latitude   = atan(ecef.z, sqrt(ecef.x*ecef.x+ecef.y*ecef.y)),
            .longitude  = atan(ecef.y, ecef.x)
        };
    }

    unit::MeterPerSecond²       GeoSpheroid::gravity(unit::Meter z) const
    {
        if(z >= 0.){
            Meter       R   = m_radius + z;
            return m_gravity * m_radius²/(R*R);
        } else {
            return m_gravity * (m_radius + z) / m_radius;
        }
    }
    
    unit::MeterPerSecond²       GeoSpheroid::gravity(const Geodetic2R&) const
    {
        return m_gravity;
    }
    
    unit::MeterPerSecond²       GeoSpheroid::gravity(const Geodetic2R&, unit::Meter z) const
    {
        return gravity(z);
    }
    
    unit::MeterPerSecond²       GeoSpheroid::gravity(const Geodetic3RM& geo) const
    {
        return gravity(geo.altitude);
    }
    
    unit::MeterPerSecond²       GeoSpheroid::gravity(const ECEFPosition&ecef) const
    {
        return gravity(ecef.length() - m_radius);
    }
    
    ECEFAcceleration            GeoSpheroid::gravity(vector_k, const Geodetic2R& geo) const
    {
        return ECEFAcceleration(m_gravity * down(geo));
    }
    
    ECEFAcceleration            GeoSpheroid::gravity(vector_k, const Geodetic2R& geo, unit::Meter z) const
    {
        return ECEFAcceleration(gravity(z) * down(geo));
    }
    
    ECEFAcceleration            GeoSpheroid::gravity(vector_k, const Geodetic3RM& geo) const
    {
        return ECEFAcceleration(gravity(geo.altitude) * down(geo));
    }
    
    ECEFAcceleration            GeoSpheroid::gravity(vector_k, const ECEFPosition& ecef) const
    {
        // TODO ... syntax issue (again)
        //return ECEFAcceleration(-(gravity(ecef.length()-m_radius) * ~ecef));
        return gravity(VECTOR, geodetic(ecef));
    }

    ECEFVector     GeoSpheroid::north(unit::Radian la, unit::Radian lo) const
    {
        double  sla = sin(la);
        return ECEFVector{
            -sla*cos(lo),
            -sla*sin(lo),
            cos(la)
        };
        return {};
    }

    ECEFVector     GeoSpheroid::north(const Geodetic2R&geo) const
    {
        return north(geo.latitude, geo.longitude);
    }
    
    ECEFVector     GeoSpheroid::north(const Geodetic2R&geo, Meter) const
    {
        return north(geo.latitude, geo.longitude);
    }
    
    ECEFVector     GeoSpheroid::north(const Geodetic3RM&geo) const
    {
        return north(geo.latitude, geo.longitude);
    }
    
    ECEFVector     GeoSpheroid::north(const ECEFPosition&ecef) const
    {
        // TODO (make better)
        return north(geodetic(ecef));
    }

    Quaternion3D  GeoSpheroid::orientation(quaternion_k, enu_k, unit::Radian la, unit::Radian lo) const
    {
        // TODO (refine this, actual math instead of transform... if better)
        return quaternion(orientation(TENSOR, ENU, la, lo));
    }

    Quaternion3D  GeoSpheroid::orientation(quaternion_k, enu_k, const Geodetic2R& geo) const
    {
        return orientation(QUAT, ENU, geo.latitude, geo.longitude);
    }
    
    Quaternion3D  GeoSpheroid::orientation(quaternion_k, enu_k, const Geodetic2R& geo, unit::Meter) const
    {
        return orientation(QUAT, ENU, geo.latitude, geo.longitude);
    }
    
    Quaternion3D  GeoSpheroid::orientation(quaternion_k, enu_k, const Geodetic3RM& geo) const
    {
        return orientation(QUAT, ENU, geo.latitude, geo.longitude);
    }
    
    Quaternion3D  GeoSpheroid::orientation(quaternion_k, enu_k, const ECEFPosition& ecef) const
    {
        // TODO (make better)
        return orientation(QUAT, ENU, geodetic(ecef));
    }

    Quaternion3D  GeoSpheroid::orientation(quaternion_k, ned_k, unit::Radian la, unit::Radian lo) const
    {
        // TODO (refine this, actual math instead of transform... if better)
        return quaternion(orientation(TENSOR, NED, la, lo));
    }

    Quaternion3D  GeoSpheroid::orientation(quaternion_k, ned_k, const Geodetic2R& geo) const
    {
        return orientation(QUAT, NED, geo.latitude, geo.longitude);
    }
    
    Quaternion3D  GeoSpheroid::orientation(quaternion_k, ned_k, const Geodetic2R& geo, unit::Meter) const
    {
        return orientation(QUAT, NED, geo.latitude, geo.longitude);
    }
    
    Quaternion3D  GeoSpheroid::orientation(quaternion_k, ned_k, const Geodetic3RM& geo) const
    {
        return orientation(QUAT, NED, geo.latitude, geo.longitude);
    }
    
    Quaternion3D  GeoSpheroid::orientation(quaternion_k, ned_k, const ECEFPosition& ecef) const
    {
        // TODO (make better)
        return orientation(QUAT, NED, geodetic(ecef));
    }

    Tensor33D  GeoSpheroid::orientation(tensor_k, enu_k, unit::Radian la, unit::Radian lo) const
    {
        return columns( east(lo), north(la,lo), up(la,lo));
    }
    
    Tensor33D  GeoSpheroid::orientation(tensor_k, enu_k, const Geodetic2R& geo) const
    {
        return orientation(TENSOR, ENU, geo.latitude, geo.longitude);
    }
    
    Tensor33D  GeoSpheroid::orientation(tensor_k, enu_k, const Geodetic2R& geo, unit::Meter) const
    {
        return orientation(TENSOR, ENU, geo.latitude, geo.longitude);
    }

    Tensor33D  GeoSpheroid::orientation(tensor_k, enu_k, const Geodetic3RM& geo) const
    {
        return orientation(TENSOR, ENU, geo.latitude, geo.longitude);
    }
    
    Tensor33D  GeoSpheroid::orientation(tensor_k, enu_k, const ECEFPosition& ecef) const
    {
        // TODO (make better)
        return orientation(TENSOR, ENU, geodetic(ecef));
    }

    Tensor33D  GeoSpheroid::orientation(tensor_k, ned_k, unit::Radian la, unit::Radian lo) const
    {
        return columns( north(la,lo), east(lo), down(la,lo));
    }

    Tensor33D  GeoSpheroid::orientation(tensor_k, ned_k, const Geodetic2R& geo) const
    {
        return orientation(TENSOR, NED, geo.latitude, geo.longitude);
    }
    
    Tensor33D  GeoSpheroid::orientation(tensor_k, ned_k, const Geodetic2R& geo, unit::Meter) const
    {
        return orientation(TENSOR, NED, geo.latitude, geo.longitude);
    }
    
    Tensor33D  GeoSpheroid::orientation(tensor_k, ned_k, const Geodetic3RM& geo) const
    {
        return orientation(TENSOR, NED, geo.latitude, geo.longitude);
    }
    
    Tensor33D  GeoSpheroid::orientation(tensor_k, ned_k, const ECEFPosition& ecef) const
    {
        // TODO (make better)
        return orientation(TENSOR, NED, geodetic(ecef));
    }


    ECEFPosition   GeoSpheroid::position(const Geodetic2R& geo) const 
    {
        double cla  = cos(geo.latitude);
        return ECEFPosition( m_radius*cos(geo.longitude)*cla, m_radius*sin(geo.longitude)*cla, m_radius*sin(geo.latitude));
    }
    
    ECEFPosition   GeoSpheroid::position(const Geodetic2R& geo, unit::Meter z) const 
    {
        unit::Meter R    = m_radius + z;
        double      cla  = cos(geo.latitude);
        return ECEFPosition(R*cos(geo.longitude)*cla, R*sin(geo.longitude)*cla, R*sin(geo.latitude));
    }
        
    ECEFPosition   GeoSpheroid::position(const Geodetic3RM&geo) const 
    {
        unit::Meter R    = m_radius + geo.altitude;
        double      cla  = cos(geo.latitude);
        return ECEFPosition(R*cos(geo.longitude)*cla, R*sin(geo.longitude)*cla, R*sin(geo.latitude));
    }
    
    unit::Meter  GeoSpheroid::radius(const Geodetic2R&) const
    {
        return m_radius;
    }
    
    unit::Meter  GeoSpheroid::radius(const Geodetic2R&, unit::Meter) const
    {
        return m_radius;
    }
    
    unit::Meter  GeoSpheroid::radius(const Geodetic3RM&) const
    {
        return m_radius;
    }
    
    unit::Meter  GeoSpheroid::radius(const ECEFPosition&) const
    {
        return m_radius;
    }

    ECEFVector   GeoSpheroid::south(unit::Radian la, unit::Radian lo) const
    {
        double  sla = sin(la);
        return ECEFVector{
            sla*cos(lo),
            sla*sin(lo),
            -cos(la)
        };
        return {};
    }
    
    ECEFVector   GeoSpheroid::south(const Geodetic2R& geo) const
    {
        return south(geo.latitude, geo.longitude);
    }
    
    ECEFVector   GeoSpheroid::south(const Geodetic2R& geo, unit::Meter) const
    {
        return south(geo.latitude, geo.longitude);
    }
    
    ECEFVector   GeoSpheroid::south(const Geodetic3RM& geo) const
    {
        return south(geo.latitude, geo.longitude);
    }
    
    ECEFVector   GeoSpheroid::south(const ECEFPosition& ecef) const
    {
        // TODO (make better)
        return south(geodetic(ecef));
    }
    
    ECEFVector   GeoSpheroid::up(unit::Radian la, unit::Radian lo) const
    {
        double cla  = cos(la);
        return ECEFVector( cos(lo) * cla, sin(lo) * cla, sin(la));
    }

    ECEFVector   GeoSpheroid::up(const Geodetic2R& geo) const
    {
        return up(geo.latitude, geo.longitude);
    }
    
    ECEFVector   GeoSpheroid::up(const Geodetic2R& geo, unit::Meter) const
    {
        return up(geo.latitude, geo.longitude);
    }
    
    ECEFVector   GeoSpheroid::up(const Geodetic3RM& geo) const
    {
        return up(geo.latitude, geo.longitude);
    }
    
    ECEFVector   GeoSpheroid::up(const ECEFPosition& ecef) const
    {
        // TODO... needs a vector constructor/conversion overload
        //return ECEFVector(~ecef);
        return up(geodetic(ecef));
    }
    
    ECEFVector   GeoSpheroid::west(unit::Radian lo) const
    {
        return ECEFVector( sin(lo), -cos(lo), 0. );
    }
    
    ECEFVector   GeoSpheroid::west(const Geodetic2R& geo) const
    {
        return west(geo.longitude);
    }
    
    ECEFVector   GeoSpheroid::west(const Geodetic2R& geo, unit::Meter) const
    {
        return west(geo.longitude);
    }
    
    ECEFVector   GeoSpheroid::west(const Geodetic3RM& geo) const
    {
        return west(geo.longitude);
    }
    
    ECEFVector   GeoSpheroid::west(const ECEFPosition& ecef) const
    {
        return ECEFVector(~Vector3D( ecef.y.value, -ecef.x.value, 0. ));
    }
    
}
