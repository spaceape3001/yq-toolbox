////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <math/preamble.hpp>
#include <math/Complex.hpp>
#include <math/Coord2.hpp>
#include <math/Dimension.hpp>
#include <math/Fraction.hpp>
#include <math/RGB.hpp>
#include <math/RGBA.hpp>
#include <math/Pose3.hpp>


#include <math/AxBox1.hpp>
#include <math/AxBox2.hpp>
#include <math/AxBox3.hpp>
#include <math/AxBox4.hpp>

#include <math/Bivector2.hpp>
#include <math/Bivector3.hpp>
#include <math/Bivector4.hpp>

#include <math/Circle2.hpp>

#include <math/Multivector1.hpp>
#include <math/Multivector2.hpp>
#include <math/Multivector3.hpp>
#include <math/Multivector4.hpp>

#include <math/Normal2.hpp>
#include <math/Normal3.hpp>

#include <math/Plane3.hpp>

#include <math/Ray2.hpp>
#include <math/Ray3.hpp>
#include <math/Ray4.hpp>

#include <math/Rectangle2.hpp>

#include <math/Segment1.hpp>
#include <math/Segment2.hpp>
#include <math/Segment3.hpp>
#include <math/Segment4.hpp>

#include <math/Size2.hpp>
#include <math/Size3.hpp>

#include <math/Sphere3.hpp>
#include <math/Sphere4.hpp>

#include <math/Tetrahedron3.hpp>

#include <math/Triangle2.hpp>
#include <math/Triangle3.hpp>
#include <math/Triangle4.hpp>

#include <math/Quadrilateral2.hpp>

#include <math/Quadvector4.hpp>
#include <math/Quaternion3.hpp>

#include <math/Tensor11.hpp>
#include <math/Tensor12.hpp>
#include <math/Tensor13.hpp>
#include <math/Tensor14.hpp>

#include <math/Tensor21.hpp>
#include <math/Tensor22.hpp>
#include <math/Tensor23.hpp>
#include <math/Tensor24.hpp>

#include <math/Tensor31.hpp>
#include <math/Tensor32.hpp>
#include <math/Tensor33.hpp>
#include <math/Tensor34.hpp>

#include <math/Tensor41.hpp>
#include <math/Tensor42.hpp>
#include <math/Tensor43.hpp>
#include <math/Tensor44.hpp>

#include <math/Trivector3.hpp>
#include <math/Trivector4.hpp>

#include <math/Vector1.hpp>
#include <math/Vector2.hpp>
#include <math/Vector3.hpp>
#include <math/Vector4.hpp>

#include <basic/DelayInit.hpp>
#include <basic/meta/Init.hpp>

#include <math/glm_types.hpp>
#include <math/vector_math.hpp>
#include <math/tensor_math.hpp>
#include <math/shape_math.hpp>
#include <math/Units.hpp>

#include <math/SimpleSpace.ipp>

using namespace yq;

YQ_TYPE_IMPLEMENT(glm::mat2)
YQ_TYPE_IMPLEMENT(glm::mat3)
YQ_TYPE_IMPLEMENT(glm::mat4)

YQ_TYPE_IMPLEMENT(glm::dmat2)
YQ_TYPE_IMPLEMENT(glm::dmat3)
YQ_TYPE_IMPLEMENT(glm::dmat4)

YQ_TYPE_IMPLEMENT(glm::vec1)
YQ_TYPE_IMPLEMENT(glm::vec2)
YQ_TYPE_IMPLEMENT(glm::vec3)
YQ_TYPE_IMPLEMENT(glm::vec4)

YQ_TYPE_IMPLEMENT(glm::dvec1)
YQ_TYPE_IMPLEMENT(glm::dvec2)
YQ_TYPE_IMPLEMENT(glm::dvec3)
YQ_TYPE_IMPLEMENT(glm::dvec4)


YQ_TYPE_IMPLEMENT(yq::AxBox1D)
YQ_TYPE_IMPLEMENT(yq::AxBox1F)
YQ_TYPE_IMPLEMENT(yq::AxBox1I)
YQ_TYPE_IMPLEMENT(yq::AxBox1U)

YQ_TYPE_IMPLEMENT(yq::AxBox2D)
YQ_TYPE_IMPLEMENT(yq::AxBox2F)
YQ_TYPE_IMPLEMENT(yq::AxBox2I)
YQ_TYPE_IMPLEMENT(yq::AxBox2U)

YQ_TYPE_IMPLEMENT(yq::AxBox3D)
YQ_TYPE_IMPLEMENT(yq::AxBox3F)
YQ_TYPE_IMPLEMENT(yq::AxBox3I)
YQ_TYPE_IMPLEMENT(yq::AxBox3U)

YQ_TYPE_IMPLEMENT(yq::AxBox4D)
YQ_TYPE_IMPLEMENT(yq::AxBox4F)
YQ_TYPE_IMPLEMENT(yq::AxBox4I)
YQ_TYPE_IMPLEMENT(yq::AxBox4U)

YQ_TYPE_IMPLEMENT(yq::Bivector2D)
YQ_TYPE_IMPLEMENT(yq::Bivector2F)

YQ_TYPE_IMPLEMENT(yq::Bivector3D)
YQ_TYPE_IMPLEMENT(yq::Bivector3F)

YQ_TYPE_IMPLEMENT(yq::Bivector4D)
YQ_TYPE_IMPLEMENT(yq::Bivector4F)

YQ_TYPE_IMPLEMENT(yq::Circle2D)
YQ_TYPE_IMPLEMENT(yq::Circle2F)
YQ_TYPE_IMPLEMENT(yq::Circle2I)
YQ_TYPE_IMPLEMENT(yq::Circle2U)


YQ_TYPE_IMPLEMENT(yq::ComplexD)
YQ_TYPE_IMPLEMENT(yq::ComplexF)
YQ_TYPE_IMPLEMENT(yq::ComplexI)
YQ_TYPE_IMPLEMENT(yq::ComplexU)

YQ_TYPE_IMPLEMENT(yq::Coord2D)
YQ_TYPE_IMPLEMENT(yq::Coord2F)
YQ_TYPE_IMPLEMENT(yq::Coord2I)
YQ_TYPE_IMPLEMENT(yq::Coord2U)

YQ_TYPE_IMPLEMENT(yq::Dimension)


YQ_TYPE_IMPLEMENT(yq::FractionI)
//YQ_TYPE_IMPLEMENT(yq::Frac16)
//YQ_TYPE_IMPLEMENT(yq::Frac32)
//YQ_TYPE_IMPLEMENT(yq::Frac64)

YQ_TYPE_IMPLEMENT(yq::Multivector1D)
YQ_TYPE_IMPLEMENT(yq::Multivector1F)

YQ_TYPE_IMPLEMENT(yq::Multivector2D)
YQ_TYPE_IMPLEMENT(yq::Multivector2F)

YQ_TYPE_IMPLEMENT(yq::Multivector3D)
YQ_TYPE_IMPLEMENT(yq::Multivector3F)

YQ_TYPE_IMPLEMENT(yq::Multivector4D)
YQ_TYPE_IMPLEMENT(yq::Multivector4F)

YQ_TYPE_IMPLEMENT(yq::Normal2D)
YQ_TYPE_IMPLEMENT(yq::Normal2F)

YQ_TYPE_IMPLEMENT(yq::Normal3D)
YQ_TYPE_IMPLEMENT(yq::Normal3F)

YQ_TYPE_IMPLEMENT(yq::Plane3D)
YQ_TYPE_IMPLEMENT(yq::Plane3F)

YQ_TYPE_IMPLEMENT(yq::Pose3D)
YQ_TYPE_IMPLEMENT(yq::Pose3F)

YQ_TYPE_IMPLEMENT(yq::Quadrilateral2D)
YQ_TYPE_IMPLEMENT(yq::Quadrilateral2F)
YQ_TYPE_IMPLEMENT(yq::Quadrilateral2I)
YQ_TYPE_IMPLEMENT(yq::Quadrilateral2U)

YQ_TYPE_IMPLEMENT(yq::Quadvector4D)
YQ_TYPE_IMPLEMENT(yq::Quadvector4F)

YQ_TYPE_IMPLEMENT(yq::Quaternion3D)
YQ_TYPE_IMPLEMENT(yq::Quaternion3F)

YQ_TYPE_IMPLEMENT(yq::Ray2D)
YQ_TYPE_IMPLEMENT(yq::Ray2F)

YQ_TYPE_IMPLEMENT(yq::Ray3D)
YQ_TYPE_IMPLEMENT(yq::Ray3F)

YQ_TYPE_IMPLEMENT(yq::Ray4D)
YQ_TYPE_IMPLEMENT(yq::Ray4F)

YQ_TYPE_IMPLEMENT(yq::RGB3D)
YQ_TYPE_IMPLEMENT(yq::RGB3F)
YQ_TYPE_IMPLEMENT(yq::RGB3U8)
YQ_TYPE_IMPLEMENT(yq::RGB3U16)

YQ_TYPE_IMPLEMENT(yq::RGBA4D)
YQ_TYPE_IMPLEMENT(yq::RGBA4F)
YQ_TYPE_IMPLEMENT(yq::RGBA4U8)
YQ_TYPE_IMPLEMENT(yq::RGBA4U16)

YQ_TYPE_IMPLEMENT(yq::Rectangle2D)
YQ_TYPE_IMPLEMENT(yq::Rectangle2F)
YQ_TYPE_IMPLEMENT(yq::Rectangle2I)
YQ_TYPE_IMPLEMENT(yq::Rectangle2U)

