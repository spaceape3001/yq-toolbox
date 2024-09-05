////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "units.hpp"

#include <yq-toolbox/strings.hpp>

#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/basic/StringLiteral.hpp>
#include <yq-toolbox/io/StreamOps.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/tensor/Tensor33.hpp>
#include <yq-toolbox/vector/Vector3.hpp>

using namespace yq;


YQ_TYPE_IMPLEMENT(yq::unit::Acre)
YQ_TYPE_IMPLEMENT(yq::unit::Ampere)
YQ_TYPE_IMPLEMENT(yq::unit::Arcminute)
YQ_TYPE_IMPLEMENT(yq::unit::Arcsecond)
YQ_TYPE_IMPLEMENT(yq::unit::Are)
YQ_TYPE_IMPLEMENT(yq::unit::Ångström)
YQ_TYPE_IMPLEMENT(yq::unit::AstronomicalUnit)
YQ_TYPE_IMPLEMENT(yq::unit::Attosecond)
YQ_TYPE_IMPLEMENT(yq::unit::Bar)
YQ_TYPE_IMPLEMENT(yq::unit::Barn)
YQ_TYPE_IMPLEMENT(yq::unit::Barye)
YQ_TYPE_IMPLEMENT(yq::unit::BritishThermalUnit)
YQ_TYPE_IMPLEMENT(yq::unit::Calorie)
YQ_TYPE_IMPLEMENT(yq::unit::Candela)
YQ_TYPE_IMPLEMENT(yq::unit::Centimeter)
YQ_TYPE_IMPLEMENT(yq::unit::Centimeter²)
YQ_TYPE_IMPLEMENT(yq::unit::Centimeter³)
YQ_TYPE_IMPLEMENT(yq::unit::CentimeterPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::CentimeterPerSecond²)
YQ_TYPE_IMPLEMENT(yq::unit::Coulomb)
YQ_TYPE_IMPLEMENT(yq::unit::CoulombPerMole)
YQ_TYPE_IMPLEMENT(yq::unit::Dalton)
YQ_TYPE_IMPLEMENT(yq::unit::Day)
YQ_TYPE_IMPLEMENT(yq::unit::Decibar)
YQ_TYPE_IMPLEMENT(yq::unit::Degree)
YQ_TYPE_IMPLEMENT(yq::unit::Degree²)
YQ_TYPE_IMPLEMENT(yq::unit::DegreeF)
YQ_TYPE_IMPLEMENT(yq::unit::DegreePerFoot)
YQ_TYPE_IMPLEMENT(yq::unit::DegreePerMeter)
YQ_TYPE_IMPLEMENT(yq::unit::DegreePerMinute)
YQ_TYPE_IMPLEMENT(yq::unit::DegreePerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::DegreePerSecond²)
YQ_TYPE_IMPLEMENT(yq::unit::Dioptre)
YQ_TYPE_IMPLEMENT(yq::unit::Dyne)
YQ_TYPE_IMPLEMENT(yq::unit::ElectronVolt)
YQ_TYPE_IMPLEMENT(yq::unit::Erg)
YQ_TYPE_IMPLEMENT(yq::unit::ErgPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::Farad)
YQ_TYPE_IMPLEMENT(yq::unit::FaradPerMeter)
YQ_TYPE_IMPLEMENT(yq::unit::Fathom)
YQ_TYPE_IMPLEMENT(yq::unit::Femtometer)
YQ_TYPE_IMPLEMENT(yq::unit::Femtosecond)
YQ_TYPE_IMPLEMENT(yq::unit::Foot)
YQ_TYPE_IMPLEMENT(yq::unit::Foot²)
YQ_TYPE_IMPLEMENT(yq::unit::Foot³)
YQ_TYPE_IMPLEMENT(yq::unit::FootF)
YQ_TYPE_IMPLEMENT(yq::unit::FootPerDegree)
YQ_TYPE_IMPLEMENT(yq::unit::FootPerRadian)
YQ_TYPE_IMPLEMENT(yq::unit::FootPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::FootPerSecond²)
YQ_TYPE_IMPLEMENT(yq::unit::FootPound)
YQ_TYPE_IMPLEMENT(yq::unit::Fortnight)
YQ_TYPE_IMPLEMENT(yq::unit::Furlong)
YQ_TYPE_IMPLEMENT(yq::unit::FurlongPerFortnight)
YQ_TYPE_IMPLEMENT(yq::unit::Gallon)
YQ_TYPE_IMPLEMENT(yq::unit::GallonPerMinute)
YQ_TYPE_IMPLEMENT(yq::unit::GigaElectronVolt)
YQ_TYPE_IMPLEMENT(yq::unit::Gigahertz)
YQ_TYPE_IMPLEMENT(yq::unit::Gigajoule)
YQ_TYPE_IMPLEMENT(yq::unit::Gigapascal)
YQ_TYPE_IMPLEMENT(yq::unit::Gigawatt)
YQ_TYPE_IMPLEMENT(yq::unit::Gradian)
YQ_TYPE_IMPLEMENT(yq::unit::Gram)
YQ_TYPE_IMPLEMENT(yq::unit::GramPerCentimeter³)
YQ_TYPE_IMPLEMENT(yq::unit::GramPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::GramPerMole)
YQ_TYPE_IMPLEMENT(yq::unit::Gravity)
YQ_TYPE_IMPLEMENT(yq::unit::Hectare)
YQ_TYPE_IMPLEMENT(yq::unit::Henry)
YQ_TYPE_IMPLEMENT(yq::unit::HenryPerMeter)
YQ_TYPE_IMPLEMENT(yq::unit::Hertz)
YQ_TYPE_IMPLEMENT(yq::unit::HertzPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::Horsepower)
YQ_TYPE_IMPLEMENT(yq::unit::Hour)
YQ_TYPE_IMPLEMENT(yq::unit::Inch)
YQ_TYPE_IMPLEMENT(yq::unit::Inch²)
YQ_TYPE_IMPLEMENT(yq::unit::Inch³)
YQ_TYPE_IMPLEMENT(yq::unit::Joule)
YQ_TYPE_IMPLEMENT(yq::unit::JoulePerKelvin)
// YQ_TYPE_IMPLEMENT(yq::unit::JoulePerKilogram)
YQ_TYPE_IMPLEMENT(yq::unit::JoulePerKilogramKelvin)
YQ_TYPE_IMPLEMENT(yq::unit::JoulePerMole)
// YQ_TYPE_IMPLEMENT(yq::unit::JoulePerMeter³)
YQ_TYPE_IMPLEMENT(yq::unit::Katal)
YQ_TYPE_IMPLEMENT(yq::unit::Kelvin)
YQ_TYPE_IMPLEMENT(yq::unit::KelvinPerMeter)
YQ_TYPE_IMPLEMENT(yq::unit::KelvinPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::Kiloampere)
YQ_TYPE_IMPLEMENT(yq::unit::Kilocalorie)
YQ_TYPE_IMPLEMENT(yq::unit::KiloElectronVolt)
YQ_TYPE_IMPLEMENT(yq::unit::Kilofoot)
YQ_TYPE_IMPLEMENT(yq::unit::Kilogram)
//YQ_TYPE_IMPLEMENT(yq::unit::KilogramMeterPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::KilogramPerMeter)
YQ_TYPE_IMPLEMENT(yq::unit::KilogramPerMeter²)
YQ_TYPE_IMPLEMENT(yq::unit::KilogramPerMeter³)
YQ_TYPE_IMPLEMENT(yq::unit::KilogramPerMole)
YQ_TYPE_IMPLEMENT(yq::unit::KilogramPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::KilogramPerSecond²)
YQ_TYPE_IMPLEMENT(yq::unit::Kilohertz)
YQ_TYPE_IMPLEMENT(yq::unit::Kilojoule)
YQ_TYPE_IMPLEMENT(yq::unit::KiloLightYear)
// YQ_TYPE_IMPLEMENT(yq::unit::Kilolitre)
YQ_TYPE_IMPLEMENT(yq::unit::Kilometer)
YQ_TYPE_IMPLEMENT(yq::unit::Kilometer²)
YQ_TYPE_IMPLEMENT(yq::unit::Kilometer³)
YQ_TYPE_IMPLEMENT(yq::unit::KilometerPerHour)
YQ_TYPE_IMPLEMENT(yq::unit::KilometerPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::KilometerPerSecond²)
YQ_TYPE_IMPLEMENT(yq::unit::Kilomole)
YQ_TYPE_IMPLEMENT(yq::unit::Kilonewton)
YQ_TYPE_IMPLEMENT(yq::unit::Kiloohm)
YQ_TYPE_IMPLEMENT(yq::unit::Kilopascal)
YQ_TYPE_IMPLEMENT(yq::unit::Kilovolt)
YQ_TYPE_IMPLEMENT(yq::unit::Kilowatt)
YQ_TYPE_IMPLEMENT(yq::unit::KilowattHour)
YQ_TYPE_IMPLEMENT(yq::unit::Knot)
YQ_TYPE_IMPLEMENT(yq::unit::LightHour)
YQ_TYPE_IMPLEMENT(yq::unit::LightMinute)
YQ_TYPE_IMPLEMENT(yq::unit::LightSecond)
YQ_TYPE_IMPLEMENT(yq::unit::LightSpeed)
YQ_TYPE_IMPLEMENT(yq::unit::LightYear)
YQ_TYPE_IMPLEMENT(yq::unit::Litre)
YQ_TYPE_IMPLEMENT(yq::unit::LongTon)
YQ_TYPE_IMPLEMENT(yq::unit::Lumen)
YQ_TYPE_IMPLEMENT(yq::unit::Lux)
YQ_TYPE_IMPLEMENT(yq::unit::Megaampere)
YQ_TYPE_IMPLEMENT(yq::unit::MegaElectronVolt)
YQ_TYPE_IMPLEMENT(yq::unit::Megahertz)
YQ_TYPE_IMPLEMENT(yq::unit::Megajoule)
YQ_TYPE_IMPLEMENT(yq::unit::MegaLightYear)
YQ_TYPE_IMPLEMENT(yq::unit::Meganewton)
YQ_TYPE_IMPLEMENT(yq::unit::Megaohm)
YQ_TYPE_IMPLEMENT(yq::unit::Megapascal)
YQ_TYPE_IMPLEMENT(yq::unit::Megavolt)
YQ_TYPE_IMPLEMENT(yq::unit::Megawatt)
YQ_TYPE_IMPLEMENT(yq::unit::Meter)
YQ_TYPE_IMPLEMENT(yq::unit::Meter²)
YQ_TYPE_IMPLEMENT(yq::unit::Meter²PerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::Meter²PerSecond²)
YQ_TYPE_IMPLEMENT(yq::unit::Meter³)
YQ_TYPE_IMPLEMENT(yq::unit::Meter³PerKilogram)
YQ_TYPE_IMPLEMENT(yq::unit::Meter³PerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::Meter³PerSecond²)
YQ_TYPE_IMPLEMENT(yq::unit::MeterF)
YQ_TYPE_IMPLEMENT(yq::unit::MeterPerRadian)
YQ_TYPE_IMPLEMENT(yq::unit::MeterPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::MeterPerSecond²)
YQ_TYPE_IMPLEMENT(yq::unit::Microampere)
YQ_TYPE_IMPLEMENT(yq::unit::MicroArcsecond)
YQ_TYPE_IMPLEMENT(yq::unit::Microfarad)
YQ_TYPE_IMPLEMENT(yq::unit::Microgram)
YQ_TYPE_IMPLEMENT(yq::unit::MicrogramPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::Microhenry)
YQ_TYPE_IMPLEMENT(yq::unit::Microjoule)
YQ_TYPE_IMPLEMENT(yq::unit::MicroLightSecond)
// YQ_TYPE_IMPLEMENT(yq::unit::Microlitre)
YQ_TYPE_IMPLEMENT(yq::unit::Micrometer)
YQ_TYPE_IMPLEMENT(yq::unit::MicrometerPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::MicrometerPerSecond²)
YQ_TYPE_IMPLEMENT(yq::unit::Micronewton)
YQ_TYPE_IMPLEMENT(yq::unit::Micropascal)
YQ_TYPE_IMPLEMENT(yq::unit::Microsecond)
YQ_TYPE_IMPLEMENT(yq::unit::Microtesla)
YQ_TYPE_IMPLEMENT(yq::unit::Microvolt)
YQ_TYPE_IMPLEMENT(yq::unit::Microwatt)
YQ_TYPE_IMPLEMENT(yq::unit::Mile)
YQ_TYPE_IMPLEMENT(yq::unit::MilePerHour)
YQ_TYPE_IMPLEMENT(yq::unit::Milliampere)
YQ_TYPE_IMPLEMENT(yq::unit::MilliArcsecond)
YQ_TYPE_IMPLEMENT(yq::unit::Millibar)
YQ_TYPE_IMPLEMENT(yq::unit::Millifarad)
YQ_TYPE_IMPLEMENT(yq::unit::Milligram)
YQ_TYPE_IMPLEMENT(yq::unit::MilligramPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::Millihenry)
YQ_TYPE_IMPLEMENT(yq::unit::Millihertz)
YQ_TYPE_IMPLEMENT(yq::unit::Millijoule)
YQ_TYPE_IMPLEMENT(yq::unit::MilliLightSecond)
YQ_TYPE_IMPLEMENT(yq::unit::Millilitre)
YQ_TYPE_IMPLEMENT(yq::unit::Millimeter)
YQ_TYPE_IMPLEMENT(yq::unit::Millimeter²)
YQ_TYPE_IMPLEMENT(yq::unit::Millimeter³)
YQ_TYPE_IMPLEMENT(yq::unit::MillimeterPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::MillimeterPerSecond²)
YQ_TYPE_IMPLEMENT(yq::unit::MillimeterPerHour)
YQ_TYPE_IMPLEMENT(yq::unit::Millinewton)
YQ_TYPE_IMPLEMENT(yq::unit::Milliohm)
YQ_TYPE_IMPLEMENT(yq::unit::Millipascal)
YQ_TYPE_IMPLEMENT(yq::unit::Milliradian)
YQ_TYPE_IMPLEMENT(yq::unit::MilliradianPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::MilliradianPerSecond²)
YQ_TYPE_IMPLEMENT(yq::unit::Millisecond)
YQ_TYPE_IMPLEMENT(yq::unit::Millitesla)
YQ_TYPE_IMPLEMENT(yq::unit::Millivolt)
YQ_TYPE_IMPLEMENT(yq::unit::Milliwatt)
YQ_TYPE_IMPLEMENT(yq::unit::Minute)
YQ_TYPE_IMPLEMENT(yq::unit::Mole)
YQ_TYPE_IMPLEMENT(yq::unit::Nanoampere)
YQ_TYPE_IMPLEMENT(yq::unit::Nanofarad)
YQ_TYPE_IMPLEMENT(yq::unit::Nanogram)
YQ_TYPE_IMPLEMENT(yq::unit::NanogramPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::Nanohenry)
YQ_TYPE_IMPLEMENT(yq::unit::Nanojoule)
YQ_TYPE_IMPLEMENT(yq::unit::NanoLightSecond)
YQ_TYPE_IMPLEMENT(yq::unit::Nanometer)
YQ_TYPE_IMPLEMENT(yq::unit::NanometerPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::NanometerPerSecond²)
YQ_TYPE_IMPLEMENT(yq::unit::Nanosecond)
YQ_TYPE_IMPLEMENT(yq::unit::Nanotesla)
YQ_TYPE_IMPLEMENT(yq::unit::Nanovolt)
YQ_TYPE_IMPLEMENT(yq::unit::Nanowatt)
YQ_TYPE_IMPLEMENT(yq::unit::NauticalMile)
YQ_TYPE_IMPLEMENT(yq::unit::Newton)
YQ_TYPE_IMPLEMENT(yq::unit::NewtonMeter)
YQ_TYPE_IMPLEMENT(yq::unit::NewtonPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::NewtonSecond)
YQ_TYPE_IMPLEMENT(yq::unit::Ohm)
YQ_TYPE_IMPLEMENT(yq::unit::Pascal)
YQ_TYPE_IMPLEMENT(yq::unit::Percent)
YQ_TYPE_IMPLEMENT(yq::unit::PerRadian)
//YQ_TYPE_IMPLEMENT(yq::unit::PerMeter)
YQ_TYPE_IMPLEMENT(yq::unit::PerMole)
YQ_TYPE_IMPLEMENT(yq::unit::Picofarad)
YQ_TYPE_IMPLEMENT(yq::unit::PicoLightSecond)
YQ_TYPE_IMPLEMENT(yq::unit::Picometer)
YQ_TYPE_IMPLEMENT(yq::unit::Picosecond)
YQ_TYPE_IMPLEMENT(yq::unit::Picovolt)
YQ_TYPE_IMPLEMENT(yq::unit::PoundMass)
YQ_TYPE_IMPLEMENT(yq::unit::PoundForce)
YQ_TYPE_IMPLEMENT(yq::unit::PoundForcePerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::PoundPerInch²)
YQ_TYPE_IMPLEMENT(yq::unit::PoundPerFoot²)
YQ_TYPE_IMPLEMENT(yq::unit::Radian)
//YQ_TYPE_IMPLEMENT(yq::unit::Radian²)
YQ_TYPE_IMPLEMENT(yq::unit::RadianF)
YQ_TYPE_IMPLEMENT(yq::unit::RadianPerMeter)
YQ_TYPE_IMPLEMENT(yq::unit::RadianPerSecond)
YQ_TYPE_IMPLEMENT(yq::unit::RadianPerSecond²)
YQ_TYPE_IMPLEMENT(yq::unit::Rankine)
YQ_TYPE_IMPLEMENT(yq::unit::RotationsPerMinute)
YQ_TYPE_IMPLEMENT(yq::unit::Scalar)
YQ_TYPE_IMPLEMENT(yq::unit::Second)
YQ_TYPE_IMPLEMENT(yq::unit::Second²)
YQ_TYPE_IMPLEMENT(yq::unit::ShortTon)
YQ_TYPE_IMPLEMENT(yq::unit::Siemens)
YQ_TYPE_IMPLEMENT(yq::unit::Slug)
YQ_TYPE_IMPLEMENT(yq::unit::SlugPerFoot³)
YQ_TYPE_IMPLEMENT(yq::unit::Steradian)
YQ_TYPE_IMPLEMENT(yq::unit::TeraElectronVolt)
YQ_TYPE_IMPLEMENT(yq::unit::Terahertz)
YQ_TYPE_IMPLEMENT(yq::unit::Terawatt)
YQ_TYPE_IMPLEMENT(yq::unit::Tesla)
YQ_TYPE_IMPLEMENT(yq::unit::Tonne)
YQ_TYPE_IMPLEMENT(yq::unit::Volt)
YQ_TYPE_IMPLEMENT(yq::unit::VoltPerMeter)
YQ_TYPE_IMPLEMENT(yq::unit::Watt)
YQ_TYPE_IMPLEMENT(yq::unit::WattPerMeter²)
YQ_TYPE_IMPLEMENT(yq::unit::WattPerMeter²Steradian)
YQ_TYPE_IMPLEMENT(yq::unit::WattPerMeter³)
YQ_TYPE_IMPLEMENT(yq::unit::WattPerSteradian)
YQ_TYPE_IMPLEMENT(yq::unit::Weber)
YQ_TYPE_IMPLEMENT(yq::unit::Week)
YQ_TYPE_IMPLEMENT(yq::unit::Yard)
YQ_TYPE_IMPLEMENT(yq::unit::Yard²)
YQ_TYPE_IMPLEMENT(yq::unit::Yard³)

