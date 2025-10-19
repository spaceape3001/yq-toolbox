////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/earth/model/GeoModel.hpp>

namespace yq {
    struct GeoSpheroidConfig {
        unit::MeterPerSecond²   gravity = 1_G;
        std::string             name    = "Spheroid";
        unit::Meter             radius  = 6378137.0_m;
    };
    
    class GeoSpheroid : public GeoModel {
        YQ_OBJECT_DECLARE(GeoSpheroid, GeoModel)
    public:
        GeoSpheroid(const GeoSpheroidConfig& options = {});
        ~GeoSpheroid();
        
        virtual unit::Meter                 altitude(const ECEFPosition&) const override;

        ECEFVector                          down(unit::Radian, unit::Radian) const;
        virtual ECEFVector                  down(const Geodetic2R&) const override;
        virtual ECEFVector                  down(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  down(const Geodetic3RM&) const override;
        virtual ECEFVector                  down(const ECEFPosition&) const override;

        ECEFVector                          east(unit::Radian, unit::Radian) const;
        virtual ECEFVector                  east(const Geodetic2R&) const override;
        virtual ECEFVector                  east(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  east(const Geodetic3RM&) const override;
        virtual ECEFVector                  east(const ECEFPosition&) const override;

        virtual Geodetic3RM                 geodetic(const ECEFPosition&) const override;
        virtual Geodetic2R                  geodetic2(const ECEFPosition&) const override;

        unit::MeterPerSecond²               gravity(unit::Meter) const;
        virtual unit::MeterPerSecond²       gravity(const Geodetic2R&) const override;
        virtual unit::MeterPerSecond²       gravity(const Geodetic2R&, unit::Meter) const override;
        virtual unit::MeterPerSecond²       gravity(const Geodetic3RM&) const override;
        virtual unit::MeterPerSecond²       gravity(const ECEFPosition&) const override;
        virtual ECEFAcceleration            gravity(vector_k, const Geodetic2R&) const override;
        virtual ECEFAcceleration            gravity(vector_k, const Geodetic2R&, unit::Meter) const override;
        virtual ECEFAcceleration            gravity(vector_k, const Geodetic3RM&) const override;
        virtual ECEFAcceleration            gravity(vector_k, const ECEFPosition&) const override;

        ECEFVector                          north(unit::Radian, unit::Radian) const;
        virtual ECEFVector                  north(const Geodetic2R&) const override;
        virtual ECEFVector                  north(const Geodetic2R&, Meter) const override;
        virtual ECEFVector                  north(const Geodetic3RM&) const override;
        virtual ECEFVector                  north(const ECEFPosition&) const override;

        Quaternion3D                        orientation(quaternion_k, enu_k, unit::Radian, unit::Radian) const;
        virtual Quaternion3D                orientation(quaternion_k, enu_k, const Geodetic2R&) const override;
        virtual Quaternion3D                orientation(quaternion_k, enu_k, const Geodetic2R&, unit::Meter) const override;
        virtual Quaternion3D                orientation(quaternion_k, enu_k, const Geodetic3RM&) const override;
        virtual Quaternion3D                orientation(quaternion_k, enu_k, const ECEFPosition&) const override;

        Quaternion3D                        orientation(quaternion_k, ned_k, unit::Radian, unit::Radian) const;
        virtual Quaternion3D                orientation(quaternion_k, ned_k, const Geodetic2R&) const override;
        virtual Quaternion3D                orientation(quaternion_k, ned_k, const Geodetic2R&, unit::Meter) const override;
        virtual Quaternion3D                orientation(quaternion_k, ned_k, const Geodetic3RM&) const override;
        virtual Quaternion3D                orientation(quaternion_k, ned_k, const ECEFPosition&) const override;
    
        Tensor33D                           orientation(tensor_k, enu_k, unit::Radian, unit::Radian) const;
        virtual Tensor33D                   orientation(tensor_k, enu_k, const Geodetic2R&) const override;
        virtual Tensor33D                   orientation(tensor_k, enu_k, const Geodetic2R&, unit::Meter) const override;
        virtual Tensor33D                   orientation(tensor_k, enu_k, const Geodetic3RM&) const override;
        virtual Tensor33D                   orientation(tensor_k, enu_k, const ECEFPosition&) const override;

        Tensor33D                           orientation(tensor_k, ned_k, unit::Radian, unit::Radian) const;
        virtual Tensor33D                   orientation(tensor_k, ned_k, const Geodetic2R&) const override;
        virtual Tensor33D                   orientation(tensor_k, ned_k, const Geodetic2R&, unit::Meter) const override;
        virtual Tensor33D                   orientation(tensor_k, ned_k, const Geodetic3RM&) const override;
        virtual Tensor33D                   orientation(tensor_k, ned_k, const ECEFPosition&) const override;

        virtual ECEFPosition                position(const Geodetic3RM&) const override;
        virtual ECEFPosition                position(const Geodetic2R&) const override;
        virtual ECEFPosition                position(const Geodetic2R&, unit::Meter) const override;

        virtual unit::Meter                 radius(const Geodetic2R&) const override;
        virtual unit::Meter                 radius(const Geodetic2R&, unit::Meter) const override;
        virtual unit::Meter                 radius(const Geodetic3RM&) const override;
        virtual unit::Meter                 radius(const ECEFPosition&) const override;
        
        ECEFVector                          south(unit::Radian, unit::Radian) const;
        virtual ECEFVector                  south(const Geodetic2R&) const override;
        virtual ECEFVector                  south(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  south(const Geodetic3RM&) const override;
        virtual ECEFVector                  south(const ECEFPosition&) const override;

        ECEFVector                          up(unit::Radian, unit::Radian) const;
        virtual ECEFVector                  up(const Geodetic2R&) const override;
        virtual ECEFVector                  up(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  up(const Geodetic3RM&) const override;
        virtual ECEFVector                  up(const ECEFPosition&) const override;
        
        ECEFVector                          west(unit::Radian, unit::Radian) const;
        virtual ECEFVector                  west(const Geodetic2R&) const override;
        virtual ECEFVector                  west(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  west(const Geodetic3RM&) const override;
        virtual ECEFVector                  west(const ECEFPosition&) const override;

        static void init_meta();
        
    private:
        unit::MeterPerSecond²               m_gravity;
        unit::Meter                         m_radius;
        unit::Meter²                        m_radius²;
    };
}
