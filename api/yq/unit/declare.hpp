////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/unit/dims.hpp>

namespace yq {

    template <typename> struct Tensor33;
    template <typename> struct Vector3;

    namespace def {
        static constexpr const long double   long_pi     = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862;
        static constexpr const long double   degree      = long_pi / 180.0;
        static constexpr const long double   degree²     = degree * degree;
        static constexpr const long double   gradian     = long_pi / 200.0;
        static constexpr const long double   foot        = 0.3048;
        static constexpr const long double   foot²       = foot * foot;
        static constexpr const long double   foot³       = foot² * foot;
        static constexpr const long double   inch        = 0.0254;
        static constexpr const long double   inch²       = inch * inch;
        static constexpr const long double   inch³       = inch² * inch;
        static constexpr const long double   gram        = 0.001;
        static constexpr const long double   lbf         = 4.4482216152605;
        static constexpr const long double   mile        = 1609.344;
        static constexpr const long double   furlong     = mile / 8.0;
        static constexpr const long double   minute      = 60.;
        static constexpr const long double   nmi         = 1852.0;
        static constexpr const long double   hour        = 60.*minute;
        static constexpr const long double   day         = 24.*hour;
        static constexpr const long double   jyear       = 365.25 * day;
        static constexpr const long double   week        = 7.*day;
        static constexpr const long double   fortnight   = 2. * week;
        static constexpr const long double   arcminute   = degree / 60.;
        static constexpr const long double   arcsecond   = arcminute / 60.;
        static constexpr const long double   light       = 299792458.0;
        static constexpr const long double   slug        = 1.459390293720636482939632545931759e1;
        static constexpr const long double   lbm         = 0.45359237;
        static constexpr const long double   eV          = 1.602176634-19;    // per 2019 definition
        static constexpr const long double   litre       = 1e-3;
        static constexpr const long double   gallon      = 3.785411784;
        static constexpr const long double   percent     = 0.01;
        static constexpr const long double   bar         = 1e5;