YQ_TYPE_IMPLEMENT(yq::unit::CentimeterPerSecond3D)
YQ_TYPE_IMPLEMENT(yq::unit::Foot3D)
YQ_TYPE_IMPLEMENT(yq::unit::Foot3F)
YQ_TYPE_IMPLEMENT(yq::unit::KilometerPerSecond3D)
YQ_TYPE_IMPLEMENT(yq::unit::Meter3D)
YQ_TYPE_IMPLEMENT(yq::unit::Meter3F)
YQ_TYPE_IMPLEMENT(yq::unit::MeterPerSecond3D)
YQ_TYPE_IMPLEMENT(yq::unit::MeterPerSecond²3D)
YQ_TYPE_IMPLEMENT(yq::unit::MicrometerPerSecond3D)
YQ_TYPE_IMPLEMENT(yq::unit::MillimeterPerSecond3D)
YQ_TYPE_IMPLEMENT(yq::unit::NanometerPerSecond3D)
YQ_TYPE_IMPLEMENT(yq::unit::Newton3D)
YQ_TYPE_IMPLEMENT(yq::unit::Pascal33D)
YQ_TYPE_IMPLEMENT(yq::unit::Radian3D)
YQ_TYPE_IMPLEMENT(yq::unit::RadianPerSecond3D)
YQ_TYPE_IMPLEMENT(yq::unit::RadianPerSecond²3D)



