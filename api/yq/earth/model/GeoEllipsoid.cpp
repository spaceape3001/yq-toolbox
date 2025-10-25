////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GeoEllipsoid.hpp"

#include <yq/coord/Geodetic2.hpp>
#include <yq/coord/Geodetic3.hpp>
#include <yq/coord/ecef/ECEFAcceleration.hpp>
#include <yq/coord/ecef/ECEFOrientation.hpp>
#include <yq/coord/ecef/ECEFPosition.hpp>
#include <yq/coord/ecef/ECEFTensor.hpp>
#include <yq/coord/ecef/ECEFVector.hpp>
#include <yq/math/trigonometry.hpp>
#include <yq/meta/ObjectMetaWriter.hpp>
#include <yq/vector/Vector3.hxx>

YQ_OBJECT_IMPLEMENT(yq::GeoEllipsoid)

namespace yq {
    void GeoEllipsoid::init_meta()
    {
        auto w = writer<GeoEllipsoid>();
        w.description("Ellipsoid (ie oblate spheroid) geodetic model");
        //w.property("area", &GeoEllipsoid::surface_area);
        w.property("eccentricity", &GeoEllipsoid::eccentricity);
        w.property("focus", &GeoEllipsoid::focus);
        w.property("semimajor", &GeoEllipsoid::semimajor);
        w.property("semiminor", &GeoEllipsoid::semiminor);
        w.property("volume", &GeoEllipsoid::volume);
    }

    GeoEllipsoid::Param GeoEllipsoid::compute_parameters(const GeoEllipsoidConfig& cfg)
    {
        Param   p{};
        
        p.a             = cfg.semimajor.value;
        p.a²            = p.a * p.a;
        p.b             = cfg.semiminor().value;
        p.b²            = p.b * p.b;
        p.c             = cfg.focus().value;
        p.c²            = p.c * p.c;
        p.e             = cfg.eccentricity();
        p.e²            = p.e * p.e;
        p.f             = cfg.flattening;
        p.a²b²          = p.a² * p.b²;
        p.a²_div_b²     = p.a² / p.b²;
        p.a_div_b       = p.a / p.b;
        p.ne2m1         = 1 - p.e²;
        p.e²a           = p.e² * p.a;
        p.e²c           = p.c² / p.b²;
        p.e²cb          = p.e²c * p.b;
        
        return p;
    }

    GeoEllipsoid::GeoEllipsoid(const GeoEllipsoidConfig& options) : 
        eccentricity(options.eccentricity()),
        flattening(options.flattening),
        focus(options.focus()),
        radius_by_area(options.radius_by_area()),
        radius_by_volume(options.radius_by_volume()),
        semimajor(options.semimajor),
        semiminor(options.semiminor()),
        surface_area(options.surface_area()),
        volume(options.volume()),
        m_param(compute_parameters(options))
    {
    }
    
    GeoEllipsoid::~GeoEllipsoid()
    {
    }

    unit::Meter  GeoEllipsoid::altitude(const ECEFPosition& ecef) const
    {
        // TODO { REFINE }
        return geodetic(ecef).altitude;
    }

    ECEFVector  GeoEllipsoid::down(unit::Radian la, unit::Radian lo) const
    {
        double cla  = cos(la);
        return ECEFVector( -cos(lo) * cla, -sin(lo) * cla, -sin(la));
    }

    ECEFVector  GeoEllipsoid::down(const Geodetic2R& geo) const 
    {
        return down(geo.latitude, geo.longitude);
    }

    ECEFVector  GeoEllipsoid::down(const Geodetic2R& geo, unit::Meter z) const 
    {
        return down(geo.latitude, geo.longitude);
    }

    ECEFVector  GeoEllipsoid::down(const Geodetic3RM& geo) const 
    {
        return down(geo.latitude, geo.longitude);
    }

    ECEFVector  GeoEllipsoid::down(const ECEFPosition& ecef) const 
    {
        // TODO { REFINE }
        return down(geodetic(ecef));
    }
    
    ECEFVector  GeoEllipsoid::east(unit::Radian lo) const
    {
        return ECEFVector( -sin(lo), cos(lo), 0. );
    }

    ECEFVector  GeoEllipsoid::east(const Geodetic2R& geo) const
    {
        return east(geo.longitude);
    }

    ECEFVector  GeoEllipsoid::east(const Geodetic2R& geo, unit::Meter) const
    {
        return east(geo.longitude);
    }

    ECEFVector  GeoEllipsoid::east(const Geodetic3RM& geo) const
    {
        return east(geo.longitude);
    }