        static constexpr const long double   quecto      = 1.e-30;
        static constexpr const long double   quecto²     = quecto * quecto;
        static constexpr const long double   quecto³     = quecto² * quecto;
        static constexpr const long double   ronto       = 1.e-27;
        static constexpr const long double   ronto²      = ronto * ronto;
        static constexpr const long double   ronto³      = ronto² * ronto;
        static constexpr const long double   yocto       = 1.e-24;
        static constexpr const long double   yocto²      = yocto * yocto;
        static constexpr const long double   yocto³      = yocto² * yocto;
        static constexpr const long double   zepto       = 1.e-21;
        static constexpr const long double   zepto²      = zepto * zepto;
        static constexpr const long double   zepto³      = zepto² * zepto;
        static constexpr const long double   atto        = 1.e-18;
        static constexpr const long double   atto²       = atto * atto;
        static constexpr const long double   atto³       = atto² * atto;
        static constexpr const long double   femto       = 1.e-15;
        static constexpr const long double   femto²      = femto * femto;
        static constexpr const long double   femto³      = femto² * femto;
        static constexpr const long double   pico        = 1.e-12;
        static constexpr const long double   pico²       = pico * pico;
        static constexpr const long double   pico³       = pico² * pico;
        static constexpr const long double   nano        = 1.e-9;
        static constexpr const long double   nano²       = nano * nano;
        static constexpr const long double   nano³       = nano² * nano;
        static constexpr const long double   micro       = 1.e-6;
        static constexpr const long double   micro²      = micro * micro;
        static constexpr const long double   micro³      = micro² * micro;
        static constexpr const long double   milli       = 1.e-3;
        static constexpr const long double   milli²      = milli * milli;
        static constexpr const long double   milli³      = milli² * milli;
        static constexpr const long double   centi       = 1.e-2;
        static constexpr const long double   centi²      = centi * centi;
        static constexpr const long double   centi³      = centi² * centi;
        static constexpr const long double   deci        = 1.e-1;
        static constexpr const long double   deci²       = deci * deci;
        static constexpr const long double   deci³       = deci² * deci;
        static constexpr const long double   deca        = 1.e1;
        static constexpr const long double   deca²       = deca * deca;
        static constexpr const long double   deca³       = deca² * deca;
        static constexpr const long double   hecto       = 1.e2;
        static constexpr const long double   hecto²      = hecto * hecto;
        static constexpr const long double   hecto³      = hecto² * hecto;
        static constexpr const long double   kilo        = 1.e3;
        static constexpr const long double   kilo²       = kilo * kilo;
        static constexpr const long double   kilo³       = kilo² * kilo;
        static constexpr const long double   mega        = 1.e6;
        static constexpr const long double   mega²       = mega * mega;
        static constexpr const long double   mega³       = mega² * mega;
        static constexpr const long double   giga        = 1.e9;
        static constexpr const long double   giga²       = giga * giga;
        static constexpr const long double   giga³       = giga² * giga;
        static constexpr const long double   tera        = 1.e12;
        static constexpr const long double   tera²       = tera * tera;
        static constexpr const long double   tera³       = tera² * tera;
        static constexpr const long double   peta        = 1.e15;
        static constexpr const long double   peta²       = peta * peta;
        static constexpr const long double   peta³       = peta² * peta;
        static constexpr const long double   exa         = 1.e18;
        static constexpr const long double   exa²        = exa * exa;
        static constexpr const long double   exa³        = exa² * exa;
        static constexpr const long double   zetta       = 1.e21;
        static constexpr const long double   zetta²      = zetta * zetta;
        static constexpr const long double   zetta³      = zetta² * zetta;
        static constexpr const long double   yotta       = 1.e24;
        static constexpr const long double   yotta²      = yotta * yotta;
        static constexpr const long double   yotta³      = yotta² * yotta;
        static constexpr const long double   ronna       = 1.e27;
        static constexpr const long double   ronna²      = ronna * ronna;
        static constexpr const long double   ronna³      = ronna² * ronna;
        static constexpr const long double   quetta      = 1.e30;
        static constexpr const long double   quetta²     = quetta * quetta;
        static constexpr const long double   quetta³     = quetta² * quetta;
    }


    template <typename T, typename DIM>             struct MKS;
    template <typename T, typename DIM, double K>   struct SCALED;
    
#if 0
    template <typename DIM>             struct MKS_SYMBOL;
    template <typename DIM, double K>   struct SCALED_SYMBOL;

    namespace udef {
        struct convMKS {
            static constexpr const long double toUnit(long double v) noexcept { return v; }
            static constexpr const long double fromUnit(long double v) noexcept { return v; }
        };
        
        template <double K>
        struct ScalarConv {
            static constexpr const long double toUnit(long double v){ return v*(1./K); }
            static constexpr const long double toMKS(long double v){ return v*K; }
        };
        
        struct NoSymbol {
        
        };
        
        template <BasicString sym>
        struct Symbol {
        };
    
        struct AcreDef : ScalarConv<4046.86> {
            using dim_t     = dim::Area;
        };
    }
    
    template <typename T, typename DIM> std::string_view  symbol(MKS<T,DIM>);
    
#endif