YQ_TYPE_IMPLEMENT(yq::Segment1D)
YQ_TYPE_IMPLEMENT(yq::Segment1F)
YQ_TYPE_IMPLEMENT(yq::Segment1I)
YQ_TYPE_IMPLEMENT(yq::Segment1U)

YQ_TYPE_IMPLEMENT(yq::Segment2D)
YQ_TYPE_IMPLEMENT(yq::Segment2F)
YQ_TYPE_IMPLEMENT(yq::Segment2I)
YQ_TYPE_IMPLEMENT(yq::Segment2U)

YQ_TYPE_IMPLEMENT(yq::Segment3D)
YQ_TYPE_IMPLEMENT(yq::Segment3F)
YQ_TYPE_IMPLEMENT(yq::Segment3I)
YQ_TYPE_IMPLEMENT(yq::Segment3U)

YQ_TYPE_IMPLEMENT(yq::Segment4D)
YQ_TYPE_IMPLEMENT(yq::Segment4F)
YQ_TYPE_IMPLEMENT(yq::Segment4I)
YQ_TYPE_IMPLEMENT(yq::Segment4U)

YQ_TYPE_IMPLEMENT(yq::Size2D)
YQ_TYPE_IMPLEMENT(yq::Size2F)
YQ_TYPE_IMPLEMENT(yq::Size2I)
YQ_TYPE_IMPLEMENT(yq::Size2U)

YQ_TYPE_IMPLEMENT(yq::Size3D)
YQ_TYPE_IMPLEMENT(yq::Size3F)
YQ_TYPE_IMPLEMENT(yq::Size3I)
YQ_TYPE_IMPLEMENT(yq::Size3U)

YQ_TYPE_IMPLEMENT(yq::Sphere3D)
YQ_TYPE_IMPLEMENT(yq::Sphere3F)
YQ_TYPE_IMPLEMENT(yq::Sphere3I)
YQ_TYPE_IMPLEMENT(yq::Sphere3U)

YQ_TYPE_IMPLEMENT(yq::Sphere4D)
YQ_TYPE_IMPLEMENT(yq::Sphere4F)
YQ_TYPE_IMPLEMENT(yq::Sphere4I)
YQ_TYPE_IMPLEMENT(yq::Sphere4U)


YQ_TYPE_IMPLEMENT(yq::Tensor11D)
YQ_TYPE_IMPLEMENT(yq::Tensor11F)
YQ_TYPE_IMPLEMENT(yq::Tensor11I)
YQ_TYPE_IMPLEMENT(yq::Tensor11U)

YQ_TYPE_IMPLEMENT(yq::Tensor12D)
YQ_TYPE_IMPLEMENT(yq::Tensor12F)
YQ_TYPE_IMPLEMENT(yq::Tensor12I)
YQ_TYPE_IMPLEMENT(yq::Tensor12U)

YQ_TYPE_IMPLEMENT(yq::Tensor13D)
YQ_TYPE_IMPLEMENT(yq::Tensor13F)
YQ_TYPE_IMPLEMENT(yq::Tensor13I)
YQ_TYPE_IMPLEMENT(yq::Tensor13U)

YQ_TYPE_IMPLEMENT(yq::Tensor14D)
YQ_TYPE_IMPLEMENT(yq::Tensor14F)
YQ_TYPE_IMPLEMENT(yq::Tensor14I)
YQ_TYPE_IMPLEMENT(yq::Tensor14U)

YQ_TYPE_IMPLEMENT(yq::Tensor21D)
YQ_TYPE_IMPLEMENT(yq::Tensor21F)
YQ_TYPE_IMPLEMENT(yq::Tensor21I)
YQ_TYPE_IMPLEMENT(yq::Tensor21U)

YQ_TYPE_IMPLEMENT(yq::Tensor22D)
YQ_TYPE_IMPLEMENT(yq::Tensor22F)
YQ_TYPE_IMPLEMENT(yq::Tensor22I)
YQ_TYPE_IMPLEMENT(yq::Tensor22U)

YQ_TYPE_IMPLEMENT(yq::Tensor23D)
YQ_TYPE_IMPLEMENT(yq::Tensor23F)
YQ_TYPE_IMPLEMENT(yq::Tensor23I)
YQ_TYPE_IMPLEMENT(yq::Tensor23U)

YQ_TYPE_IMPLEMENT(yq::Tensor24D)
YQ_TYPE_IMPLEMENT(yq::Tensor24F)
YQ_TYPE_IMPLEMENT(yq::Tensor24I)
YQ_TYPE_IMPLEMENT(yq::Tensor24U)

YQ_TYPE_IMPLEMENT(yq::Tensor31D)
YQ_TYPE_IMPLEMENT(yq::Tensor31F)
YQ_TYPE_IMPLEMENT(yq::Tensor31I)
YQ_TYPE_IMPLEMENT(yq::Tensor31U)

YQ_TYPE_IMPLEMENT(yq::Tensor32D)
YQ_TYPE_IMPLEMENT(yq::Tensor32F)
YQ_TYPE_IMPLEMENT(yq::Tensor32I)
YQ_TYPE_IMPLEMENT(yq::Tensor32U)

YQ_TYPE_IMPLEMENT(yq::Tensor33D)
YQ_TYPE_IMPLEMENT(yq::Tensor33F)
YQ_TYPE_IMPLEMENT(yq::Tensor33I)
YQ_TYPE_IMPLEMENT(yq::Tensor33U)

YQ_TYPE_IMPLEMENT(yq::Tensor34D)
YQ_TYPE_IMPLEMENT(yq::Tensor34F)
YQ_TYPE_IMPLEMENT(yq::Tensor34I)
YQ_TYPE_IMPLEMENT(yq::Tensor34U)

YQ_TYPE_IMPLEMENT(yq::Tensor41D)
YQ_TYPE_IMPLEMENT(yq::Tensor41F)
YQ_TYPE_IMPLEMENT(yq::Tensor41I)
YQ_TYPE_IMPLEMENT(yq::Tensor41U)

YQ_TYPE_IMPLEMENT(yq::Tensor42D)
YQ_TYPE_IMPLEMENT(yq::Tensor42F)
YQ_TYPE_IMPLEMENT(yq::Tensor42I)
YQ_TYPE_IMPLEMENT(yq::Tensor42U)

YQ_TYPE_IMPLEMENT(yq::Tensor43D)
YQ_TYPE_IMPLEMENT(yq::Tensor43F)
YQ_TYPE_IMPLEMENT(yq::Tensor43I)
YQ_TYPE_IMPLEMENT(yq::Tensor43U)

YQ_TYPE_IMPLEMENT(yq::Tensor44D)
YQ_TYPE_IMPLEMENT(yq::Tensor44F)
YQ_TYPE_IMPLEMENT(yq::Tensor44I)
YQ_TYPE_IMPLEMENT(yq::Tensor44U)

YQ_TYPE_IMPLEMENT(yq::Tetrahedron3D)
YQ_TYPE_IMPLEMENT(yq::Tetrahedron3F)
YQ_TYPE_IMPLEMENT(yq::Tetrahedron3I)
YQ_TYPE_IMPLEMENT(yq::Tetrahedron3U)

YQ_TYPE_IMPLEMENT(yq::Triangle2D)
YQ_TYPE_IMPLEMENT(yq::Triangle2F)
YQ_TYPE_IMPLEMENT(yq::Triangle2I)
YQ_TYPE_IMPLEMENT(yq::Triangle2U)

YQ_TYPE_IMPLEMENT(yq::Triangle3D)
YQ_TYPE_IMPLEMENT(yq::Triangle3F)
YQ_TYPE_IMPLEMENT(yq::Triangle3I)
YQ_TYPE_IMPLEMENT(yq::Triangle3U)

YQ_TYPE_IMPLEMENT(yq::Triangle4D)
YQ_TYPE_IMPLEMENT(yq::Triangle4F)
YQ_TYPE_IMPLEMENT(yq::Triangle4I)
YQ_TYPE_IMPLEMENT(yq::Triangle4U)

YQ_TYPE_IMPLEMENT(yq::Trivector3D)
YQ_TYPE_IMPLEMENT(yq::Trivector3F)

YQ_TYPE_IMPLEMENT(yq::Trivector4D)
YQ_TYPE_IMPLEMENT(yq::Trivector4F)


YQ_TYPE_IMPLEMENT(yq::Vector1D)
YQ_TYPE_IMPLEMENT(yq::Vector1F)
YQ_TYPE_IMPLEMENT(yq::Vector1I)
YQ_TYPE_IMPLEMENT(yq::Vector1U)

YQ_TYPE_IMPLEMENT(yq::Vector2D)
YQ_TYPE_IMPLEMENT(yq::Vector2F)
YQ_TYPE_IMPLEMENT(yq::Vector2I)
YQ_TYPE_IMPLEMENT(yq::Vector2U)

YQ_TYPE_IMPLEMENT(yq::Vector3D)
YQ_TYPE_IMPLEMENT(yq::Vector3F)
YQ_TYPE_IMPLEMENT(yq::Vector3I)
YQ_TYPE_IMPLEMENT(yq::Vector3U)

YQ_TYPE_IMPLEMENT(yq::Vector4D)
YQ_TYPE_IMPLEMENT(yq::Vector4F)
YQ_TYPE_IMPLEMENT(yq::Vector4I)
YQ_TYPE_IMPLEMENT(yq::Vector4U)


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