    ECEFVector  GeoEllipsoid::east(const ECEFPosition& ecef) const
    {
        return ECEFVector(~Vector3D( -ecef.y.value, ecef.x.value, 0. ));
    }

    Geodetic3RM  GeoEllipsoid::geodetic(const ECEFPosition& ecef) const 
    {
        // https://www.icao.int/sites/default/files/safety/pbn/External%20References/Eurocontrol-WGS-84-Implementation-Manual.pdf
        double  p       = sqrt(ecef.x*ecef.x+ecef.y*ecef.y).value;
        double  lo      = atan2(ecef.y.value, ecef.x.value);
        double  la      = 0.;
        double  h       = 0.;
        
        if(p == 0.0){   // got a singularity...
            la          = copysign(0.5*std::numbers::pi_v<double>, ecef.z.value);
            h           = fabs(ecef.z.value) - m_param.b;
        } else {
            double u, su, cu, n, d, r1, r2, sla;
        
            u   = std::atan((ecef.z.value/p)*m_param.a_div_b);
            su  = std::sin(u);  cu = std::cos(u);
            n   = ecef.z.value + m_param.e²cb*su*su*su;
            d   = p - m_param.e²a * cu*cu*cu;
            la  = std::atan(n/d);
            r1  = p / std::cos(la);
            sla = std::sin(la);
            r2  = m_param.a / sqrt(1-m_param.e²*sla*sla);
            h   = r1 - r2;
        }
        
        return { la, lo, h };
    }

    Geodetic2R  GeoEllipsoid::geodetic2(const ECEFPosition& ecef) const 
    {
        double  p       = sqrt(ecef.x*ecef.x+ecef.y*ecef.y).value;
        double  lo      = atan2(ecef.y.value, ecef.x.value);
        double  la      = 0.;
        
        if(p == 0.0){   // got a singularity...
            la          = copysign(0.5*std::numbers::pi_v<double>, ecef.z.value);
        } else {
            double u, su, cu, n, d;
        
            u   = std::atan((ecef.z.value/p)*m_param.a_div_b);
            su  = std::sin(u);  cu = std::cos(u);
            n   = ecef.z.value + m_param.e²cb*su*su*su;
            d   = p - m_param.e²a * cu*cu*cu;
            la  = std::atan(n/d);
        }
        
        return { la, lo };
    }

    unit::MeterPerSecond²  GeoEllipsoid::gravity(unit::Radian la, unit::Meter z) const
    {
        // TODO
        return 1_G;
    }

    unit::MeterPerSecond²  GeoEllipsoid::gravity(const Geodetic2R& geo) const
    {
        return gravity(geo.latitude, 0._m);
    }

    unit::MeterPerSecond²  GeoEllipsoid::gravity(const Geodetic2R& geo, unit::Meter z) const
    {
        return gravity(geo.latitude,  z);
    }

    unit::MeterPerSecond²  GeoEllipsoid::gravity(const Geodetic3RM& geo) const
    {
        return gravity(geo.latitude, geo.altitude);
    }

    unit::MeterPerSecond²  GeoEllipsoid::gravity(const ECEFPosition& ecef) const
    {
        // TODO (REFINE)
        return gravity(geodetic(ecef));
    }

    ECEFAcceleration  GeoEllipsoid::gravity(vector_k, unit::Radian la, unit::Radian lo, unit::Meter z) const
    {
        return ECEFAcceleration(gravity(la,z)*down(la,lo));
    }

    ECEFAcceleration  GeoEllipsoid::gravity(vector_k, const Geodetic2R& geo) const
    {
        return gravity(VECTOR, geo.latitude, geo.longitude, 0._m);
    }

    ECEFAcceleration  GeoEllipsoid::gravity(vector_k, const Geodetic2R& geo, unit::Meter z) const
    {
        return gravity(VECTOR, geo.latitude, geo.longitude, z);
    }

    ECEFAcceleration  GeoEllipsoid::gravity(vector_k, const Geodetic3RM& geo) const
    {
        return gravity(VECTOR, geo.latitude, geo.longitude, geo.altitude);
    }

    ECEFAcceleration  GeoEllipsoid::gravity(vector_k, const ECEFPosition& ecef) const
    {
        // TODO (REFINE)
        return gravity(VECTOR, geodetic(ecef));
    }

    ECEFVector  GeoEllipsoid::north(unit::Radian la, unit::Radian lo) const
    {
        double  sla = sin(la);
        return ECEFVector{
            -sla*cos(lo),
            -sla*sin(lo),
            cos(la)
        };
        return {};
    }

