////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GeoModel.hpp"
#include <yq/meta/ObjectMetaWriter.hpp>
#include <yq/coord/Geodetic2.hpp>
#include <yq/coord/Geodetic3.hpp>
#include <yq/coord/ecef/ECEFOrientation.hpp>
#include <yq/coord/ecef/ECEFPosition.hpp>
#include <yq/coord/ecef/ECEFTensor.hpp>
#include <yq/coord/ecef/ECEFVector.hpp>

#include <yq/vector/Quaternion3.hxx>
#include <yq/vector/Vector3.hxx>

YQ_OBJECT_IMPLEMENT(yq::GeoModel)

namespace yq {
    void GeoModel::init_meta()
    {
        auto w = writer<GeoModel>();
        w.description("Geodetic Coordinate Model");
        w.property("name", &GeoModel::m_name);
    }
        
    GeoModel::GeoModel()
    {
    }
    
    GeoModel::~GeoModel()
    {
    }


    Meter                       GeoModel::altitude(const ECEFPosition& ecef) const
    {
        return geodetic(ecef).altitude;
    }

    ECEFVector                  GeoModel::down(const Geodetic2R& geo) const
    {
        return down(Geodetic3RM{geo.latitude, geo.longitude, 0._m});
    }
    
    ECEFVector                  GeoModel::down(const Geodetic2R& geo, unit::Meter z) const
    {
        return down(Geodetic3RM{geo.latitude, geo.longitude, z});
    }
    
    ECEFVector                  GeoModel::down(const Geodetic3RM& geo) const
    {
        return ECEFVector(-up(geo));
    }

    ECEFVector                  GeoModel::down(const ECEFPosition& ecef) const
    {
        return down(geodetic(ecef));
    }

    ECEFVector                  GeoModel::east(const Geodetic2R& geo) const
    {
        return east(Geodetic3RM{geo.latitude, geo.longitude, 0._m});
    }
    
    ECEFVector                  GeoModel::east(const Geodetic2R&geo, unit::Meter z) const
    {
        return east(Geodetic3RM{geo.latitude, geo.longitude, z});
    }

    ECEFVector                  GeoModel::east(const Geodetic3RM&geo) const
    {
        Vector3M    delta   = position(Geodetic3RM{ geo.latitude, geo.longitude+1e-5_rad, geo.altitude}) - position(geo);
        // TODO
        return {};
    }

    ECEFVector                  GeoModel::east(const ECEFPosition&ecef) const
    {
        return east(geodetic(ecef));
    }

    Geodetic2R                  GeoModel::geodetic2(const ECEFPosition& ecef) const
    {
        Geodetic3RM geo = geodetic(ecef);
        return { geo.latitude, geo.longitude };
    }

    unit::MeterPerSecond²       GeoModel::gravity(const Geodetic2R& geo) const
    {
        return gravity(Geodetic3RM{ geo.latitude, geo.longitude, 0._m});
    }

    unit::MeterPerSecond²       GeoModel::gravity(const Geodetic2R& geo, unit::Meter z) const
    {
        return gravity(Geodetic3RM{ geo.latitude, geo.longitude, z});
    }

    unit::MeterPerSecond²       GeoModel::gravity(const Geodetic3RM& geo) const
    {
        return 1_G;
    }

    unit::MeterPerSecond²       GeoModel::gravity(const ECEFPosition& ecef) const
    {
        return gravity(geodetic(ecef));
    }

    ECEFAcceleration            GeoModel::gravity(vector_k, const Geodetic2R& geo) const
    {
        return gravity(VECTOR, Geodetic3RM{ geo.latitude, geo.longitude, 0._m});
    }

    ECEFAcceleration            GeoModel::gravity(vector_k, const Geodetic2R& geo, unit::Meter z) const
    {
        return gravity(VECTOR, Geodetic3RM{ geo.latitude, geo.longitude, z});
    }

    ECEFAcceleration            GeoModel::gravity(vector_k, const Geodetic3RM& geo) const
    {
        return ECEFAcceleration( gravity(geo) * down(geo) );
    }

    ECEFAcceleration            GeoModel::gravity(vector_k, const ECEFPosition& ecef) const
    {
        return gravity(VECTOR, geodetic(ecef));
    }

    void                        GeoModel::name(set_k, std::string_view k)
    {
        m_name  = k;
    }

    ECEFVector                  GeoModel::north(const Geodetic2R& geo) const
    {
        return north(Geodetic3RM{geo.latitude, geo.longitude, 0._m});
    }

    ECEFVector                  GeoModel::north(const Geodetic2R& geo, Meter z) const
    {
        return north(Geodetic3RM{geo.latitude, geo.longitude, z});
    }

    ECEFVector                  GeoModel::north(const Geodetic3RM& geo) const
    {
        Vector3M    delta   = position(Geodetic3RM{ geo.latitude+1e-5_rad, geo.longitude, geo.altitude}) - position(geo);
        // TODO
        return {};
    }

    ECEFVector                  GeoModel::north(const ECEFPosition& ecef) const
    {
        return north(geodetic(ecef));
    }

    Quaternion3D                GeoModel::orientation(quaternion_k, enu_k, const Geodetic2R& geo) const
    {
        return orientation(QUAT, ENU, Geodetic3RM{geo.latitude, geo.longitude, 0._m});
    }

    Quaternion3D                GeoModel::orientation(quaternion_k, enu_k, const Geodetic2R& geo, unit::Meter z) const
    {
        return orientation(QUAT, ENU, Geodetic3RM{geo.latitude, geo.longitude, z});
    }

    Quaternion3D                GeoModel::orientation(quaternion_k, enu_k, const Geodetic3RM& geo) const
    {
        return quaternion(orientation(TENSOR, ENU, geo));
    }

