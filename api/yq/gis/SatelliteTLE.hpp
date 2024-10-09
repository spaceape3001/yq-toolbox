////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/units.hpp>

namespace yq {
    struct SatelliteTLE {
        std::string     name;
        uint32_t        catalog                 = 0;
        char            classification          = ' ';
        uint8_t         launchYear              = 0;
        uint16_t        launchNumber            = 0;
        std::string     launchDesignator;
        uint8_t         epochYear               = 0;
        unit::Day       epochDay                = ZERO;
        double          firstDerivMeanMotion    = 0.;
        double          secondDerivMeanMotion   = 0.;
        double          Bstar                   = 0.;
        uint8_t         ephemerisType           = 0;
        uint16_t        elementSetNumber        = 0;
        unit::Degree    inclination             = ZERO;
        unit::Degree    rightAscension          = ZERO; 
        double          eccentricity            = 0.;
        unit::Degree    argPerigee              = ZERO;
        unit::Degree    meanAnomaly             = ZERO;
        double          meanMotion              = 0.;
        uint32_t        revolutionAtEpoch       = 0;
        
        static Expect<SatelliteTLE>  parse( std::string_view line0, std::string_view line1, std::string_view line2);
        static Expect<SatelliteTLE>  parse( std::string_view line1, std::string_view line2);
        
        static bool     verify_checksum(std::string_view line);
    };
}