    ECEFVector  GeoEllipsoid::north(const Geodetic2R& geo) const
    {
        return north(geo.latitude, geo.longitude);
    }

    ECEFVector  GeoEllipsoid::north(const Geodetic2R& geo, Meter) const
    {
        return north(geo.latitude, geo.longitude);
    }

    ECEFVector  GeoEllipsoid::north(const Geodetic3RM& geo) const
    {
        return north(geo.latitude, geo.longitude);
    }

    ECEFVector  GeoEllipsoid::north(const ECEFPosition& ecef) const
    {
        // TODO (REFINE)
        return north(geodetic(ecef));
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, enu_k, unit::Radian la, unit::Radian lo) const
    {
        // TODO (REFINE)
        return quaternion(orientation(TENSOR, ENU, la, lo));
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, enu_k, const Geodetic2R& geo) const
    {
        return orientation(QUAT, ENU, geo.latitude, geo.longitude);
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, enu_k, const Geodetic2R& geo, unit::Meter z) const
    {
        return orientation(QUAT, ENU, geo.latitude, geo.longitude);
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, enu_k, const Geodetic3RM& geo) const
    {
        return orientation(QUAT, ENU, geo.latitude, geo.longitude);
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, enu_k, const ECEFPosition& ecef) const
    {
        // TODO (REFINE)
        return orientation(QUAT, ENU, geodetic(ecef));
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, ned_k, unit::Radian la, unit::Radian lo) const
    {
        // TODO (refine this, actual math instead of transform... if better)
        return quaternion(orientation(TENSOR, NED, la, lo));
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, ned_k, const Geodetic2R& geo) const
    {
        return orientation(QUAT, NED, geo.latitude, geo.longitude);
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, ned_k, const Geodetic2R& geo, unit::Meter z) const
    {
        return orientation(QUAT, NED, geo.latitude, geo.longitude);
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, ned_k, const Geodetic3RM& geo) const
    {
        return orientation(QUAT, NED, geo.latitude, geo.longitude);
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, ned_k, const ECEFPosition& ecef) const
    {
        // TODO (REFINE)
        return orientation(QUAT, NED, geodetic(ecef));
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, enu_k, unit::Radian la, unit::Radian lo) const
    {
        //  TODO (REFINE)
        return columns(east(lo), north(la, lo), up(la, lo));
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, enu_k, const Geodetic2R& geo) const
    {
        return orientation(TENSOR, ENU, geo.latitude, geo.longitude);
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, enu_k, const Geodetic2R& geo, unit::Meter z) const
    {
        return orientation(TENSOR, ENU, geo.latitude, geo.longitude);
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, enu_k, const Geodetic3RM& geo) const
    {
        return orientation(TENSOR, ENU, geo.latitude, geo.longitude);
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, enu_k, const ECEFPosition& ecef) const
    {
        // TODO (REFINE)
        return orientation(TENSOR, ENU, geodetic(ecef));
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, ned_k, unit::Radian la, unit::Radian lo) const
    {
        //  TODO (REFINE)
        return columns(north(la, lo), east(lo), down(la, lo));
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, ned_k, const Geodetic2R& geo) const
    {
        return orientation(TENSOR, NED, geo.latitude, geo.longitude);
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, ned_k, const Geodetic2R& geo, unit::Meter z) const
    {
        return orientation(TENSOR, NED, geo.latitude, geo.longitude);
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, ned_k, const Geodetic3RM& geo) const
    {
        return orientation(TENSOR, NED, geo.latitude, geo.longitude);
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, ned_k, const ECEFPosition& ecef) const
    {
        // TODO (REFINE)
        return orientation(TENSOR, NED, geodetic(ecef));
    }

    ECEFPosition  GeoEllipsoid::position(unit::Radian la, unit::Radian lo, unit::Meter h) const 
    {
        double  sla = sin(la);
        double  cla = cos(la);
        unit::Meter N   = semimajor/sqrt(1-m_param.e²*sla*sla);
        
        unit::Meter x   = (N+h)*cla*cos(lo);
        unit::Meter y   = (N+h)*cla*sin(lo);
        unit::Meter z   = (m_param.ne2m1*N+h)*sla;
        
        return ECEFPosition(x,y,z);
    }

    ECEFPosition  GeoEllipsoid::position(const Geodetic3RM& geo) const 
    {
        return position(geo.latitude, geo.longitude, geo.altitude);
    }

    ECEFPosition  GeoEllipsoid::position(const Geodetic2R& geo) const 
    {
        return position(geo.latitude, geo.longitude, 0._m);
    }

