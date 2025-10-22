////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/earth/model/GeoModel.hpp>

namespace yq {
    struct GeoEllipsoidConfig {
        std::string                     name;
        unit::Meter                     semimajor{};
        double                          flattening{};
        unit::RadianPerSecond           ω{};                //!< Spin parameter 4
        
        unit::Meter³PerSecond²          μ{};
        unit::MeterPerSecond²           ge{};               //!< equitorial gravity
        unit::Meter³PerSecond²          gp{};               //!< polar gravity
      
        double          eccentricity() const;
        unit::Meter     focus() const;
        unit::Meter     radius_by_area() const;
        unit::Meter     radius_by_volume() const;
        unit::Meter     semiminor() const;
        unit::Meter²    surface_area() const;
        unit::Meter³    volume() const;
    };
    
    class GeoEllipsoid : public GeoModel {
        YQ_OBJECT_DECLARE(GeoEllipsoid, GeoModel)
    public:
        GeoEllipsoid(const GeoEllipsoidConfig& options = {});
        ~GeoEllipsoid();
        
        virtual unit::Meter                 altitude(const ECEFPosition&) const override;

        ECEFVector                          down(unit::Radian, unit::Radian) const;
        virtual ECEFVector                  down(const Geodetic2R&) const override;
        virtual ECEFVector                  down(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  down(const Geodetic3RM&) const override;
        virtual ECEFVector                  down(const ECEFPosition&) const override;

        ECEFVector                          east(unit::Radian) const;
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

        virtual Quaternion3D                orientation(quaternion_k, ned_k, const Geodetic2R&) const override;
        virtual Quaternion3D                orientation(quaternion_k, ned_k, const Geodetic2R&, unit::Meter) const override;
        virtual Quaternion3D                orientation(quaternion_k, ned_k, const Geodetic3RM&) const override;
        virtual Quaternion3D                orientation(quaternion_k, ned_k, const ECEFPosition&) const override;
    
        virtual Tensor33D                   orientation(tensor_k, enu_k, const Geodetic2R&) const override;
        virtual Tensor33D                   orientation(tensor_k, enu_k, const Geodetic2R&, unit::Meter) const override;
        virtual Tensor33D                   orientation(tensor_k, enu_k, const Geodetic3RM&) const override;
        virtual Tensor33D                   orientation(tensor_k, enu_k, const ECEFPosition&) const override;

        virtual Tensor33D                   orientation(tensor_k, ned_k, const Geodetic2R&) const override;
        virtual Tensor33D                   orientation(tensor_k, ned_k, const Geodetic2R&, unit::Meter) const override;
        virtual Tensor33D                   orientation(tensor_k, ned_k, const Geodetic3RM&) const override;
        virtual Tensor33D                   orientation(tensor_k, ned_k, const ECEFPosition&) const override;

        ECEFPosition                        position(unit::Radian, unit::Radian, unit::Meter) const;
        virtual ECEFPosition                position(const Geodetic3RM&) const override;
        virtual ECEFPosition                position(const Geodetic2R&) const override;
        virtual ECEFPosition                position(const Geodetic2R&, unit::Meter) const override;

        virtual unit::Meter                 radius(const Geodetic2R&) const override;
        virtual unit::Meter                 radius(const Geodetic2R&, unit::Meter) const override;
        virtual unit::Meter                 radius(const Geodetic3RM&) const override;
        virtual unit::Meter                 radius(const ECEFPosition&) const override;
        
        virtual ECEFVector                  south(const Geodetic2R&) const override;
        virtual ECEFVector                  south(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  south(const Geodetic3RM&) const override;
        virtual ECEFVector                  south(const ECEFPosition&) const override;

        ECEFVector                          up(unit::Radian, unit::Radian) const;
        virtual ECEFVector                  up(const Geodetic2R&) const override;
        virtual ECEFVector                  up(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  up(const Geodetic3RM&) const override;
        virtual ECEFVector                  up(const ECEFPosition&) const override;
        
        ECEFVector                          west(unit::Radian) const;
        virtual ECEFVector                  west(const Geodetic2R&) const override;
        virtual ECEFVector                  west(const Geodetic2R&, unit::Meter) const override;
        virtual ECEFVector                  west(const Geodetic3RM&) const override;
        virtual ECEFVector                  west(const ECEFPosition&) const override;

        static void init_meta();
        
        const double                        eccentricity;       //!< Eccentricity
        const double                        flattening;         //!< Flattening factor
        const unit::Meter                   focus;              //!< Focus
        const unit::Meter                   radius_by_area;     //!< Mean radius using area
        const unit::Meter                   radius_by_volume;   //!< Mean radius using volume
        const unit::Meter                   semimajor;          //!< Semi major axis
        const unit::Meter                   semiminor;          //!< Semi minor axis
        const unit::Meter²                  surface_area;       //!< Surface area
        const unit::Meter³                  volume;             //!< Volume
        
    private:
        
        struct Param {
            double a;
            double a²;
            double a²b²;
            double a²_div_b²;   // a²÷b²
            double a_div_b;
            double b;
            double b²;
            double c;
            double c²;
            double e;
            double e²;
            double f;
            double ne2m1;   // 1-e²
            double e²a;
            double e²c;
            double e²cb;
            double k;
            double maxG;
            double hc1a;
            double hc1b;
            double hc²;
        };
        
        const Param           m_param;
    
        static Param compute_parameters(const GeoEllipsoidConfig&);
    };
}