    //  Unit sizes double checked with wikipedia!
    namespace unit {
        using Acre                      = SCALED<double,dim::Area,4046.86>;
        using Ampere                    = MKS<double,dim::Current>;
        using Arcminute                 = SCALED<double,dim::Angle,(double) def::arcminute>;
        using Arcsecond                 = SCALED<double,dim::Angle,(double) def::arcsecond>;
        using Are                       = SCALED<double,dim::Area,100.0>;
        using Ångström                  = SCALED<double,dim::Length,1e-10>;
        using AstronomicalUnit          = SCALED<double,dim::Length,149597870700.0>;
        using Attosecond                = SCALED<double,dim::Time,(double) def::atto>;
        using Bar                       = SCALED<double,dim::Pressure,(double) def::bar>;
        using Barn                      = SCALED<double,dim::Area,1e-28>;
        using Barye                     = SCALED<double,dim::Pressure,0.1>;
        using BritishThermalUnit        = SCALED<double,dim::Energy,1055.05585262>; // the definition is ambiguous, choosing
        using Calorie                   = SCALED<double,dim::Energy,4.184>;
        using Candela                   = MKS<double,dim::Intensity>;
        using Centimeter                = SCALED<double,dim::Length,(double) def::centi>;
        using Centimeter²               = SCALED<double,dim::Area,(double) def::centi²>;
        using Centimeter³               = SCALED<double,dim::Volume,(double) def::centi³>;
        using CentimeterPerSecond       = SCALED<double,dim::Speed,(double) def::centi>;
        using CentimeterPerSecond²      = SCALED<double,dim::Acceleration,(double) def::centi>;
        using Coulomb                   = MKS<double,dim::Charge>;
        using CoulombPerMole            = MKS<double,dim::ChargeMolecularDensity>;
        using Dalton                    = SCALED<double,dim::Mass,1.66005390666050e-27>; //!< Atomic Mass Unit
        using Day                       = SCALED<double,dim::Time,(double) def::day>;
        using Decibar                   = SCALED<double,dim::Pressure,(double) (def::deci*def::bar)>;
        using Degree                    = SCALED<double,dim::Angle,(double) def::degree>;
        using Degree²                   = SCALED<double,dim::Angle,(double) def::degree²>;
        using DegreeF                   = SCALED<float,dim::Angle,(double) def::degree>;
        using DegreePerFoot             = SCALED<double,dim::InverseCurvature,(double) (def::degree/def::foot)>;
        using DegreePerMeter            = SCALED<double,dim::InverseCurvature,(double) def::degree>;
        using DegreePerMinute           = SCALED<double,dim::AngularVelocity,(double) (def::degree/def::minute)>;
        using DegreePerSecond           = SCALED<double,dim::AngularVelocity,(double) def::degree>;
        using DegreePerSecond²          = SCALED<double,dim::AngularAcceleration,(double) def::degree>;
        using Dioptre                   = MKS<double,dim::PerLength>;
        using Dyne                      = SCALED<double,dim::Force,1e-5>;
        using ElectronVolt              = SCALED<double,dim::Energy,(double) def::eV>;    // per 2019 definition
        using Erg                       = SCALED<double,dim::Energy,1e-7>; // used in CGS units
        using ErgPerSecond              = SCALED<double,dim::Power,1e-7>; // used in CGS units
        using Farad                     = MKS<double,dim::Capacitance>;
        using FaradPerMeter             = MKS<double,dim::Permittivity>;
        using Fathom                    = SCALED<double,dim::Length,1.8288>;
        using Femtometer                = SCALED<double,dim::Length,(double) def::femto>;
        using Femtosecond               = SCALED<double,dim::Time,(double) def::femto>;
        using Foot                      = SCALED<double,dim::Length,(double) def::foot>;
        using Foot²                     = SCALED<double,dim::Area,(double) def::foot²>;
        using Foot³                     = SCALED<double,dim::Volume,(double) def::foot³>;
        using FootF                     = SCALED<float,dim::Length,(double) def::foot>;
        using FootPerDegree             = SCALED<float,dim::Curvature,(double) (def::foot/def::degree)>;
        using FootPerRadian             = SCALED<float,dim::Curvature,(double) def::foot>;
        using FootPerSecond             = SCALED<double,dim::Speed,(double) def::foot>;
        using FootPerSecond²            = SCALED<double,dim::Acceleration,(double) def::foot>;
        using FootPound                 = SCALED<double,dim::Torque,(double) (def::foot*def::lbf)>;
        using Fortnight                 = SCALED<double,dim::Time, (double) def::fortnight>;
        using Furlong                   = SCALED<double,dim::Length,(double) def::furlong>;
        using FurlongPerFortnight       = SCALED<double,dim::Length,(double) (def::furlong/def::fortnight)>;
        using Gallon                    = SCALED<double,dim::Volume,(double) def::gallon>;
        using GallonPerMinute           = SCALED<double,dim::VolumeFlowRate, (double) (def::gallon/def::minute)>;
        using GigaElectronVolt          = SCALED<double,dim::Energy,(double) (def::eV*def::giga)>;
        using Gigahertz                 = SCALED<double,dim::Frequency,(double) def::giga>;
        using Gigajoule                 = SCALED<double,dim::Energy,(double) def::giga>;
        using Gigapascal                = SCALED<double,dim::Pressure,(double) def::giga>;
        using Gigawatt                  = SCALED<double,dim::Power,(double) def::giga>;
        using Gradian                   = SCALED<double,dim::Angle,(double) def::gradian>;
        using Gram                      = SCALED<double,dim::Mass,(double) def::gram>;
        using GramPerCentimeter³        = SCALED<double,dim::Density,(double) (def::gram / def::centi³)>;
        using GramPerSecond             = SCALED<double,dim::MassFlow,(double) def::gram>;
        using GramPerMole               = SCALED<double,dim::SpecificMass,(double) def::gram>;
        using Gravity                   = SCALED<double,dim::Acceleration,9.80665>;
        using Hectare                   = SCALED<double,dim::Area,1e4>;
        using Henry                     = MKS<double,dim::Inductance>;
        using HenryPerMeter             = MKS<double,dim::Permeability>;
        using Hertz                     = MKS<double,dim::Frequency>;
        using HertzPerSecond            = MKS<double,dim::FrequencyRate>;
        using Horsepower                = SCALED<double,dim::Power,745.69987>;  // using mechanical horsepower
        using Hour                      = SCALED<double,dim::Time, (double) def::hour>;
        using Inch                      = SCALED<double,dim::Length,(double) def::inch>;
        using Inch²                     = SCALED<double,dim::Area,(double) def::inch²>;
        using Inch³                     = SCALED<double,dim::Volume,(double) def::inch³>;
        using Joule                     = MKS<double,dim::Energy>;
        using JoulePerKelvin            = MKS<double,dim::Heat>;
        using JoulePerKilogram          = MKS<double,dim::SpecificEnergy>;
        using JoulePerKilogramKelvin    = MKS<double,dim::SpecificMolecularHeat>;
        using JoulePerMole              = MKS<double,dim::SpecificMolecularEnergy>;
        using JoulePerMeter³            = MKS<double,dim::Pressure>;
        using Katal                     = MKS<double,dim::CatalyticActivity>;
        using Kelvin                    = MKS<double,dim::Temperature>;
        using KelvinPerMeter            = MKS<double,dim::ThermalGradient>;
        using KelvinPerSecond           = MKS<double,dim::ThermalChange>;
        using Kiloampere                = SCALED<double,dim::Current,(double) def::kilo>;
        using Kilocalorie               = SCALED<double,dim::Energy,4.184e3>;
        using KiloElectronVolt          = SCALED<double,dim::Energy,(double) (def::kilo*def::eV)>;
        using Kilofoot                  = SCALED<double,dim::Length,(double) (def::kilo*def::foot)>;
        using Kilogram                  = MKS<double,dim::Mass>;
        using KilogramMeterPerSecond    = MKS<double,dim::Impulse>; //!< Alias to N*s
        using KilogramPerMeter          = MKS<double,dim::LinearDensity>;
        using KilogramPerMeter²         = MKS<double,dim::ArealDensity>;
        using KilogramPerMeter³         = MKS<double,dim::Density>;
        using KilogramPerMole           = MKS<double,dim::SpecificMass>;
        using KilogramPerSecond         = MKS<double,dim::MassFlow>;
        using KilogramPerSecond²        = MKS<double,dim::MassFlowRate>;
        using Kilohertz                 = SCALED<double,dim::Frequency,(double) def::kilo>;
        using Kilojoule                 = SCALED<double,dim::Energy,(double) def::kilo>;
        using KiloLightYear             = SCALED<double,dim::Length,(double) (def::kilo*def::light*def::jyear)>;
        using Kilolitre                 = MKS<double,dim::Volume>;
        using Kilometer                 = SCALED<double,dim::Length,(double) def::kilo>;
        using Kilometer²                = SCALED<double,dim::Area,(double) def::kilo²>;
        using Kilometer³                = SCALED<double,dim::Volume,(double) def::kilo³>;
        using KilometerPerHour          = SCALED<double,dim::Speed,(double) (def::kilo/def::hour)>;
        using KilometerPerSecond        = SCALED<double,dim::Speed,(double) def::kilo>;
        using KilometerPerSecond²       = SCALED<double,dim::Acceleration,(double) def::kilo>;
        using Kilomole                  = SCALED<double,dim::Matter,(double) def::kilo>;
        using Kilonewton                = SCALED<double,dim::Force,(double) def::kilo>;
        using Kiloohm                   = SCALED<double,dim::Resistance,(double) def::kilo>;
        using Kilopascal                = SCALED<double,dim::Pressure,(double) def::kilo>;
        using Kilovolt                  = SCALED<double,dim::Voltage,(double) def::kilo>;
        using Kilowatt                  = SCALED<double,dim::Power,(double) def::kilo>;
        using KilowattHour              = SCALED<double,dim::Energy,(double) (def::kilo*def::hour)>;
        using Knot                      = SCALED<double,dim::Speed,(double) (def::nmi/def::hour)>;
        using LightHour                 = SCALED<double,dim::Length,(double) (def::light*def::hour)>;
        using LightMinute               = SCALED<double,dim::Length,(double) (def::light*def::minute)>;
        using LightSecond               = SCALED<double,dim::Length,(double) def::light>;
        using LightSpeed                = SCALED<double,dim::Speed,(double) def::light>;
        using LightYear                 = SCALED<double,dim::Length, (double) (def::light*def::jyear)>;
        using Litre                     = SCALED<double,dim::Volume, (double) def::litre>;
        using LongTon                   = SCALED<double,dim::Mass,1016.0469088>;
        using Lumen                     = MKS<double,dim::LuminousFlux>;
        using Lux                       = MKS<double,dim::Illuminance>;
        using Megaampere                = SCALED<double,dim::Current,(double) def::mega>;
        using MegaElectronVolt          = SCALED<double,dim::Energy,(double) (def::mega*def::eV)>;
        using Megahertz                 = SCALED<double,dim::Frequency,(double) def::mega>;
        using Megajoule                 = SCALED<double,dim::Energy,(double) def::mega>;
        using MegaLightYear             = SCALED<double,dim::Length, (double) (def::mega*def::light*def::jyear)>;
        using Meganewton                = SCALED<double,dim::Force,(double) def::mega>;
        using Megaohm                   = SCALED<double,dim::Resistance,(double) def::mega>;
        using Megapascal                = SCALED<double,dim::Pressure,(double) def::mega>;
        using Megavolt                  = SCALED<double,dim::Voltage,(double) def::mega>;
        using Megawatt                  = SCALED<double,dim::Power,(double) def::mega>;
        using Meter                     = MKS<double,dim::Length>;
        using Meter²                    = MKS<double,dim::Area>;
        using Meter²PerSecond           = MKS<double,dim::AreaFlow>;
        using Meter²PerSecond²          = MKS<double,dim::SpecificEnergy>;
        using Meter³                    = MKS<double,dim::Volume>;
        using Meter³PerKilogram         = MKS<double,dim::SpecificVolume>;
        using Meter³PerSecond           = MKS<double,dim::VolumeFlow>;
        using Meter³PerSecond²          = MKS<double,dim::VolumeFlowRate>;
        using MeterF                    = MKS<float,dim::Length>;
        using MeterPerRadian            = MKS<double,dim::Curvature>;
        using MeterPerSecond            = MKS<double,dim::Speed>;
        using MeterPerSecond²           = MKS<double,dim::Acceleration>;
        using Microampere               = SCALED<double,dim::Current,(double) def::micro>;
        using MicroArcsecond            = SCALED<double,dim::Angle,(double) (def::micro*def::arcsecond)>;
        using Microfarad                = SCALED<double,dim::Capacitance,(double) def::micro>;
        using Microgram                 = SCALED<double,dim::Mass,(double) (def::micro*def::gram)>;
        using MicrogramPerSecond        = SCALED<double,dim::MassFlow,(double) (def::micro*def::gram)>;
        using Microhenry                = SCALED<double,dim::Inductance,(double) def::micro>;
        using Microjoule                = SCALED<double,dim::Energy,(double) def::micro>;
        using MicroLightSecond          = SCALED<double,dim::Length,(double) (def::micro*def::light)>;
        using Microlitre                = SCALED<double,dim::Volume, (double) (def::micro*def::litre)>;
        using Micrometer                = SCALED<double,dim::Length,(double) def::micro>;
        using MicrometerPerSecond       = SCALED<double,dim::Speed,(double) def::micro>;
        using MicrometerPerSecond²      = SCALED<double,dim::Acceleration,(double) def::micro>;
        using Micronewton               = SCALED<double,dim::Force,(double) def::micro>;
        using Micropascal               = SCALED<double,dim::Pressure,(double) def::micro>;
        using Microsecond               = SCALED<double,dim::Time,(double) def::micro>;
        using Microtesla                = SCALED<double,dim::MagneticFluxDensity,(double) def::micro>;
        using Microvolt                 = SCALED<double,dim::Voltage,(double) def::micro>;
        using Microwatt                 = SCALED<double,dim::Power,(double) def::micro>;
        using Mile                      = SCALED<double,dim::Length,(double) def::mile>;
        using MilePerHour               = SCALED<double,dim::Speed,(double) (def::mile/def::hour)>;
        using Milliampere               = SCALED<double,dim::Current,(double) def::milli>;
        using MilliArcsecond            = SCALED<double,dim::Angle,(double) (def::milli*def::arcsecond)>;
        using Millibar                  = SCALED<double,dim::Pressure,(double) (def::milli*def::bar)>;
        using Millifarad                = SCALED<double,dim::Capacitance,(double) def::milli>;
        using Milligram                 = SCALED<double,dim::Mass,(double) (def::milli*def::gram)>;
        using MilligramPerSecond        = SCALED<double,dim::MassFlow,(double) (def::milli*def::gram)>;
        using Millihenry                = SCALED<double,dim::Inductance,(double) def::milli>;
        using Millihertz                = SCALED<double,dim::Frequency,(double) def::milli>;
        using Millijoule                = SCALED<double,dim::Energy,(double) def::milli>;
        using MilliLightSecond          = SCALED<double,dim::Length,(double) (def::milli * def::light)>;
        using Millilitre                = SCALED<double,dim::Volume, (double) (def::milli * def::litre)>;
        using Millimeter                = SCALED<double,dim::Length,(double) def::milli>;
        using Millimeter²               = SCALED<double,dim::Area,(double) def::milli²>;
        using Millimeter³               = SCALED<double,dim::Volume,(double) def::milli³>;
        using MillimeterPerSecond       = SCALED<double,dim::Speed,(double) def::milli>;
        using MillimeterPerSecond²      = SCALED<double,dim::Acceleration,(double) def::milli>;
        using MillimeterPerHour         = SCALED<double,dim::Speed,(double) (def::milli/def::hour)>;
        using Millinewton               = SCALED<double,dim::Force,(double) def::milli>;
        using Milliohm                  = SCALED<double,dim::Resistance,(double) def::milli>;
        using Millipascal               = SCALED<double,dim::Pressure,(double) def::milli>;
        using Milliradian               = SCALED<double,dim::Angle,(double) def::milli>;
        using MilliradianPerSecond      = SCALED<double,dim::AngularVelocity,(double) def::milli>;
        using MilliradianPerSecond²     = SCALED<double,dim::AngularAcceleration,(double) def::milli>;
        using Millisecond               = SCALED<double,dim::Time,(double) def::milli>;
        using Millitesla                = SCALED<double,dim::MagneticFluxDensity,(double) def::milli>;
        using Millivolt                 = SCALED<double,dim::Voltage,(double) def::milli>;
        using Milliwatt                 = SCALED<double,dim::Power,(double) def::milli>;
        using Minute                    = SCALED<double,dim::Time, (double) def::minute>;   
        using Mole                      = MKS<double,dim::Matter>;
        using Nanoampere                = SCALED<double,dim::Current,(double) def::nano>;
        using Nanofarad                 = SCALED<double,dim::Capacitance,(double) def::nano>;
        using Nanogram                  = SCALED<double,dim::Mass,(double) (def::nano*def::gram)>;
        using NanogramPerSecond         = SCALED<double,dim::MassFlow,(double) (def::nano*def::gram)>;
        using Nanohenry                 = SCALED<double,dim::Inductance,(double) def::nano>;
        using Nanojoule                 = SCALED<double,dim::Energy,(double) def::nano>;
        using NanoLightSecond           = SCALED<double,dim::Length,(double) (def::nano*def::light)>;
        using Nanometer                 = SCALED<double,dim::Length,(double) def::nano>;
        using NanometerPerSecond        = SCALED<double,dim::Speed,(double) def::nano>;
        using NanometerPerSecond²       = SCALED<double,dim::Acceleration,(double) def::nano>;
        using Nanosecond                = SCALED<double,dim::Time,(double) def::nano>;
        using Nanotesla                 = SCALED<double,dim::MagneticFluxDensity,(double) def::nano>;
        using Nanovolt                  = SCALED<double,dim::Voltage,(double) def::nano>;
        using Nanowatt                  = SCALED<double,dim::Power,(double) def::nano>;
        using NauticalMile              = SCALED<double,dim::Length,(double) def::nmi>;
        using Newton                    = MKS<double,dim::Force>;
        using NewtonMeter               = MKS<double,dim::Torque>;
        using NewtonPerSecond           = MKS<double,dim::ForceRate>;
        using NewtonSecond              = MKS<double,dim::Impulse>;
        using Ohm                       = MKS<double,dim::Resistance>;
        using Pascal                    = MKS<double,dim::Pressure>;
        using Percent                   = SCALED<double,dim::None, (double) def::percent>;
        using PerRadian                 = MKS<double,dim::PerAngle>;
        using PerMeter                  = MKS<double,dim::PerLength>;
        using PerMole                   = MKS<double,dim::PerMatter>;
        using Picofarad                 = SCALED<double,dim::Capacitance,(double) def::pico>;
        using PicoLightSecond           = SCALED<double,dim::Length,(double) (def::pico*def::light)>;
        using Picometer                 = SCALED<double,dim::Length,(double) def::pico>;
        using Picosecond                = SCALED<double,dim::Time,(double) def::pico>;
        using Picovolt                  = SCALED<double,dim::Voltage,(double) def::pico>;
        using PoundMass                 = SCALED<double,dim::Mass,(double) def::lbm>;
        using PoundForce                = SCALED<double,dim::Force,(double) def::lbf>;
        using PoundForcePerSecond       = SCALED<double,dim::ForceRate,(double) def::lbf>;
        using PoundPerInch²             = SCALED<double,dim::Pressure,(double) (def::lbf/def::inch²)>;
        using PoundPerFoot²             = SCALED<double,dim::Pressure,(double) (def::lbf/def::foot²)>;
        using Radian                    = MKS<double,dim::Angle>;
        using Radian²                   = MKS<double,dim::SolidAngle>;
        using RadianF                   = MKS<float,dim::Angle>;
        using RadianPerMeter            = MKS<double,dim::InverseCurvature>;
        using RadianPerSecond           = MKS<double,dim::AngularVelocity>;
        using RadianPerSecond²          = MKS<double,dim::AngularAcceleration>;
        using Rankine                   = SCALED<double,dim::Temperature,5./9.>;
        using RotationsPerMinute        = SCALED<double,dim::AngularVelocity,(double) (def::long_pi/30.)>;
        using Scalar                    = MKS<double,dim::None>;
        using Second                    = MKS<double,dim::Time>;
        using Second²                   = MKS<double,dim::TimeSquare>;
        using ShortTon                  = SCALED<double,dim::Mass,907.18474>;
        using Siemens                   = MKS<double,dim::Conductance>;
        using Slug                      = SCALED<double,dim::Mass,(double) def::slug>;
        using SlugPerFoot³              = SCALED<double,dim::Density,(double) (def::slug/def::foot³)>;
        using Steradian                 = MKS<double,dim::SolidAngle>;
        using TeraElectronVolt          = SCALED<double,dim::Energy,(double) (def::tera*def::eV)>;
        using Terahertz                 = SCALED<double,dim::Frequency,(double) def::tera>;
        using Terawatt                  = SCALED<double,dim::Power,(double) def::tera>;
        using Tesla                     = MKS<double,dim::MagneticFluxDensity>;
        using Tonne                     = SCALED<double,dim::Mass,(double) def::kilo>;
        using Volt                      = MKS<double,dim::Voltage>;
        using VoltPerMeter              = MKS<double,dim::ElectricField>;
        using Watt                      = MKS<double,dim::Power>;
        using WattPerMeter²             = MKS<double,dim::PowerArealDensity>;
        using WattPerMeter²Steradian    = MKS<double,dim::Radiance>;
        using WattPerMeter³             = MKS<double,dim::PowerDensity>;
        using WattPerSteradian          = MKS<double,dim::RadiantIntensity>;
        using Weber                     = MKS<double,dim::MagneticFlux>;
        using Week                      = SCALED<double,dim::Time, (double) def::week>;
        using Yard                      = SCALED<double,dim::Length, (double) (3.*def::foot)>;
        using Yard²                     = SCALED<double,dim::Area, (double) (9.*def::foot²)>;
        using Yard³                     = SCALED<double,dim::Volume, (double) (27.*def::foot³)>;
        