    ECEFPosition  GeoEllipsoid::position(const Geodetic2R& geo, unit::Meter z) const 
    {
        return position(geo.latitude, geo.longitude, z);
    }

    unit::Meter  GeoEllipsoid::radius(unit::Radian la) const
    {
        double  sla = sin(la);
        return semimajor/sqrt(1-m_param.e²*sla*sla);
    }

    unit::Meter  GeoEllipsoid::radius(const Geodetic2R& geo) const
    {
        return radius(geo.latitude);
    }

    unit::Meter  GeoEllipsoid::radius(const Geodetic2R& geo, unit::Meter z) const
    {
        return radius(geo.latitude);
    }

    unit::Meter  GeoEllipsoid::radius(const Geodetic3RM& geo) const
    {
        return radius(geo.latitude);
    }

    unit::Meter  GeoEllipsoid::radius(const ECEFPosition& ecef) const
    {
        // TODO (REFINE)
        return radius(geodetic(ecef));
    }
    
    ECEFVector   GeoEllipsoid::south(unit::Radian la, unit::Radian lo) const
    {
        double  sla = sin(la);
        return ECEFVector{
            sla*cos(lo),
            sla*sin(lo),
            -cos(la)
        };
        return {};
    }
    
    ECEFVector  GeoEllipsoid::south(const Geodetic2R& geo) const
    {
        return south(geo.latitude, geo.longitude);
    }

    ECEFVector  GeoEllipsoid::south(const Geodetic2R& geo, unit::Meter z) const
    {
        return south(geo.latitude, geo.longitude);
    }

    ECEFVector  GeoEllipsoid::south(const Geodetic3RM& geo) const
    {
        return south(geo.latitude, geo.longitude);
    }

    ECEFVector  GeoEllipsoid::south(const ECEFPosition& ecef) const
    {
        // TODO (REFINE)
        return south(geodetic(ecef));
    }

    ECEFVector  GeoEllipsoid::up(unit::Radian la, unit::Radian lo) const
    {
        double cla  = cos(la);
        return ECEFVector( cos(lo) * cla, sin(lo) * cla, sin(la));
    }

    ECEFVector  GeoEllipsoid::up(const Geodetic2R& geo) const
    {
        return up(geo.latitude, geo.longitude);
    }

    ECEFVector  GeoEllipsoid::up(const Geodetic2R& geo, unit::Meter z) const
    {
        return up(geo.latitude, geo.longitude);
    }

    ECEFVector  GeoEllipsoid::up(const Geodetic3RM& geo) const
    {
        return up(geo.latitude, geo.longitude);
    }

    ECEFVector  GeoEllipsoid::up(const ECEFPosition& ecef) const
    {
        // TODO (ie, make better)
        return up(geodetic(ecef));
    }
    
    ECEFVector  GeoEllipsoid::west(unit::Radian lo) const
    {
        return ECEFVector( sin(lo), -cos(lo), 0. );
    }

    ECEFVector  GeoEllipsoid::west(const Geodetic2R& geo) const
    {
        return west(geo.longitude);
    }

    ECEFVector  GeoEllipsoid::west(const Geodetic2R& geo, unit::Meter z) const
    {
        return west(geo.longitude);
    }

    ECEFVector  GeoEllipsoid::west(const Geodetic3RM& geo) const
    {
        return west(geo.longitude);
    }

    ECEFVector  GeoEllipsoid::west(const ECEFPosition& ecef) const
    {
        return ECEFVector(~Vector3D( ecef.y.value, -ecef.x.value, 0. ));
    }

    /////////////////////////////////////////////////////
    double          GeoEllipsoidConfig::eccentricity() const
    {
        return (focus() / semimajor).value;
    }
    
    unit::Meter     GeoEllipsoidConfig::focus() const
    {
        auto b = semiminor();
        return sqrt( semimajor*semimajor - b*b);
    }
    
    unit::Meter     GeoEllipsoidConfig::radius_by_area() const
    {
        // TODO
        return {};
    }
    
    unit::Meter     GeoEllipsoidConfig::radius_by_volume() const
    {
        return {pow(semimajor.value*semimajor.value*semiminor().value, 1.0/3.0)};
    }

    unit::Meter     GeoEllipsoidConfig::semiminor() const
    {
        return semimajor * (1-flattening);
    }
    
    unit::Meter²    GeoEllipsoidConfig::surface_area() const
    {
        // TODO
        return {};
    }

    unit::Meter³    GeoEllipsoidConfig::volume() const
    {
        static constexpr const double PI   = std::numbers::pi_v<double>;
        return (4.0 / 3.0 * PI) * semimajor * semimajor * semiminor();
    }
    

}
