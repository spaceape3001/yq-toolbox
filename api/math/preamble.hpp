////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>

#include <basic/StreamOps.hpp>
#include <basic/meta/InfoBinder.hpp>
#include <basic/trait/always_false.hpp>

#include <math/trait/has_abs.hpp>
#include <math/trait/has_copysign.hpp>
#include <math/trait/has_identity.hpp>
#include <math/trait/has_is_finite.hpp>
#include <math/trait/has_nan.hpp>
#include <math/trait/has_one.hpp>
#include <math/trait/has_sqrt.hpp>
#include <math/trait/has_zero.hpp>
#include <math/trait/ieee754.hpp>

#include <math/dims.hpp>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <numbers>
#include <utility>

#include <log4cpp/CategoryStream.hh>

#include <glm/glm.hpp>

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //      MACROS
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

#ifdef PI
#undef PI
#endif

/*! \brief Dot product operator

    As C++ doesn't let us define new operators, we must make do with the
    existing operators.  
    
    This is the macro used for the dot product between zvecs.
    
    \note   It is HIGHLY recommended to use parathensis as the operational 
        priorities are based on C++'s interpretation of the actual symbol,
        which is not necessarily our intended order.
*/
#define DOT         |

/*! \brief Inner product operator

    As C++ doesn't let us define new operators, we must make do with the
    existing operators.  
    
    This is the macro used for the inner product.

    \note   It is HIGHLY recommended to use parathensis as the operational 
        priorities are based on C++'s interpretation of the actual symbol,
        which is not necessarily our intended order.
*/
#define INNER       &
#define INNER_EQ    &=

/*! \brief Outer product operator

    As C++ doesn't let us define new operators, we must make do with the
    existing operators.  
    
    This is the macro used for the outer product.

    \note   It is HIGHLY recommended to use parathensis as the operational 
        priorities are based on C++'s interpretation of the actual symbol,
        which is not necessarily our intended order.
*/
#define OUTER       ^
#define OUTER_EQ    ^=

/*! \brief Outer Vector to Tensor operator

    As C++ doesn't let us define new operators, we must make do with the
    existing operators.  
    
    This is the macro used for the outer zvec product between zvecs.
    This is different than the general outer product because this one
    produces ztens, whereas the general outer product makes for zbvecs.
    
    Also, this operator can produce non-square ztens (ie, 3x2).

    \note   It is HIGHLY recommended to use parathensis as the operational 
        priorities are based on C++'s interpretation of the actual symbol,
        which is not necessarily our intended order.
*/
#define OTIMES      &&

/*! \brief Cross product operator

    As C++ doesn't let us define new operators, we must make do with the
    existing operators.  
    
    This is the macro used for the cross product between zvecs.

    \note   It is HIGHLY recommended to use parathensis as the operational 
        priorities are based on C++'s interpretation of the actual symbol,
        which is not necessarily our intended order.
*/
#define CROSS       %
#define CROSS_EQ   %=

namespace std {
    template <typename> class complex;
}


namespace yq {
    

    static constexpr const double   pi      = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862;
    static constexpr const double   sqrt2   = 1.4142135623730950488016887242096980785696718753769480731766797379907324784621;
    static constexpr const double   sqrt3   = 1.7320508075688772935274463415058723669428052538103806280558069794519330169088;
    static constexpr const int64_t  max64   = std::numeric_limits<int64_t>::max();
    static constexpr const uint64_t maxu64  = std::numeric_limits<uint64_t>::max();
    
    struct two_t {};
    struct three_t {};
    
