////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/units.hpp>

#include <yq/strings.hpp>

#include <yq/core/DelayInit.hpp>
#include <yq/core/StreamOps.hpp>
#include <yq/core/StringLiteral.hpp>
#include <yq/meta/Init.hpp>
#include <yq/tensor/Tensor33.hpp>
#include <yq/vector/Vector3.hpp>
#include <yq/text/format.hpp>
#include <yq/text/parse.hpp>

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
YQ_TYPE_IMPLEMENT(yq::unit::Degree3D)
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
    
    template <typename U>
    std::string_view    write_unit(U v)
    {
        return fmt_double(v.value);
    }
    
    template <typename U>
    bool parse_unit(std::string_view str, U& v)
    {
        auto dbl = to_double(str);
        if(!dbl)
            return false;
        v.value = *dbl;
        return true;
    }
}
    
//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

static void reg_units_math () {

    {
        auto w = writer<unit::Acre>();
        w.print<print_unit<unit::Acre, "ac">>();
        w.format<write_unit<unit::Acre>>();
        w.parse<parse_unit<unit::Acre>>();
    }
    
    {
        auto w = writer<unit::Ampere>();
        w.print<print_unit<unit::Ampere, "A">>();
        w.format<write_unit<unit::Ampere>>();
        w.parse<parse_unit<unit::Ampere>>();
    }
    
    {
        auto w = writer<unit::Arcminute>();
        w.print<print_unit<unit::Arcminute, "'">>();
        w.format<write_unit<unit::Arcminute>>();
        w.parse<parse_unit<unit::Arcminute>>();
    }

    {
        auto w = writer<unit::Arcsecond>();
        w.print<print_unit<unit::Arcsecond, "\"">>();
        w.format<write_unit<unit::Arcsecond>>();
        w.parse<parse_unit<unit::Arcsecond>>();
    }
    
    
    {
        auto w = writer<unit::Are>();
        w.print<print_unit<unit::Are, "are">>();
        w.format<write_unit<unit::Are>>();
        w.parse<parse_unit<unit::Are>>();
    }

    {
        auto w = writer<unit::Ångström>();
        w.print<print_unit<unit::Ångström, "Å">>();
        w.format<write_unit<unit::Ångström>>();
        w.parse<parse_unit<unit::Ångström>>();
    }

    {
        auto w = writer<unit::AstronomicalUnit>();
        w.print<print_unit<unit::AstronomicalUnit, "AU">>();
        w.format<write_unit<unit::AstronomicalUnit>>();
        w.parse<parse_unit<unit::AstronomicalUnit>>();
    }

    {
        auto w = writer<unit::Attosecond>();
        w.print<print_unit<unit::Attosecond, "as">>();
        w.format<write_unit<unit::Attosecond>>();
        w.parse<parse_unit<unit::Attosecond>>();
    }

    {
        auto w = writer<unit::Bar>();
        w.print<print_unit<unit::Bar, "bar">>();
        w.format<write_unit<unit::Bar>>();
        w.parse<parse_unit<unit::Bar>>();
    }

    {
        auto w = writer<unit::Barn>();
        w.print<print_unit<unit::Barn, "b">>();
        w.format<write_unit<unit::Barn>>();
        w.parse<parse_unit<unit::Barn>>();
    }

    {
        auto w = writer<unit::Barye>();
        w.print<print_unit<unit::Barye, "Ba">>();
        w.format<write_unit<unit::Barye>>();
        w.parse<parse_unit<unit::Barye>>();
    }

    {
        auto w = writer<unit::BritishThermalUnit>();
        w.print<print_unit<unit::BritishThermalUnit, "BTU">>();
        w.format<write_unit<unit::BritishThermalUnit>>();
        w.parse<parse_unit<unit::BritishThermalUnit>>();
    }

    {
        auto w = writer<unit::Calorie>();
        w.print<print_unit<unit::Calorie, "cal">>();
        w.format<write_unit<unit::Calorie>>();
        w.parse<parse_unit<unit::Calorie>>();
    }

    {
        auto w = writer<unit::Candela>();
        w.print<print_unit<unit::Candela, "cd">>();
        w.format<write_unit<unit::Candela>>();
        w.parse<parse_unit<unit::Candela>>();
    }

    {
        auto w = writer<unit::Centimeter>();
        w.print<print_unit<unit::Centimeter, "cm">>();
        w.format<write_unit<unit::Centimeter>>();
        w.parse<parse_unit<unit::Centimeter>>();
    }

    {
        auto w = writer<unit::Centimeter²>();
        w.print<print_unit<unit::Centimeter², "cm²">>();
        w.format<write_unit<unit::Centimeter²>>();
        w.parse<parse_unit<unit::Centimeter²>>();
    }

    {
        auto w = writer<unit::Centimeter³>();
        w.print<print_unit<unit::Centimeter³, "cc">>();
        w.format<write_unit<unit::Centimeter³>>();
        w.parse<parse_unit<unit::Centimeter³>>();
    }

    {
        auto w = writer<unit::CentimeterPerSecond>();
        w.print<print_unit<unit::CentimeterPerSecond, "cm/s">>();
        w.format<write_unit<unit::CentimeterPerSecond>>();
        w.parse<parse_unit<unit::CentimeterPerSecond>>();
    }
    
    {
        auto w = writer<unit::CentimeterPerSecond²>();
        w.print<print_unit<unit::CentimeterPerSecond², "cm/s²">>();
        w.format<write_unit<unit::CentimeterPerSecond²>>();
        w.parse<parse_unit<unit::CentimeterPerSecond²>>();
    }
    
    {
        auto w = writer<unit::Coulomb>();
        w.print<print_unit<unit::Coulomb, "C">>();
        w.format<write_unit<unit::Coulomb>>();
        w.parse<parse_unit<unit::Coulomb>>();
    }

    {
        auto w = writer<unit::CoulombPerMole>();
        w.print<print_unit<unit::CoulombPerMole, "C/mole">>();
        w.format<write_unit<unit::CoulombPerMole>>();
        w.parse<parse_unit<unit::CoulombPerMole>>();
    }
    
    {
        auto w = writer<unit::Dalton>();
        w.print<print_unit<unit::Dalton, "u">>();
        w.format<write_unit<unit::Dalton>>();
        w.parse<parse_unit<unit::Dalton>>();
    }

    {
        auto w = writer<unit::Day>();
        w.print<print_unit<unit::Day, "d">>();
        w.format<write_unit<unit::Day>>();
        w.parse<parse_unit<unit::Day>>();
    }

    {
        auto w = writer<unit::Decibar>();
        w.print<print_unit<unit::Decibar, "dbar">>();
        w.format<write_unit<unit::Decibar>>();
        w.parse<parse_unit<unit::Decibar>>();
    }
    
    {
        auto w = writer<unit::Degree>();
        w.print<print_unit<unit::Degree, "°">>();
        w.format<write_unit<unit::Degree>>();
        w.parse<parse_unit<unit::Degree>>();
    }
    
    {
        auto w = writer<unit::Degree²>();
        w.print<print_unit<unit::Degree², "°²">>();
        w.format<write_unit<unit::Degree²>>();
        w.parse<parse_unit<unit::Degree²>>();
    }

    {
        auto w = writer<unit::DegreeF>();
        w.print<print_unit<unit::DegreeF, "°">>();
        w.format<write_unit<unit::DegreeF>>();
        w.parse<parse_unit<unit::DegreeF>>();
    }

    {
        auto w = writer<unit::DegreePerFoot>();
        w.print<print_unit<unit::DegreePerFoot, "°/ft">>();
        w.format<write_unit<unit::DegreePerFoot>>();
        w.parse<parse_unit<unit::DegreePerFoot>>();
    }
    
    {
        auto w = writer<unit::DegreePerMeter>();
        w.print<print_unit<unit::DegreePerMeter, "°/m">>();
        w.format<write_unit<unit::DegreePerMeter>>();
        w.parse<parse_unit<unit::DegreePerMeter>>();
    }
    
    {
        auto w = writer<unit::DegreePerMinute>();
        w.print<print_unit<unit::DegreePerMinute, "°/min">>();
        w.format<write_unit<unit::DegreePerMinute>>();
        w.parse<parse_unit<unit::DegreePerMinute>>();
    }

    {
        auto w = writer<unit::DegreePerSecond>();
        w.print<print_unit<unit::DegreePerSecond, "°/s">>();
        w.format<write_unit<unit::DegreePerSecond>>();
        w.parse<parse_unit<unit::DegreePerSecond>>();
    }
    
    {
        auto w = writer<unit::DegreePerSecond²>();
        w.print<print_unit<unit::DegreePerSecond², "°/s²">>();
        w.format<write_unit<unit::DegreePerSecond²>>();
        w.parse<parse_unit<unit::DegreePerSecond²>>();
    }

    {
        auto w = writer<unit::Dioptre>();
        w.print<print_unit<unit::Dioptre, "dpt">>();
        w.format<write_unit<unit::Dioptre>>();
        w.parse<parse_unit<unit::Dioptre>>();
    }

    {
        auto w = writer<unit::Dyne>();
        w.print<print_unit<unit::Dyne, "dyn">>();
        w.format<write_unit<unit::Dyne>>();
        w.parse<parse_unit<unit::Dyne>>();
    }

    {
        auto w = writer<unit::ElectronVolt>();
        w.print<print_unit<unit::ElectronVolt, "eV">>();
        w.format<write_unit<unit::ElectronVolt>>();
        w.parse<parse_unit<unit::ElectronVolt>>();
    }

    {
        auto w = writer<unit::Erg>();
        w.print<print_unit<unit::Erg, "erg">>();
        w.format<write_unit<unit::Erg>>();
        w.parse<parse_unit<unit::Erg>>();
    }

    {
        auto w = writer<unit::ErgPerSecond>();
        w.print<print_unit<unit::ErgPerSecond, "erg/s">>();
        w.format<write_unit<unit::ErgPerSecond>>();
        w.parse<parse_unit<unit::ErgPerSecond>>();
    }

    {
        auto w = writer<unit::Farad>();
        w.print<print_unit<unit::Farad, "F">>();
        w.format<write_unit<unit::Farad>>();
        w.parse<parse_unit<unit::Farad>>();
    }

    {
        auto w = writer<unit::FaradPerMeter>();
        w.print<print_unit<unit::FaradPerMeter, "F/m">>();
        w.format<write_unit<unit::FaradPerMeter>>();
        w.parse<parse_unit<unit::FaradPerMeter>>();
    }

    {
        auto w = writer<unit::Fathom>();
        w.print<print_unit<unit::Fathom, "fathom">>();
        w.format<write_unit<unit::Fathom>>();
        w.parse<parse_unit<unit::Fathom>>();
    }

    {
        auto w = writer<unit::Femtometer>();
        w.print<print_unit<unit::Femtometer, "fm">>();
        w.format<write_unit<unit::Femtometer>>();
        w.parse<parse_unit<unit::Femtometer>>();
    }

    {
        auto w = writer<unit::Femtosecond>();
        w.print<print_unit<unit::Femtosecond, "fs">>();
        w.format<write_unit<unit::Femtosecond>>();
        w.parse<parse_unit<unit::Femtosecond>>();
    }

    {
        auto w = writer<unit::Foot>();
        w.print<print_unit<unit::Foot, "ft">>();
        w.format<write_unit<unit::Foot>>();
        w.parse<parse_unit<unit::Foot>>();
    }

    {
        auto w = writer<unit::Foot²>();
        w.print<print_unit<unit::Foot², "ft²">>();
        w.format<write_unit<unit::Foot²>>();
        w.parse<parse_unit<unit::Foot²>>();
    }

    {
        auto w = writer<unit::Foot³>();
        w.print<print_unit<unit::Foot³, "ft³">>();
        w.format<write_unit<unit::Foot³>>();
        w.parse<parse_unit<unit::Foot³>>();
    }

    {
        auto w = writer<unit::FootF>();
        w.print<print_unit<unit::FootF, "ft">>();
        w.format<write_unit<unit::FootF>>();
        w.parse<parse_unit<unit::FootF>>();
    }

    {
        auto w = writer<unit::FootPerDegree>();
        w.print<print_unit<unit::FootPerDegree, "ft/°">>();
        w.format<write_unit<unit::FootPerDegree>>();
        w.parse<parse_unit<unit::FootPerDegree>>();
    }

    {
        auto w = writer<unit::FootPerRadian>();
        w.print<print_unit<unit::FootPerRadian, "ft/rad">>();
        w.format<write_unit<unit::FootPerRadian>>();
        w.parse<parse_unit<unit::FootPerRadian>>();
    }

    {
        auto w = writer<unit::FootPerSecond>();
        w.print<print_unit<unit::FootPerSecond, "ft/s">>();
        w.format<write_unit<unit::FootPerSecond>>();
        w.parse<parse_unit<unit::FootPerSecond>>();
    }

    {
        auto w = writer<unit::FootPerSecond²>();
        w.print<print_unit<unit::FootPerSecond², "ft/s²">>();
        w.format<write_unit<unit::FootPerSecond²>>();
        w.parse<parse_unit<unit::FootPerSecond²>>();
    }

    {
        auto w = writer<unit::FootPound>();
        w.print<print_unit<unit::FootPound, "lbf*ft">>();
        w.format<write_unit<unit::FootPound>>();
        w.parse<parse_unit<unit::FootPound>>();
    }

    {
        auto w = writer<unit::Fortnight>();
        w.print<print_unit<unit::Fortnight, "fortnight">>();
        w.format<write_unit<unit::Fortnight>>();
        w.parse<parse_unit<unit::Fortnight>>();
    }

    {
        auto w = writer<unit::Furlong>();
        w.print<print_unit<unit::Furlong, "furlong">>();
        w.format<write_unit<unit::Furlong>>();
        w.parse<parse_unit<unit::Furlong>>();
    }

    {
        auto w = writer<unit::FurlongPerFortnight>();
        w.print<print_unit<unit::FurlongPerFortnight, "furlong/fortnight">>();
        w.format<write_unit<unit::FurlongPerFortnight>>();
        w.parse<parse_unit<unit::FurlongPerFortnight>>();
    }

    {
        auto w = writer<unit::Gallon>();
        w.print<print_unit<unit::Gallon, "gal">>();
        w.format<write_unit<unit::Gallon>>();
        w.parse<parse_unit<unit::Gallon>>();
    }

    {
        auto w = writer<unit::GallonPerMinute>();
        w.print<print_unit<unit::GallonPerMinute, "gpm">>();
        w.format<write_unit<unit::GallonPerMinute>>();
        w.parse<parse_unit<unit::GallonPerMinute>>();
    }

    {
        auto w = writer<unit::GigaElectronVolt>();
        w.print<print_unit<unit::GigaElectronVolt, "GeV">>();
        w.format<write_unit<unit::GigaElectronVolt>>();
        w.parse<parse_unit<unit::GigaElectronVolt>>();
    }

    {
        auto w = writer<unit::Gigahertz>();
        w.print<print_unit<unit::Gigahertz, "GHz">>();
        w.format<write_unit<unit::Gigahertz>>();
        w.parse<parse_unit<unit::Gigahertz>>();
    }

    {
        auto w = writer<unit::Gigajoule>();
        w.print<print_unit<unit::Gigajoule, "GJ">>();
        w.format<write_unit<unit::Gigajoule>>();
        w.parse<parse_unit<unit::Gigajoule>>();
    }

    {
        auto w = writer<unit::Gigapascal>();
        w.print<print_unit<unit::Gigapascal, "GPa">>();
        w.format<write_unit<unit::Gigapascal>>();
        w.parse<parse_unit<unit::Gigapascal>>();
    }

    {
        auto w = writer<unit::Gigawatt>();
        w.print<print_unit<unit::Gigawatt, "GW">>();
        w.format<write_unit<unit::Gigawatt>>();
        w.parse<parse_unit<unit::Gigawatt>>();
    }

    {
        auto w = writer<unit::Gradian>();
        w.print<print_unit<unit::Gradian, "grad">>();
        w.format<write_unit<unit::Gradian>>();
        w.parse<parse_unit<unit::Gradian>>();
    }

    {
        auto w = writer<unit::Gram>();
        w.print<print_unit<unit::Gram, "g">>();
        w.format<write_unit<unit::Gram>>();
        w.parse<parse_unit<unit::Gram>>();
    }

    {
        auto w = writer<unit::GramPerCentimeter³>();
        w.print<print_unit<unit::GramPerCentimeter³, "g/cc">>();
        w.format<write_unit<unit::GramPerCentimeter³>>();
        w.parse<parse_unit<unit::GramPerCentimeter³>>();
    }

    {
        auto w = writer<unit::GramPerSecond>();
        w.print<print_unit<unit::GramPerSecond, "g/s">>();
        w.format<write_unit<unit::GramPerSecond>>();
        w.parse<parse_unit<unit::GramPerSecond>>();
    }

    {
        auto w = writer<unit::GramPerMole>();
        w.print<print_unit<unit::GramPerMole, "g/mol">>();
        w.format<write_unit<unit::GramPerMole>>();
        w.parse<parse_unit<unit::GramPerMole>>();
    }

    {
        auto w = writer<unit::Gravity>();
        w.print<print_unit<unit::Gravity, "G">>();
        w.format<write_unit<unit::Gravity>>();
        w.parse<parse_unit<unit::Gravity>>();
    }

    {
        auto w = writer<unit::Hectare>();
        w.print<print_unit<unit::Hectare, "ha">>();
        w.format<write_unit<unit::Hectare>>();
        w.parse<parse_unit<unit::Hectare>>();
    }

    {
        auto w = writer<unit::Henry>();
        w.print<print_unit<unit::Henry, "H">>();
        w.format<write_unit<unit::Henry>>();
        w.parse<parse_unit<unit::Henry>>();
    }

    {
        auto w = writer<unit::HenryPerMeter>();
        w.print<print_unit<unit::HenryPerMeter, "H/m">>();
        w.format<write_unit<unit::HenryPerMeter>>();
        w.parse<parse_unit<unit::HenryPerMeter>>();
    }

    {
        auto w = writer<unit::Hertz>();
        w.print<print_unit<unit::Hertz, "Hz">>();
        w.format<write_unit<unit::Hertz>>();
        w.parse<parse_unit<unit::Hertz>>();
    }

    {
        auto w = writer<unit::HertzPerSecond>();
        w.print<print_unit<unit::HertzPerSecond, "Hz/s">>();
        w.format<write_unit<unit::HertzPerSecond>>();
        w.parse<parse_unit<unit::HertzPerSecond>>();
    }

    {
        auto w = writer<unit::Horsepower>();
        w.print<print_unit<unit::Horsepower, "hp">>();
        w.format<write_unit<unit::Horsepower>>();
        w.parse<parse_unit<unit::Horsepower>>();
    }

    {
        auto w = writer<unit::Hour>();
        w.print<print_unit<unit::Hour, "h">>();
        w.format<write_unit<unit::Hour>>();
        w.parse<parse_unit<unit::Hour>>();
    }

    {
        auto w = writer<unit::Inch>();
        w.print<print_unit<unit::Inch, "in">>();
        w.format<write_unit<unit::Inch>>();
        w.parse<parse_unit<unit::Inch>>();
    }

    {
        auto w = writer<unit::Inch²>();
        w.print<print_unit<unit::Inch², "in²">>();
        w.format<write_unit<unit::Inch²>>();
        w.parse<parse_unit<unit::Inch²>>();
    }

    {
        auto w = writer<unit::Inch³>();
        w.print<print_unit<unit::Inch³, "in³">>();
        w.format<write_unit<unit::Inch³>>();
        w.parse<parse_unit<unit::Inch³>>();
    }

    {
        auto w = writer<unit::Joule>();
        w.print<print_unit<unit::Joule, "J">>();
        w.format<write_unit<unit::Joule>>();
        w.parse<parse_unit<unit::Joule>>();
    }

    {
        auto w = writer<unit::JoulePerKelvin>();
        w.print<print_unit<unit::JoulePerKelvin, "J/K">>();
        w.format<write_unit<unit::JoulePerKelvin>>();
        w.parse<parse_unit<unit::JoulePerKelvin>>();
    }

    {
        auto w = writer<unit::JoulePerKilogram>();
        w.print<print_unit<unit::JoulePerKilogram, "J/kg">>();
        w.format<write_unit<unit::JoulePerKilogram>>();
        w.parse<parse_unit<unit::JoulePerKilogram>>();
    }

    {
        auto w = writer<unit::JoulePerKilogramKelvin>();
        w.print<print_unit<unit::JoulePerKilogramKelvin, "J/(kg*K)">>();
        w.format<write_unit<unit::JoulePerKilogramKelvin>>();
        w.parse<parse_unit<unit::JoulePerKilogramKelvin>>();
    }

    {
        auto w = writer<unit::JoulePerMole>();
        w.print<print_unit<unit::JoulePerMole, "J/mol">>();
        w.format<write_unit<unit::JoulePerMole>>();
        w.parse<parse_unit<unit::JoulePerMole>>();
    }

    {
        auto w = writer<unit::JoulePerMeter³>();
        w.print<print_unit<unit::JoulePerMeter³, "J/m³">>();
        w.format<write_unit<unit::JoulePerMeter³>>();
        w.parse<parse_unit<unit::JoulePerMeter³>>();
    }

    {
        auto w = writer<unit::Katal>();
        w.print<print_unit<unit::Katal, "kat">>();
        w.format<write_unit<unit::Katal>>();
        w.parse<parse_unit<unit::Katal>>();
    }

    {
        auto w = writer<unit::Kelvin>();
        w.print<print_unit<unit::Kelvin, "K">>();
        w.format<write_unit<unit::Kelvin>>();
        w.parse<parse_unit<unit::Kelvin>>();
    }

    {
        auto w = writer<unit::KelvinPerMeter>();
        w.print<print_unit<unit::KelvinPerMeter, "K/m">>();
        w.format<write_unit<unit::KelvinPerMeter>>();
        w.parse<parse_unit<unit::KelvinPerMeter>>();
    }
    
    {
        auto w = writer<unit::KelvinPerSecond>();
        w.print<print_unit<unit::KelvinPerSecond, "K/s">>();
        w.format<write_unit<unit::KelvinPerSecond>>();
        w.parse<parse_unit<unit::KelvinPerSecond>>();
    }
    
    {
        auto w = writer<unit::Kiloampere>();
        w.print<print_unit<unit::Kiloampere, "kA">>();
        w.format<write_unit<unit::Kiloampere>>();
        w.parse<parse_unit<unit::Kiloampere>>();
    }
    
    {
        auto w = writer<unit::Kilocalorie>();
        w.print<print_unit<unit::Kilocalorie, "kcal">>();
        w.format<write_unit<unit::Kilocalorie>>();
        w.parse<parse_unit<unit::Kilocalorie>>();
    }
    
    {
        auto w = writer<unit::KiloElectronVolt>();
        w.print<print_unit<unit::KiloElectronVolt, "keV">>();
        w.format<write_unit<unit::KiloElectronVolt>>();
        w.parse<parse_unit<unit::KiloElectronVolt>>();
    }
    
    {
        auto w = writer<unit::Kilofoot>();
        w.print<print_unit<unit::Kilofoot, "kft">>();
        w.format<write_unit<unit::Kilofoot>>();
        w.parse<parse_unit<unit::Kilofoot>>();
    }
    
    {
        auto w = writer<unit::Kilogram>();
        w.print<print_unit<unit::Kilogram, "kg">>();
        w.format<write_unit<unit::Kilogram>>();
        w.parse<parse_unit<unit::Kilogram>>();
    }
    
    {
        auto w = writer<unit::KilogramMeterPerSecond>();
        w.print<print_unit<unit::KilogramMeterPerSecond, "kg*m/s">>();
        w.format<write_unit<unit::KilogramMeterPerSecond>>();
        w.parse<parse_unit<unit::KilogramMeterPerSecond>>();
    }
    
    {
        auto w = writer<unit::KilogramPerMeter>();
        w.print<print_unit<unit::KilogramPerMeter, "kg/m">>();
        w.format<write_unit<unit::KilogramPerMeter>>();
        w.parse<parse_unit<unit::KilogramPerMeter>>();
    }
    
    {
        auto w = writer<unit::KilogramPerMeter²>();
        w.print<print_unit<unit::KilogramPerMeter², "kg/m²">>();
        w.format<write_unit<unit::KilogramPerMeter²>>();
        w.parse<parse_unit<unit::KilogramPerMeter²>>();
    }
    
    {
        auto w = writer<unit::KilogramPerMeter³>();
        w.print<print_unit<unit::KilogramPerMeter³, "kg/m³">>();
        w.format<write_unit<unit::KilogramPerMeter³>>();
        w.parse<parse_unit<unit::KilogramPerMeter³>>();
    }
    
    {
        auto w = writer<unit::KilogramPerMole>();
        w.print<print_unit<unit::KilogramPerMole, "kg/mole">>();
        w.format<write_unit<unit::KilogramPerMole>>();
        w.parse<parse_unit<unit::KilogramPerMole>>();
    }
    
    {
        auto w = writer<unit::KilogramPerSecond>();
        w.print<print_unit<unit::KilogramPerSecond, "kg/s">>();
        w.format<write_unit<unit::KilogramPerSecond>>();
        w.parse<parse_unit<unit::KilogramPerSecond>>();
    }
    
    {
        auto w = writer<unit::KilogramPerSecond²>();
        w.print<print_unit<unit::KilogramPerSecond², "kg/s²">>();
        w.format<write_unit<unit::KilogramPerSecond²>>();
        w.parse<parse_unit<unit::KilogramPerSecond²>>();
    }
    
    {
        auto w = writer<unit::Kilohertz>();
        w.print<print_unit<unit::Kilohertz, "kHz">>();
        w.format<write_unit<unit::Kilohertz>>();
        w.parse<parse_unit<unit::Kilohertz>>();
    }
    
    {
        auto w = writer<unit::Kilojoule>();
        w.print<print_unit<unit::Kilojoule, "kJ">>();
        w.format<write_unit<unit::Kilojoule>>();
        w.parse<parse_unit<unit::Kilojoule>>();
    }
    
    {
        auto w = writer<unit::KiloLightYear>();
        w.print<print_unit<unit::KiloLightYear, "kly">>();
        w.format<write_unit<unit::KiloLightYear>>();
        w.parse<parse_unit<unit::KiloLightYear>>();
    }
    
    {
        auto w = writer<unit::Kilolitre>();
        w.print<print_unit<unit::Kilolitre, "kL">>();
        w.format<write_unit<unit::Kilolitre>>();
        w.parse<parse_unit<unit::Kilolitre>>();
    }
    
    {
        auto w = writer<unit::Kilometer>();
        w.print<print_unit<unit::Kilometer, "km">>();
        w.format<write_unit<unit::Kilometer>>();
        w.parse<parse_unit<unit::Kilometer>>();
    }
    
    {
        auto w = writer<unit::Kilometer²>();
        w.print<print_unit<unit::Kilometer², "km²">>();
        w.format<write_unit<unit::Kilometer²>>();
        w.parse<parse_unit<unit::Kilometer²>>();
    }
    
    {
        auto w = writer<unit::Kilometer³>();
        w.print<print_unit<unit::Kilometer³, "km³">>();
        w.format<write_unit<unit::Kilometer³>>();
        w.parse<parse_unit<unit::Kilometer³>>();
    }
    
    {
        auto w = writer<unit::KilometerPerHour>();
        w.print<print_unit<unit::KilometerPerHour, "kph">>();
        w.format<write_unit<unit::KilometerPerHour>>();
        w.parse<parse_unit<unit::KilometerPerHour>>();
    }
    
    {
        auto w = writer<unit::KilometerPerSecond>();
        w.print<print_unit<unit::KilometerPerSecond, "km/s">>();
        w.format<write_unit<unit::KilometerPerSecond>>();
        w.parse<parse_unit<unit::KilometerPerSecond>>();
    }
    
    {
        auto w = writer<unit::KilometerPerSecond²>();
        w.print<print_unit<unit::KilometerPerSecond², "km/s²">>();
        w.format<write_unit<unit::KilometerPerSecond²>>();
        w.parse<parse_unit<unit::KilometerPerSecond²>>();
    }
    
    {
        auto w = writer<unit::Kilomole>();
        w.print<print_unit<unit::Kilomole, "kmol">>();
        w.format<write_unit<unit::Kilomole>>();
        w.parse<parse_unit<unit::Kilomole>>();
    }
    
    {
        auto w = writer<unit::Kilonewton>();
        w.print<print_unit<unit::Kilonewton, "kN">>();
        w.format<write_unit<unit::Kilonewton>>();
        w.parse<parse_unit<unit::Kilonewton>>();
    }
    
    {
        auto w = writer<unit::Kiloohm>();
        w.print<print_unit<unit::Kiloohm, "kΩ">>();
        w.format<write_unit<unit::Kiloohm>>();
        w.parse<parse_unit<unit::Kiloohm>>();
    }
    
    {
        auto w = writer<unit::Kilopascal>();
        w.print<print_unit<unit::Kilopascal, "kPa">>();
        w.format<write_unit<unit::Kilopascal>>();
        w.parse<parse_unit<unit::Kilopascal>>();
    }
    
    {
        auto w = writer<unit::Kilovolt>();
        w.print<print_unit<unit::Kilovolt, "kV">>();
        w.format<write_unit<unit::Kilovolt>>();
        w.parse<parse_unit<unit::Kilovolt>>();
    }
    
    {
        auto w = writer<unit::Kilowatt>();
        w.print<print_unit<unit::Kilowatt, "kW">>();
        w.format<write_unit<unit::Kilowatt>>();
        w.parse<parse_unit<unit::Kilowatt>>();
    }
    
    {
        auto w = writer<unit::KilowattHour>();
        w.print<print_unit<unit::KilowattHour, "kWh">>();
        w.format<write_unit<unit::KilowattHour>>();
        w.parse<parse_unit<unit::KilowattHour>>();
    }
    
    {
        auto w = writer<unit::Knot>();
        w.print<print_unit<unit::Knot, "kt">>();
        w.format<write_unit<unit::Knot>>();
        w.parse<parse_unit<unit::Knot>>();
    }
    
    {
        auto w = writer<unit::LightHour>();
        w.print<print_unit<unit::LightHour, "lh">>();
        w.format<write_unit<unit::LightHour>>();
        w.parse<parse_unit<unit::LightHour>>();
    }
    
    {
        auto w = writer<unit::LightMinute>();
        w.print<print_unit<unit::LightMinute, "lmin">>();
        w.format<write_unit<unit::LightMinute>>();
        w.parse<parse_unit<unit::LightMinute>>();
    }
    
    {
        auto w = writer<unit::LightSecond>();
        w.print<print_unit<unit::LightSecond, "ls">>();
        w.format<write_unit<unit::LightSecond>>();
        w.parse<parse_unit<unit::LightSecond>>();
    }
    
    {
        auto w = writer<unit::LightSpeed>();
        w.print<print_unit<unit::LightSpeed, "c">>();
        w.format<write_unit<unit::LightSpeed>>();
        w.parse<parse_unit<unit::LightSpeed>>();
    }
    
    {
        auto w = writer<unit::LightYear>();
        w.print<print_unit<unit::LightYear, "ly">>();
        w.format<write_unit<unit::LightYear>>();
        w.parse<parse_unit<unit::LightYear>>();
    }
    
    {
        auto w = writer<unit::Litre>();
        w.print<print_unit<unit::Litre, "L">>();
        w.format<write_unit<unit::Litre>>();
        w.parse<parse_unit<unit::Litre>>();
    }
    
    {
        auto w = writer<unit::LongTon>();
        w.print<print_unit<unit::LongTon, "lton">>();
        w.format<write_unit<unit::LongTon>>();
        w.parse<parse_unit<unit::LongTon>>();
    }
    
    {
        auto w = writer<unit::Lumen>();
        w.print<print_unit<unit::Lumen, "lm">>();
        w.format<write_unit<unit::Lumen>>();
        w.parse<parse_unit<unit::Lumen>>();
    }
    
    {
        auto w = writer<unit::Lux>();
        w.print<print_unit<unit::Lux, "lx">>();
        w.format<write_unit<unit::Lux>>();
        w.parse<parse_unit<unit::Lux>>();
    }
    
    {
        auto w = writer<unit::Megaampere>();
        w.print<print_unit<unit::Megaampere, "MA">>();
        w.format<write_unit<unit::Megaampere>>();
        w.parse<parse_unit<unit::Megaampere>>();
    }
    
    {
        auto w = writer<unit::MegaElectronVolt>();
        w.print<print_unit<unit::MegaElectronVolt, "MeV">>();
        w.format<write_unit<unit::MegaElectronVolt>>();
        w.parse<parse_unit<unit::MegaElectronVolt>>();
    }
    
    {
        auto w = writer<unit::Megahertz>();
        w.print<print_unit<unit::Megahertz, "MHz">>();
        w.format<write_unit<unit::Megahertz>>();
        w.parse<parse_unit<unit::Megahertz>>();
    }
    
    {
        auto w = writer<unit::Megajoule>();
        w.print<print_unit<unit::Megajoule, "MJ">>();
        w.format<write_unit<unit::Megajoule>>();
        w.parse<parse_unit<unit::Megajoule>>();
    }
    
    {
        auto w = writer<unit::MegaLightYear>();
        w.print<print_unit<unit::MegaLightYear, "Mly">>();
        w.format<write_unit<unit::MegaLightYear>>();
        w.parse<parse_unit<unit::MegaLightYear>>();
    }
    
    {
        auto w = writer<unit::Meganewton>();
        w.print<print_unit<unit::Meganewton, "MN">>();
        w.format<write_unit<unit::Meganewton>>();
        w.parse<parse_unit<unit::Meganewton>>();
    }
    
    {
        auto w = writer<unit::Megaohm>();
        w.print<print_unit<unit::Megaohm, "MΩ">>();
        w.format<write_unit<unit::Megaohm>>();
        w.parse<parse_unit<unit::Megaohm>>();
    }
    
    {
        auto w = writer<unit::Megapascal>();
        w.print<print_unit<unit::Megapascal, "MPa">>();
        w.format<write_unit<unit::Megapascal>>();
        w.parse<parse_unit<unit::Megapascal>>();
    }
    
    {
        auto w = writer<unit::Megavolt>();
        w.print<print_unit<unit::Megavolt, "MV">>();
        w.format<write_unit<unit::Megavolt>>();
        w.parse<parse_unit<unit::Megavolt>>();
    }
    
    {
        auto w = writer<unit::Megawatt>();
        w.print<print_unit<unit::Megawatt, "MW">>();
        w.format<write_unit<unit::Megawatt>>();
        w.parse<parse_unit<unit::Megawatt>>();
    }
    
    {
        auto w = writer<unit::Meter>();
        w.print<print_unit<unit::Meter, "m">>();
        w.format<write_unit<unit::Meter>>();
        w.parse<parse_unit<unit::Meter>>();
    }
    
    {
        auto w = writer<unit::Meter²>();
        w.print<print_unit<unit::Meter², "m²">>();
        w.format<write_unit<unit::Meter²>>();
        w.parse<parse_unit<unit::Meter²>>();
    }
    
    {
        auto w = writer<unit::Meter²PerSecond>();
        w.print<print_unit<unit::Meter²PerSecond, "m²/s">>();
        w.format<write_unit<unit::Meter²PerSecond>>();
        w.parse<parse_unit<unit::Meter²PerSecond>>();
    }
    
    {
        auto w = writer<unit::Meter²PerSecond²>();
        w.print<print_unit<unit::Meter²PerSecond², "m²/s²">>();
        w.format<write_unit<unit::Meter²PerSecond²>>();
        w.parse<parse_unit<unit::Meter²PerSecond²>>();
    }
    
    {
        auto w = writer<unit::Meter³>();
        w.print<print_unit<unit::Meter³, "m³">>();
        w.format<write_unit<unit::Meter³>>();
        w.parse<parse_unit<unit::Meter³>>();
    }
    
    {
        auto w = writer<unit::Meter³PerKilogram>();
        w.print<print_unit<unit::Meter³PerKilogram, "m³/kg">>();
        w.format<write_unit<unit::Meter³PerKilogram>>();
        w.parse<parse_unit<unit::Meter³PerKilogram>>();
    }
    
    {
        auto w = writer<unit::Meter³PerSecond>();
        w.print<print_unit<unit::Meter³PerSecond, "m³/s">>();
        w.format<write_unit<unit::Meter³PerSecond>>();
        w.parse<parse_unit<unit::Meter³PerSecond>>();
    }
    
    {
        auto w = writer<unit::Meter³PerSecond²>();
        w.print<print_unit<unit::Meter³PerSecond², "m³/s²">>();
        w.format<write_unit<unit::Meter³PerSecond²>>();
        w.parse<parse_unit<unit::Meter³PerSecond²>>();
    }
    
    {
        auto w = writer<unit::Microampere>();
        w.print<print_unit<unit::Microampere, "μA">>();
        w.format<write_unit<unit::Microampere>>();
        w.parse<parse_unit<unit::Microampere>>();
    }
    
    {
        auto w = writer<unit::MicroArcsecond>();
        w.print<print_unit<unit::MicroArcsecond, "μas">>();
        w.format<write_unit<unit::MicroArcsecond>>();
        w.parse<parse_unit<unit::MicroArcsecond>>();
    }
    
    {
        auto w = writer<unit::Microfarad>();
        w.print<print_unit<unit::Microfarad, "μF">>();
        w.format<write_unit<unit::Microfarad>>();
        w.parse<parse_unit<unit::Microfarad>>();
    }
    
    {
        auto w = writer<unit::Microgram>();
        w.print<print_unit<unit::Microgram, "μg">>();
        w.format<write_unit<unit::Microgram>>();
        w.parse<parse_unit<unit::Microgram>>();
    }
    
    {
        auto w = writer<unit::MicrogramPerSecond>();
        w.print<print_unit<unit::MicrogramPerSecond, "μg/s">>();
        w.format<write_unit<unit::MicrogramPerSecond>>();
        w.parse<parse_unit<unit::MicrogramPerSecond>>();
    }
    
    {
        auto w = writer<unit::Microhenry>();
        w.print<print_unit<unit::Microhenry, "μH">>();
        w.format<write_unit<unit::Microhenry>>();
        w.parse<parse_unit<unit::Microhenry>>();
    }
    
    {
        auto w = writer<unit::Microjoule>();
        w.print<print_unit<unit::Microjoule, "μJ">>();
        w.format<write_unit<unit::Microjoule>>();
        w.parse<parse_unit<unit::Microjoule>>();
    }
    
    {
        auto w = writer<unit::MicroLightSecond>();
        w.print<print_unit<unit::MicroLightSecond, "μls">>();
        w.format<write_unit<unit::MicroLightSecond>>();
        w.parse<parse_unit<unit::MicroLightSecond>>();
    }
    
    {
        auto w = writer<unit::Microlitre>();
        w.print<print_unit<unit::Microlitre, "μL">>();
        w.format<write_unit<unit::Microlitre>>();
        w.parse<parse_unit<unit::Microlitre>>();
    }
    
    {
        auto w = writer<unit::Micrometer>();
        w.print<print_unit<unit::Micrometer, "μm">>();
        w.format<write_unit<unit::Micrometer>>();
        w.parse<parse_unit<unit::Micrometer>>();
    }
    
    {
        auto w = writer<unit::MicrometerPerSecond>();
        w.print<print_unit<unit::MicrometerPerSecond, "μm/s">>();
        w.format<write_unit<unit::MicrometerPerSecond>>();
        w.parse<parse_unit<unit::MicrometerPerSecond>>();
    }
    
    {
        auto w = writer<unit::MicrometerPerSecond²>();
        w.print<print_unit<unit::MicrometerPerSecond², "μm/s²">>();
        w.format<write_unit<unit::MicrometerPerSecond²>>();
        w.parse<parse_unit<unit::MicrometerPerSecond²>>();
    }
    
    {
        auto w = writer<unit::Micronewton>();
        w.print<print_unit<unit::Micronewton, "μN">>();
        w.format<write_unit<unit::Micronewton>>();
        w.parse<parse_unit<unit::Micronewton>>();
    }
    
    {
        auto w = writer<unit::Micropascal>();
        w.print<print_unit<unit::Micropascal, "μPa">>();
        w.format<write_unit<unit::Micropascal>>();
        w.parse<parse_unit<unit::Micropascal>>();
    }
    
    {
        auto w = writer<unit::Microsecond>();
        w.print<print_unit<unit::Microsecond, "μs">>();
        w.format<write_unit<unit::Microsecond>>();
        w.parse<parse_unit<unit::Microsecond>>();
    }
    
    {
        auto w = writer<unit::Microtesla>();
        w.print<print_unit<unit::Microtesla, "μT">>();
        w.format<write_unit<unit::Microtesla>>();
        w.parse<parse_unit<unit::Microtesla>>();
    }
    
    {
        auto w = writer<unit::Microvolt>();
        w.print<print_unit<unit::Microvolt, "μV">>();
        w.format<write_unit<unit::Microvolt>>();
        w.parse<parse_unit<unit::Microvolt>>();
    }
    
    {
        auto w = writer<unit::Microwatt>();
        w.print<print_unit<unit::Microwatt, "μW">>();
        w.format<write_unit<unit::Microwatt>>();
        w.parse<parse_unit<unit::Microwatt>>();
    }
    
    {
        auto w = writer<unit::Mile>();
        w.print<print_unit<unit::Mile, "mi">>();
        w.format<write_unit<unit::Mile>>();
        w.parse<parse_unit<unit::Mile>>();
    }
    
    {
        auto w = writer<unit::MilePerHour>();
        w.print<print_unit<unit::MilePerHour, "mph">>();
        w.format<write_unit<unit::MilePerHour>>();
        w.parse<parse_unit<unit::MilePerHour>>();
    }
    
    {
        auto w = writer<unit::Milliampere>();
        w.print<print_unit<unit::Milliampere, "mA">>();
        w.format<write_unit<unit::Milliampere>>();
        w.parse<parse_unit<unit::Milliampere>>();
    }
    
    {
        auto w = writer<unit::MilliArcsecond>();
        w.print<print_unit<unit::MilliArcsecond, "mas">>();
        w.format<write_unit<unit::MilliArcsecond>>();
        w.parse<parse_unit<unit::MilliArcsecond>>();
    }
    
    {
        auto w = writer<unit::Millibar>();
        w.print<print_unit<unit::Millibar, "mbar">>();
        w.format<write_unit<unit::Millibar>>();
        w.parse<parse_unit<unit::Millibar>>();
    }
    
    {
        auto w = writer<unit::Millifarad>();
        w.print<print_unit<unit::Millifarad, "mF">>();
        w.format<write_unit<unit::Millifarad>>();
        w.parse<parse_unit<unit::Millifarad>>();
    }
    
    {
        auto w = writer<unit::Milligram>();
        w.print<print_unit<unit::Milligram, "mg">>();
        w.format<write_unit<unit::Milligram>>();
        w.parse<parse_unit<unit::Milligram>>();
    }
    
    {
        auto w = writer<unit::MilligramPerSecond>();
        w.print<print_unit<unit::MilligramPerSecond, "mg/s">>();
        w.format<write_unit<unit::MilligramPerSecond>>();
        w.parse<parse_unit<unit::MilligramPerSecond>>();
    }
    
    {
        auto w = writer<unit::Millihenry>();
        w.print<print_unit<unit::Millihenry, "mH">>();
        w.format<write_unit<unit::Millihenry>>();
        w.parse<parse_unit<unit::Millihenry>>();
    }
    
    {
        auto w = writer<unit::Millihertz>();
        w.print<print_unit<unit::Millihertz, "mHz">>();
        w.format<write_unit<unit::Millihertz>>();
        w.parse<parse_unit<unit::Millihertz>>();
    }
    
    {
        auto w = writer<unit::Millijoule>();
        w.print<print_unit<unit::Millijoule, "mJ">>();
        w.format<write_unit<unit::Millijoule>>();
        w.parse<parse_unit<unit::Millijoule>>();
    }
    
    {
        auto w = writer<unit::MilliLightSecond>();
        w.print<print_unit<unit::MilliLightSecond, "mls">>();
        w.format<write_unit<unit::MilliLightSecond>>();
        w.parse<parse_unit<unit::MilliLightSecond>>();
    }
    
    {
        auto w = writer<unit::Millilitre>();
        w.print<print_unit<unit::Millilitre, "mL">>();
        w.format<write_unit<unit::Millilitre>>();
        w.parse<parse_unit<unit::Millilitre>>();
    }
    
    {
        auto w = writer<unit::Millimeter>();
        w.print<print_unit<unit::Millimeter, "mm">>();
        w.format<write_unit<unit::Millimeter>>();
        w.parse<parse_unit<unit::Millimeter>>();
    }
    
    {
        auto w = writer<unit::Millimeter²>();
        w.print<print_unit<unit::Millimeter², "mm²">>();
        w.format<write_unit<unit::Millimeter²>>();
        w.parse<parse_unit<unit::Millimeter²>>();
    }
    
    {
        auto w = writer<unit::Millimeter³>();
        w.print<print_unit<unit::Millimeter³, "mm³">>();
        w.format<write_unit<unit::Millimeter³>>();
        w.parse<parse_unit<unit::Millimeter³>>();
    }
    
    {
        auto w = writer<unit::MillimeterPerSecond>();
        w.print<print_unit<unit::MillimeterPerSecond, "mm/s">>();
        w.format<write_unit<unit::MillimeterPerSecond>>();
        w.parse<parse_unit<unit::MillimeterPerSecond>>();
    }
    
    {
        auto w = writer<unit::MillimeterPerSecond²>();
        w.print<print_unit<unit::MillimeterPerSecond², "mm/s²">>();
        w.format<write_unit<unit::MillimeterPerSecond²>>();
        w.parse<parse_unit<unit::MillimeterPerSecond²>>();
    }
    
    {
        auto w = writer<unit::Millisecond>();
        w.print<print_unit<unit::Millisecond, "ms">>();
        w.format<write_unit<unit::Millisecond>>();
        w.parse<parse_unit<unit::Millisecond>>();
    }
    
    {
        auto w = writer<unit::Millitesla>();
        w.print<print_unit<unit::Millitesla, "mT">>();
        w.format<write_unit<unit::Millitesla>>();
        w.parse<parse_unit<unit::Millitesla>>();
    }
    
    {
        auto w = writer<unit::Millivolt>();
        w.print<print_unit<unit::Millivolt, "mV">>();
        w.format<write_unit<unit::Millivolt>>();
        w.parse<parse_unit<unit::Millivolt>>();
    }
    
    {
        auto w = writer<unit::Milliwatt>();
        w.print<print_unit<unit::Milliwatt, "mW">>();
        w.format<write_unit<unit::Milliwatt>>();
        w.parse<parse_unit<unit::Milliwatt>>();
    }
    
    {
        auto w = writer<unit::Minute>();
        w.print<print_unit<unit::Minute, "min">>();
        w.format<write_unit<unit::Minute>>();
        w.parse<parse_unit<unit::Minute>>();
    }
    
    {
        auto w = writer<unit::Mole>();
        w.print<print_unit<unit::Mole, "mol">>();
        w.format<write_unit<unit::Mole>>();
        w.parse<parse_unit<unit::Mole>>();
    }
    
    {
        auto w = writer<unit::Nanoampere>();
        w.print<print_unit<unit::Nanoampere, "nA">>();
        w.format<write_unit<unit::Nanoampere>>();
        w.parse<parse_unit<unit::Nanoampere>>();
    }
    
    {
        auto w = writer<unit::Nanofarad>();
        w.print<print_unit<unit::Nanofarad, "nF">>();
        w.format<write_unit<unit::Nanofarad>>();
        w.parse<parse_unit<unit::Nanofarad>>();
    }
    
    {
        auto w = writer<unit::Nanogram>();
        w.print<print_unit<unit::Nanogram, "ng">>();
        w.format<write_unit<unit::Nanogram>>();
        w.parse<parse_unit<unit::Nanogram>>();
    }
    
    {
        auto w = writer<unit::NanogramPerSecond>();
        w.print<print_unit<unit::NanogramPerSecond, "ng/s">>();
        w.format<write_unit<unit::NanogramPerSecond>>();
        w.parse<parse_unit<unit::NanogramPerSecond>>();
    }
    
    {
        auto w = writer<unit::Nanohenry>();
        w.print<print_unit<unit::Nanohenry, "nH">>();
        w.format<write_unit<unit::Nanohenry>>();
        w.parse<parse_unit<unit::Nanohenry>>();
    }
    
    {
        auto w = writer<unit::Nanojoule>();
        w.print<print_unit<unit::Nanojoule, "nJ">>();
        w.format<write_unit<unit::Nanojoule>>();
        w.parse<parse_unit<unit::Nanojoule>>();
    }
    
    {
        auto w = writer<unit::NanoLightSecond>();
        w.print<print_unit<unit::NanoLightSecond, "nls">>();
        w.format<write_unit<unit::NanoLightSecond>>();
        w.parse<parse_unit<unit::NanoLightSecond>>();
    }
    
    {
        auto w = writer<unit::Nanometer>();
        w.print<print_unit<unit::Nanometer, "nm">>();
        w.format<write_unit<unit::Nanometer>>();
        w.parse<parse_unit<unit::Nanometer>>();
    }
    
    {
        auto w = writer<unit::NanometerPerSecond>();
        w.print<print_unit<unit::NanometerPerSecond, "nm/s">>();
        w.format<write_unit<unit::NanometerPerSecond>>();
        w.parse<parse_unit<unit::NanometerPerSecond>>();
    }
    
    {
        auto w = writer<unit::NanometerPerSecond²>();
        w.print<print_unit<unit::NanometerPerSecond², "nm/s²">>();
        w.format<write_unit<unit::NanometerPerSecond²>>();
        w.parse<parse_unit<unit::NanometerPerSecond²>>();
    }
    
    {
        auto w = writer<unit::Nanosecond>();
        w.print<print_unit<unit::Nanosecond, "ns">>();
        w.format<write_unit<unit::Nanosecond>>();
        w.parse<parse_unit<unit::Nanosecond>>();
    }
    
    {
        auto w = writer<unit::Nanotesla>();
        w.print<print_unit<unit::Nanotesla, "nT">>();
        w.format<write_unit<unit::Nanotesla>>();
        w.parse<parse_unit<unit::Nanotesla>>();
    }
    
    {
        auto w = writer<unit::Nanovolt>();
        w.print<print_unit<unit::Nanovolt, "nV">>();
        w.format<write_unit<unit::Nanovolt>>();
        w.parse<parse_unit<unit::Nanovolt>>();
    }
    
    {
        auto w = writer<unit::Nanowatt>();
        w.print<print_unit<unit::Nanowatt, "nW">>();
        w.format<write_unit<unit::Nanowatt>>();
        w.parse<parse_unit<unit::Nanowatt>>();
    }
    
    {
        auto w = writer<unit::NauticalMile>();
        w.print<print_unit<unit::NauticalMile, "NM">>();
        w.format<write_unit<unit::NauticalMile>>();
        w.parse<parse_unit<unit::NauticalMile>>();
    }
    
    {
        auto w = writer<unit::Newton>();
        w.print<print_unit<unit::Newton, "N">>();
        w.format<write_unit<unit::Newton>>();
        w.parse<parse_unit<unit::Newton>>();
    }
    
    {
        auto w = writer<unit::NewtonMeter>();
        w.print<print_unit<unit::NewtonMeter, "N*m">>();
        w.format<write_unit<unit::NewtonMeter>>();
        w.parse<parse_unit<unit::NewtonMeter>>();
    }
    
    {
        auto w = writer<unit::NewtonPerSecond>();
        w.print<print_unit<unit::NewtonPerSecond, "N/s">>();
        w.format<write_unit<unit::NewtonPerSecond>>();
        w.parse<parse_unit<unit::NewtonPerSecond>>();
    }
    
    {
        auto w = writer<unit::NewtonSecond>();
        w.print<print_unit<unit::NewtonSecond, "N*s">>();
        w.format<write_unit<unit::NewtonSecond>>();
        w.parse<parse_unit<unit::NewtonSecond>>();
    }
    
    {
        auto w = writer<unit::Ohm>();
        w.print<print_unit<unit::Ohm, "Ω">>();
        w.format<write_unit<unit::Ohm>>();
        w.parse<parse_unit<unit::Ohm>>();
    }
    
    {
        auto w = writer<unit::Pascal>();
        w.print<print_unit<unit::Pascal, "Pa">>();
        w.format<write_unit<unit::Pascal>>();
        w.parse<parse_unit<unit::Pascal>>();
    }
    
    {
        auto w = writer<unit::Percent>();
        w.print<print_unit<unit::Percent, "%">>();
        w.format<write_unit<unit::Percent>>();
        w.parse<parse_unit<unit::Percent>>();
    }
    
    {
        auto w = writer<unit::PerRadian>();
        w.print<print_unit<unit::PerRadian, "1/rad">>();
        w.format<write_unit<unit::PerRadian>>();
        w.parse<parse_unit<unit::PerRadian>>();
    }
    
    {
        auto w = writer<unit::PerMeter>();
        w.print<print_unit<unit::PerMeter, "1/m">>();
        w.format<write_unit<unit::PerMeter>>();
        w.parse<parse_unit<unit::PerMeter>>();
    }
    
    {
        auto w = writer<unit::PerMole>();
        w.print<print_unit<unit::PerMole, "1/mol">>();
        w.format<write_unit<unit::PerMole>>();
        w.parse<parse_unit<unit::PerMole>>();
    }
    
    {
        auto w = writer<unit::Picofarad>();
        w.print<print_unit<unit::Picofarad, "pF">>();
        w.format<write_unit<unit::Picofarad>>();
        w.parse<parse_unit<unit::Picofarad>>();
    }
    
    {
        auto w = writer<unit::PicoLightSecond>();
        w.print<print_unit<unit::PicoLightSecond, "pls">>();
        w.format<write_unit<unit::PicoLightSecond>>();
        w.parse<parse_unit<unit::PicoLightSecond>>();
    }
    
    {
        auto w = writer<unit::Picometer>();
        w.print<print_unit<unit::Picometer, "pm">>();
        w.format<write_unit<unit::Picometer>>();
        w.parse<parse_unit<unit::Picometer>>();
    }
    
    {
        auto w = writer<unit::Picosecond>();
        w.print<print_unit<unit::Picosecond, "ps">>();
        w.format<write_unit<unit::Picosecond>>();
        w.parse<parse_unit<unit::Picosecond>>();
    }
    
    {
        auto w = writer<unit::Picovolt>();
        w.print<print_unit<unit::Picovolt, "pV">>();
        w.format<write_unit<unit::Picovolt>>();
        w.parse<parse_unit<unit::Picovolt>>();
    }
    
    {
        auto w = writer<unit::PoundMass>();
        w.print<print_unit<unit::PoundMass, "lbm">>();
        w.format<write_unit<unit::PoundMass>>();
        w.parse<parse_unit<unit::PoundMass>>();
    }
    
    {
        auto w = writer<unit::PoundForce>();
        w.print<print_unit<unit::PoundForce, "lbf">>();
        w.format<write_unit<unit::PoundForce>>();
        w.parse<parse_unit<unit::PoundForce>>();
    }
    
    {
        auto w = writer<unit::PoundForcePerSecond>();
        w.print<print_unit<unit::PoundForcePerSecond, "lbf/s">>();
        w.format<write_unit<unit::PoundForcePerSecond>>();
        w.parse<parse_unit<unit::PoundForcePerSecond>>();
    }
    
    {
        auto w = writer<unit::PoundPerInch²>();
        w.print<print_unit<unit::PoundPerInch², "psi">>();
        w.format<write_unit<unit::PoundPerInch²>>();
        w.parse<parse_unit<unit::PoundPerInch²>>();
    }
    
    {
        auto w = writer<unit::PoundPerFoot²>();
        w.print<print_unit<unit::PoundPerFoot², "psf">>();
        w.format<write_unit<unit::PoundPerFoot²>>();
        w.parse<parse_unit<unit::PoundPerFoot²>>();
    }
    
    {
        auto w = writer<unit::Radian>();
        w.print<print_unit<unit::Radian, "rad">>();
        w.format<write_unit<unit::Radian>>();
        w.parse<parse_unit<unit::Radian>>();
    }
    
    {
        auto w = writer<unit::Radian²>();
        w.print<print_unit<unit::Radian², "rad²">>();
        w.format<write_unit<unit::Radian²>>();
        w.parse<parse_unit<unit::Radian²>>();
    }
    
    {
        auto w = writer<unit::RadianF>();
        w.print<print_unit<unit::RadianF, "rad">>();
        w.format<write_unit<unit::RadianF>>();
        w.parse<parse_unit<unit::RadianF>>();
    }
    
    {
        auto w = writer<unit::RadianPerMeter>();
        w.print<print_unit<unit::RadianPerMeter, "rad/m">>();
        w.format<write_unit<unit::RadianPerMeter>>();
        w.parse<parse_unit<unit::RadianPerMeter>>();
    }
    
    {
        auto w = writer<unit::RadianPerSecond>();
        w.print<print_unit<unit::RadianPerSecond, "rad/s">>();
        w.format<write_unit<unit::RadianPerSecond>>();
        w.parse<parse_unit<unit::RadianPerSecond>>();
    }
    
    {
        auto w = writer<unit::RadianPerSecond²>();
        w.print<print_unit<unit::RadianPerSecond², "rad/s²">>();
        w.format<write_unit<unit::RadianPerSecond²>>();
        w.parse<parse_unit<unit::RadianPerSecond²>>();
    }
    
    {
        auto w = writer<unit::Rankine>();
        w.print<print_unit<unit::Rankine, "°R">>();
        w.format<write_unit<unit::Rankine>>();
        w.parse<parse_unit<unit::Rankine>>();
    }
    
    {
        auto w = writer<unit::RotationsPerMinute>();
        w.print<print_unit<unit::RotationsPerMinute, "rpm">>();
        w.format<write_unit<unit::RotationsPerMinute>>();
        w.parse<parse_unit<unit::RotationsPerMinute>>();
    }
    
    {
        auto w = writer<unit::Second>();
        w.print<print_unit<unit::Second, "s">>();
        w.format<write_unit<unit::Second>>();
        w.parse<parse_unit<unit::Second>>();
    }
    
    {
        auto w = writer<unit::Second²>();
        w.print<print_unit<unit::Second², "s²">>();
        w.format<write_unit<unit::Second²>>();
        w.parse<parse_unit<unit::Second²>>();
    }
    
    {
        auto w = writer<unit::ShortTon>();
        w.print<print_unit<unit::ShortTon, "ston">>();
        w.format<write_unit<unit::ShortTon>>();
        w.parse<parse_unit<unit::ShortTon>>();
    }
    
    {
        auto w = writer<unit::Siemens>();
        w.print<print_unit<unit::Siemens, "S">>();
        w.format<write_unit<unit::Siemens>>();
        w.parse<parse_unit<unit::Siemens>>();
    }
    
    {
        auto w = writer<unit::Slug>();
        w.print<print_unit<unit::Slug, "slug">>();
        w.format<write_unit<unit::Slug>>();
        w.parse<parse_unit<unit::Slug>>();
    }
    
    {
        auto w = writer<unit::SlugPerFoot³>();
        w.print<print_unit<unit::SlugPerFoot³, "slug/ft³">>();
        w.format<write_unit<unit::SlugPerFoot³>>();
        w.parse<parse_unit<unit::SlugPerFoot³>>();
    }
    
    {
        auto w = writer<unit::Steradian>();
        w.print<print_unit<unit::Steradian, "sr">>();
        w.format<write_unit<unit::Steradian>>();
        w.parse<parse_unit<unit::Steradian>>();
    }
    
    {
        auto w = writer<unit::TeraElectronVolt>();
        w.print<print_unit<unit::TeraElectronVolt, "TeV">>();
        w.format<write_unit<unit::TeraElectronVolt>>();
        w.parse<parse_unit<unit::TeraElectronVolt>>();
    }
    
    {
        auto w = writer<unit::Terahertz>();
        w.print<print_unit<unit::Terahertz, "THz">>();
        w.format<write_unit<unit::Terahertz>>();
        w.parse<parse_unit<unit::Terahertz>>();
    }
    
    {
        auto w = writer<unit::Terawatt>();
        w.print<print_unit<unit::Terawatt, "TW">>();
        w.format<write_unit<unit::Terawatt>>();
        w.parse<parse_unit<unit::Terawatt>>();
    }
    
    {
        auto w = writer<unit::Tesla>();
        w.print<print_unit<unit::Tesla, "T">>();
        w.format<write_unit<unit::Tesla>>();
        w.parse<parse_unit<unit::Tesla>>();
    }
    
    {
        auto w = writer<unit::Tonne>();
        w.print<print_unit<unit::Tonne, "t">>();
        w.format<write_unit<unit::Tonne>>();
        w.parse<parse_unit<unit::Tonne>>();
    }
    
    {
        auto w = writer<unit::Volt>();
        w.print<print_unit<unit::Volt, "V">>();
        w.format<write_unit<unit::Volt>>();
        w.parse<parse_unit<unit::Volt>>();
    }
    
    {
        auto w = writer<unit::VoltPerMeter>();
        w.print<print_unit<unit::VoltPerMeter, "V/m">>();
        w.format<write_unit<unit::VoltPerMeter>>();
        w.parse<parse_unit<unit::VoltPerMeter>>();
    }
    
    {
        auto w = writer<unit::Watt>();
        w.print<print_unit<unit::Watt, "W">>();
        w.format<write_unit<unit::Watt>>();
        w.parse<parse_unit<unit::Watt>>();
    }
    
    {
        auto w = writer<unit::WattPerMeter²>();
        w.print<print_unit<unit::WattPerMeter², "W/m²">>();
        w.format<write_unit<unit::WattPerMeter²>>();
        w.parse<parse_unit<unit::WattPerMeter²>>();
    }
    
    {
        auto w = writer<unit::WattPerMeter²Steradian>();
        w.print<print_unit<unit::WattPerMeter²Steradian, "W/(m²*sr)">>();
        w.format<write_unit<unit::WattPerMeter²Steradian>>();
        w.parse<parse_unit<unit::WattPerMeter²Steradian>>();
    }
    
    {
        auto w = writer<unit::Weber>();
        w.print<print_unit<unit::Weber, "Wb">>();
        w.format<write_unit<unit::Weber>>();
        w.parse<parse_unit<unit::Weber>>();
    }
    
    {
        auto w = writer<unit::Week>();
        w.print<print_unit<unit::Week, "week">>();
        w.format<write_unit<unit::Week>>();
        w.parse<parse_unit<unit::Week>>();
    }
    
    {
        auto w = writer<unit::Yard>();
        w.print<print_unit<unit::Yard, "yd">>();
        w.format<write_unit<unit::Yard>>();
        w.parse<parse_unit<unit::Yard>>();
    }
    
    {
        auto w = writer<unit::Yard²>();
        w.print<print_unit<unit::Yard², "yd²">>();
        w.format<write_unit<unit::Yard²>>();
        w.parse<parse_unit<unit::Yard²>>();
    }

    {
        auto w = writer<unit::Yard³>();
        w.print<print_unit<unit::Yard³, "yd³">>();
        w.format<write_unit<unit::Yard³>>();
        w.parse<parse_unit<unit::Yard³>>();
    }

}

YQ_INVOKE(reg_units_math();)

#include "MKS.hxx"
#include "SCALED.hxx"