        using CentimeterPerSecond3D     = Vector3<CentimeterPerSecond>;
        using Foot3D                    = Vector3<Foot>;
        using Foot3F                    = Vector3<FootF>;
        using KilometerPerSecond3D      = Vector3<KilometerPerSecond>;
        using Meter3D                   = Vector3<Meter>;
        using Meter3F                   = Vector3<MeterF>;
        using Meter3I                   = Vector3<int>;
        using MeterPerSecond3D          = Vector3<MeterPerSecond>;
        using MeterPerSecond²3D         = Vector3<MeterPerSecond²>;
        using MicrometerPerSecond3D     = Vector3<MicrometerPerSecond>;
        using MillimeterPerSecond3D     = Vector3<MillimeterPerSecond>;
        using NanometerPerSecond3D      = Vector3<NanometerPerSecond>;
        using Newton3D                  = Vector3<Newton>;
        using Pascal33D                 = Tensor33<Pascal>;
        using Radian3D                  = Vector3<Radian>;
        using RadianPerSecond3D         = Vector3<RadianPerSecond>;
        using RadianPerSecond²3D        = Vector3<RadianPerSecond²>;
        
        
    }
    
    using unit::Radian;
    using unit::Meter;
    using unit::Degree;
    using unit::Foot;
    using unit::Second;
}
