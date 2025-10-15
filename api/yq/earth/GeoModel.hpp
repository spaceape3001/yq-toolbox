////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/units.hpp>
#include <yq/core/Object.hpp>
#include <yq/typedef/ecef.hpp>
#include <yq/typedef/geodetic2.hpp>
#include <yq/typedef/geodetic3.hpp>

namespace yq {

#if 0
    class GeoEllipsoid {
    };
    
    class GeoSpheroid {
    public:
    
    
    };
    
    class GeoFlatNED {
    };
    
    class GeoFlatENU {
    };
    
    class GeoGeoid {
    };
    
    //  And somewhere... want... something like
    //! Standard WGS84
    const Globe&  wgs84();

    //! Standard EGM96 Geoid
    // static const Globe&  egm96();
    
#endif


    /*! \brief Geodetic Model (ie, a planet, moon, etc)
    */
    class GeoModel : public Object {
        YQ_OBJECT_DECLARE(GeoModel, Object)
    public:

        //! Altitude of the given position
        virtual Meter                       altitude(const ECEFPosition&) const;

        virtual ECEFVector                  down(const Geodetic2R&) const;
        virtual ECEFVector                  down(const Geodetic2R&, unit::Meter) const;
        virtual ECEFVector                  down(const Geodetic3RM&) const;
        virtual ECEFVector                  down(const ECEFPosition&) const;

        virtual ECEFVector                  east(const Geodetic2R&) const;
        virtual ECEFVector                  east(const Geodetic2R&, unit::Meter) const;
        virtual ECEFVector                  east(const Geodetic3RM&) const;
        virtual ECEFVector                  east(const ECEFPosition&) const;

        //! Geodetic from a position 
        //! \note Mandatory override (no default) as this is the planet's basic shape
        virtual Geodetic3RM                 geodetic(const ECEFPosition&) const = 0;
        
        //! 2D Geodetic from a position 
        virtual Geodetic2R                  geodetic2(const ECEFPosition&) const;

        //! Gravity at location
        virtual unit::MeterPerSecond²       gravity(const Geodetic2R&) const;

        //! Gravity at location/altitude
        virtual unit::MeterPerSecond²       gravity(const Geodetic2R&, unit::Meter) const;
        
        //! Gravity at location
        //! \note This is considered the primary, the other defaults use this
        virtual unit::MeterPerSecond²       gravity(const Geodetic3RM&) const;
        
        //! Gravity at location
        virtual unit::MeterPerSecond²       gravity(const ECEFPosition&) const;

        //! Default/default is 1G (down)
        virtual ECEFAcceleration            gravity(vector_k, const Geodetic2R&) const;

        //! Default/default is 1G (down)
        virtual ECEFAcceleration            gravity(vector_k, const Geodetic2R&, unit::Meter) const;

        //! Default/default is 1G (down)
        virtual ECEFAcceleration            gravity(vector_k, const Geodetic3RM&) const;

        //! Default/default is 1G (down)
        virtual ECEFAcceleration            gravity(vector_k, const ECEFPosition&) const;
        
        const std::string&                  name() const { return m_name; }
        void                                name(set_k, std::string_view);

        virtual ECEFVector                  north(const Geodetic2R&) const;
        virtual ECEFVector                  north(const Geodetic2R&, Meter) const;
        virtual ECEFVector                  north(const Geodetic3RM&) const;
        virtual ECEFVector                  north(const ECEFPosition&) const;
        
        //! Rotation quaternion for a reference frame to ECEF
        virtual Quaternion3D                orientation(quaternion_k, enu_k, const Geodetic2R&) const;
        virtual Quaternion3D                orientation(quaternion_k, enu_k, const Geodetic2R&, unit::Meter) const;
        virtual Quaternion3D                orientation(quaternion_k, enu_k, const Geodetic3RM&) const;
        virtual Quaternion3D                orientation(quaternion_k, enu_k, const ECEFPosition&) const;

        virtual Quaternion3D                orientation(quaternion_k, ned_k, const Geodetic3RM&) const;
        virtual Quaternion3D                orientation(quaternion_k, ned_k, const Geodetic2R&) const;
        virtual Quaternion3D                orientation(quaternion_k, ned_k, const Geodetic2R&, unit::Meter) const;
        virtual Quaternion3D                orientation(quaternion_k, ned_k, const ECEFPosition&) const;
    
        virtual Tensor33D                   orientation(tensor_k, enu_k, const Geodetic2R&) const;
        virtual Tensor33D                   orientation(tensor_k, enu_k, const Geodetic2R&, unit::Meter) const;
        virtual Tensor33D                   orientation(tensor_k, enu_k, const Geodetic3RM&) const;
        virtual Tensor33D                   orientation(tensor_k, enu_k, const ECEFPosition&) const;

        virtual Tensor33D                   orientation(tensor_k, ned_k, const Geodetic2R&) const;
        virtual Tensor33D                   orientation(tensor_k, ned_k, const Geodetic2R&, unit::Meter) const;
        virtual Tensor33D                   orientation(tensor_k, ned_k, const Geodetic3RM&) const;
        virtual Tensor33D                   orientation(tensor_k, ned_k, const ECEFPosition&) const;

        //! Position from a geodetic
        //! \note Mandatory override (no default) as this is the planet's basic shape
        virtual ECEFPosition                position(const Geodetic3RM&) const = 0;

        //! Postition from a 2D geodetic
        virtual ECEFPosition                position(const Geodetic2R&) const;

        //! Postition from a 2D geodetic & altitude
        virtual ECEFPosition                position(const Geodetic2R&, unit::Meter) const;

        virtual Meter                       radius(const Geodetic2R&) const;
        virtual Meter                       radius(const Geodetic2R&, unit::Meter) const;
        virtual Meter                       radius(const Geodetic3RM&) const;
        virtual Meter                       radius(const ECEFPosition&) const;
        
        virtual ECEFVector                  south(const Geodetic2R&) const;
        virtual ECEFVector                  south(const Geodetic2R&, unit::Meter) const;
        virtual ECEFVector                  south(const Geodetic3RM&) const;
        virtual ECEFVector                  south(const ECEFPosition&) const;

        virtual ECEFVector                  up(const Geodetic2R&) const;
        virtual ECEFVector                  up(const Geodetic2R&, unit::Meter) const;
        virtual ECEFVector                  up(const Geodetic3RM&) const;
        virtual ECEFVector                  up(const ECEFPosition&) const;
        
        virtual ECEFVector                  west(const Geodetic2R&) const;
        virtual ECEFVector                  west(const Geodetic2R&, unit::Meter) const;
        virtual ECEFVector                  west(const Geodetic3RM&) const;
        virtual ECEFVector                  west(const ECEFPosition&) const;
        
        
        static void init_meta();
        
    protected:
        GeoModel();
        ~GeoModel();
        
    private:
        std::string             m_name;
    };
}