    static constexpr const two_t        ²;
    static constexpr const three_t      ³;

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
    }

    template <typename F, typename S>
    S       greatest(const std::pair<F,S>& a, const std::pair<F,S>& b)
    {
        if(a.first >= b.first)
            return a.second;
        else
            return b.second;
    }

    template <typename F, typename S>
    S       greatest(const std::pair<F,S>& a, const std::pair<F,S>& b, const std::pair<F,S>& c)
    {
        if(c.first >= std::max(a.first, b.first))
            return c.second;
        else if(b.first >= std::max(a.first, c.first))
            return b.second;
        else
            return a.second;
    }


    inline int   iround(double v)
    {
        return (int)(std::round(v)+std::copysign(0.1,v));
    }

    inline int   iceil(double r)
    {
        return (int)(ceil(r)+std::copysign(0.1,r));
    }

    inline int   itrunc(double r)
    {
        return (int)(trunc(r)+std::copysign(0.1,r));
    }

    inline int   ifloor(double r)
    {
        return (int)(floor(r)+std::copysign(0.1,r));
    }
    
    template <typename T, typename R>
    requires std::is_floating_point_v<T>
    bool    is_close(const R& compare, T actual, T expected)
    {
        return compare(actual-expected, expected);
    }
    
    template <typename> struct PolygonData;
    template <typename> struct QuadrilateralData;
    template <typename> struct SegmentData;
    template <typename> struct TetrahedronData;
    template <typename> struct TriangleData;

    template <typename> struct AxBox1;
    template <typename> struct AxBox2;
    template <typename> struct AxBox3;
    template <typename> struct AxBox4;
    template <typename> struct AxCorners1;
    template <typename> struct AxCorners2;
    template <typename> struct AxCorners3;
    template <typename> struct AxCorners4;
    template <typename> struct Bivector2;
    template <typename> struct Bivector3;
    template <typename> struct Bivector4;
    template <typename> struct Circle2;
    template <typename> struct Fraction;
    template <typename> struct Multivector1;
    template <typename> struct Multivector2;
    template <typename> struct Multivector3;
    template <typename> struct Multivector4;
    template <typename> struct Normal2;
    template <typename> struct Normal3;
    template <typename> struct Plane3;
    //template <typename> struct Pose2;
    template <typename> struct Pose3;
    template <typename> struct Quadvector4;
    template <typename> struct Quaternion3;
    template <typename> struct Ray2;
    template <typename> struct Ray3;
    template <typename> struct Ray4;
    template <typename> struct Rectangle2;
    template <typename> struct RGB;
    template <typename> struct RGBA;
    template <typename> struct Size2;
    template <typename> struct Size3;
    template <typename> struct Sphere3;
    template <typename> struct Sphere4;
    template <typename> struct Tensor11;
    template <typename> struct Tensor12;
    template <typename> struct Tensor13;
    template <typename> struct Tensor14;
    template <typename> struct Tensor21;
    template <typename> struct Tensor22;
    template <typename> struct Tensor23;
    template <typename> struct Tensor24;
    template <typename> struct Tensor31;
    template <typename> struct Tensor32;
    template <typename> struct Tensor33;
    template <typename> struct Tensor34;
    template <typename> struct Tensor41;
    template <typename> struct Tensor42;
    template <typename> struct Tensor43;
    template <typename> struct Tensor44;
    template <typename> struct Trivector3;
    template <typename> struct Trivector4;
    template <typename> struct Vector1;
    template <typename> struct Vector2;
    template <typename> struct Vector3;
    template <typename> struct Vector4;

    template <typename T> using Segment1        = SegmentData<Vector1<T>>;
    template <typename T> using Segment2        = SegmentData<Vector2<T>>;
    template <typename T> using Segment3        = SegmentData<Vector3<T>>;
    template <typename T> using Segment4        = SegmentData<Vector4<T>>;
    template <typename T> using Tetrahedron3    = TetrahedronData<Vector3<T>>;
    template <typename T> using Triangle2       = TriangleData<Vector2<T>>;
    template <typename T> using Triangle3       = TriangleData<Vector3<T>>;
    template <typename T> using Triangle4       = TriangleData<Vector4<T>>;
    template <typename T> using Quadrilateral2  = QuadrilateralData<Vector2<T>>;
    template <typename T> using Polygon2        = PolygonData<Vector2<T>>;
    template <typename T> using Polygon3        = PolygonData<Vector3<T>>;
    template <typename T> using Polygon4        = PolygonData<Vector4<T>>;

    //  ------------------------------------------------
    //  COMPLEX NUMBERS


    using ComplexD                  = std::complex<double>;
    using ComplexF                  = std::complex<float>;
    using ComplexI                  = std::complex<int>;
    using ComplexU                  = std::complex<unsigned>;

    
    //  ------------------------------------------------
    //  FORWARD DECLARE UNITS

    template <typename T, typename DIM>             struct MKS;
    template <typename T, typename DIM, double K>   struct SCALED;

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
        using RotationsPerMinute        = SCALED<double,dim::AngularVelocity,pi/30.>;
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

    //  ------------------------------------------------
    //  FORWARD DECLARE VECTORS & TENSOR (RELATED)
    
    using Bivector2D                = Bivector2<double>;
    using Bivector2F                = Bivector2<float>;
    
    using Bivector3D                = Bivector3<double>;
    using Bivector3F                = Bivector3<float>;

    using Bivector4D                = Bivector4<double>;
    using Bivector4F                = Bivector4<float>;
    
    using Multivector1D             = Multivector1<double>;
    using Multivector1F             = Multivector1<float>;
    
    using Multivector2D             = Multivector2<double>;
    using Multivector2F             = Multivector2<float>;

    using Multivector3D             = Multivector3<double>;
    using Multivector3F             = Multivector3<float>;

    using Multivector4D             = Multivector4<double>;
    using Multivector4F             = Multivector4<float>;

    using Quadvector4D              = Quadvector4<double>;
    using Quadvector4F              = Quadvector4<float>;

    using Quaternion3D              = Quaternion3<double>;
    using Quaternion3F              = Quaternion3<float>;

    using Tensor11D                 = Tensor11<double>;
    using Tensor11F                 = Tensor11<float>;
    using Tensor11I                 = Tensor11<int>;
    using Tensor11U                 = Tensor11<unsigned>;

    using Tensor12D                 = Tensor12<double>;
    using Tensor12F                 = Tensor12<float>;
    using Tensor12I                 = Tensor12<int>;
    using Tensor12U                 = Tensor12<unsigned>;

    using Tensor13D                 = Tensor13<double>;
    using Tensor13F                 = Tensor13<float>;
    using Tensor13I                 = Tensor13<int>;
    using Tensor13U                 = Tensor13<unsigned>;

    using Tensor14D                 = Tensor14<double>;
    using Tensor14F                 = Tensor14<float>;
    using Tensor14I                 = Tensor14<int>;
    using Tensor14U                 = Tensor14<unsigned>;

    using Tensor21D                 = Tensor21<double>;
    using Tensor21F                 = Tensor21<float>;
    using Tensor21I                 = Tensor21<int>;
    using Tensor21U                 = Tensor21<unsigned>;

    using Tensor22D                 = Tensor22<double>;
    using Tensor22F                 = Tensor22<float>;
    using Tensor22I                 = Tensor22<int>;
    using Tensor22U                 = Tensor22<unsigned>;

    using Tensor23D                 = Tensor23<double>;
    using Tensor23F                 = Tensor23<float>;
    using Tensor23I                 = Tensor23<int>;
    using Tensor23U                 = Tensor23<unsigned>;

    using Tensor24D                 = Tensor24<double>;
    using Tensor24F                 = Tensor24<float>;
    using Tensor24I                 = Tensor24<int>;
    using Tensor24U                 = Tensor24<unsigned>;

    using Tensor31D                 = Tensor31<double>;
    using Tensor31F                 = Tensor31<float>;
    using Tensor31I                 = Tensor31<int>;
    using Tensor31U                 = Tensor31<unsigned>;

    using Tensor32D                 = Tensor32<double>;
    using Tensor32F                 = Tensor32<float>;
    using Tensor32I                 = Tensor32<int>;
    using Tensor32U                 = Tensor32<unsigned>;

    using Tensor33D                 = Tensor33<double>;
    using Tensor33F                 = Tensor33<float>;
    using Tensor33I                 = Tensor33<int>;
    using Tensor33U                 = Tensor33<unsigned>;

    using Tensor34D                 = Tensor34<double>;
    using Tensor34F                 = Tensor34<float>;
    using Tensor34I                 = Tensor34<int>;
    using Tensor34U                 = Tensor34<unsigned>;

    using Tensor41D                 = Tensor41<double>;
    using Tensor41F                 = Tensor41<float>;
    using Tensor41I                 = Tensor41<int>;
    using Tensor41U                 = Tensor41<unsigned>;

    using Tensor42D                 = Tensor42<double>;
    using Tensor42F                 = Tensor42<float>;
    using Tensor42I                 = Tensor42<int>;
    using Tensor42U                 = Tensor42<unsigned>;

    using Tensor43D                 = Tensor43<double>;
    using Tensor43F                 = Tensor43<float>;
    using Tensor43I                 = Tensor43<int>;
    using Tensor43U                 = Tensor43<unsigned>;

    using Tensor44D                 = Tensor44<double>;
    using Tensor44F                 = Tensor44<float>;
    using Tensor44I                 = Tensor44<int>;
    using Tensor44U                 = Tensor44<unsigned>;    

    using Trivector3D               = Trivector3<double>;
    using Trivector3F               = Trivector3<float>;

    using Trivector4D               = Trivector4<double>;
    using Trivector4F               = Trivector4<float>;

    using Vector1D                  = Vector1<double>;
    using Vector1F                  = Vector1<float>;
    using Vector1I                  = Vector1<int>;
    using Vector1U                  = Vector1<unsigned>;

    using Vector2D                  = Vector2<double>;
    using Vector2F                  = Vector2<float>;
    using Vector2I                  = Vector2<int>;
    using Vector2U                  = Vector2<unsigned>;

    using Vector3D                  = Vector3<double>;
    using Vector3F                  = Vector3<float>;
    using Vector3I                  = Vector3<int>;
    using Vector3U                  = Vector3<unsigned>;

    using Vector4D                  = Vector4<double>;
    using Vector4F                  = Vector4<float>;
    using Vector4I                  = Vector4<int>;
    using Vector4U                  = Vector4<unsigned>;

    //  ------------------------------------------------
    //  FORWARD DECLARE SHAPES


    using AxBox1D                   = AxBox1<double>;
    using AxBox1F                   = AxBox1<float>;
    using AxBox1I                   = AxBox1<int>;
    using AxBox1U                   = AxBox1<unsigned>;

    using AxBox2D                   = AxBox2<double>;
    using AxBox2F                   = AxBox2<float>;
    using AxBox2I                   = AxBox2<int>;
    using AxBox2U                   = AxBox2<unsigned>;

    using AxBox3D                   = AxBox3<double>;
    using AxBox3F                   = AxBox3<float>;
    using AxBox3I                   = AxBox3<int>;
    using AxBox3U                   = AxBox3<unsigned>;

    using AxBox4D                   = AxBox4<double>;
    using AxBox4F                   = AxBox4<float>;
    using AxBox4I                   = AxBox4<int>;
    using AxBox4U                   = AxBox4<unsigned>;

    using Circle2D                  = Circle2<double>;
    using Circle2F                  = Circle2<float>;
    using Circle2I                  = Circle2<int>;
    using Circle2U                  = Circle2<unsigned>;

    using Coord2D                   = Coord2<double>;
    using Coord2F                   = Coord2<float>;
    //using Coord2I                   = Coord2<int>;
    //using Coord2U                   = Coord2<unsigned>;

    using FractionI                 = Fraction<int>;
    //using Fraction8      = Fraction<int8_t>;
    //using Fraction16     = Fraction<int16_t>;
    //using Fraction32     = Fraction<int32_t>;
    //using Fraction64     = Fraction<int64_t>;
    
    using Normal2D                  = Normal2<double>;
    using Normal2F                  = Normal2<float>;
    
    using Normal3D                  = Normal3<double>;
    using Normal3F                  = Normal3<float>;

    using Plane3D                   = Plane3<double>;
    using Plane3F                   = Plane3<float>;
    
    using Polygon2D                 = Polygon2<double>;
    using Polygon2F                 = Polygon2<float>;

    using Polygon3D                 = Polygon3<double>;
    using Polygon3F                 = Polygon3<float>;
    
    using Polygon4D                 = Polygon4<double>;
    using Polygon4F                 = Polygon4<float>;

    using Quadrilateral2D           = Quadrilateral2<double>;
    using Quadrilateral2F           = Quadrilateral2<float>;
    using Quadrilateral2I           = Quadrilateral2<int>;
    using Quadrilateral2U           = Quadrilateral2<unsigned>;
    
    using Ray2D                     = Ray2<double>;
    using Ray2F                     = Ray2<float>;

    using Ray3D                     = Ray3<double>;
    using Ray3F                     = Ray3<float>;

    using Ray4D                     = Ray4<double>;
    using Ray4F                     = Ray4<float>;
    
    using Rectangle2D               = Rectangle2<double>;
    using Rectangle2F               = Rectangle2<float>;
    using Rectangle2I               = Rectangle2<int>;
    using Rectangle2U               = Rectangle2<unsigned>;

    using Segment1D                 = Segment1<double>;
    using Segment1F                 = Segment1<float>;
    using Segment1I                 = Segment1<int>;
    using Segment1U                 = Segment1<unsigned>;

    using Segment2D                 = Segment2<double>;
    using Segment2F                 = Segment2<float>;
    using Segment2I                 = Segment2<int>;
    using Segment2U                 = Segment2<unsigned>;

    using Segment3D                 = Segment3<double>;
    using Segment3F                 = Segment3<float>;
    using Segment3I                 = Segment3<int>;
    using Segment3U                 = Segment3<unsigned>;

    using Segment4D                 = Segment4<double>;
    using Segment4F                 = Segment4<float>;
    using Segment4I                 = Segment4<int>;
    using Segment4U                 = Segment4<unsigned>;
    
    using Size2D                    = Size2<double>;
    using Size2F                    = Size2<float>;
    using Size2I                    = Size2<int>;
    using Size2I8                   = Size2<int8_t>;
    using Size2I16                  = Size2<int16_t>;
    using Size2I32                  = Size2<int32_t>;
    using Size2I64                  = Size2<int64_t>;
    using Size2U                    = Size2<unsigned>;
    using Size2U8                   = Size2<int8_t>;
    using Size2U16                  = Size2<int16_t>;
    using Size2U32                  = Size2<int32_t>;
    using Size2U64                  = Size2<int64_t>;
    using Size2Z                    = Size2<size_t>;

    using Size3D                    = Size3<double>;
    using Size3F                    = Size3<float>;
    using Size3I                    = Size3<int>;
    using Size3I8                   = Size3<int8_t>;
    using Size3I16                  = Size3<int16_t>;
    using Size3I33                  = Size3<int32_t>;
    using Size3I64                  = Size3<int64_t>;
    using Size3U                    = Size3<unsigned>;
    using Size3U8                   = Size3<int8_t>;
    using Size3U16                  = Size3<int16_t>;
    using Size3U33                  = Size3<int32_t>;
    using Size3U64                  = Size3<int64_t>;
    using Size3Z                    = Size3<size_t>;

    using Sphere3D                  = Sphere3<double>;
    using Sphere3F                  = Sphere3<float>;
    using Sphere3I                  = Sphere3<int>;
    using Sphere3U                  = Sphere3<unsigned>;
    
    using Sphere4D                  = Sphere4<double>;
    using Sphere4F                  = Sphere4<float>;
    using Sphere4I                  = Sphere4<int>;
    using Sphere4U                  = Sphere4<unsigned>;
    
    using Tetrahedron3D             = Tetrahedron3<double>;
    using Tetrahedron3F             = Tetrahedron3<float>;
    using Tetrahedron3I             = Tetrahedron3<int>;
    using Tetrahedron3U             = Tetrahedron3<unsigned>;

    using Triangle2D                = Triangle2<double>;
    using Triangle2F                = Triangle2<float>;
    using Triangle2I                = Triangle2<int>;
    using Triangle2U                = Triangle2<unsigned>;

    using Triangle3D                = Triangle3<double>;
    using Triangle3F                = Triangle3<float>;
    using Triangle3I                = Triangle3<int>;
    using Triangle3U                = Triangle3<unsigned>;

    using Triangle4D                = Triangle4<double>;
    using Triangle4F                = Triangle4<float>;
    using Triangle4I                = Triangle4<int>;
    using Triangle4U                = Triangle4<unsigned>;

    //  ------------------------------------------------
    //  FORWARD DECLARE Colors

    using RGB3D                     = RGB<double>;
    using RGB3F                     = RGB<float>;
    using RGB3I                     = RGB<int>;
    using RGB3U                     = RGB<unsigned>;
    using RGB3U8                    = RGB<uint8_t>;
    using RGB3U16                   = RGB<uint16_t>;

    using RGBA4D                    = RGBA<double>;
    using RGBA4F                    = RGBA<float>;
    using RGBA4U8                   = RGBA<uint8_t>;
    using RGBA4U16                  = RGBA<uint16_t>;
    
    //  ------------------------------------------------
    //  Miscellaneous
    
    struct SimpleSpace;
    
    //using Pose2D        = Pose2<double>;
    //using Pose2F        = Pose2<float>;

    using Pose3D        = Pose3<double>;
    using Pose3F        = Pose3<float>;

    //! Call this if math isn't getting startup-initialized 
    void        initialize_math();

    template <typename T> using unity_t = decltype(T()/T());
    template <typename T> using square_t = decltype(T()*T());
    template <typename T> using cube_t   = decltype(T()*T()*T());
    template <typename T> using fourth_t = decltype(T()*T()*T()*T());
    template <typename T, typename U>  using product_t     = decltype(T()*U());
    template <typename T, typename U>  using quotient_t    = decltype(T()/U());
    template <typename T> using inverse_t = decltype(T()/square_t<T>());
    
    using std::max;
    using std::min;
    using std::abs;
    
    namespace trait {
        template <typename T, typename U>  static constexpr const bool self_mul_v = std::is_same_v<T,product_t<T,U>>;
        template <typename T, typename U>  static constexpr const bool self_div_v = std::is_same_v<T,quotient_t<T,U>>;
        
        template <typename T>   static constexpr const bool is_basic_v = std::is_floating_point_v<T>;
        
    }
}