//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//  OTHER HELPERS FOR MATH

namespace {
    template <typename U, StringLiteral SYM="">
    void    print_unit(Stream& str, const U& v)
    {
        str << v.value << ' ' <<  SYM.value;
    }
}
    
//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

static void reg_units_math () {

    {
        auto w = writer<unit::Acre>();
        w.operate_self();
        w.print<print_unit<unit::Acre, "ac">>();
    }
    
    {
        auto w = writer<unit::Ampere>();
        w.operate_self();
        w.print<print_unit<unit::Ampere, "A">>();
    }
    
    {
        auto w = writer<unit::Arcminute>();
        w.operate_self();
        w.print<print_unit<unit::Arcminute, "'">>();
    }

    {
        auto w = writer<unit::Arcsecond>();
        w.operate_self();
        w.print<print_unit<unit::Arcsecond, "\"">>();
    }
    
    
    {
        auto w = writer<unit::Are>();
        w.operate_self();
        w.print<print_unit<unit::Are, "are">>();
    }

    {
        auto w = writer<unit::Ångström>();
        w.operate_self();
        w.print<print_unit<unit::Ångström, "Å">>();
    }

    {
        auto w = writer<unit::AstronomicalUnit>();
        w.operate_self();
        w.print<print_unit<unit::AstronomicalUnit, "AU">>();
    }

    {
        auto w = writer<unit::Attosecond>();
        w.operate_self();
        w.print<print_unit<unit::Attosecond, "as">>();
    }

    {
        auto w = writer<unit::Bar>();
        w.operate_self();
        w.print<print_unit<unit::Bar, "bar">>();
    }

    {
        auto w = writer<unit::Barn>();
        w.operate_self();
        w.print<print_unit<unit::Barn, "b">>();
    }

    {
        auto w = writer<unit::Barye>();
        w.operate_self();
        w.print<print_unit<unit::Barye, "Ba">>();
    }

    {
        auto w = writer<unit::BritishThermalUnit>();
        w.print<print_unit<unit::BritishThermalUnit, "BTU">>();
    }

    {
        auto w = writer<unit::Calorie>();
        w.print<print_unit<unit::Calorie, "cal">>();
    }

    {
        auto w = writer<unit::Candela>();
        w.print<print_unit<unit::Candela, "cd">>();
    }

    {
        auto w = writer<unit::Centimeter>();
        w.print<print_unit<unit::Centimeter, "cm">>();
    }

    {
        auto w = writer<unit::Centimeter²>();
        w.print<print_unit<unit::Centimeter², "cm²">>();
    }

    {
        auto w = writer<unit::Centimeter³>();
        w.print<print_unit<unit::Centimeter³, "cc">>();
    }

    {
        auto w = writer<unit::CentimeterPerSecond>();
        w.print<print_unit<unit::CentimeterPerSecond, "cm/s">>();
    }
    
    {
        auto w = writer<unit::CentimeterPerSecond²>();
        w.print<print_unit<unit::CentimeterPerSecond², "cm/s²">>();
    }
    
    {
        auto w = writer<unit::Coulomb>();
        w.print<print_unit<unit::Coulomb, "C">>();
    }

    {
        auto w = writer<unit::CoulombPerMole>();
        w.print<print_unit<unit::CoulombPerMole, "C/mole">>();
    }
    
    {
        auto w = writer<unit::Dalton>();
        w.print<print_unit<unit::Dalton, "u">>();
    }

    {
        auto w = writer<unit::Day>();
        w.print<print_unit<unit::Day, "d">>();
    }

    {
        auto w = writer<unit::Decibar>();
        w.print<print_unit<unit::Decibar, "dbar">>();
    }
    
    {
        auto w = writer<unit::Degree>();
        w.print<print_unit<unit::Degree, "°">>();
    }
    
    {
        auto w = writer<unit::Degree²>();
        w.print<print_unit<unit::Degree², "°²">>();
    }

    {
        auto w = writer<unit::DegreeF>();
        w.print<print_unit<unit::DegreeF, "°">>();
    }

    {
        auto w = writer<unit::DegreePerFoot>();
        w.print<print_unit<unit::DegreePerFoot, "°/ft">>();
    }
    
    {
        auto w = writer<unit::DegreePerMeter>();
        w.print<print_unit<unit::DegreePerMeter, "°/m">>();
    }
    
    {
        auto w = writer<unit::DegreePerMinute>();
        w.print<print_unit<unit::DegreePerMinute, "°/min">>();
    }

    {
        auto w = writer<unit::DegreePerSecond>();
        w.print<print_unit<unit::DegreePerSecond, "°/s">>();
    }
    
    {
        auto w = writer<unit::DegreePerSecond²>();
        w.print<print_unit<unit::DegreePerSecond², "°/s²">>();
    }

    {
        auto w = writer<unit::Dioptre>();
        w.print<print_unit<unit::Dioptre, "dpt">>();
    }

    {
        auto w = writer<unit::Dyne>();
        w.print<print_unit<unit::Dyne, "dyn">>();
    }

    {
        auto w = writer<unit::ElectronVolt>();
        w.print<print_unit<unit::ElectronVolt, "eV">>();
    }

    {
        auto w = writer<unit::Erg>();
        w.print<print_unit<unit::Erg, "erg">>();
    }

    {
        auto w = writer<unit::ErgPerSecond>();
        w.print<print_unit<unit::ErgPerSecond, "erg/s">>();
    }

    {
        auto w = writer<unit::Farad>();
        w.print<print_unit<unit::Farad, "F">>();
    }

    {
        auto w = writer<unit::FaradPerMeter>();
        w.print<print_unit<unit::FaradPerMeter, "F/m">>();
    }

    {
        auto w = writer<unit::Fathom>();
        w.print<print_unit<unit::Fathom, "fathom">>();
    }

    {
        auto w = writer<unit::Femtometer>();
        w.print<print_unit<unit::Femtometer, "fm">>();
    }

    {
        auto w = writer<unit::Femtosecond>();
        w.print<print_unit<unit::Femtosecond, "fs">>();
    }

    {
        auto w = writer<unit::Foot>();
        w.print<print_unit<unit::Foot, "ft">>();
    }

    {
        auto w = writer<unit::Foot²>();
        w.print<print_unit<unit::Foot², "ft²">>();
    }

    {
        auto w = writer<unit::Foot³>();
        w.print<print_unit<unit::Foot³, "ft³">>();
    }

    {
        auto w = writer<unit::FootF>();
        w.print<print_unit<unit::FootF, "ft">>();
    }

    {
        auto w = writer<unit::FootPerDegree>();
        w.print<print_unit<unit::FootPerDegree, "ft/°">>();
    }

    {
        auto w = writer<unit::FootPerRadian>();
        w.print<print_unit<unit::FootPerRadian, "ft/rad">>();
    }

    {
        auto w = writer<unit::FootPerSecond>();
        w.print<print_unit<unit::FootPerSecond, "ft/s">>();
    }

    {
        auto w = writer<unit::FootPerSecond²>();
        w.print<print_unit<unit::FootPerSecond², "ft/s²">>();
    }

    {
        auto w = writer<unit::FootPound>();
        w.print<print_unit<unit::FootPound, "lbf*ft">>();
    }

    {
        auto w = writer<unit::Fortnight>();
        w.print<print_unit<unit::Fortnight, "fortnight">>();
    }

    {
        auto w = writer<unit::Furlong>();
        w.print<print_unit<unit::Furlong, "furlong">>();
    }

    {
        auto w = writer<unit::FurlongPerFortnight>();
        w.print<print_unit<unit::FurlongPerFortnight, "furlong/fortnight">>();
    }

    {
        auto w = writer<unit::Gallon>();
        w.print<print_unit<unit::Gallon, "gal">>();
    }

    {
        auto w = writer<unit::GallonPerMinute>();
        w.print<print_unit<unit::GallonPerMinute, "gpm">>();
    }

    {
        auto w = writer<unit::GigaElectronVolt>();
        w.print<print_unit<unit::GigaElectronVolt, "GeV">>();
    }

    {
        auto w = writer<unit::Gigahertz>();
        w.print<print_unit<unit::Gigahertz, "GHz">>();
    }

    {
        auto w = writer<unit::Gigajoule>();
        w.print<print_unit<unit::Gigajoule, "GJ">>();
    }

    {
        auto w = writer<unit::Gigapascal>();
        w.print<print_unit<unit::Gigapascal, "GPa">>();
    }

    {
        auto w = writer<unit::Gigawatt>();
        w.print<print_unit<unit::Gigawatt, "GW">>();
    }

    {
        auto w = writer<unit::Gradian>();
        w.print<print_unit<unit::Gradian, "grad">>();
    }

    {
        auto w = writer<unit::Gram>();
        w.print<print_unit<unit::Gram, "g">>();
    }

    {
        auto w = writer<unit::GramPerCentimeter³>();
        w.print<print_unit<unit::GramPerCentimeter³, "g/cc">>();
    }

    {
        auto w = writer<unit::GramPerSecond>();
        w.print<print_unit<unit::GramPerSecond, "g/s">>();
    }

    {
        auto w = writer<unit::GramPerMole>();
        w.print<print_unit<unit::GramPerMole, "g/mol">>();
    }

    {
        auto w = writer<unit::Gravity>();
        w.print<print_unit<unit::Gravity, "G">>();
    }

    {
        auto w = writer<unit::Hectare>();
        w.print<print_unit<unit::Hectare, "ha">>();
    }

    {
        auto w = writer<unit::Henry>();
        w.print<print_unit<unit::Henry, "H">>();
    }

    {
        auto w = writer<unit::HenryPerMeter>();
        w.print<print_unit<unit::HenryPerMeter, "H/m">>();
    }

    {
        auto w = writer<unit::Hertz>();
        w.print<print_unit<unit::Hertz, "Hz">>();
    }

    {
        auto w = writer<unit::HertzPerSecond>();
        w.print<print_unit<unit::HertzPerSecond, "Hz/s">>();
    }

    {
        auto w = writer<unit::Horsepower>();
        w.print<print_unit<unit::Horsepower, "hp">>();
    }

    {
        auto w = writer<unit::Hour>();
        w.print<print_unit<unit::Hour, "h">>();
    }

    {
        auto w = writer<unit::Inch>();
        w.print<print_unit<unit::Inch, "in">>();
    }

    {
        auto w = writer<unit::Inch²>();
        w.print<print_unit<unit::Inch², "in²">>();
    }

    {
        auto w = writer<unit::Inch³>();
        w.print<print_unit<unit::Inch³, "in³">>();
    }

    {
        auto w = writer<unit::Joule>();
        w.print<print_unit<unit::Joule, "J">>();
    }

    {
        auto w = writer<unit::JoulePerKelvin>();
        w.print<print_unit<unit::JoulePerKelvin, "J/K">>();
    }

    {
        auto w = writer<unit::JoulePerKilogram>();
        w.print<print_unit<unit::JoulePerKilogram, "J/kg">>();
    }

    {
        auto w = writer<unit::JoulePerKilogramKelvin>();
        w.print<print_unit<unit::JoulePerKilogramKelvin, "J/(kg*K)">>();
    }

    {
        auto w = writer<unit::JoulePerMole>();
        w.print<print_unit<unit::JoulePerMole, "J/mol">>();
    }

    {
        auto w = writer<unit::JoulePerMeter³>();
        w.print<print_unit<unit::JoulePerMeter³, "J/m³">>();
    }

    {
        auto w = writer<unit::Katal>();
        w.print<print_unit<unit::Katal, "kat">>();
    }

    {
        auto w = writer<unit::Kelvin>();
        w.print<print_unit<unit::Kelvin, "K">>();
    }

    {
        auto w = writer<unit::KelvinPerMeter>();
        w.print<print_unit<unit::KelvinPerMeter, "K/m">>();
    }
    
    {
        auto w = writer<unit::KelvinPerSecond>();
        w.print<print_unit<unit::KelvinPerSecond, "K/s">>();
    }
    
    {
        auto w = writer<unit::Kiloampere>();
        w.print<print_unit<unit::Kiloampere, "kA">>();
    }
    
    {
        auto w = writer<unit::Kilocalorie>();
        w.print<print_unit<unit::Kilocalorie, "kcal">>();
    }
    
    {
        auto w = writer<unit::KiloElectronVolt>();
        w.print<print_unit<unit::KiloElectronVolt, "keV">>();
    }
    
    {
        auto w = writer<unit::Kilofoot>();
        w.print<print_unit<unit::Kilofoot, "kft">>();
    }
    
    {
        auto w = writer<unit::Kilogram>();
        w.print<print_unit<unit::Kilogram, "kg">>();
    }
    
    {
        auto w = writer<unit::KilogramMeterPerSecond>();
        w.print<print_unit<unit::KilogramMeterPerSecond, "kg*m/s">>();
    }
    
    {
        auto w = writer<unit::KilogramPerMeter>();
        w.print<print_unit<unit::KilogramPerMeter, "kg/m">>();
    }
    
    {
        auto w = writer<unit::KilogramPerMeter²>();
        w.print<print_unit<unit::KilogramPerMeter², "kg/m²">>();
    }
    
    {
        auto w = writer<unit::KilogramPerMeter³>();
        w.print<print_unit<unit::KilogramPerMeter³, "kg/m³">>();
    }
    
    {
        auto w = writer<unit::KilogramPerMole>();
        w.print<print_unit<unit::KilogramPerMole, "kg/mole">>();
    }
    
    {
        auto w = writer<unit::KilogramPerSecond>();
        w.print<print_unit<unit::KilogramPerSecond, "kg/s">>();
    }
    
    {
        auto w = writer<unit::KilogramPerSecond²>();
        w.print<print_unit<unit::KilogramPerSecond², "kg/s²">>();
    }
    
    {
        auto w = writer<unit::Kilohertz>();
        w.print<print_unit<unit::Kilohertz, "kHz">>();
    }
    
    {
        auto w = writer<unit::Kilojoule>();
        w.print<print_unit<unit::Kilojoule, "kJ">>();
    }
    
    {
        auto w = writer<unit::KiloLightYear>();
        w.print<print_unit<unit::KiloLightYear, "kly">>();
    }
    
    {
        auto w = writer<unit::Kilolitre>();
        w.print<print_unit<unit::Kilolitre, "kL">>();
    }
    
    {
        auto w = writer<unit::Kilometer>();
        w.print<print_unit<unit::Kilometer, "km">>();
    }
    
    {
        auto w = writer<unit::Kilometer²>();
        w.print<print_unit<unit::Kilometer², "km²">>();
    }
    
    {
        auto w = writer<unit::Kilometer³>();
        w.print<print_unit<unit::Kilometer³, "km³">>();
    }
    
    {
        auto w = writer<unit::KilometerPerHour>();
        w.print<print_unit<unit::KilometerPerHour, "kph">>();
    }
    
    {
        auto w = writer<unit::KilometerPerSecond>();
        w.print<print_unit<unit::KilometerPerSecond, "km/s">>();
    }
    
    {
        auto w = writer<unit::KilometerPerSecond²>();
        w.print<print_unit<unit::KilometerPerSecond², "km/s²">>();
    }
    
    {
        auto w = writer<unit::Kilomole>();
        w.print<print_unit<unit::Kilomole, "kmol">>();
    }
    
    {
        auto w = writer<unit::Kilonewton>();
        w.print<print_unit<unit::Kilonewton, "kN">>();
    }
    
    {
        auto w = writer<unit::Kiloohm>();
        w.print<print_unit<unit::Kiloohm, "kΩ">>();
    }
    
    {
        auto w = writer<unit::Kilopascal>();
        w.print<print_unit<unit::Kilopascal, "kPa">>();
    }
    
    {
        auto w = writer<unit::Kilovolt>();
        w.print<print_unit<unit::Kilovolt, "kV">>();
    }
    
    {
        auto w = writer<unit::Kilowatt>();
        w.print<print_unit<unit::Kilowatt, "kW">>();
    }
    
    {
        auto w = writer<unit::KilowattHour>();
        w.print<print_unit<unit::KilowattHour, "kWh">>();
    }
    
    {
        auto w = writer<unit::Knot>();
        w.print<print_unit<unit::Knot, "kt">>();
    }
    
    {
        auto w = writer<unit::LightHour>();
        w.print<print_unit<unit::LightHour, "lh">>();
    }
    
    {
        auto w = writer<unit::LightMinute>();
        w.print<print_unit<unit::LightMinute, "lmin">>();
    }
    
    {
        auto w = writer<unit::LightSecond>();
        w.print<print_unit<unit::LightSecond, "ls">>();
    }
    
    {
        auto w = writer<unit::LightSpeed>();
        w.print<print_unit<unit::LightSpeed, "c">>();
    }
    
    {
        auto w = writer<unit::LightYear>();
        w.print<print_unit<unit::LightYear, "ly">>();
    }
    
    {
        auto w = writer<unit::Litre>();
        w.print<print_unit<unit::Litre, "L">>();
    }
    
    {
        auto w = writer<unit::LongTon>();
        w.print<print_unit<unit::LongTon, "lton">>();
    }
    
    {
        auto w = writer<unit::Lumen>();
        w.print<print_unit<unit::Lumen, "lm">>();
    }
    
    {
        auto w = writer<unit::Lux>();
        w.print<print_unit<unit::Lux, "lx">>();
    }
    
    {
        auto w = writer<unit::Megaampere>();
        w.print<print_unit<unit::Megaampere, "MA">>();
    }
    
    {
        auto w = writer<unit::MegaElectronVolt>();
        w.print<print_unit<unit::MegaElectronVolt, "MeV">>();
    }
    
    {
        auto w = writer<unit::Megahertz>();
        w.print<print_unit<unit::Megahertz, "MHz">>();
    }
    
    {
        auto w = writer<unit::Megajoule>();
        w.print<print_unit<unit::Megajoule, "MJ">>();
    }
    
    {
        auto w = writer<unit::MegaLightYear>();
        w.print<print_unit<unit::MegaLightYear, "Mly">>();
    }
    
    {
        auto w = writer<unit::Meganewton>();
        w.print<print_unit<unit::Meganewton, "MN">>();
    }
    
    {
        auto w = writer<unit::Megaohm>();
        w.print<print_unit<unit::Megaohm, "MΩ">>();
    }
    
    {
        auto w = writer<unit::Megapascal>();
        w.print<print_unit<unit::Megapascal, "MPa">>();
    }
    
    {
        auto w = writer<unit::Megavolt>();
        w.print<print_unit<unit::Megavolt, "MV">>();
    }
    
    {
        auto w = writer<unit::Megawatt>();
        w.print<print_unit<unit::Megawatt, "MW">>();
    }
    
    {
        auto w = writer<unit::Meter>();
        w.print<print_unit<unit::Meter, "m">>();
    }
    
    {
        auto w = writer<unit::Meter²>();
        w.print<print_unit<unit::Meter², "m²">>();
    }
    
    {
        auto w = writer<unit::Meter²PerSecond>();
        w.print<print_unit<unit::Meter²PerSecond, "m²/s">>();
    }
    
    {
        auto w = writer<unit::Meter²PerSecond²>();
        w.print<print_unit<unit::Meter²PerSecond², "m²/s²">>();
    }
    
    {
        auto w = writer<unit::Meter³>();
        w.print<print_unit<unit::Meter³, "m³">>();
    }
    
    {
        auto w = writer<unit::Meter³PerKilogram>();
        w.print<print_unit<unit::Meter³PerKilogram, "m³/kg">>();
    }
    
    {
        auto w = writer<unit::Meter³PerSecond>();
        w.print<print_unit<unit::Meter³PerSecond, "m³/s">>();
    }
    
    {
        auto w = writer<unit::Meter³PerSecond²>();
        w.print<print_unit<unit::Meter³PerSecond², "m³/s²">>();
    }
    
    {
        auto w = writer<unit::Microampere>();
        w.print<print_unit<unit::Microampere, "μA">>();
    }
    
    {
        auto w = writer<unit::MicroArcsecond>();
        w.print<print_unit<unit::MicroArcsecond, "μas">>();
    }
    
    {
        auto w = writer<unit::Microfarad>();
        w.print<print_unit<unit::Microfarad, "μF">>();
    }
    
    {
        auto w = writer<unit::Microgram>();
        w.print<print_unit<unit::Microgram, "μg">>();
    }
    
    {
        auto w = writer<unit::MicrogramPerSecond>();
        w.print<print_unit<unit::MicrogramPerSecond, "μg/s">>();
    }
    
    {
        auto w = writer<unit::Microhenry>();
        w.print<print_unit<unit::Microhenry, "μH">>();
    }
    
    {
        auto w = writer<unit::Microjoule>();
        w.print<print_unit<unit::Microjoule, "μJ">>();
    }
    
    {
        auto w = writer<unit::MicroLightSecond>();
        w.print<print_unit<unit::MicroLightSecond, "μls">>();
    }
    
    {
        auto w = writer<unit::Microlitre>();
        w.print<print_unit<unit::Microlitre, "μL">>();
    }
    
    {
        auto w = writer<unit::Micrometer>();
        w.print<print_unit<unit::Micrometer, "μm">>();
    }
    
    {
        auto w = writer<unit::MicrometerPerSecond>();
        w.print<print_unit<unit::MicrometerPerSecond, "μm/s">>();
    }
    
    {
        auto w = writer<unit::MicrometerPerSecond²>();
        w.print<print_unit<unit::MicrometerPerSecond², "μm/s²">>();
    }
    
    {
        auto w = writer<unit::Micronewton>();
        w.print<print_unit<unit::Micronewton, "μN">>();
    }
    
    {
        auto w = writer<unit::Micropascal>();
        w.print<print_unit<unit::Micropascal, "μPa">>();
    }
    
    {
        auto w = writer<unit::Microsecond>();
        w.print<print_unit<unit::Microsecond, "μs">>();
    }
    
    {
        auto w = writer<unit::Microtesla>();
        w.print<print_unit<unit::Microtesla, "μT">>();
    }
    
    {
        auto w = writer<unit::Microvolt>();
        w.print<print_unit<unit::Microvolt, "μV">>();
    }
    
    {
        auto w = writer<unit::Microwatt>();
        w.print<print_unit<unit::Microwatt, "μW">>();
    }
    
    {
        auto w = writer<unit::Mile>();
        w.print<print_unit<unit::Mile, "mi">>();
    }
    
    {
        auto w = writer<unit::MilePerHour>();
        w.print<print_unit<unit::MilePerHour, "mph">>();
    }
    
    {
        auto w = writer<unit::Milliampere>();
        w.print<print_unit<unit::Milliampere, "mA">>();
    }
    
    {
        auto w = writer<unit::MilliArcsecond>();
        w.print<print_unit<unit::MilliArcsecond, "mas">>();
    }
    
    {
        auto w = writer<unit::Millibar>();
        w.print<print_unit<unit::Millibar, "mbar">>();
    }
    
    {
        auto w = writer<unit::Millifarad>();
        w.print<print_unit<unit::Millifarad, "mF">>();
    }
    
    {
        auto w = writer<unit::Milligram>();
        w.print<print_unit<unit::Milligram, "mg">>();
    }
    
    {
        auto w = writer<unit::MilligramPerSecond>();
        w.print<print_unit<unit::MilligramPerSecond, "mg/s">>();
    }
    
    {
        auto w = writer<unit::Millihenry>();
        w.print<print_unit<unit::Millihenry, "mH">>();
    }
    
    {
        auto w = writer<unit::Millihertz>();
        w.print<print_unit<unit::Millihertz, "mHz">>();
    }
    
    {
        auto w = writer<unit::Millijoule>();
        w.print<print_unit<unit::Millijoule, "mJ">>();
    }
    
    {
        auto w = writer<unit::MilliLightSecond>();
        w.print<print_unit<unit::MilliLightSecond, "mls">>();
    }
    
    {
        auto w = writer<unit::Millilitre>();
        w.print<print_unit<unit::Millilitre, "mL">>();
    }
    
    {
        auto w = writer<unit::Millimeter>();
        w.print<print_unit<unit::Millimeter, "mm">>();
    }
    
    {
        auto w = writer<unit::Millimeter²>();
        w.print<print_unit<unit::Millimeter², "mm²">>();
    }
    
    {
        auto w = writer<unit::Millimeter³>();
        w.print<print_unit<unit::Millimeter³, "mm³">>();
    }
    
    {
        auto w = writer<unit::MillimeterPerSecond>();
        w.print<print_unit<unit::MillimeterPerSecond, "mm/s">>();
    }
    
    {
        auto w = writer<unit::MillimeterPerSecond²>();
        w.print<print_unit<unit::MillimeterPerSecond², "mm/s²">>();
    }
    
    {
        auto w = writer<unit::Millisecond>();
        w.print<print_unit<unit::Millisecond, "ms">>();
    }
    
    {
        auto w = writer<unit::Millitesla>();
        w.print<print_unit<unit::Millitesla, "mT">>();
    }
    
    {
        auto w = writer<unit::Millivolt>();
        w.print<print_unit<unit::Millivolt, "mV">>();
    }
    
    {
        auto w = writer<unit::Milliwatt>();
        w.print<print_unit<unit::Milliwatt, "mW">>();
    }
    
    {
        auto w = writer<unit::Minute>();
        w.print<print_unit<unit::Minute, "min">>();
    }
    
    {
        auto w = writer<unit::Mole>();
        w.print<print_unit<unit::Mole, "mol">>();
    }
    
    {
        auto w = writer<unit::Nanoampere>();
        w.print<print_unit<unit::Nanoampere, "nA">>();
    }
    
    {
        auto w = writer<unit::Nanofarad>();
        w.print<print_unit<unit::Nanofarad, "nF">>();
    }
    
    {
        auto w = writer<unit::Nanogram>();
        w.print<print_unit<unit::Nanogram, "ng">>();
    }
    
    {
        auto w = writer<unit::NanogramPerSecond>();
        w.print<print_unit<unit::NanogramPerSecond, "ng/s">>();
    }
    
    {
        auto w = writer<unit::Nanohenry>();
        w.print<print_unit<unit::Nanohenry, "nH">>();
    }
    
    {
        auto w = writer<unit::Nanojoule>();
        w.print<print_unit<unit::Nanojoule, "nJ">>();
    }
    
    {
        auto w = writer<unit::NanoLightSecond>();
        w.print<print_unit<unit::NanoLightSecond, "nls">>();
    }
    
    {
        auto w = writer<unit::Nanometer>();
        w.print<print_unit<unit::Nanometer, "nm">>();
    }
    
    {
        auto w = writer<unit::NanometerPerSecond>();
        w.print<print_unit<unit::NanometerPerSecond, "nm/s">>();
    }
    
    {
        auto w = writer<unit::NanometerPerSecond²>();
        w.print<print_unit<unit::NanometerPerSecond², "nm/s²">>();
    }
    
    {
        auto w = writer<unit::Nanosecond>();
        w.print<print_unit<unit::Nanosecond, "ns">>();
    }
    
    {
        auto w = writer<unit::Nanotesla>();
        w.print<print_unit<unit::Nanotesla, "nT">>();
    }
    
    {
        auto w = writer<unit::Nanovolt>();
        w.print<print_unit<unit::Nanovolt, "nV">>();
    }
    
    {
        auto w = writer<unit::Nanowatt>();
        w.print<print_unit<unit::Nanowatt, "nW">>();
    }
    
    {
        auto w = writer<unit::NauticalMile>();
        w.print<print_unit<unit::NauticalMile, "NM">>();
    }
    
    {
        auto w = writer<unit::Newton>();
        w.print<print_unit<unit::Newton, "N">>();
    }
    
    {
        auto w = writer<unit::NewtonMeter>();
        w.print<print_unit<unit::NewtonMeter, "N*m">>();
    }
    
    {
        auto w = writer<unit::NewtonPerSecond>();
        w.print<print_unit<unit::NewtonPerSecond, "N/s">>();
    }
    
    {
        auto w = writer<unit::NewtonSecond>();
        w.print<print_unit<unit::NewtonSecond, "N*s">>();
    }
    
    {
        auto w = writer<unit::Ohm>();
        w.print<print_unit<unit::Ohm, "Ω">>();
    }
    
    {
        auto w = writer<unit::Pascal>();
        w.print<print_unit<unit::Pascal, "Pa">>();
    }
    
    {
        auto w = writer<unit::Percent>();
        w.print<print_unit<unit::Percent, "%">>();
    }
    
    {
        auto w = writer<unit::PerRadian>();
        w.print<print_unit<unit::PerRadian, "1/rad">>();
    }
    
    {
        auto w = writer<unit::PerMeter>();
        w.print<print_unit<unit::PerMeter, "1/m">>();
    }
    
    {
        auto w = writer<unit::PerMole>();
        w.print<print_unit<unit::PerMole, "1/mol">>();
    }
    
    {
        auto w = writer<unit::Picofarad>();
        w.print<print_unit<unit::Picofarad, "pF">>();
    }
    
    {
        auto w = writer<unit::PicoLightSecond>();
        w.print<print_unit<unit::PicoLightSecond, "pls">>();
    }
    
    {
        auto w = writer<unit::Picometer>();
        w.print<print_unit<unit::Picometer, "pm">>();
    }
    
    {
        auto w = writer<unit::Picosecond>();
        w.print<print_unit<unit::Picosecond, "ps">>();
    }
    
    {
        auto w = writer<unit::Picovolt>();
        w.print<print_unit<unit::Picovolt, "pV">>();
    }
    
    {
        auto w = writer<unit::PoundMass>();
        w.print<print_unit<unit::PoundMass, "lbm">>();
    }
    
    {
        auto w = writer<unit::PoundForce>();
        w.print<print_unit<unit::PoundForce, "lbf">>();
    }
    
    {
        auto w = writer<unit::PoundForcePerSecond>();
        w.print<print_unit<unit::PoundForcePerSecond, "lbf/s">>();
    }
    
    {
        auto w = writer<unit::PoundPerInch²>();
        w.print<print_unit<unit::PoundPerInch², "psi">>();
    }
    
    {
        auto w = writer<unit::PoundPerFoot²>();
        w.print<print_unit<unit::PoundPerFoot², "psf">>();
    }
    
    {
        auto w = writer<unit::Radian>();
        w.print<print_unit<unit::Radian, "rad">>();
    }
    
    {
        auto w = writer<unit::Radian²>();
        w.print<print_unit<unit::Radian², "rad²">>();
    }
    
    {
        auto w = writer<unit::RadianF>();
        w.print<print_unit<unit::RadianF, "rad">>();
    }
    
    {
        auto w = writer<unit::RadianPerMeter>();
        w.print<print_unit<unit::RadianPerMeter, "rad/m">>();
    }
    
    {
        auto w = writer<unit::RadianPerSecond>();
        w.print<print_unit<unit::RadianPerSecond, "rad/s">>();
    }
    
    {
        auto w = writer<unit::RadianPerSecond²>();
        w.print<print_unit<unit::RadianPerSecond², "rad/s²">>();
    }
    
    {
        auto w = writer<unit::Rankine>();
        w.print<print_unit<unit::Rankine, "°R">>();
    }
    
    {
        auto w = writer<unit::RotationsPerMinute>();
        w.print<print_unit<unit::RotationsPerMinute, "rpm">>();
    }
    
    {
        auto w = writer<unit::Second>();
        w.print<print_unit<unit::Second, "s">>();
    }
    
    {
        auto w = writer<unit::Second²>();
        w.print<print_unit<unit::Second², "s²">>();
    }
    
    {
        auto w = writer<unit::ShortTon>();
        w.print<print_unit<unit::ShortTon, "ston">>();
    }
    
    {
        auto w = writer<unit::Siemens>();
        w.print<print_unit<unit::Siemens, "S">>();
    }
    
    {
        auto w = writer<unit::Slug>();
        w.print<print_unit<unit::Slug, "slug">>();
    }
    
    {
        auto w = writer<unit::SlugPerFoot³>();
        w.print<print_unit<unit::SlugPerFoot³, "slug/ft³">>();
    }
    
    {
        auto w = writer<unit::Steradian>();
        w.print<print_unit<unit::Steradian, "sr">>();
    }
    
    {
        auto w = writer<unit::TeraElectronVolt>();
        w.print<print_unit<unit::TeraElectronVolt, "TeV">>();
    }
    
    {
        auto w = writer<unit::Terahertz>();
        w.print<print_unit<unit::Terahertz, "THz">>();
    }
    
    {
        auto w = writer<unit::Terawatt>();
        w.print<print_unit<unit::Terawatt, "TW">>();
    }
    
    {
        auto w = writer<unit::Tesla>();
        w.print<print_unit<unit::Tesla, "T">>();
    }
    
    {
        auto w = writer<unit::Tonne>();
        w.print<print_unit<unit::Tonne, "t">>();
    }
    
    {
        auto w = writer<unit::Volt>();
        w.print<print_unit<unit::Volt, "V">>();
    }
    
    {
        auto w = writer<unit::VoltPerMeter>();
        w.print<print_unit<unit::VoltPerMeter, "V/m">>();
    }
    
    {
        auto w = writer<unit::Watt>();
        w.print<print_unit<unit::Watt, "W">>();
    }
    
    {
        auto w = writer<unit::WattPerMeter²>();
        w.print<print_unit<unit::WattPerMeter², "W/m²">>();
    }
    
    {
        auto w = writer<unit::WattPerMeter²Steradian>();
        w.print<print_unit<unit::WattPerMeter²Steradian, "W/(m²*sr)">>();
    }
    
    {
        auto w = writer<unit::Weber>();
        w.print<print_unit<unit::Weber, "Wb">>();
    }
    
    {
        auto w = writer<unit::Week>();
        w.print<print_unit<unit::Week, "week">>();
    }
    
    {
        auto w = writer<unit::Yard>();
        w.print<print_unit<unit::Yard, "yd">>();
    }
    
    {
        auto w = writer<unit::Yard²>();
        w.print<print_unit<unit::Yard², "yd²">>();
    }

    {
        auto w = writer<unit::Yard³>();
        w.print<print_unit<unit::Yard³, "yd³">>();
    }

}

YQ_INVOKE(reg_units_math();)

#include "unit/MKS.hxx"
#include "unit/SCALED.hxx"