    Quaternion3D                GeoModel::orientation(quaternion_k, enu_k, const ECEFPosition&ecef) const
    {
        return orientation(QUAT, ENU, geodetic(ecef));
    }

    Quaternion3D                GeoModel::orientation(quaternion_k, ned_k, const Geodetic2R&geo) const
    {
        return orientation(QUAT, NED, Geodetic3RM{geo.latitude, geo.longitude, 0._m});
    }

    Quaternion3D                GeoModel::orientation(quaternion_k, ned_k, const Geodetic2R&geo, unit::Meter z) const
    {
        return orientation(QUAT, NED, Geodetic3RM{geo.latitude, geo.longitude, z});
    }

    Quaternion3D                GeoModel::orientation(quaternion_k, ned_k, const Geodetic3RM& geo) const
    {
        return quaternion(orientation(TENSOR, NED, geo));
    }

    Quaternion3D                GeoModel::orientation(quaternion_k, ned_k, const ECEFPosition& ecef) const
    {
        return orientation(QUAT, NED, geodetic(ecef));
    }

    Tensor33D                   GeoModel::orientation(tensor_k, enu_k, const Geodetic2R& geo) const
    {
        return orientation(TENSOR, ENU, Geodetic3RM{geo.latitude, geo.longitude, 0._m});
    }

    Tensor33D                   GeoModel::orientation(tensor_k, enu_k, const Geodetic2R&geo, unit::Meter z) const
    {
        return orientation(TENSOR, ENU, Geodetic3RM{geo.latitude, geo.longitude, z});
    }

    Tensor33D                   GeoModel::orientation(tensor_k, enu_k, const Geodetic3RM& geo) const
    {
        return rows(east(geo), north(geo), up(geo));
    }

    Tensor33D                   GeoModel::orientation(tensor_k, enu_k, const ECEFPosition& ecef) const
    {
        return orientation(TENSOR, ENU, geodetic(ecef));
    }

    Tensor33D                   GeoModel::orientation(tensor_k, ned_k, const Geodetic2R&geo) const
    {
        return orientation(TENSOR, NED, Geodetic3RM{geo.latitude, geo.longitude, 0._m});
    }

    Tensor33D                   GeoModel::orientation(tensor_k, ned_k, const Geodetic2R&geo, unit::Meter z) const
    {
        return orientation(TENSOR, NED, Geodetic3RM{geo.latitude, geo.longitude, z});
    }

    Tensor33D                   GeoModel::orientation(tensor_k, ned_k, const Geodetic3RM& geo) const
    {
        return rows(north(geo), east(geo), down(geo));
    }

    Tensor33D                   GeoModel::orientation(tensor_k, ned_k, const ECEFPosition&ecef) const
    {
        return orientation(TENSOR, NED, geodetic(ecef));
    }

    ECEFPosition                GeoModel::position(const Geodetic2R& geo) const
    {
        return position(Geodetic3RM{ geo.latitude, geo.longitude, 0._m });
    }

    ECEFPosition                GeoModel::position(const Geodetic2R& geo, unit::Meter z) const
    {
        return position(Geodetic3RM{ geo.latitude, geo.longitude, z });
    }

    Meter                       GeoModel::radius(const Geodetic2R& geo) const
    {
        return radius(Geodetic3RM{geo.latitude, geo.longitude, 0._m});
    }

    Meter                       GeoModel::radius(const Geodetic2R& geo, unit::Meter z) const
    {
        return radius(Geodetic3RM{ geo.latitude, geo.longitude, z });
    }

    Meter                       GeoModel::radius(const Geodetic3RM& geo) const
    {
        return position(geo).length();
    }

    Meter                       GeoModel::radius(const ECEFPosition& ecef) const
    {
        return radius(geodetic(ecef));
    }


    ECEFVector                  GeoModel::south(const Geodetic2R& geo) const
    {
        return south(Geodetic3RM{geo.latitude, geo.longitude, 0._m});
    }

    ECEFVector                  GeoModel::south(const Geodetic2R&geo, unit::Meter z) const
    {
        return south(Geodetic3RM{geo.latitude, geo.longitude, z});
    }

    ECEFVector                  GeoModel::south(const Geodetic3RM& geo) const
    {
        return ECEFVector(-north(geo));
    }

    ECEFVector                  GeoModel::south(const ECEFPosition& ecef) const
    {
        return south(geodetic(ecef));
    }


    ECEFVector                  GeoModel::up(const Geodetic2R& geo) const
    {
        return up(Geodetic3RM{geo.latitude, geo.longitude, 0._m});
    }

    ECEFVector                  GeoModel::up(const Geodetic2R& geo, unit::Meter z) const
    {
        return up(Geodetic3RM{geo.latitude, geo.longitude, z});
    }

    ECEFVector                  GeoModel::up(const Geodetic3RM&geo) const
    {
        Vector3M    delta   = position(Geodetic3RM{ geo.latitude, geo.longitude, geo.altitude+1._m}) - position(geo);
        // TODO
        return {};
    }

    ECEFVector                  GeoModel::up(const ECEFPosition&ecef) const
    {
        return up(geodetic(ecef));
    }

    ECEFVector                  GeoModel::west(const Geodetic2R& geo) const
    {
        return west(Geodetic3RM{ geo.latitude, geo.longitude, 0.});
    }

    ECEFVector                  GeoModel::west(const Geodetic2R& geo, unit::Meter z) const
    {
        return west(Geodetic3RM{ geo.latitude, geo.longitude, z});
    }

    ECEFVector                  GeoModel::west(const Geodetic3RM& geo) const
    {
        return ECEFVector(-east(geo));
    }

    ECEFVector                  GeoModel::west(const ECEFPosition& ecef) const
    {
        return west(geodetic(ecef));
    }
}