YQ_INVOKE(


    auto axbox1d = writer<AxBox1D>();
    axbox1d.property("lo", &AxBox1D::lo);
    axbox1d.property("hi", &AxBox1D::hi);

    auto axbox1f = writer<AxBox1F>();
    axbox1f.property("lo", &AxBox1F::lo);
    axbox1f.property("hi", &AxBox1F::hi);

    auto axbox1i = writer<AxBox1I>();
    axbox1i.property("lo", &AxBox1I::lo);
    axbox1i.property("hi", &AxBox1I::hi);

    auto axbox1u = writer<AxBox1U>();
    axbox1u.property("lo", &AxBox1U::lo);
    axbox1u.property("hi", &AxBox1U::hi);


    auto axbox2d = writer<AxBox2D>();
    axbox2d.property("lo", &AxBox2D::lo);
    axbox2d.property("hi", &AxBox2D::hi);

    auto axbox2f = writer<AxBox2F>();
    axbox2f.property("lo", &AxBox2F::lo);
    axbox2f.property("hi", &AxBox2F::hi);

    auto axbox2i = writer<AxBox2I>();
    axbox2i.property("lo", &AxBox2I::lo);
    axbox2i.property("hi", &AxBox2I::hi);

    auto axbox2u = writer<AxBox2U>();
    axbox2u.property("lo", &AxBox2U::lo);
    axbox2u.property("hi", &AxBox2U::hi);


    auto axbox3d = writer<AxBox3D>();
    axbox3d.property("lo", &AxBox3D::lo);
    axbox3d.property("hi", &AxBox3D::hi);

    auto axbox3f = writer<AxBox3F>();
    axbox3f.property("lo", &AxBox3F::lo);
    axbox3f.property("hi", &AxBox3F::hi);

    auto axbox3i = writer<AxBox3I>();
    axbox3i.property("lo", &AxBox3I::lo);
    axbox3i.property("hi", &AxBox3I::hi);

    auto axbox3u = writer<AxBox3U>();
    axbox3u.property("lo", &AxBox3U::lo);
    axbox3u.property("hi", &AxBox3U::hi);


    auto axbox4d = writer<AxBox4D>();
    axbox4d.property("lo", &AxBox4D::lo);
    axbox4d.property("hi", &AxBox4D::hi);

    auto axbox4f = writer<AxBox4F>();
    axbox4f.property("lo", &AxBox4F::lo);
    axbox4f.property("hi", &AxBox4F::hi);

    auto axbox4i = writer<AxBox4I>();
    axbox4i.property("lo", &AxBox4I::lo);
    axbox4i.property("hi", &AxBox4I::hi);

    auto axbox4u = writer<AxBox4U>();
    axbox4u.property("lo", &AxBox4U::lo);
    axbox4u.property("hi", &AxBox4U::hi);


    auto bivec2d = writer<Bivector2D>();
    bivec2d.property("xy", &Bivector2D::xy);

    auto bivec2f = writer<Bivector2F>();
    bivec2f.property("xy", &Bivector2F::xy);


    auto bivec3d = writer<Bivector3D>();
    bivec3d.property("xy", &Bivector3D::xy);
    bivec3d.property("yz", &Bivector3D::yz);
    bivec3d.property("zx", &Bivector3D::zx);

    auto bivec3f = writer<Bivector3F>();
    bivec3f.property("xy", &Bivector3F::xy);
    bivec3f.property("yz", &Bivector3F::yz);
    bivec3f.property("zx", &Bivector3F::zx);


    auto bivec4d = writer<Bivector4D>();
    bivec4d.property("xy", &Bivector4D::xy);
    bivec4d.property("yz", &Bivector4D::yz);
    bivec4d.property("zw", &Bivector4D::zw);
    bivec4d.property("wx", &Bivector4D::wx);
    bivec4d.property("xz", &Bivector4D::xz);
    bivec4d.property("yw", &Bivector4D::yw);

    auto bivec4f = writer<Bivector4F>();
    bivec4f.property("xy", &Bivector4F::xy);
    bivec4f.property("yz", &Bivector4F::yz);
    bivec4f.property("zw", &Bivector4F::zw);
    bivec4f.property("wx", &Bivector4F::wx);
    bivec4f.property("xz", &Bivector4F::xz);
    bivec4f.property("yw", &Bivector4F::yw);


    auto circle2d = writer<Circle2D>();
    circle2d.property("pt", &Circle2D::point);
    circle2d.property("r", &Circle2D::radius);
    
    auto circle2f = writer<Circle2F>();
    circle2f.property("pt", &Circle2F::point);
    circle2f.property("r", &Circle2F::radius);

    auto circle2i = writer<Circle2I>();
    circle2i.property("pt", &Circle2I::point);
    circle2i.property("r", &Circle2I::radius);

    auto circle2u = writer<Circle2U>();
    circle2u.property("pt", &Circle2U::point);
    circle2u.property("r", &Circle2U::radius);


    auto complexD = writer<ComplexD>();
    complexD.property("real", (double (ComplexD::*)() const) &ComplexD::real).setter((void(ComplexD::*)(double)) &ComplexD::real);
    complexD.property("im", (double (ComplexD::*)() const) &ComplexD::imag).setter((void(ComplexD::*)(double)) &ComplexD::imag);

    auto complexF = writer<ComplexF>();
    complexF.property("re", (float (ComplexF::*)() const) &ComplexF::real).setter((void(ComplexF::*)(float)) &ComplexF::real);
    complexF.property("im", (float (ComplexF::*)() const) &ComplexF::imag).setter((void(ComplexF::*)(float)) &ComplexF::imag);

    auto complexI = writer<ComplexI>();
    complexI.property("re", (int (ComplexI::*)() const) &ComplexI::real).setter((void(ComplexI::*)(int)) &ComplexI::real);
    complexI.property("im", (int (ComplexI::*)() const) &ComplexI::imag).setter((void(ComplexI::*)(int)) &ComplexI::imag);

    auto complexU = writer<ComplexU>();
    complexU.property("re", (unsigned (ComplexU::*)() const) &ComplexU::real).setter((void(ComplexU::*)(unsigned)) &ComplexU::real);
    complexU.property("im", (unsigned (ComplexU::*)() const) &ComplexU::imag).setter((void(ComplexU::*)(unsigned)) &ComplexU::imag);


    auto coord2d = writer<Coord2D>();
    coord2d.property("i", &Coord2D::i);
    coord2d.property("j", &Coord2D::j);

    auto coord2f = writer<Coord2F>();
    coord2f.property("i", &Coord2F::i);
    coord2f.property("j", &Coord2F::j);

    auto coord2i = writer<Coord2I>();
    coord2i.property("i", &Coord2I::i);
    coord2i.property("j", &Coord2I::j);

    auto coord2u = writer<Coord2U>();
    coord2u.property("i", &Coord2U::i);
    coord2u.property("j", &Coord2U::j);

    auto fraci  = writer<FractionI>();
    fraci.property("n", &FractionI::num);
    fraci.property("d", &FractionI::den);
    
/*
    auto frac16 = writer<Frac16>();
    frac16.property("n", &Frac16::num);
    frac16.property("d", &Frac16::den);

    auto frac32 = writer<Frac32>();
    frac32.property("n", &Frac32::num);
    frac32.property("d", &Frac32::den);

    auto frac64 = writer<Frac64>();
    frac64.property("n", &Frac64::num);
    frac64.property("d", &Frac64::den);
*/

    auto mul1d  = writer<Multivector1D>();
    mul1d.property("a", &Multivector1D::a);
    mul1d.property("x", &Multivector1D::x);

    auto mul1f  = writer<Multivector1F>();
    mul1f.property("a", &Multivector1F::a);
    mul1f.property("x", &Multivector1F::x);
    
    
    auto mul2d  = writer<Multivector2D>();
    mul2d.property("a", &Multivector2D::a);
    mul2d.property("x", &Multivector2D::x);
    mul2d.property("y", &Multivector2D::y);
    mul2d.property("xy", &Multivector2D::xy);

    auto mul2f  = writer<Multivector2F>();
    mul2f.property("a", &Multivector2F::a);
    mul2f.property("x", &Multivector2F::x);
    mul2f.property("y", &Multivector2F::y);
    mul2f.property("xy", &Multivector2F::xy);
    
    
    auto mul3d  = writer<Multivector3D>();
    mul3d.property("a", &Multivector3D::a);
    mul3d.property("x", &Multivector3D::x);
    mul3d.property("y", &Multivector3D::y);
    mul3d.property("z", &Multivector3D::z);
    mul3d.property("xy", &Multivector3D::xy);
    mul3d.property("yz", &Multivector3D::yz);
    mul3d.property("zx", &Multivector3D::zx);
    mul3d.property("xyz", &Multivector3D::xyz);

    auto mul3f  = writer<Multivector3F>();
    mul3f.property("a", &Multivector3F::a);
    mul3f.property("x", &Multivector3F::x);
    mul3f.property("y", &Multivector3F::y);
    mul3f.property("z", &Multivector3F::z);
    mul3f.property("xy", &Multivector3F::xy);
    mul3f.property("yz", &Multivector3F::yz);
    mul3f.property("zx", &Multivector3F::zx);
    mul3f.property("xyz", &Multivector3F::xyz);
    

    auto mul4d  = writer<Multivector4D>();
    mul4d.property("a", &Multivector4D::a);
    mul4d.property("x", &Multivector4D::x);
    mul4d.property("y", &Multivector4D::y);
    mul4d.property("z", &Multivector4D::z);
    mul4d.property("w", &Multivector4D::w);
    mul4d.property("xy", &Multivector4D::xy);
    mul4d.property("yz", &Multivector4D::yz);
    mul4d.property("zw", &Multivector4D::zw);
    mul4d.property("wx", &Multivector4D::wx);
    mul4d.property("xz", &Multivector4D::xz);
    mul4d.property("yw", &Multivector4D::yw);
    mul4d.property("xyz", &Multivector4D::xyz);
    mul4d.property("yzw", &Multivector4D::yzw);
    mul4d.property("zwx", &Multivector4D::zwx);
    mul4d.property("wxy", &Multivector4D::wxy);
    mul4d.property("xyzw", &Multivector4D::xyzw);

    auto mul4f  = writer<Multivector4F>();
    mul4f.property("a", &Multivector4F::a);
    mul4f.property("x", &Multivector4F::x);
    mul4f.property("y", &Multivector4F::y);
    mul4f.property("z", &Multivector4F::z);
    mul4f.property("w", &Multivector4F::w);
    mul4f.property("xy", &Multivector4F::xy);
    mul4f.property("yz", &Multivector4F::yz);
    mul4f.property("zw", &Multivector4F::zw);
    mul4f.property("wx", &Multivector4F::wx);
    mul4f.property("xz", &Multivector4F::xz);
    mul4f.property("yw", &Multivector4F::yw);
    mul4f.property("xyz", &Multivector4F::xyz);
    mul4f.property("yzw", &Multivector4F::yzw);
    mul4f.property("zwx", &Multivector4F::zwx);
    mul4f.property("wxy", &Multivector4F::wxy);
    mul4f.property("xyzw", &Multivector4F::xyzw);
    

    auto norm2d = writer<Normal2D>();
    norm2d.property("dir", &Normal2D::direction);

    auto norm2f = writer<Normal2F>();
    norm2f.property("dir", &Normal2F::direction);

    auto norm3d = writer<Normal3D>();
    norm3d.property("dir", &Normal3D::direction);
    
    auto norm3f = writer<Normal3F>();
    norm3f.property("dir", &Normal3F::direction);
    
    auto pose3d = writer<Pose3D>();
    pose3d.property("ori", &Pose3D::orientation);
    pose3d.property("pos", &Pose3D::position);
    
    auto pose3f = writer<Pose3F>();
    pose3f.property("ori", &Pose3F::orientation);
    pose3f.property("pos", &Pose3F::position);
    
    auto quad2d = writer<Quadrilateral2D>();
    quad2d.property("a", &Quadrilateral2D::a);
    quad2d.property("b", &Quadrilateral2D::b);
    quad2d.property("c", &Quadrilateral2D::c);
    quad2d.property("d", &Quadrilateral2D::d);

    auto quad2f = writer<Quadrilateral2F>();
    quad2f.property("a", &Quadrilateral2F::a);
    quad2f.property("b", &Quadrilateral2F::b);
    quad2f.property("c", &Quadrilateral2F::c);
    quad2f.property("d", &Quadrilateral2F::d);

    auto quad2i = writer<Quadrilateral2I>();
    quad2i.property("a", &Quadrilateral2I::a);
    quad2i.property("b", &Quadrilateral2I::b);
    quad2i.property("c", &Quadrilateral2I::c);
    quad2i.property("d", &Quadrilateral2I::d);

    auto quad2u = writer<Quadrilateral2U>();
    quad2u.property("a", &Quadrilateral2U::a);
    quad2u.property("b", &Quadrilateral2U::b);
    quad2u.property("c", &Quadrilateral2U::c);
    quad2u.property("d", &Quadrilateral2U::d);


    auto quadvec4d = writer<Quadvector4D>();
    quadvec4d.property("xyzw", &Quadvector4D::xyzw);

    auto quadvec4f = writer<Quadvector4F>();
    quadvec4f.property("xyzw", &Quadvector4F::xyzw);


    auto quat3d = writer<Quaternion3D>();
    quat3d.property("w", &Quaternion3D::w);
    quat3d.property("x", &Quaternion3D::x);
    quat3d.property("y", &Quaternion3D::y);
    quat3d.property("z", &Quaternion3D::z);

    auto quat3f = writer<Quaternion3F>();
    quat3f.property("w", &Quaternion3F::w);
    quat3f.property("x", &Quaternion3F::x);
    quat3f.property("y", &Quaternion3F::y);
    quat3f.property("z", &Quaternion3F::z);
    
    auto ray2d = writer<Ray2D>();
    ray2d.property("pt", &Ray2D::point);
    ray2d.property("dir", &Ray2D::direction);

    auto ray2f = writer<Ray2F>();
    ray2f.property("pt", &Ray2F::point);
    ray2f.property("dir", &Ray2F::direction);

    auto ray3d = writer<Ray3D>();
    ray3d.property("pt", &Ray3D::point);
    ray3d.property("dir", &Ray3D::direction);

    auto ray3f = writer<Ray3F>();
    ray3f.property("pt", &Ray3F::point);
    ray3f.property("dir", &Ray3F::direction);

    auto ray4d = writer<Ray4D>();
    ray4d.property("pt", &Ray4D::point);
    ray4d.property("dir", &Ray4D::direction);

    auto ray4f = writer<Ray4F>();
    ray4f.property("pt", &Ray4F::point);
    ray4f.property("dir", &Ray4F::direction);

    auto rgbd   = writer<RGB3D>();
    rgbd.property("r", &RGB3D::red);
    rgbd.property("g", &RGB3D::green);
    rgbd.property("b", &RGB3D::blue);

    auto rgbf   = writer<RGB3F>();
    rgbf.property("r", &RGB3F::red);
    rgbf.property("g", &RGB3F::green);
    rgbf.property("b", &RGB3F::blue);

    auto rgbu8   = writer<RGB3U8>();
    rgbu8.property("r", &RGB3U8::red);
    rgbu8.property("g", &RGB3U8::green);
    rgbu8.property("b", &RGB3U8::blue);

    auto rgbu16   = writer<RGB3U16>();
    rgbu16.property("r", &RGB3U16::red);
    rgbu16.property("g", &RGB3U16::green);
    rgbu16.property("b", &RGB3U16::blue);

    auto rgbad   = writer<RGBA4D>();
    rgbad.property("r", &RGBA4D::red);
    rgbad.property("g", &RGBA4D::green);
    rgbad.property("b", &RGBA4D::blue);
    rgbad.property("a", &RGBA4D::alpha);

    auto rgbaf   = writer<RGBA4F>();
    rgbaf.property("r", &RGBA4F::red);
    rgbaf.property("g", &RGBA4F::green);
    rgbaf.property("b", &RGBA4F::blue);
    rgbaf.property("a", &RGBA4F::alpha);

    auto rgbau8   = writer<RGBA4U8>();
    rgbau8.property("r", &RGBA4U8::red);
    rgbau8.property("g", &RGBA4U8::green);
    rgbau8.property("b", &RGBA4U8::blue);
    rgbau8.property("a", &RGBA4U8::alpha);

    auto rgbau16   = writer<RGBA4U16>();
    rgbau16.property("r", &RGBA4U16::red);
    rgbau16.property("g", &RGBA4U16::green);
    rgbau16.property("b", &RGBA4U16::blue);
    rgbau16.property("a", &RGBA4U16::alpha);
    
    
    auto rect2d = writer<Rectangle2D>();
    rect2d.property("pos", &Rectangle2D::position);
    rect2d.property("size", &Rectangle2D::size);

    auto rect2f = writer<Rectangle2F>();
    rect2f.property("pos", &Rectangle2F::position);
    rect2f.property("size", &Rectangle2F::size);

    auto rect2i = writer<Rectangle2I>();
    rect2i.property("pos", &Rectangle2I::position);
    rect2i.property("size", &Rectangle2I::size);
    
    auto rect2u = writer<Rectangle2U>();
    rect2u.property("pos", &Rectangle2U::position);
    rect2u.property("size", &Rectangle2U::size);

    auto seg1d = writer<Segment1D>();
    seg1d.property("a", &Segment1D::a);
    seg1d.property("b", &Segment1D::b);

    auto seg1f = writer<Segment1F>();
    seg1f.property("a", &Segment1F::a);
    seg1f.property("b", &Segment1F::b);

    auto seg1i = writer<Segment1I>();
    seg1i.property("a", &Segment1I::a);
    seg1i.property("b", &Segment1I::b);

    auto seg1u = writer<Segment1U>();
    seg1u.property("a", &Segment1U::a);
    seg1u.property("b", &Segment1U::b);


    auto seg2d = writer<Segment2D>();
    seg2d.property("a", &Segment2D::a);
    seg2d.property("b", &Segment2D::b);

    auto seg2f = writer<Segment2F>();
    seg2f.property("a", &Segment2F::a);
    seg2f.property("b", &Segment2F::b);

    auto seg2i = writer<Segment2I>();
    seg2i.property("a", &Segment2I::a);
    seg2i.property("b", &Segment2I::b);

    auto seg2u = writer<Segment2U>();
    seg2u.property("a", &Segment2U::a);
    seg2u.property("b", &Segment2U::b);


    auto seg3d = writer<Segment3D>();
    seg3d.property("a", &Segment3D::a);
    seg3d.property("b", &Segment3D::b);

    auto seg3f = writer<Segment3F>();
    seg3f.property("a", &Segment3F::a);
    seg3f.property("b", &Segment3F::b);

    auto seg3i = writer<Segment3I>();
    seg3i.property("a", &Segment3I::a);
    seg3i.property("b", &Segment3I::b);

    auto seg3u = writer<Segment3U>();
    seg3u.property("a", &Segment3U::a);
    seg3u.property("b", &Segment3U::b);


    auto seg4d = writer<Segment4D>();
    seg4d.property("a", &Segment4D::a);
    seg4d.property("b", &Segment4D::b);

    auto seg4f = writer<Segment4F>();
    seg4f.property("a", &Segment4F::a);
    seg4f.property("b", &Segment4F::b);

    auto seg4i = writer<Segment4I>();
    seg4i.property("a", &Segment4I::a);
    seg4i.property("b", &Segment4I::b);

    auto seg4u = writer<Segment4U>();
    seg4u.property("a", &Segment4U::a);
    seg4u.property("b", &Segment4U::b);

    auto size2d = writer<Size2D>();
    size2d.property("x", &Size2D::x);
    size2d.property("y", &Size2D::y);
    size2d.property("w", &Size2D::width);
    size2d.property("h", &Size2D::height);

    auto size2f = writer<Size2F>();
    size2f.property("x", &Size2F::x);
    size2f.property("y", &Size2F::y);
    size2f.property("w", &Size2F::width);
    size2f.property("h", &Size2F::height);

    auto size2i = writer<Size2I>();
    size2i.property("x", &Size2I::x);
    size2i.property("y", &Size2I::y);
    size2i.property("w", &Size2I::width);
    size2i.property("h", &Size2I::height);

    auto size2u = writer<Size2U>();
    size2u.property("x", &Size2U::x);
    size2u.property("y", &Size2U::y);
    size2u.property("w", &Size2U::width);
    size2u.property("h", &Size2U::height);

    auto size3d = writer<Size3D>();
    size3d.property("x", &Size3D::x);
    size3d.property("y", &Size3D::y);
    size3d.property("z", &Size3D::z);
    size3d.property("w", &Size3D::width);
    size3d.property("h", &Size3D::height);
    size3d.property("d", &Size3D::depth);

    auto size3f = writer<Size3F>();
    size3f.property("x", &Size3F::x);
    size3f.property("y", &Size3F::y);
    size3f.property("z", &Size3F::z);
    size3f.property("w", &Size3F::width);
    size3f.property("h", &Size3F::height);
    size3f.property("d", &Size3F::depth);

    auto size3i = writer<Size3I>();
    size3i.property("x", &Size3I::x);
    size3i.property("y", &Size3I::y);
    size3i.property("z", &Size3I::z);
    size3i.property("w", &Size3I::width);
    size3i.property("h", &Size3I::height);
    size3i.property("d", &Size3I::depth);

    auto size3u = writer<Size3U>();
    size3u.property("x", &Size3U::x);
    size3u.property("y", &Size3U::y);
    size3u.property("z", &Size3U::z);
    size3u.property("w", &Size3U::width);
    size3u.property("h", &Size3U::height);
    size3u.property("d", &Size3U::depth);


    auto sphere3d = writer<Sphere3D>();
    sphere3d.property("pt", &Sphere3D::point);
    sphere3d.property("r", &Sphere3D::radius);
    
    auto sphere3f = writer<Sphere3F>();
    sphere3f.property("pt", &Sphere3F::point);
    sphere3f.property("r", &Sphere3F::radius);

    auto sphere3i = writer<Sphere3I>();
    sphere3i.property("pt", &Sphere3I::point);
    sphere3i.property("r", &Sphere3I::radius);

    auto sphere3u = writer<Sphere3U>();
    sphere3u.property("pt", &Sphere3U::point);
    sphere3u.property("r", &Sphere3U::radius);

    auto sphere4d = writer<Sphere4D>();
    sphere4d.property("pt", &Sphere4D::point);
    sphere4d.property("r", &Sphere4D::radius);
    
    auto sphere4f = writer<Sphere4F>();
    sphere4f.property("pt", &Sphere4F::point);
    sphere4f.property("r", &Sphere4F::radius);

    auto sphere4i = writer<Sphere4I>();
    sphere4i.property("pt", &Sphere4I::point);
    sphere4i.property("r", &Sphere4I::radius);

    auto sphere4u = writer<Sphere4U>();
    sphere4u.property("pt", &Sphere4U::point);
    sphere4u.property("r", &Sphere4U::radius);

    auto ten11d = writer<Tensor11D>();
    ten11d.property("xx", &Tensor11D::xx);

    auto ten11f = writer<Tensor11F>();
    ten11f.property("xx", &Tensor11F::xx);

    auto ten11i = writer<Tensor11I>();
    ten11i.property("xx", &Tensor11I::xx);

    auto ten11u = writer<Tensor11U>();
    ten11u.property("xx", &Tensor11U::xx);


    auto ten12d = writer<Tensor12D>();
    ten12d.property("xx", &Tensor12D::xx);
    ten12d.property("xy", &Tensor12D::xy);

    auto ten12f = writer<Tensor12F>();
    ten12f.property("xx", &Tensor12F::xx);
    ten12f.property("xy", &Tensor12F::xy);

    auto ten12i = writer<Tensor12I>();
    ten12i.property("xx", &Tensor12I::xx);
    ten12i.property("xy", &Tensor12I::xy);

    auto ten12u = writer<Tensor12U>();
    ten12u.property("xx", &Tensor12U::xx);
    ten12u.property("xy", &Tensor12U::xy);


    auto ten13d = writer<Tensor13D>();
    ten13d.property("xx", &Tensor13D::xx);
    ten13d.property("xy", &Tensor13D::xy);
    ten13d.property("xz", &Tensor13D::xz);

    auto ten13f = writer<Tensor13F>();
    ten13f.property("xx", &Tensor13F::xx);
    ten13f.property("xy", &Tensor13F::xy);
    ten13f.property("xz", &Tensor13F::xz);

    auto ten13i = writer<Tensor13I>();
    ten13i.property("xx", &Tensor13I::xx);
    ten13i.property("xy", &Tensor13I::xy);
    ten13i.property("xz", &Tensor13I::xz);

    auto ten13u = writer<Tensor13U>();
    ten13u.property("xx", &Tensor13U::xx);
    ten13u.property("xy", &Tensor13U::xy);
    ten13u.property("xz", &Tensor13U::xz);


    auto ten14d = writer<Tensor14D>();
    ten14d.property("xx", &Tensor14D::xx);
    ten14d.property("xy", &Tensor14D::xy);
    ten14d.property("xz", &Tensor14D::xz);
    ten14d.property("xw", &Tensor14D::xw);

    auto ten14f = writer<Tensor14F>();
    ten14f.property("xx", &Tensor14F::xx);
    ten14f.property("xy", &Tensor14F::xy);
    ten14f.property("xz", &Tensor14F::xz);
    ten14f.property("xw", &Tensor14F::xw);

    auto ten14i = writer<Tensor14I>();
    ten14i.property("xx", &Tensor14I::xx);
    ten14i.property("xy", &Tensor14I::xy);
    ten14i.property("xz", &Tensor14I::xz);
    ten14i.property("xw", &Tensor14I::xw);

    auto ten14u = writer<Tensor14U>();
    ten14u.property("xx", &Tensor14U::xx);
    ten14u.property("xy", &Tensor14U::xy);
    ten14u.property("xz", &Tensor14U::xz);
    ten14u.property("xw", &Tensor14U::xw);


    auto ten21d = writer<Tensor21D>();
    ten21d.property("xx", &Tensor21D::xx);
    ten21d.property("yx", &Tensor21D::yx);

    auto ten21f = writer<Tensor21F>();
    ten21f.property("xx", &Tensor21F::xx);
    ten21f.property("yx", &Tensor21F::yx);

    auto ten21i = writer<Tensor21I>();
    ten21i.property("xx", &Tensor21I::xx);
    ten21i.property("yx", &Tensor21I::yx);

    auto ten21u = writer<Tensor21U>();
    ten21u.property("xx", &Tensor21U::xx);
    ten21u.property("yx", &Tensor21U::yx);


    auto ten22d = writer<Tensor22D>();
    ten22d.property("xx", &Tensor22D::xx);
    ten22d.property("xy", &Tensor22D::xy);
    ten22d.property("yx", &Tensor22D::yx);
    ten22d.property("yy", &Tensor22D::yy);

    auto ten22f = writer<Tensor22F>();
    ten22f.property("xx", &Tensor22F::xx);
    ten22f.property("xy", &Tensor22F::xy);
    ten22f.property("yx", &Tensor22F::yx);
    ten22f.property("yy", &Tensor22F::yy);

    auto ten22i = writer<Tensor22I>();
    ten22i.property("xx", &Tensor22I::xx);
    ten22i.property("xy", &Tensor22I::xy);
    ten22i.property("yx", &Tensor22I::yx);
    ten22i.property("yy", &Tensor22I::yy);

    auto ten22u = writer<Tensor22U>();
    ten22u.property("xx", &Tensor22U::xx);
    ten22u.property("xy", &Tensor22U::xy);
    ten22u.property("yx", &Tensor22U::yx);
    ten22u.property("yy", &Tensor22U::yy);


    auto ten23d = writer<Tensor23D>();
    ten23d.property("xx", &Tensor23D::xx);
    ten23d.property("xy", &Tensor23D::xy);
    ten23d.property("xz", &Tensor23D::xz);
    ten23d.property("yx", &Tensor23D::yx);
    ten23d.property("yy", &Tensor23D::yy);
    ten23d.property("yz", &Tensor23D::yz);

    auto ten23f = writer<Tensor23F>();
    ten23f.property("xx", &Tensor23F::xx);
    ten23f.property("xy", &Tensor23F::xy);
    ten23f.property("xz", &Tensor23F::xz);
    ten23f.property("yx", &Tensor23F::yx);
    ten23f.property("yy", &Tensor23F::yy);
    ten23f.property("yz", &Tensor23F::yz);

    auto ten23i = writer<Tensor23I>();
    ten23i.property("xx", &Tensor23I::xx);
    ten23i.property("xy", &Tensor23I::xy);
    ten23i.property("xz", &Tensor23I::xz);
    ten23i.property("yx", &Tensor23I::yx);
    ten23i.property("yy", &Tensor23I::yy);
    ten23i.property("yz", &Tensor23I::yz);

    auto ten23u = writer<Tensor23U>();
    ten23u.property("xx", &Tensor23U::xx);
    ten23u.property("xy", &Tensor23U::xy);
    ten23u.property("xz", &Tensor23U::xz);
    ten23u.property("yx", &Tensor23U::yx);
    ten23u.property("yy", &Tensor23U::yy);
    ten23u.property("yz", &Tensor23U::yz);


    auto ten24d = writer<Tensor24D>();
    ten24d.property("xx", &Tensor24D::xx);
    ten24d.property("xy", &Tensor24D::xy);
    ten24d.property("xz", &Tensor24D::xz);
    ten24d.property("xw", &Tensor24D::xw);
    ten24d.property("yx", &Tensor24D::yx);
    ten24d.property("yy", &Tensor24D::yy);
    ten24d.property("yz", &Tensor24D::yz);
    ten24d.property("yw", &Tensor24D::yw);

    auto ten24f = writer<Tensor24F>();
    ten24f.property("xx", &Tensor24F::xx);
    ten24f.property("xy", &Tensor24F::xy);
    ten24f.property("xz", &Tensor24F::xz);
    ten24f.property("xw", &Tensor24F::xw);
    ten24f.property("yx", &Tensor24F::yx);
    ten24f.property("yy", &Tensor24F::yy);
    ten24f.property("yz", &Tensor24F::yz);
    ten24f.property("yw", &Tensor24F::yw);

    auto ten24i = writer<Tensor24I>();
    ten24i.property("xx", &Tensor24I::xx);
    ten24i.property("xy", &Tensor24I::xy);
    ten24i.property("xz", &Tensor24I::xz);
    ten24i.property("xw", &Tensor24I::xw);
    ten24i.property("yx", &Tensor24I::yx);
    ten24i.property("yy", &Tensor24I::yy);
    ten24i.property("yz", &Tensor24I::yz);
    ten24i.property("yw", &Tensor24I::yw);

    auto ten24u = writer<Tensor24U>();
    ten24u.property("xx", &Tensor24U::xx);
    ten24u.property("xy", &Tensor24U::xy);
    ten24u.property("xz", &Tensor24U::xz);
    ten24u.property("xw", &Tensor24U::xw);
    ten24u.property("yx", &Tensor24U::yx);
    ten24u.property("yy", &Tensor24U::yy);
    ten24u.property("yz", &Tensor24U::yz);
    ten24u.property("yw", &Tensor24U::yw);


    auto ten31d = writer<Tensor31D>();
    ten31d.property("xx", &Tensor31D::xx);
    ten31d.property("yx", &Tensor31D::yx);
    ten31d.property("zx", &Tensor31D::zx);

    auto ten31f = writer<Tensor31F>();
    ten31f.property("xx", &Tensor31F::xx);
    ten31f.property("yx", &Tensor31F::yx);
    ten31f.property("zx", &Tensor31F::zx);

    auto ten31i = writer<Tensor31I>();
    ten31i.property("xx", &Tensor31I::xx);
    ten31i.property("yx", &Tensor31I::yx);
    ten31i.property("zx", &Tensor31I::zx);

    auto ten31u = writer<Tensor31U>();
    ten31u.property("xx", &Tensor31U::xx);
    ten31u.property("yx", &Tensor31U::yx);
    ten31u.property("zx", &Tensor31U::zx);


    auto ten32d = writer<Tensor32D>();
    ten32d.property("xx", &Tensor32D::xx);
    ten32d.property("xy", &Tensor32D::xy);
    ten32d.property("yx", &Tensor32D::yx);
    ten32d.property("yy", &Tensor32D::yy);
    ten32d.property("zx", &Tensor32D::zx);
    ten32d.property("zy", &Tensor32D::zy);

    auto ten32f = writer<Tensor32F>();
    ten32f.property("xx", &Tensor32F::xx);
    ten32f.property("xy", &Tensor32F::xy);
    ten32f.property("yx", &Tensor32F::yx);
    ten32f.property("yy", &Tensor32F::yy);
    ten32f.property("zx", &Tensor32F::zx);
    ten32f.property("zy", &Tensor32F::zy);

    auto ten32i = writer<Tensor32I>();
    ten32i.property("xx", &Tensor32I::xx);
    ten32i.property("xy", &Tensor32I::xy);
    ten32i.property("yx", &Tensor32I::yx);
    ten32i.property("yy", &Tensor32I::yy);
    ten32i.property("zx", &Tensor32I::zx);
    ten32i.property("zy", &Tensor32I::zy);

    auto ten32u = writer<Tensor32U>();
    ten32u.property("xx", &Tensor32U::xx);
    ten32u.property("xy", &Tensor32U::xy);
    ten32u.property("yx", &Tensor32U::yx);
    ten32u.property("yy", &Tensor32U::yy);
    ten32u.property("zx", &Tensor32U::zx);
    ten32u.property("zy", &Tensor32U::zy);


    auto ten33d = writer<Tensor33D>();
    ten33d.property("xx", &Tensor33D::xx);
    ten33d.property("xy", &Tensor33D::xy);
    ten33d.property("xz", &Tensor33D::xz);
    ten33d.property("yx", &Tensor33D::yx);
    ten33d.property("yy", &Tensor33D::yy);
    ten33d.property("yz", &Tensor33D::yz);
    ten33d.property("zx", &Tensor33D::zx);
    ten33d.property("zy", &Tensor33D::zy);
    ten33d.property("zz", &Tensor33D::zz);

    auto ten33f = writer<Tensor33F>();
    ten33f.property("xx", &Tensor33F::xx);
    ten33f.property("xy", &Tensor33F::xy);
    ten33f.property("xz", &Tensor33F::xz);
    ten33f.property("yx", &Tensor33F::yx);
    ten33f.property("yy", &Tensor33F::yy);
    ten33f.property("yz", &Tensor33F::yz);
    ten33f.property("zx", &Tensor33F::zx);
    ten33f.property("zy", &Tensor33F::zy);
    ten33f.property("zz", &Tensor33F::zz);

    auto ten33i = writer<Tensor33I>();
    ten33i.property("xx", &Tensor33I::xx);
    ten33i.property("xy", &Tensor33I::xy);
    ten33i.property("xz", &Tensor33I::xz);
    ten33i.property("yx", &Tensor33I::yx);
    ten33i.property("yy", &Tensor33I::yy);
    ten33i.property("yz", &Tensor33I::yz);
    ten33i.property("zx", &Tensor33I::zx);
    ten33i.property("zy", &Tensor33I::zy);
    ten33i.property("zz", &Tensor33I::zz);

    auto ten33u = writer<Tensor33U>();
    ten33u.property("xx", &Tensor33U::xx);
    ten33u.property("xy", &Tensor33U::xy);
    ten33u.property("xz", &Tensor33U::xz);
    ten33u.property("yx", &Tensor33U::yx);
    ten33u.property("yy", &Tensor33U::yy);
    ten33u.property("yz", &Tensor33U::yz);
    ten33u.property("zx", &Tensor33U::zx);
    ten33u.property("zy", &Tensor33U::zy);
    ten33u.property("zz", &Tensor33U::zz);


    auto ten34d = writer<Tensor34D>();
    ten34d.property("xx", &Tensor34D::xx);
    ten34d.property("xy", &Tensor34D::xy);
    ten34d.property("xz", &Tensor34D::xz);
    ten34d.property("xw", &Tensor34D::xw);
    ten34d.property("yx", &Tensor34D::yx);
    ten34d.property("yy", &Tensor34D::yy);
    ten34d.property("yz", &Tensor34D::yz);
    ten34d.property("yw", &Tensor34D::yw);
    ten34d.property("zx", &Tensor34D::zx);
    ten34d.property("zy", &Tensor34D::zy);
    ten34d.property("zz", &Tensor34D::zz);
    ten34d.property("zw", &Tensor34D::zw);

    auto ten34f = writer<Tensor34F>();
    ten34f.property("xx", &Tensor34F::xx);
    ten34f.property("xy", &Tensor34F::xy);
    ten34f.property("xz", &Tensor34F::xz);
    ten34f.property("xw", &Tensor34F::xw);
    ten34f.property("yx", &Tensor34F::yx);
    ten34f.property("yy", &Tensor34F::yy);
    ten34f.property("yz", &Tensor34F::yz);
    ten34f.property("yw", &Tensor34F::yw);
    ten34f.property("zx", &Tensor34F::zx);
    ten34f.property("zy", &Tensor34F::zy);
    ten34f.property("zz", &Tensor34F::zz);
    ten34f.property("zw", &Tensor34F::zw);

    auto ten34i = writer<Tensor34I>();
    ten34i.property("xx", &Tensor34I::xx);
    ten34i.property("xy", &Tensor34I::xy);
    ten34i.property("xz", &Tensor34I::xz);
    ten34i.property("xw", &Tensor34I::xw);
    ten34i.property("yx", &Tensor34I::yx);
    ten34i.property("yy", &Tensor34I::yy);
    ten34i.property("yz", &Tensor34I::yz);
    ten34i.property("yw", &Tensor34I::yw);
    ten34i.property("zx", &Tensor34I::zx);
    ten34i.property("zy", &Tensor34I::zy);
    ten34i.property("zz", &Tensor34I::zz);
    ten34i.property("zw", &Tensor34I::zw);

    auto ten34u = writer<Tensor34U>();
    ten34u.property("xx", &Tensor34U::xx);
    ten34u.property("xy", &Tensor34U::xy);
    ten34u.property("xz", &Tensor34U::xz);
    ten34u.property("xw", &Tensor34U::xw);
    ten34u.property("yx", &Tensor34U::yx);
    ten34u.property("yy", &Tensor34U::yy);
    ten34u.property("yz", &Tensor34U::yz);
    ten34u.property("yw", &Tensor34U::yw);
    ten34u.property("zx", &Tensor34U::zx);
    ten34u.property("zy", &Tensor34U::zy);
    ten34u.property("zz", &Tensor34U::zz);
    ten34u.property("zw", &Tensor34U::zw);


    auto ten41d = writer<Tensor41D>();
    ten41d.property("xx", &Tensor41D::xx);
    ten41d.property("yx", &Tensor41D::yx);
    ten41d.property("zx", &Tensor41D::zx);
    ten41d.property("wx", &Tensor41D::wx);

    auto ten41f = writer<Tensor41F>();
    ten41f.property("xx", &Tensor41F::xx);
    ten41f.property("yx", &Tensor41F::yx);
    ten41f.property("zx", &Tensor41F::zx);
    ten41f.property("wx", &Tensor41F::wx);

    auto ten41i = writer<Tensor41I>();
    ten41i.property("xx", &Tensor41I::xx);
    ten41i.property("yx", &Tensor41I::yx);
    ten41i.property("zx", &Tensor41I::zx);
    ten41i.property("wx", &Tensor41I::wx);

    auto ten41u = writer<Tensor41U>();
    ten41u.property("xx", &Tensor41U::xx);
    ten41u.property("yx", &Tensor41U::yx);
    ten41u.property("zx", &Tensor41U::zx);
    ten41u.property("wx", &Tensor41U::wx);


    auto ten42d = writer<Tensor42D>();
    ten42d.property("xx", &Tensor42D::xx);
    ten42d.property("xy", &Tensor42D::xy);
    ten42d.property("yx", &Tensor42D::yx);
    ten42d.property("yy", &Tensor42D::yy);
    ten42d.property("zx", &Tensor42D::zx);
    ten42d.property("zy", &Tensor42D::zy);
    ten42d.property("wx", &Tensor42D::wx);
    ten42d.property("wy", &Tensor42D::wy);

    auto ten42f = writer<Tensor42F>();
    ten42f.property("xx", &Tensor42F::xx);
    ten42f.property("xy", &Tensor42F::xy);
    ten42f.property("yx", &Tensor42F::yx);
    ten42f.property("yy", &Tensor42F::yy);
    ten42f.property("zx", &Tensor42F::zx);
    ten42f.property("zy", &Tensor42F::zy);
    ten42f.property("wx", &Tensor42F::wx);
    ten42f.property("wy", &Tensor42F::wy);

    auto ten42i = writer<Tensor42I>();
    ten42i.property("xx", &Tensor42I::xx);
    ten42i.property("xy", &Tensor42I::xy);
    ten42i.property("yx", &Tensor42I::yx);
    ten42i.property("yy", &Tensor42I::yy);
    ten42i.property("zx", &Tensor42I::zx);
    ten42i.property("zy", &Tensor42I::zy);
    ten42i.property("wx", &Tensor42I::wx);
    ten42i.property("wy", &Tensor42I::wy);

    auto ten42u = writer<Tensor42U>();
    ten42u.property("xx", &Tensor42U::xx);
    ten42u.property("xy", &Tensor42U::xy);
    ten42u.property("yx", &Tensor42U::yx);
    ten42u.property("yy", &Tensor42U::yy);
    ten42u.property("zx", &Tensor42U::zx);
    ten42u.property("zy", &Tensor42U::zy);
    ten42u.property("wx", &Tensor42U::wx);
    ten42u.property("wy", &Tensor42U::wy);


    auto ten43d = writer<Tensor43D>();
    ten43d.property("xx", &Tensor43D::xx);
    ten43d.property("xy", &Tensor43D::xy);
    ten43d.property("xz", &Tensor43D::xz);
    ten43d.property("yx", &Tensor43D::yx);
    ten43d.property("yy", &Tensor43D::yy);
    ten43d.property("yz", &Tensor43D::yz);
    ten43d.property("zx", &Tensor43D::zx);
    ten43d.property("zy", &Tensor43D::zy);
    ten43d.property("zz", &Tensor43D::zz);
    ten43d.property("wx", &Tensor43D::wx);
    ten43d.property("wy", &Tensor43D::wy);
    ten43d.property("wz", &Tensor43D::wz);

    auto ten43f = writer<Tensor43F>();
    ten43f.property("xx", &Tensor43F::xx);
    ten43f.property("xy", &Tensor43F::xy);
    ten43f.property("xz", &Tensor43F::xz);
    ten43f.property("yx", &Tensor43F::yx);
    ten43f.property("yy", &Tensor43F::yy);
    ten43f.property("yz", &Tensor43F::yz);
    ten43f.property("zx", &Tensor43F::zx);
    ten43f.property("zy", &Tensor43F::zy);
    ten43f.property("zz", &Tensor43F::zz);
    ten43f.property("wx", &Tensor43F::wx);
    ten43f.property("wy", &Tensor43F::wy);
    ten43f.property("wz", &Tensor43F::wz);

    auto ten43i = writer<Tensor43I>();
    ten43i.property("xx", &Tensor43I::xx);
    ten43i.property("xy", &Tensor43I::xy);
    ten43i.property("xz", &Tensor43I::xz);
    ten43i.property("yx", &Tensor43I::yx);
    ten43i.property("yy", &Tensor43I::yy);
    ten43i.property("yz", &Tensor43I::yz);
    ten43i.property("zx", &Tensor43I::zx);
    ten43i.property("zy", &Tensor43I::zy);
    ten43i.property("zz", &Tensor43I::zz);
    ten43i.property("wx", &Tensor43I::wx);
    ten43i.property("wy", &Tensor43I::wy);
    ten43i.property("wz", &Tensor43I::wz);

    auto ten43u = writer<Tensor43U>();
    ten43u.property("xx", &Tensor43U::xx);
    ten43u.property("xy", &Tensor43U::xy);
    ten43u.property("xz", &Tensor43U::xz);
    ten43u.property("yx", &Tensor43U::yx);
    ten43u.property("yy", &Tensor43U::yy);
    ten43u.property("yz", &Tensor43U::yz);
    ten43u.property("zx", &Tensor43U::zx);
    ten43u.property("zy", &Tensor43U::zy);
    ten43u.property("zz", &Tensor43U::zz);
    ten43u.property("wx", &Tensor43U::wx);
    ten43u.property("wy", &Tensor43U::wy);
    ten43u.property("wz", &Tensor43U::wz);


    auto ten44d = writer<Tensor44D>();
    ten44d.property("xx", &Tensor44D::xx);
    ten44d.property("xy", &Tensor44D::xy);
    ten44d.property("xz", &Tensor44D::xz);
    ten44d.property("xw", &Tensor44D::xw);
    ten44d.property("yx", &Tensor44D::yx);
    ten44d.property("yy", &Tensor44D::yy);
    ten44d.property("yz", &Tensor44D::yz);
    ten44d.property("yw", &Tensor44D::yw);
    ten44d.property("zx", &Tensor44D::zx);
    ten44d.property("zy", &Tensor44D::zy);
    ten44d.property("zz", &Tensor44D::zz);
    ten44d.property("zw", &Tensor44D::zw);
    ten44d.property("wx", &Tensor44D::wx);
    ten44d.property("wy", &Tensor44D::wy);
    ten44d.property("wz", &Tensor44D::wz);
    ten44d.property("ww", &Tensor44D::ww);

    auto ten44f = writer<Tensor44F>();
    ten44f.property("xx", &Tensor44F::xx);
    ten44f.property("xy", &Tensor44F::xy);
    ten44f.property("xz", &Tensor44F::xz);
    ten44f.property("xw", &Tensor44F::xw);
    ten44f.property("yx", &Tensor44F::yx);
    ten44f.property("yy", &Tensor44F::yy);
    ten44f.property("yz", &Tensor44F::yz);
    ten44f.property("yw", &Tensor44F::yw);
    ten44f.property("zx", &Tensor44F::zx);
    ten44f.property("zy", &Tensor44F::zy);
    ten44f.property("zz", &Tensor44F::zz);
    ten44f.property("zw", &Tensor44F::zw);
    ten44f.property("wx", &Tensor44F::wx);
    ten44f.property("wy", &Tensor44F::wy);
    ten44f.property("wz", &Tensor44F::wz);
    ten44f.property("ww", &Tensor44F::ww);

    auto ten44i = writer<Tensor44I>();
    ten44i.property("xx", &Tensor44I::xx);
    ten44i.property("xy", &Tensor44I::xy);
    ten44i.property("xz", &Tensor44I::xz);
    ten44i.property("xw", &Tensor44I::xw);
    ten44i.property("yx", &Tensor44I::yx);
    ten44i.property("yy", &Tensor44I::yy);
    ten44i.property("yz", &Tensor44I::yz);
    ten44i.property("yw", &Tensor44I::yw);
    ten44i.property("zx", &Tensor44I::zx);
    ten44i.property("zy", &Tensor44I::zy);
    ten44i.property("zz", &Tensor44I::zz);
    ten44i.property("zw", &Tensor44I::zw);
    ten44i.property("wx", &Tensor44I::wx);
    ten44i.property("wy", &Tensor44I::wy);
    ten44i.property("wz", &Tensor44I::wz);
    ten44i.property("ww", &Tensor44I::ww);

    auto ten44u = writer<Tensor44U>();
    ten44u.property("xx", &Tensor44U::xx);
    ten44u.property("xy", &Tensor44U::xy);
    ten44u.property("xz", &Tensor44U::xz);
    ten44u.property("xw", &Tensor44U::xw);
    ten44u.property("yx", &Tensor44U::yx);
    ten44u.property("yy", &Tensor44U::yy);
    ten44u.property("yz", &Tensor44U::yz);
    ten44u.property("yw", &Tensor44U::yw);
    ten44u.property("zx", &Tensor44U::zx);
    ten44u.property("zy", &Tensor44U::zy);
    ten44u.property("zz", &Tensor44U::zz);
    ten44u.property("zw", &Tensor44U::zw);
    ten44u.property("wx", &Tensor44U::wx);
    ten44u.property("wy", &Tensor44U::wy);
    ten44u.property("wz", &Tensor44U::wz);
    ten44u.property("ww", &Tensor44U::ww);

    auto tetrahedron3d = writer<Tetrahedron3D>();
    tetrahedron3d.property("a", &Tetrahedron3D::a);
    tetrahedron3d.property("b", &Tetrahedron3D::b);
    tetrahedron3d.property("c", &Tetrahedron3D::c);
    tetrahedron3d.property("d", &Tetrahedron3D::d);
    
    auto tetrahedron3f = writer<Tetrahedron3F>();
    tetrahedron3f.property("a", &Tetrahedron3F::a);
    tetrahedron3f.property("b", &Tetrahedron3F::b);
    tetrahedron3f.property("c", &Tetrahedron3F::c);
    tetrahedron3f.property("d", &Tetrahedron3F::d);

    auto tetrahedron3i = writer<Tetrahedron3I>();
    tetrahedron3i.property("a", &Tetrahedron3I::a);
    tetrahedron3i.property("b", &Tetrahedron3I::b);
    tetrahedron3i.property("c", &Tetrahedron3I::c);
    tetrahedron3i.property("d", &Tetrahedron3I::d);

    auto tetrahedron3u = writer<Tetrahedron3U>();
    tetrahedron3u.property("a", &Tetrahedron3U::a);
    tetrahedron3u.property("b", &Tetrahedron3U::b);
    tetrahedron3u.property("c", &Tetrahedron3U::c);
    tetrahedron3u.property("d", &Tetrahedron3U::d);


    auto triangle2d = writer<Triangle2D>();
    triangle2d.property("a", &Triangle2D::a);
    triangle2d.property("b", &Triangle2D::b);
    triangle2d.property("c", &Triangle2D::c);
    
    auto triangle2f = writer<Triangle2F>();
    triangle2f.property("a", &Triangle2F::a);
    triangle2f.property("b", &Triangle2F::b);
    triangle2f.property("c", &Triangle2F::c);

    auto triangle2i = writer<Triangle2I>();
    triangle2i.property("a", &Triangle2I::a);
    triangle2i.property("b", &Triangle2I::b);
    triangle2i.property("c", &Triangle2I::c);

    auto triangle2u = writer<Triangle2U>();
    triangle2u.property("a", &Triangle2U::a);
    triangle2u.property("b", &Triangle2U::b);
    triangle2u.property("c", &Triangle2U::c);
    

    auto triangle3d = writer<Triangle3D>();
    triangle3d.property("a", &Triangle3D::a);
    triangle3d.property("b", &Triangle3D::b);
    triangle3d.property("c", &Triangle3D::c);
    
    auto triangle3f = writer<Triangle3F>();
    triangle3f.property("a", &Triangle3F::a);
    triangle3f.property("b", &Triangle3F::b);
    triangle3f.property("c", &Triangle3F::c);

    auto triangle3i = writer<Triangle3I>();
    triangle3i.property("a", &Triangle3I::a);
    triangle3i.property("b", &Triangle3I::b);
    triangle3i.property("c", &Triangle3I::c);

    auto triangle3u = writer<Triangle3U>();
    triangle3u.property("a", &Triangle3U::a);
    triangle3u.property("b", &Triangle3U::b);
    triangle3u.property("c", &Triangle3U::c);


    auto triangle4d = writer<Triangle4D>();
    triangle4d.property("a", &Triangle4D::a);
    triangle4d.property("b", &Triangle4D::b);
    triangle4d.property("c", &Triangle4D::c);
    
    auto triangle4f = writer<Triangle4F>();
    triangle4f.property("a", &Triangle4F::a);
    triangle4f.property("b", &Triangle4F::b);
    triangle4f.property("c", &Triangle4F::c);

    auto triangle4i = writer<Triangle4I>();
    triangle4i.property("a", &Triangle4I::a);
    triangle4i.property("b", &Triangle4I::b);
    triangle4i.property("c", &Triangle4I::c);

    auto triangle4u = writer<Triangle4U>();
    triangle4u.property("a", &Triangle4U::a);
    triangle4u.property("b", &Triangle4U::b);
    triangle4u.property("c", &Triangle4U::c);


    auto trivec3d = writer<Trivector3D>();
    trivec3d.property("xyz", &Trivector3D::xyz);

    auto trivec3f = writer<Trivector3F>();
    trivec3f.property("xyz", &Trivector3F::xyz);
    

    auto trivec4d = writer<Trivector4D>();
    trivec4d.property("xyz", &Trivector4D::xyz);
    trivec4d.property("yzw", &Trivector4D::yzw);
    trivec4d.property("zwx", &Trivector4D::zwx);
    trivec4d.property("wxy", &Trivector4D::wxy);

    auto trivec4f = writer<Trivector4F>();
    trivec4f.property("xyz", &Trivector4F::xyz);
    trivec4f.property("yzw", &Trivector4F::yzw);
    trivec4f.property("zwx", &Trivector4F::zwx);
    trivec4f.property("wxy", &Trivector4F::wxy);
    

    auto vec1d = writer<Vector1D>();
    vec1d.property("x", &Vector1D::x);

    auto vec1f = writer<Vector1F>();
    vec1f.property("x", &Vector1F::x);

    auto vec1i = writer<Vector1I>();
    vec1i.property("x", &Vector1I::x);

    auto vec1u = writer<Vector1U>();
    vec1u.property("x", &Vector1U::x);


    auto vec2d = writer<Vector2D>();
    vec2d.property("x", &Vector2D::x);
    vec2d.property("y", &Vector2D::y);

    auto vec2f = writer<Vector2F>();
    vec2f.property("x", &Vector2F::x);
    vec2f.property("y", &Vector2F::y);

    auto vec2i = writer<Vector2I>();
    vec2i.property("x", &Vector2I::x);
    vec2i.property("y", &Vector2I::y);

    auto vec2u = writer<Vector2U>();
    vec2u.property("x", &Vector2U::x);
    vec2u.property("y", &Vector2U::y);


    auto vec3d = writer<Vector3D>();
    vec3d.property("x", &Vector3D::x);
    vec3d.property("y", &Vector3D::y);
    vec3d.property("z", &Vector3D::z);

    auto vec3f = writer<Vector3F>();
    vec3f.property("x", &Vector3F::x);
    vec3f.property("y", &Vector3F::y);
    vec3f.property("z", &Vector3F::z);

    auto vec3i = writer<Vector3I>();
    vec3i.property("x", &Vector3I::x);
    vec3i.property("y", &Vector3I::y);
    vec3i.property("z", &Vector3I::z);

    auto vec3u = writer<Vector3U>();
    vec3u.property("x", &Vector3U::x);
    vec3u.property("y", &Vector3U::y);
    vec3u.property("z", &Vector3U::z);


    auto vec4d = writer<Vector4D>();
    vec4d.property("x", &Vector4D::x);
    vec4d.property("y", &Vector4D::y);
    vec4d.property("z", &Vector4D::z);
    vec4d.property("w", &Vector4D::w);

    auto vec4f = writer<Vector4F>();
    vec4f.property("x", &Vector4F::x);
    vec4f.property("y", &Vector4F::y);
    vec4f.property("z", &Vector4F::z);
    vec4f.property("w", &Vector4F::w);

    auto vec4i = writer<Vector4I>();
    vec4i.property("x", &Vector4I::x);
    vec4i.property("y", &Vector4I::y);
    vec4i.property("z", &Vector4I::z);
    vec4i.property("w", &Vector4I::w);

    auto vec4u = writer<Vector4U>();
    vec4u.property("x", &Vector4U::x);
    vec4u.property("y", &Vector4U::y);
    vec4u.property("z", &Vector4U::z);
    vec4u.property("w", &Vector4U::w);
);

namespace yq {
    void        initialize_math()
    {
    }
}
