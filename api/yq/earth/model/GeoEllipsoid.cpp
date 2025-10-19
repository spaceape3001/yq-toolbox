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
        w.property("area", &GeoEllipsoid::surface_area);
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
        p.e²c           = p.e² * p.c;
        p.e²cb          = p.e² * p.c * p.b;
        
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

    ECEFVector  GeoEllipsoid::east(const Geodetic2R& geo) const
    {
        // TODO
        return {};
    }

    ECEFVector  GeoEllipsoid::east(const Geodetic2R& geo, unit::Meter z) const
    {
        // TODO
        return {};
    }

    ECEFVector  GeoEllipsoid::east(const Geodetic3RM& geo) const
    {
        // TODO
        return {};
    }

    ECEFVector  GeoEllipsoid::east(const ECEFPosition& ecef) const
    {
        // TODO
        return {};
    }

    Geodetic3RM  GeoEllipsoid::geodetic(const ECEFPosition& ecef) const 
    {
        // TODO
        return {};
    }

    Geodetic2R  GeoEllipsoid::geodetic2(const ECEFPosition& ecef) const 
    {
        // TODO
        return {};
    }

    unit::MeterPerSecond²  GeoEllipsoid::gravity(const Geodetic2R& geo) const
    {
        // TODO
        return {};
    }

    unit::MeterPerSecond²  GeoEllipsoid::gravity(const Geodetic2R& geo, unit::Meter z) const
    {
        // TODO
        return {};
    }

    unit::MeterPerSecond²  GeoEllipsoid::gravity(const Geodetic3RM& geo) const
    {
        // TODO
        return {};
    }

    unit::MeterPerSecond²  GeoEllipsoid::gravity(const ECEFPosition& ecef) const
    {
        // TODO
        return {};
    }

    ECEFAcceleration  GeoEllipsoid::gravity(vector_k, const Geodetic2R& geo) const
    {
        // TODO
        return {};
    }

    ECEFAcceleration  GeoEllipsoid::gravity(vector_k, const Geodetic2R& geo, unit::Meter z) const
    {
        // TODO
        return {};
    }

    ECEFAcceleration  GeoEllipsoid::gravity(vector_k, const Geodetic3RM& geo) const
    {
        // TODO
        return {};
    }

    ECEFAcceleration  GeoEllipsoid::gravity(vector_k, const ECEFPosition& ecef) const
    {
        // TODO
        return {};
    }

    ECEFVector  GeoEllipsoid::north(const Geodetic2R& geo) const
    {
        // TODO
        return {};
    }

    ECEFVector  GeoEllipsoid::north(const Geodetic2R& geo, Meter) const
    {
        // TODO
        return {};
    }

    ECEFVector  GeoEllipsoid::north(const Geodetic3RM& geo) const
    {
        // TODO
        return {};
    }

    ECEFVector  GeoEllipsoid::north(const ECEFPosition& ecef) const
    {
        // TODO
        return {};
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, enu_k, const Geodetic2R& geo) const
    {
        // TODO
        return {};
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, enu_k, const Geodetic2R& geo, unit::Meter z) const
    {
        // TODO
        return {};
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, enu_k, const Geodetic3RM& geo) const
    {
        // TODO
        return {};
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, enu_k, const ECEFPosition& ecef) const
    {
        // TODO
        return {};
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, ned_k, const Geodetic2R& geo) const
    {
        // TODO
        return {};
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, ned_k, const Geodetic2R& geo, unit::Meter z) const
    {
        // TODO
        return {};
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, ned_k, const Geodetic3RM& geo) const
    {
        // TODO
        return {};
    }

    Quaternion3D  GeoEllipsoid::orientation(quaternion_k, ned_k, const ECEFPosition& ecef) const
    {
        // TODO
        return {};
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, enu_k, const Geodetic2R& geo) const
    {
        // TODO
        return {};
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, enu_k, const Geodetic2R& geo, unit::Meter z) const
    {
        // TODO
        return {};
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, enu_k, const Geodetic3RM& geo) const
    {
        // TODO
        return {};
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, enu_k, const ECEFPosition& ecef) const
    {
        // TODO
        return {};
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, ned_k, const Geodetic2R& geo) const
    {
        // TODO
        return {};
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, ned_k, const Geodetic2R& geo, unit::Meter z) const
    {
        // TODO
        return {};
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, ned_k, const Geodetic3RM& geo) const
    {
        // TODO
        return {};
    }

    Tensor33D  GeoEllipsoid::orientation(tensor_k, ned_k, const ECEFPosition& ecef) const
    {
        // TODO
        return {};
    }

    ECEFPosition  GeoEllipsoid::position(const Geodetic3RM& geo) const 
    {
        
        // TODO
        return {};
    }

    ECEFPosition  GeoEllipsoid::position(const Geodetic2R& geo) const 
    {
        // TODO
        return {};
    }

    ECEFPosition  GeoEllipsoid::position(const Geodetic2R& geo, unit::Meter z) const 
    {
        // TODO
        return {};
    }

    unit::Meter  GeoEllipsoid::radius(const Geodetic2R& geo) const
    {
        // TODO
        return {};
    }

    unit::Meter  GeoEllipsoid::radius(const Geodetic2R& geo, unit::Meter z) const
    {
        // TODO
        return {};
    }

    unit::Meter  GeoEllipsoid::radius(const Geodetic3RM& geo) const
    {
        // TODO
        return {};
    }

    unit::Meter  GeoEllipsoid::radius(const ECEFPosition& ecef) const
    {
        // TODO
        return {};
    }
    
    ECEFVector  GeoEllipsoid::south(const Geodetic2R& geo) const
    {
        // TODO
        return {};
    }

    ECEFVector  GeoEllipsoid::south(const Geodetic2R& geo, unit::Meter z) const
    {
        // TODO
        return {};
    }

    ECEFVector  GeoEllipsoid::south(const Geodetic3RM& geo) const
    {
        // TODO
        return {};
    }

    ECEFVector  GeoEllipsoid::south(const ECEFPosition& ecef) const
    {
        // TODO
        return {};
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
    
    ECEFVector  GeoEllipsoid::west(const Geodetic2R& geo) const
    {
        // TODO
        return {};
    }

    ECEFVector  GeoEllipsoid::west(const Geodetic2R& geo, unit::Meter z) const
    {
        // TODO
        return {};
    }

    ECEFVector  GeoEllipsoid::west(const Geodetic3RM& geo) const
    {
        // TODO
        return {};
    }

    ECEFVector  GeoEllipsoid::west(const ECEFPosition& ecef) const
    {
        // TODO
        return {};
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
        return {};
    }
    
    unit::Meter     GeoEllipsoidConfig::radius_by_volume() const
    {
        return {};
    }

    unit::Meter     GeoEllipsoidConfig::semiminor() const
    {
        return semimajor * (1-flattening);
    }
    
    unit::Meter²    GeoEllipsoidConfig::surface_area() const
    {
        return {};
    }

    unit::Meter³    GeoEllipsoidConfig::volume() const
    {
        // semimajor*semimajor*semimajor *(1.-flattening);
        return {};
    }
    

}
