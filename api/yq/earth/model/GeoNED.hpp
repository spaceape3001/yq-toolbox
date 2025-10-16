////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/earth/model/GeoModel.hpp>
#include <yq/coord/Geodetic2.hpp>

namespace yq {
    struct GeoNEDConfig {
        Geodetic2R              center  = {};
        unit::MeterPerSecond²   gravity = 1_G;
        std::string             name    = "NED";
        unit::Meter             radius  = 6378137.0_m;
    };
    
    class GeoNED : public GeoModel {
        YQ_OBJECT_DECLARE(GeoNED, GeoModel)
    public:
        GeoNED(const GeoNEDConfig& cfg = {});
        ~GeoNED();

        virtual Meter                       altitude(const ECEFPosition&) const override;
        virtual ECEFVector                  down(const Geodetic2R&) const override;
        virtual ECEFVector                  down(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  down(const Geodetic3RM&) const override;
        virtual ECEFVector                  down(const ECEFPosition&) const override;
        virtual ECEFVector                  east(const Geodetic2R&) const override;
        virtual ECEFVector                  east(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  east(const Geodetic3RM&) const override;
        virtual ECEFVector                  east(const ECEFPosition&) const override;
        virtual Geodetic3RM                 geodetic(const ECEFPosition&) const override;
        virtual Geodetic2R                  geodetic2(const ECEFPosition&) const override;

        virtual unit::MeterPerSecond²       gravity(const Geodetic2R&) const override;
        virtual unit::MeterPerSecond²       gravity(const Geodetic2R&, unit::Meter) const override;
        virtual unit::MeterPerSecond²       gravity(const Geodetic3RM&) const override;
        virtual unit::MeterPerSecond²       gravity(const ECEFPosition&) const override;

        virtual ECEFAcceleration            gravity(vector_k, const Geodetic2R&) const override;
        virtual ECEFAcceleration            gravity(vector_k, const Geodetic2R&, unit::Meter) const override;
        virtual ECEFAcceleration            gravity(vector_k, const Geodetic3RM&) const override;
        virtual ECEFAcceleration            gravity(vector_k, const ECEFPosition&) const override;

        virtual ECEFVector                  north(const Geodetic2R&) const override;
        virtual ECEFVector                  north(const Geodetic2R&, Meter) const override;
        virtual ECEFVector                  north(const Geodetic3RM&) const override;
        virtual ECEFVector                  north(const ECEFPosition&) const override;

        virtual Quaternion3D                orientation(quaternion_k, enu_k, const Geodetic2R&) const override;
        virtual Quaternion3D                orientation(quaternion_k, enu_k, const Geodetic2R&, unit::Meter) const override;
        virtual Quaternion3D                orientation(quaternion_k, enu_k, const Geodetic3RM&) const override;
        virtual Quaternion3D                orientation(quaternion_k, enu_k, const ECEFPosition&) const override;

        virtual Quaternion3D                orientation(quaternion_k, ned_k, const Geodetic3RM&) const override;
        virtual Quaternion3D                orientation(quaternion_k, ned_k, const Geodetic2R&) const override;
        virtual Quaternion3D                orientation(quaternion_k, ned_k, const Geodetic2R&, unit::Meter) const override;
        virtual Quaternion3D                orientation(quaternion_k, ned_k, const ECEFPosition&) const override;
    
        virtual Tensor33D                   orientation(tensor_k, enu_k, const Geodetic2R&) const override;
        virtual Tensor33D                   orientation(tensor_k, enu_k, const Geodetic2R&, unit::Meter) const override;
        virtual Tensor33D                   orientation(tensor_k, enu_k, const Geodetic3RM&) const override;
        virtual Tensor33D                   orientation(tensor_k, enu_k, const ECEFPosition&) const override;

        virtual Tensor33D                   orientation(tensor_k, ned_k, const Geodetic2R&) const override;
        virtual Tensor33D                   orientation(tensor_k, ned_k, const Geodetic2R&, unit::Meter) const override;
        virtual Tensor33D                   orientation(tensor_k, ned_k, const Geodetic3RM&) const override;
        virtual Tensor33D                   orientation(tensor_k, ned_k, const ECEFPosition&) const override;
    
        virtual ECEFPosition                position(const Geodetic3RM&) const override;
        virtual ECEFPosition                position(const Geodetic2R&) const override;
        virtual ECEFPosition                position(const Geodetic2R&, unit::Meter) const override;

        virtual Meter                       radius(const Geodetic2R&) const override;
        virtual Meter                       radius(const Geodetic2R&, unit::Meter) const override;
        virtual Meter                       radius(const Geodetic3RM&) const override;
        virtual Meter                       radius(const ECEFPosition&) const override;
        
        virtual ECEFVector                  south(const Geodetic2R&) const override;
        virtual ECEFVector                  south(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  south(const Geodetic3RM&) const override;
        virtual ECEFVector                  south(const ECEFPosition&) const override;

        virtual ECEFVector                  up(const Geodetic2R&) const override;
        virtual ECEFVector                  up(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  up(const Geodetic3RM&) const override;
        virtual ECEFVector                  up(const ECEFPosition&) const override;
        
        virtual ECEFVector                  west(const Geodetic2R&) const override;
        virtual ECEFVector                  west(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  west(const Geodetic3RM&) const override;
        virtual ECEFVector                  west(const ECEFPosition&) const override;

        static void init_meta();

    private:
        Geodetic2R                          m_center;
        unit::MeterPerSecond²               m_gravity;
        unit::Meter                         m_radius;
        Geodetic2<unit::MeterPerRadian>     m_curvature;
        Geodetic2<unit::RadianPerMeter>     m_iCurvature;
    };
}
