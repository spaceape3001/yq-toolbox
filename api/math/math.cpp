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

#include <math/Counter.hpp>

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

#include <math/Range.hpp>

#include <math/Rectangle2.hpp>

#include <math/Segment1.hpp>
#include <math/Segment2.hpp>
#include <math/Segment3.hpp>
#include <math/Segment4.hpp>

#include <math/Size1.hpp>
#include <math/Size2.hpp>
#include <math/Size3.hpp>
#include <math/Size4.hpp>

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
#include <math/shape_utils.hpp>
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

YQ_TYPE_IMPLEMENT(yq::CountI8)
YQ_TYPE_IMPLEMENT(yq::CountI16)
YQ_TYPE_IMPLEMENT(yq::CountI32)
YQ_TYPE_IMPLEMENT(yq::CountI64)

YQ_TYPE_IMPLEMENT(yq::CountU8)
YQ_TYPE_IMPLEMENT(yq::CountU16)
YQ_TYPE_IMPLEMENT(yq::CountU32)
YQ_TYPE_IMPLEMENT(yq::CountU64)

YQ_TYPE_IMPLEMENT(yq::Dimension)


YQ_TYPE_IMPLEMENT(yq::FractionI)
//YQ_TYPE_IMPLEMENT(yq::Frac16)
//YQ_TYPE_IMPLEMENT(yq::Frac32)
//YQ_TYPE_IMPLEMENT(yq::Frac64)

YQ_TYPE_IMPLEMENT(yq::HCountI8)
YQ_TYPE_IMPLEMENT(yq::HCountI16)
YQ_TYPE_IMPLEMENT(yq::HCountI32)
YQ_TYPE_IMPLEMENT(yq::HCountI64)

YQ_TYPE_IMPLEMENT(yq::HCountU8)
YQ_TYPE_IMPLEMENT(yq::HCountU16)
YQ_TYPE_IMPLEMENT(yq::HCountU32)
YQ_TYPE_IMPLEMENT(yq::HCountU64)

YQ_TYPE_IMPLEMENT(yq::LCountI8)
YQ_TYPE_IMPLEMENT(yq::LCountI16)
YQ_TYPE_IMPLEMENT(yq::LCountI32)
YQ_TYPE_IMPLEMENT(yq::LCountI64)

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

YQ_TYPE_IMPLEMENT(yq::RangeD)
YQ_TYPE_IMPLEMENT(yq::RangeF)
YQ_TYPE_IMPLEMENT(yq::RangeI)
YQ_TYPE_IMPLEMENT(yq::RangeU)

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

YQ_TYPE_IMPLEMENT(yq::Size1D)
YQ_TYPE_IMPLEMENT(yq::Size1F)
YQ_TYPE_IMPLEMENT(yq::Size1I)
YQ_TYPE_IMPLEMENT(yq::Size1U)

YQ_TYPE_IMPLEMENT(yq::Size2D)
YQ_TYPE_IMPLEMENT(yq::Size2F)
YQ_TYPE_IMPLEMENT(yq::Size2I)
YQ_TYPE_IMPLEMENT(yq::Size2U)

YQ_TYPE_IMPLEMENT(yq::Size3D)
YQ_TYPE_IMPLEMENT(yq::Size3F)
YQ_TYPE_IMPLEMENT(yq::Size3I)
YQ_TYPE_IMPLEMENT(yq::Size3U)

YQ_TYPE_IMPLEMENT(yq::Size4D)
YQ_TYPE_IMPLEMENT(yq::Size4F)
YQ_TYPE_IMPLEMENT(yq::Size4I)
YQ_TYPE_IMPLEMENT(yq::Size4U)

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


//  Grammaer to below

static constexpr const std::string_view     szA                         = "a";
static constexpr const std::string_view     szAlpha                     = "alpha";
static constexpr const std::string_view     szAlpha_Color               = "Alpha channel of the color";
static constexpr const std::string_view     szArea                      = "area";
static constexpr const std::string_view     szArea_Box                  = "Area of the box";
static constexpr const std::string_view     szArea_Circle               = "Area of the box";
static constexpr const std::string_view     szB                         = "b";
static constexpr const std::string_view     szBlue                      = "blue";
static constexpr const std::string_view     szBlue_Color                = "Blue channel of the color";
static constexpr const std::string_view     szBox                       = "box";
static constexpr const std::string_view     szBox_Circle                = "Bounding box of the circle";
static constexpr const std::string_view     szCenter                    = "center";
static constexpr const std::string_view     szCenter_Box                = "Center of the box";
static constexpr const std::string_view     szCenter_Circle             = "Center of the circle";
static constexpr const std::string_view     szCircumcircle              = "circumcircle";
static constexpr const std::string_view     szCircumcircle_Box          = "Circumcircle of the box";
static constexpr const std::string_view     szCircumference             = "circumference";
static constexpr const std::string_view     szCircumference_Circle      = "Circumference of the circle";
static constexpr const std::string_view     szContains                  = "contains";
static constexpr const std::string_view     szContains_Box_Box          = "Tests if other box is inside/touching this box";
static constexpr const std::string_view     szContains_Box_Pt           = "Tests if point is inside/touching the box";
static constexpr const std::string_view     szCtr                       = "ctr";
static constexpr const std::string_view     szD                         = "d";
static constexpr const std::string_view     szDia                       = "dia";
static constexpr const std::string_view     szDiameter                  = "diameter";
static constexpr const std::string_view     szDiameter_Circle           = "Diameter of the circle";
static constexpr const std::string_view     szDim                       = "dim";
static constexpr const std::string_view     szDimension                 = "dimensions";
static constexpr const std::string_view     szDimension_Box             = "Dimension(s) of the box";
static constexpr const std::string_view     szDir                       = "dir";
static constexpr const std::string_view     szDirection                 = "direction";
static constexpr const std::string_view     szDirection_Ray             = "Direction of the ray";
static constexpr const std::string_view     szEclipses                  = "eclipses";
static constexpr const std::string_view     szEclipses_Box_Box          = "Tests if other box is inside/touching this box";
static constexpr const std::string_view     szEclipses_Box_Circle       = "Tests if circle is inside/touching this box";
static constexpr const std::string_view     szEclipses_Box_Pt           = "Tests if point is inside/touching the box";
static constexpr const std::string_view     szG                         = "g";
static constexpr const std::string_view     szGreen                     = "green";
static constexpr const std::string_view     szGreen_Color               = "Green channel of the color";
static constexpr const std::string_view     szHigh                      = "hi";
static constexpr const std::string_view     szHigh_Box                  = "High-corner of the box";
static constexpr const std::string_view     szHigh_Range                = "High-value of the range";
static constexpr const std::string_view     szHypervolume               = "hypervolume";
static constexpr const std::string_view     szHypervolume_Box4          = "Hypervolume of the box";
static constexpr const std::string_view     szHVol                      = "hvol";
static constexpr const std::string_view     szIncircle                  = "incircle";
static constexpr const std::string_view     szIncircle_Box              = "Incircle of the box";
static constexpr const std::string_view     szLen                       = "len";
static constexpr const std::string_view     szLen²                      = "len2";
static constexpr const std::string_view     szLength                    = "length";
static constexpr const std::string_view     szLength_Vector             = "Length of the vector";
static constexpr const std::string_view     szLength²                   = "length2";
static constexpr const std::string_view     szLength²_Vector            = "Length SQUARED of the vector";
static constexpr const std::string_view     szLow                       = "lo";
static constexpr const std::string_view     szLow_Box                   = "Low-corner of the box";
static constexpr const std::string_view     szLow_Range                 = "Low-value of the range";
static constexpr const std::string_view     szNE                        = "ne";
static constexpr const std::string_view     szNortheast                 = "northeast";
static constexpr const std::string_view     szNortheast_Box             = "North-east corner of the box";
static constexpr const std::string_view     szNorthwest                 = "northwest";
static constexpr const std::string_view     szNorthwest_Box             = "North-west corner of the box";
static constexpr const std::string_view     szNW                        = "nw";
static constexpr const std::string_view     szOverlaps                  = "overlaps";
static constexpr const std::string_view     szOverlaps_Box_Box          = "Tests if other box overlaps this box";
static constexpr const std::string_view     szPerimeter                 = "perimeter";
static constexpr const std::string_view     szPerimeter_Box             = "Perimeter of the box";
static constexpr const std::string_view     szPerimeter_Circle          = "Perimeter of the circle";
static constexpr const std::string_view     szPoint                     = "point";
static constexpr const std::string_view     szPoint_Ray                 = "Point of the ray";
static constexpr const std::string_view     szProject                   = "global";
static constexpr const std::string_view     szProject_Box               = "Project local point (u/v/w) to real space (x/y/z)";
static constexpr const std::string_view     szR                         = "r";
static constexpr const std::string_view     szRadius                    = "radius";
static constexpr const std::string_view     szRadius_Circle             = "Radius of the circle";
static constexpr const std::string_view     szRed                       = "red";
static constexpr const std::string_view     szRed_Color                 = "Red channel of the color";
static constexpr const std::string_view     szSE                        = "se";
static constexpr const std::string_view     szSArea                     = "sarea";
static constexpr const std::string_view     szSize                      = "size";
static constexpr const std::string_view     szSize_Box                  = "Size of the box";
static constexpr const std::string_view     szSoutheast                 = "southeast";
static constexpr const std::string_view     szSoutheast_Box             = "North-east corner of the box";
static constexpr const std::string_view     szSouthwest                 = "southwest";
static constexpr const std::string_view     szSouthwest_Box             = "North-west corner of the box";
static constexpr const std::string_view     szSurfaceArea               = "surface_area";
static constexpr const std::string_view     szSurfaceArea_Box3          = "Surface area of the box";
static constexpr const std::string_view     szSW                        = "sw";
static constexpr const std::string_view     szUnproject                 = "local";
static constexpr const std::string_view     szUnproject_Box             = "Project global point (x/y/z) to local space (u/v/w)";
static constexpr const std::string_view     szValid                     = "valid";
static constexpr const std::string_view     szValid_Box                 = "Tests if the box is valid (ie, lo < hi)";
static constexpr const std::string_view     szValid_Circle              = "Tests if the circle is valid (ie, radius >= 0)";
static constexpr const std::string_view     szVol                       = "vol";
static constexpr const std::string_view     szVolume                    = "volume";
static constexpr const std::string_view     szVolume_Box                = "Volume of the box";
static constexpr const std::string_view     szW                         = "w";
static constexpr const std::string_view     szW_Box                     = "W range of the box";
static constexpr const std::string_view     szW_Vector                  = "W component of the vector";
static constexpr const std::string_view     szWW                        = "ww";
static constexpr const std::string_view     szWW_Tensor                 = "WW component of the tensor";
static constexpr const std::string_view     szWX                        = "wx";
static constexpr const std::string_view     szWX_Tensor                 = "WX component of the tensor";
static constexpr const std::string_view     szWY                        = "wy";
static constexpr const std::string_view     szWY_Tensor                 = "WY component of the tensor";
static constexpr const std::string_view     szWZ                        = "wz";
static constexpr const std::string_view     szWZ_Tensor                 = "WZ component of the tensor";
static constexpr const std::string_view     szX                         = "x";
static constexpr const std::string_view     szX_Box                     = "X range of the box";
static constexpr const std::string_view     szX_Vector                  = "X component of the vector";
static constexpr const std::string_view     szXW                        = "xw";
static constexpr const std::string_view     szXW_Tensor                 = "XW component of the tensor";
static constexpr const std::string_view     szXX                        = "xx";
static constexpr const std::string_view     szXX_Tensor                 = "XX component of the tensor";
static constexpr const std::string_view     szXY                        = "xy";
static constexpr const std::string_view     szXY_Bivector               = "XY component of the bivector";
static constexpr const std::string_view     szXY_Tensor                 = "XY component of the tensor";
static constexpr const std::string_view     szXZ                        = "xz";
static constexpr const std::string_view     szXZ_Tensor                 = "XZ component of the tensor";
static constexpr const std::string_view     szY                         = "y";
static constexpr const std::string_view     szY_Box                     = "Y range of the box";
static constexpr const std::string_view     szY_Vector                  = "Y component of the vector";
static constexpr const std::string_view     szYW                        = "yw";
static constexpr const std::string_view     szYW_Tensor                 = "YW component of the tensor";
static constexpr const std::string_view     szYX                        = "yx";
static constexpr const std::string_view     szYX_Tensor                 = "YX component of the tensor";
static constexpr const std::string_view     szYY                        = "yy";
static constexpr const std::string_view     szYY_Tensor                 = "YY component of the tensor";
static constexpr const std::string_view     szYZ                        = "yz";
static constexpr const std::string_view     szYZ_Tensor                 = "YZ component of the tensor";
static constexpr const std::string_view     szZ                         = "z";
static constexpr const std::string_view     szZ_Box                     = "Z range of the box";
static constexpr const std::string_view     szZ_Vector                  = "Z component of the vector";
static constexpr const std::string_view     szZ_Vector2                 = "Promotes to Vector3 with a z-value";
static constexpr const std::string_view     szZW                        = "zw";
static constexpr const std::string_view     szZW                        = "ZW component of the tensor";
static constexpr const std::string_view     szZX                        = "zx";
static constexpr const std::string_view     szZX                        = "ZX component of the tensor";
static constexpr const std::string_view     szZY                        = "zy";
static constexpr const std::string_view     szZY                        = "ZY component of the tensor";
static constexpr const std::string_view     szZZ                        = "zz";
static constexpr const std::string_view     szZZ                        = "ZZ component of the tensor";


static void reg_math () {

    // General order ... all alphabetical
    //
    //      1. properties
    //      2. methods
    //


    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  AxBox1

    {
        auto w = writer<AxBox1D>();
        w.property(szCenter, &AxBox1D::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox1D::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox1D::hi).description(szHigh_Box);
        w.property(szLow, &AxBox1D::lo).description(szLow_Box);
        w.property(szValid, &AxBox1D::valid).description(szValid_Box);
        w.property(szX, &AxBox1D::x_range).description(szX_Box);
        w.method(szContains, (bool(AxBox1D::*)(const Vector1D&) const) &AxBox1D::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox1D::*)(const AxBox1D&) const) &AxBox1D::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox1D::*)(const AxBox1D&) const) &AxBox1D::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox1D::project).description(szProject_Box);
        w.method(szUnproject, &AxBox1D::unproject).description(szUnproject_Box);
    }

    {
        auto w = writer<AxBox1F>();
        w.property(szCenter, &AxBox1F::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox1F::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox1F::hi).description(szHigh_Box);
        w.property(szLow, &AxBox1F::lo).description(szLow_Box);
        w.property(szValid, &AxBox1F::valid).description(szValid_Box);
        w.property(szX, &AxBox1F::x_range).description(szX_Box);
        w.method(szContains, (bool(AxBox1F::*)(const Vector1F&) const) &AxBox1F::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox1F::*)(const AxBox1F&) const) &AxBox1F::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox1F::*)(const AxBox1F&) const) &AxBox1F::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox1F::project).description(szProject_Box);
        w.method(szUnproject, &AxBox1F::unproject).description(szUnproject_Box);
    }

    {
        auto w = writer<AxBox1I>();
        w.property(szCenter, &AxBox1I::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox1I::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox1I::hi).description(szHigh_Box);
        w.property(szLow, &AxBox1I::lo).description(szLow_Box);
        w.property(szValid, &AxBox1I::valid).description(szValid_Box);
        w.property(szX, &AxBox1I::x_range).description(szX_Box);
        w.method(szContains, (bool(AxBox1I::*)(const Vector1I&) const) &AxBox1I::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox1I::*)(const AxBox1I&) const) &AxBox1I::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox1I::*)(const AxBox1I&) const) &AxBox1I::overlaps).description(szOverlaps_Box_Box);
    }

    {
        auto w = writer<AxBox1U>();
        w.property(szCenter, &AxBox1U::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox1U::span).description(szDimension_Box).alias(szDim);
        w.property(szLow, &AxBox1U::lo).description(szLow_Box);
        w.property(szHigh, &AxBox1U::hi).description(szHigh_Box);
        w.property(szValid, &AxBox1U::valid).description(szValid_Box);
        w.property(szX, &AxBox1U::x_range).description(szX_Box);
        w.method(szContains, (bool(AxBox1U::*)(const Vector1U&) const) &AxBox1U::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox1U::*)(const AxBox1U&) const) &AxBox1U::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox1U::*)(const AxBox1U&) const) &AxBox1U::overlaps).description(szOverlaps_Box_Box);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  AxBox2

    {
        auto w = writer<AxBox2D>();
        w.property(szArea, &AxBox2D::area).description(szArea_Box);
        w.property(szCenter, &AxBox2D::center).description(szCenter_Box).alias(szCtr);
        w.property(szCircumcircle, &AxBox2D::circumcircle).description(szCircumcircle);
        w.property(szDimension, &AxBox2D::span).description(szDimension_Box).alias(szDim);
        w.property(szIncircle, &AxBox2D::incircle).description(szIncircle_Box);
        w.property(szLow, &AxBox2D::lo).description(szLow_Box);
        w.property(szHigh, &AxBox2D::hi).description(szHigh_Box);
        w.property(szNortheast, &AxBox2D::northeast).description(szNortheast_Box).alias(szNE);
        w.property(szNorthwest, &AxBox2D::northwest).description(szNorthwest_Box).alias(szNW);
        w.property(szPerimeter, &AxBox2D::perimeter).description(szPerimeter_Box);
        w.property(szSoutheast, &AxBox2D::southeast).description(szSoutheast_Box).alias(szSE);
        w.property(szSouthwest, &AxBox2D::southwest).description(szSouthwest_Box).alias(szSW);
        w.property(szValid, &AxBox2D::valid).description(szValid_Box);
        w.property(szX, &AxBox2D::x_range).description(szX_Box);
        w.property(szY, &AxBox2D::y_range).description(szY_Box);
        w.method(szContains, (bool(AxBox2D::*)(const Vector2D&) const) &AxBox2D::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox2D::*)(const AxBox2D&) const) &AxBox2D::eclipses).description(szEclipses_Box_Box);
        w.method(szEclipses, (bool(AxBox2D::*)(const Circle2D&) const) &AxBox2D::eclipses).description(szEclipses_Box_Circle);
        w.method(szOverlaps, (bool(AxBox2D::*)(const AxBox2D&) const) &AxBox2D::overlaps).description(szContains_Box_Box);
        w.method(szProject, &AxBox2D::project).description(szProject_Box);
        w.method(szUnproject, &AxBox2D::unproject).description(szUnproject_Box);
    }
    
    {
        auto w = writer<AxBox2F>();
        w.property(szArea, &AxBox2F::area).description(szArea_Box);
        w.property(szCenter, &AxBox2F::center).description(szCenter_Box).alias(szCtr);
        w.property(szCircumcircle, &AxBox2F::circumcircle).description(szCircumcircle);
        w.property(szDimension, &AxBox2F::span).description(szDimension_Box).alias(szDim);
        w.property(szIncircle, &AxBox2F::incircle).description(szIncircle_Box);
        w.property(szLow, &AxBox2F::lo).description(szLow_Box);
        w.property(szHigh, &AxBox2F::hi).description(szHigh_Box);
        w.property(szNortheast, &AxBox2F::northeast).description(szNortheast_Box).alias(szNE);
        w.property(szNorthwest, &AxBox2F::northwest).description(szNorthwest_Box).alias(szNW);
        w.property(szPerimeter, &AxBox2F::perimeter).description(szPerimeter_Box);
        w.property(szSoutheast, &AxBox2F::southeast).description(szSoutheast_Box).alias(szSE);
        w.property(szSouthwest, &AxBox2F::southwest).description(szSouthwest_Box).alias(szSW);
        w.property(szValid, &AxBox2F::valid).description(szValid_Box);
        w.property(szX, &AxBox2F::x_range).description(szX_Box);
        w.property(szY, &AxBox2F::y_range).description(szY_Box);
        w.method(szContains, (bool(AxBox2F::*)(const Vector2F&) const) &AxBox2F::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox2F::*)(const AxBox2F&) const) &AxBox2F::eclipses).description(szEclipses_Box_Box);
        w.method(szEclipses, (bool(AxBox2F::*)(const Circle2F&) const) &AxBox2F::eclipses).description(szEclipses_Box_Circle);
        w.method(szOverlaps, (bool(AxBox2F::*)(const AxBox2F&) const) &AxBox2F::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox2F::project).description(szProject_Box);
        w.method(szUnproject, &AxBox2F::unproject).description(szUnproject_Box);
    }
    
    {
        auto w = writer<AxBox2I>();
        w.property(szArea, &AxBox2I::area).description(szArea_Box);
        w.property(szCenter, &AxBox2I::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox2I::span).description(szDimension_Box).alias(szDim);
        w.property(szLow, &AxBox2I::lo).description(szLow_Box);
        w.property(szHigh, &AxBox2I::hi).description(szHigh_Box);
        w.property(szNortheast, &AxBox2I::northeast).description(szNortheast_Box).alias(szNE);
        w.property(szNorthwest, &AxBox2I::northwest).description(szNorthwest_Box).alias(szNW);
        w.property(szPerimeter, &AxBox2I::perimeter).description(szPerimeter_Box);
        w.property(szSoutheast, &AxBox2I::southeast).description(szSoutheast_Box).alias(szSE);
        w.property(szSouthwest, &AxBox2I::southwest).description(szSouthwest_Box).alias(szSW);
        w.property(szValid, &AxBox2I::valid).description(szValid_Box);
        w.property(szX, &AxBox2I::x_range).description(szX_Box);
        w.property(szY, &AxBox2I::y_range).description(szY_Box);
        w.method(szContains, (bool(AxBox2I::*)(const Vector2I&) const) &AxBox2I::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox2I::*)(const AxBox2I&) const) &AxBox2I::eclipses).description(szEclipses_Box_Box);
        w.method(szEclipses, (bool(AxBox2I::*)(const Circle2I&) const) &AxBox2I::eclipses).description(szEclipses_Box_Circle);
        w.method(szOverlaps, (bool(AxBox2I::*)(const AxBox2I&) const) &AxBox2I::overlaps).description(szOverlaps_Box_Box);
    }
    
    {
        auto w = writer<AxBox2U>();
        w.property(szArea, &AxBox2U::area).description(szArea_Box);
        w.property(szCenter, &AxBox2U::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox2U::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox2U::hi).description(szHigh_Box);
        w.property(szLow, &AxBox2U::lo).description(szLow_Box);
        w.property(szNortheast, &AxBox2U::northeast).description(szNortheast_Box).alias(szNE);
        w.property(szNorthwest, &AxBox2U::northwest).description(szNorthwest_Box).alias(szNW);
        w.property(szPerimeter, &AxBox2U::perimeter).description(szPerimeter_Box);
        w.property(szSoutheast, &AxBox2U::southeast).description(szSoutheast_Box).alias(szSE);
        w.property(szSouthwest, &AxBox2U::southwest).description(szSouthwest_Box).alias(szSW);
        w.property(szValid, &AxBox2U::valid).description(szValid_Box);
        w.property(szX, &AxBox2U::x_range).description(szX_Box);
        w.property(szY, &AxBox2U::y_range).description(szY_Box);
        w.method(szContains, (bool(AxBox2U::*)(const Vector2U&) const) &AxBox2U::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox2U::*)(const AxBox2U&) const) &AxBox2U::eclipses).description(szEclipses_Box_Box);
        w.method(szEclipses, (bool(AxBox2U::*)(const Circle2U&) const) &AxBox2U::eclipses).description(szEclipses_Box_Circle);
        w.method(szOverlaps, (bool(AxBox2U::*)(const AxBox2U&) const) &AxBox2U::overlaps).description(szOverlaps_Box_Box);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  AxBox3
    
    {
        auto w = writer<AxBox3D>();
        w.property(szCenter, &AxBox3D::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox3D::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox3D::hi).description(szHigh_Box);
        w.property(szLow, &AxBox3D::lo).description(szLow_Box);
        w.property(szSurfaceArea, &AxBox3D::surface_area).description(szSurfaceArea_Box3).alias(szSArea);
        w.property(szValid, &AxBox3D::valid).description(szValid_Box);
        w.property(szVolume, &AxBox3D::volume).description(szVolume_Box).alias(szVol);
        w.property(szX, &AxBox3D::x_range).description(szX_Box);
        w.property(szY, &AxBox3D::y_range).description(szY_Box);
        w.property(szZ, &AxBox3D::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox3D::*)(const Vector3D&) const) &AxBox3D::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox3D::*)(const AxBox3D&) const) &AxBox3D::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox3D::*)(const AxBox3D&) const) &AxBox3D::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox3D::project).description(szProject_Box);
        w.method(szUnproject, &AxBox3D::unproject).description(szUnproject_Box);
    }

    {
        auto w = writer<AxBox3F>();
        w.property(szCenter, &AxBox3F::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox3F::span).description(szDimension_Box).alias(szDim);
        w.property(szLow, &AxBox3F::lo).description(szLow_Box);
        w.property(szHigh, &AxBox3F::hi).description(szHigh_Box);
        w.property(szSurfaceArea, &AxBox3F::surface_area).description(szSurfaceArea_Box3).alias(szSArea);
        w.property(szValid, &AxBox3F::valid).description(szValid_Box);
        w.property(szVolume, &AxBox3F::volume).description(szVolume_Box).alias(szVol);
        w.property(szX, &AxBox3F::x_range).description(szX_Box);
        w.property(szY, &AxBox3F::y_range).description(szY_Box);
        w.property(szZ, &AxBox3F::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox3F::*)(const Vector3F&) const) &AxBox3F::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox3F::*)(const AxBox3F&) const) &AxBox3F::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox3F::*)(const AxBox3F&) const) &AxBox3F::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox3F::project).description(szProject_Box);
        w.method(szUnproject, &AxBox3F::unproject).description(szUnproject_Box);
    }

    {
        auto w = writer<AxBox3I>();
        w.property(szCenter, &AxBox3I::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox3I::span).description(szDimension_Box).alias(szDim);
        w.property(szLow, &AxBox3I::lo).description(szLow_Box);
        w.property(szHigh, &AxBox3I::hi).description(szHigh_Box);
        w.property(szSurfaceArea, &AxBox3I::surface_area).description(szSurfaceArea_Box3).alias(szSArea);
        w.property(szValid, &AxBox3I::valid).description(szValid_Box);
        w.property(szVolume, &AxBox3I::volume).description(szVolume_Box).alias(szVol);
        w.property(szX, &AxBox3I::x_range).description(szX_Box);
        w.property(szY, &AxBox3I::y_range).description(szY_Box);
        w.property(szZ, &AxBox3I::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox3I::*)(const Vector3I&) const) &AxBox3I::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox3I::*)(const AxBox3I&) const) &AxBox3I::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox3I::*)(const AxBox3I&) const) &AxBox3I::overlaps).description(szOverlaps_Box_Box);
    }

    {
        auto w = writer<AxBox3U>();
        w.property(szCenter, &AxBox3U::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox3U::span).description(szDimension_Box).alias(szDim);
        w.property(szLow, &AxBox3U::lo).description(szLow_Box);
        w.property(szHigh, &AxBox3U::hi).description(szHigh_Box);
        w.property(szSurfaceArea, &AxBox3U::surface_area).description(szSurfaceArea_Box3);
        w.property(szValid, &AxBox3U::valid).description(szValid_Box);
        w.property(szVolume, &AxBox3U::volume).description(szVolume_Box).alias(szVol);
        w.property(szX, &AxBox3U::x_range).description(szX_Box);
        w.property(szY, &AxBox3U::y_range).description(szY_Box);
        w.property(szZ, &AxBox3U::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox3U::*)(const Vector3U&) const) &AxBox3U::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox3U::*)(const AxBox3U&) const) &AxBox3U::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox3U::*)(const AxBox3U&) const) &AxBox3U::overlaps).description(szOverlaps_Box_Box);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  AxBox4
    
    {
        auto w = writer<AxBox4D>();
        w.property(szCenter, &AxBox4D::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox4D::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox4D::hi).description(szHigh_Box);
        w.property(szHypervolume, &AxBox4D::hypervolume).description(szHypervolume_Box4);
        w.property(szLow, &AxBox4D::lo).description(szLow_Box);
        w.property(szValid, &AxBox4D::valid).description(szValid_Box);
        w.property(szW, &AxBox4D::w_range).description(szW_Box);
        w.property(szX, &AxBox4D::x_range).description(szX_Box);
        w.property(szY, &AxBox4D::y_range).description(szY_Box);
        w.property(szZ, &AxBox4D::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox4D::*)(const Vector4D&) const) &AxBox4D::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox4D::*)(const AxBox4D&) const) &AxBox4D::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox4D::*)(const AxBox4D&) const) &AxBox4D::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox4D::project).description(szProject_Box);
        w.method(szUnproject, &AxBox4D::unproject).description(szUnproject_Box);
    }

    {
        auto w = writer<AxBox4F>();
        w.property(szCenter, &AxBox4F::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox4F::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox4F::hi).description(szHigh_Box);
        w.property(szHypervolume, &AxBox4F::hypervolume).description(szHypervolume_Box4);
        w.property(szLow, &AxBox4F::lo).description(szLow_Box);
        w.property(szValid, &AxBox4F::valid).description(szValid_Box);
        w.property(szW, &AxBox4F::w_range).description(szW_Box);
        w.property(szX, &AxBox4F::x_range).description(szX_Box);
        w.property(szY, &AxBox4F::y_range).description(szY_Box);
        w.property(szZ, &AxBox4F::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox4F::*)(const Vector4F&) const) &AxBox4F::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox4F::*)(const AxBox4F&) const) &AxBox4F::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox4F::*)(const AxBox4F&) const) &AxBox4F::overlaps).description(szOverlaps_Box_Box);
        w.method(szProject, &AxBox4F::project).description(szProject_Box);
        w.method(szUnproject, &AxBox4F::unproject).description(szUnproject_Box);
    }
    
    {
        auto w = writer<AxBox4I>();
        w.property(szCenter, &AxBox4I::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox4I::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox4I::hi).description(szHigh_Box);
        w.property(szHypervolume, &AxBox4I::hypervolume).description(szHypervolume_Box4);
        w.property(szLow, &AxBox4I::lo).description(szLow_Box);
        w.property(szValid, &AxBox4I::valid).description(szValid_Box);
        w.property(szW, &AxBox4I::w_range).description(szW_Box);
        w.property(szX, &AxBox4I::x_range).description(szX_Box);
        w.property(szY, &AxBox4I::y_range).description(szY_Box);
        w.property(szZ, &AxBox4I::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox4I::*)(const Vector4I&) const) &AxBox4I::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox4I::*)(const AxBox4I&) const) &AxBox4I::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox4I::*)(const AxBox4I&) const) &AxBox4I::overlaps).description(szOverlaps_Box_Box);
    }
    
    {
        auto w = writer<AxBox4U>();
        w.property(szCenter, &AxBox4U::center).description(szCenter_Box).alias(szCtr);
        w.property(szDimension, &AxBox4U::span).description(szDimension_Box).alias(szDim);
        w.property(szHigh, &AxBox4U::hi).description(szHigh_Box);
        w.property(szHypervolume, &AxBox4U::hypervolume).description(szHypervolume_Box4);
        w.property(szLow, &AxBox4U::lo).description(szLow_Box);
        w.property(szValid, &AxBox4U::valid).description(szValid_Box);
        w.property(szW, &AxBox4U::w_range).description(szW_Box);
        w.property(szX, &AxBox4U::x_range).description(szX_Box);
        w.property(szY, &AxBox4U::y_range).description(szY_Box);
        w.property(szZ, &AxBox4U::z_range).description(szZ_Box);
        w.method(szContains, (bool(AxBox4U::*)(const Vector4U&) const) &AxBox4U::contains).description(szContains_Box_Pt);
        w.method(szEclipses, (bool(AxBox4U::*)(const AxBox4U&) const) &AxBox4U::eclipses).description(szEclipses_Box_Box);
        w.method(szOverlaps, (bool(AxBox4U::*)(const AxBox4U&) const) &AxBox4U::overlaps).description(szOverlaps_Box_Box);
    }
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Bivectors
    
    {
        auto w = writer<Bivector2D>();
        w.property(szXY, &Bivector2D::xy).description(szXY_Bivector);
    }

    {
        auto bivec2f = writer<Bivector2F>();
        bivec2f.property(szXY, &Bivector2F::xy).description(szXY_Bivector);
    }

    {
        auto bivec3d = writer<Bivector3D>();
        bivec3d.property(szXY, &Bivector3D::xy).description(szXY_Bivector);
        bivec3d.property(szYZ, &Bivector3D::yz);
        bivec3d.property(szZX, &Bivector3D::zx);
    }

    {
        auto bivec3f = writer<Bivector3F>();
        bivec3f.property(szXY, &Bivector3F::xy).description(szXY_Bivector);
        bivec3f.property(szYZ, &Bivector3F::yz);
        bivec3f.property(szZX, &Bivector3F::zx);
    }

    {
        auto bivec4d = writer<Bivector4D>();
        bivec4d.property(szXY, &Bivector4D::xy).description(szXY_Bivector);
        bivec4d.property(szYZ, &Bivector4D::yz);
        bivec4d.property(szZW, &Bivector4D::zw);
        bivec4d.property(szWX, &Bivector4D::wx);
        bivec4d.property(szXZ, &Bivector4D::xz);
        bivec4d.property(szYW, &Bivector4D::yw);
    }

    {
        auto bivec4f = writer<Bivector4F>();
        bivec4f.property(szXY, &Bivector4F::xy).description(szXY_Bivector);
        bivec4f.property(szYZ, &Bivector4F::yz);
        bivec4f.property(szZW, &Bivector4F::zw);
        bivec4f.property(szWX, &Bivector4F::wx);
        bivec4f.property(szXZ, &Bivector4F::xz);
        bivec4f.property(szYW, &Bivector4F::yw);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Circle2
    
    {
        auto w = writer<Circle2D>();
        w.property(szArea, &Circle2D::area).description(szArea_Circle);
        w.property(szBox, &Circle2D::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2D::point).description(szCenter_Circle);
        w.property(szCircumference, &Circle2D::circumference).description(szCircumference);
        w.property(szDiameter, &Circle2D::diameter).description(szDiameter_Circle).alias(szDia).alias(szD);
        w.property(szPerimeter, &Circle2D::circumference).description(szPerimeter_Circle);
        w.property(szRadius, &Circle2D::radius).description(szRadius_Circle).alias(szR);
        w.property(szValid, &Circle2D::valid).description(szValid_Circle);
    }
    
    {
        auto w = writer<Circle2F>();
        w.property(szArea, &Circle2F::area).description(szArea_Circle);
        w.property(szBox, &Circle2F::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2F::point).description(szCenter_Circle);
        w.property(szCircumference, &Circle2F::circumference).description(szCircumference);
        w.property(szDiameter, &Circle2F::diameter).description(szDiameter_Circle).alias(szDia).alias(szD);
        w.property(szPerimeter, &Circle2F::circumference).description(szPerimeter_Circle);
        w.property(szRadius, &Circle2F::radius).description(szRadius_Circle).alias(szR);
        w.property(szValid, &Circle2F::valid).description(szValid_Circle);
    }
    
    {
        auto w = writer<Circle2I>();
        w.property(szBox, &Circle2I::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2I::point).description(szCenter_Circle);
        w.property(szDiameter, &Circle2I::diameter).description(szDiameter_Circle).alias(szDia).alias(szD);
        w.property(szPerimeter, &Circle2I::circumference).description(szPerimeter_Circle);
        w.property(szRadius, &Circle2I::radius).description(szRadius_Circle).alias(szR);
        w.property(szValid, &Circle2I::valid).description(szValid_Circle);
    }
    
    {
        auto w = writer<Circle2U>();
        w.property(szBox, &Circle2U::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2U::point).description(szCenter_Circle);
        w.property(szDiameter, &Circle2U::diameter).description(szDiameter_Circle).alias(szDia).alias(szD);
        w.property(szPerimeter, &Circle2U::circumference).description(szPerimeter_Circle);
        w.property(szRadius, &Circle2U::radius).description(szRadius_Circle).alias(szR);
        w.property(szValid, &Circle2U::valid).description(szValid_Circle);
    }
    
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    {
        auto complexD = writer<ComplexD>();
        complexD.property("re", &ComplexD::real).setter((void(ComplexD::*)(double)) &ComplexD::real);
        complexD.property("im", &ComplexD::imag).setter((void(ComplexD::*)(double)) &ComplexD::imag);
        //complexD.property("mag", [](const ComplexD&v) -> double { return std::abs(v); });
    }

    {
        auto complexF = writer<ComplexF>();
        complexF.property("re", (float (ComplexF::*)() const) &ComplexF::real).setter((void(ComplexF::*)(float)) &ComplexF::real);
        complexF.property("im", (float (ComplexF::*)() const) &ComplexF::imag).setter((void(ComplexF::*)(float)) &ComplexF::imag);
        //complexD.property("mag", [](const ComplexF&v) -> float { return std::abs(v); });
    }

    {
        auto complexI = writer<ComplexI>();
        complexI.property("re", (int (ComplexI::*)() const) &ComplexI::real).setter((void(ComplexI::*)(int)) &ComplexI::real);
        complexI.property("im", (int (ComplexI::*)() const) &ComplexI::imag).setter((void(ComplexI::*)(int)) &ComplexI::imag);
    }

    {
        auto complexU = writer<ComplexU>();
        complexU.property("re", (unsigned (ComplexU::*)() const) &ComplexU::real).setter((void(ComplexU::*)(unsigned)) &ComplexU::real);
        complexU.property("im", (unsigned (ComplexU::*)() const) &ComplexU::imag).setter((void(ComplexU::*)(unsigned)) &ComplexU::imag);
    }

    {
        auto coord2d = writer<Coord2D>();
        coord2d.property("i", &Coord2D::i);
        coord2d.property("j", &Coord2D::j);
    }

    {
        auto coord2f = writer<Coord2F>();
        coord2f.property("i", &Coord2F::i);
        coord2f.property("j", &Coord2F::j);
    }

    {
        auto coord2i = writer<Coord2I>();
        coord2i.property("i", &Coord2I::i);
        coord2i.property("j", &Coord2I::j);
    }

    {
        auto coord2u = writer<Coord2U>();
        coord2u.property("i", &Coord2U::i);
        coord2u.property("j", &Coord2U::j);
    }

    {
        auto countI8   = writer<CountI8>();
        countI8.property("cnt", &CountI8::cnt);
    }

    {
        auto countI16   = writer<CountI16>();
        countI16.property("cnt", &CountI16::cnt);
    }

    {
        auto countI32   = writer<CountI32>();
        countI32.property("cnt", &CountI32::cnt);
    }

    {
        auto countI64   = writer<CountI64>();
        countI64.property("cnt", &CountI64::cnt);
    }

    {
        auto countU8   = writer<CountU8>();
        countU8.property("cnt", &CountU8::cnt);
    }

    {
        auto countU16   = writer<CountU16>();
        countU16.property("cnt", &CountU16::cnt);
    }

    {
        auto countU32   = writer<CountU32>();
        countU32.property("cnt", &CountU32::cnt);
    }

    {
        auto countU64   = writer<CountU64>();
        countU64.property("cnt", &CountU64::cnt);
    }

    {
        auto fraci  = writer<FractionI>();
        fraci.property("n", &FractionI::num);
        fraci.property("d", &FractionI::den);
    }
    
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

    {
        auto hcountI8   = writer<HCountI8>();
        hcountI8.property("cnt", &HCountI8::cnt);
    }

    {
        auto hcountI16   = writer<HCountI16>();
        hcountI16.property("cnt", &HCountI16::cnt);
    }

    {
        auto hcountI32   = writer<HCountI32>();
        hcountI32.property("cnt", &HCountI32::cnt);
    }

    {
        auto hcountI64   = writer<HCountI64>();
        hcountI64.property("cnt", &HCountI64::cnt);
    }

    {
        auto hcountU8   = writer<HCountU8>();
        hcountU8.property("cnt", &HCountU8::cnt);
    }

    {
        auto hcountU16   = writer<HCountU16>();
        hcountU16.property("cnt", &HCountU16::cnt);
    }

    {
        auto hcountU32   = writer<HCountU32>();
        hcountU32.property("cnt", &HCountU32::cnt);
    }

    {
        auto hcountU64   = writer<HCountU64>();
        hcountU64.property("cnt", &HCountU64::cnt);
    }

    {
        auto lcountI8   = writer<LCountI8>();
        lcountI8.property("cnt", &LCountI8::cnt);
    }

    {
        auto lcountI16   = writer<LCountI16>();
        lcountI16.property("cnt", &LCountI16::cnt);
    }

    {
        auto lcountI32   = writer<LCountI32>();
        lcountI32.property("cnt", &LCountI32::cnt);
    }

    {
        auto lcountI64   = writer<LCountI64>();
        lcountI64.property("cnt", &LCountI64::cnt);
    }

    {
        auto w  = writer<Multivector1D>();
        w.property("a", &Multivector1D::a);
        w.property(szX, &Multivector1D::x);
    }

    {
        auto w  = writer<Multivector1F>();
        w.property("a", &Multivector1F::a);
        w.property(szX, &Multivector1F::x);
    }

    {
        auto w  = writer<Multivector2D>();
        w.property("a", &Multivector2D::a);
        w.property(szX, &Multivector2D::x);
        w.property(szY, &Multivector2D::y);
        w.property(szXY, &Multivector2D::xy);
    }

    {
        auto w  = writer<Multivector2F>();
        w.property("a", &Multivector2F::a);
        w.property(szX, &Multivector2F::x);
        w.property(szY, &Multivector2F::y);
        w.property(szXY, &Multivector2F::xy);
    }

    {
        auto w  = writer<Multivector3D>();
        w.property("a", &Multivector3D::a);
        w.property(szX, &Multivector3D::x);
        w.property(szY, &Multivector3D::y);
        w.property(szZ, &Multivector3D::z);
        w.property(szXY, &Multivector3D::xy);
        w.property(szYZ, &Multivector3D::yz);
        w.property(szZX, &Multivector3D::zx);
        w.property("xyz", &Multivector3D::xyz);
    }

    {
        auto w  = writer<Multivector3F>();
        w.property("a", &Multivector3F::a);
        w.property(szX, &Multivector3F::x);
        w.property(szY, &Multivector3F::y);
        w.property(szZ, &Multivector3F::z);
        w.property(szXY, &Multivector3F::xy);
        w.property(szYZ, &Multivector3F::yz);
        w.property(szZX, &Multivector3F::zx);
        w.property("xyz", &Multivector3F::xyz);
    }

    {
        auto w  = writer<Multivector4D>();
        w.property("a", &Multivector4D::a);
        w.property(szX, &Multivector4D::x);
        w.property(szY, &Multivector4D::y);
        w.property(szZ, &Multivector4D::z);
        w.property(szW, &Multivector4D::w);
        w.property(szXY, &Multivector4D::xy);
        w.property(szYZ, &Multivector4D::yz);
        w.property(szZW, &Multivector4D::zw);
        w.property(szWX, &Multivector4D::wx);
        w.property(szXZ, &Multivector4D::xz);
        w.property(szYW, &Multivector4D::yw);
        w.property("xyz", &Multivector4D::xyz);
        w.property("yzw", &Multivector4D::yzw);
        w.property("zwx", &Multivector4D::zwx);
        w.property("wxy", &Multivector4D::wxy);
        w.property("xyzw", &Multivector4D::xyzw);
    }

    {
        auto w  = writer<Multivector4F>();
        w.property("a", &Multivector4F::a);
        w.property(szX, &Multivector4F::x);
        w.property(szY, &Multivector4F::y);
        w.property(szZ, &Multivector4F::z);
        w.property(szW, &Multivector4F::w);
        w.property(szXY, &Multivector4F::xy);
        w.property(szYZ, &Multivector4F::yz);
        w.property(szZW, &Multivector4F::zw);
        w.property(szWX, &Multivector4F::wx);
        w.property(szXZ, &Multivector4F::xz);
        w.property(szYW, &Multivector4F::yw);
        w.property("xyz", &Multivector4F::xyz);
        w.property("yzw", &Multivector4F::yzw);
        w.property("zwx", &Multivector4F::zwx);
        w.property("wxy", &Multivector4F::wxy);
        w.property("xyzw", &Multivector4F::xyzw);
    }

    {
        auto norm2d = writer<Normal2D>();
        norm2d.property("dir", &Normal2D::direction);
    }

    {
        auto norm2f = writer<Normal2F>();
        norm2f.property("dir", &Normal2F::direction);
    }

    {
        auto norm3d = writer<Normal3D>();
        norm3d.property("dir", &Normal3D::direction);
    }

    {
        auto norm3f = writer<Normal3F>();
        norm3f.property("dir", &Normal3F::direction);
    }

    {
        auto pose3d = writer<Pose3D>();
        pose3d.property("ori", &Pose3D::orientation);
        pose3d.property("pos", &Pose3D::position);
    }

    {
        auto pose3f = writer<Pose3F>();
        pose3f.property("ori", &Pose3F::orientation);
        pose3f.property("pos", &Pose3F::position);
    }

    {
        auto quad2d = writer<Quadrilateral2D>();
        quad2d.property("a", &Quadrilateral2D::a);
        quad2d.property("b", &Quadrilateral2D::b);
        quad2d.property("c", &Quadrilateral2D::c);
        quad2d.property("d", &Quadrilateral2D::d);
    }

    {
        auto quad2f = writer<Quadrilateral2F>();
        quad2f.property("a", &Quadrilateral2F::a);
        quad2f.property("b", &Quadrilateral2F::b);
        quad2f.property("c", &Quadrilateral2F::c);
        quad2f.property("d", &Quadrilateral2F::d);
    }

    {
        auto quad2i = writer<Quadrilateral2I>();
        quad2i.property("a", &Quadrilateral2I::a);
        quad2i.property("b", &Quadrilateral2I::b);
        quad2i.property("c", &Quadrilateral2I::c);
        quad2i.property("d", &Quadrilateral2I::d);
    }

    {
        auto quad2u = writer<Quadrilateral2U>();
        quad2u.property("a", &Quadrilateral2U::a);
        quad2u.property("b", &Quadrilateral2U::b);
        quad2u.property("c", &Quadrilateral2U::c);
        quad2u.property("d", &Quadrilateral2U::d);
    }

    {
        auto quadvec4d = writer<Quadvector4D>();
        quadvec4d.property("xyzw", &Quadvector4D::xyzw);
    }

    {
        auto quadvec4f = writer<Quadvector4F>();
        quadvec4f.property("xyzw", &Quadvector4F::xyzw);
    }

    {
        auto quat3d = writer<Quaternion3D>();
        quat3d.property(szW, &Quaternion3D::w);
        quat3d.property(szX, &Quaternion3D::x);
        quat3d.property(szY, &Quaternion3D::y);
        quat3d.property(szZ, &Quaternion3D::z);
    }

    {
        auto quat3f = writer<Quaternion3F>();
        quat3f.property(szW, &Quaternion3F::w);
        quat3f.property(szX, &Quaternion3F::x);
        quat3f.property(szY, &Quaternion3F::y);
        quat3f.property(szZ, &Quaternion3F::z);
    }
        
    {
        auto w  = writer<RangeD>();
        w.property(szLow, &RangeD::lo).description(szLow_Range);
        w.property(szHigh, &RangeD::hi).description(szHigh_Range);
    }
    
    {
        auto w  = writer<RangeF>();
        w.property(szLow, &RangeF::lo).description(szLow_Range);
        w.property(szHigh, &RangeF::hi).description(szHigh_Range);
    }

    {
        auto w  = writer<RangeI>();
        w.property(szLow, &RangeI::lo).description(szLow_Range);
        w.property(szHigh, &RangeI::hi).description(szHigh_Range);
    }

    {
        auto w  = writer<RangeU>();
        w.property(szLow, &RangeU::lo).description(szLow_Range);
        w.property(szHigh, &RangeU::hi).description(szHigh_Range);
    }

    {
        auto ray2d = writer<Ray2D>();
        ray2d.property("pt", &Ray2D::point);
        ray2d.property("dir", &Ray2D::direction);
    }

    {
        auto ray2f = writer<Ray2F>();
        ray2f.property("pt", &Ray2F::point);
        ray2f.property("dir", &Ray2F::direction);
    }

    {
        auto ray3d = writer<Ray3D>();
        ray3d.property("pt", &Ray3D::point);
        ray3d.property("dir", &Ray3D::direction);
    }

    {
        auto ray3f = writer<Ray3F>();
        ray3f.property("pt", &Ray3F::point);
        ray3f.property("dir", &Ray3F::direction);
    }

    {
        auto ray4d = writer<Ray4D>();
        ray4d.property("pt", &Ray4D::point);
        ray4d.property("dir", &Ray4D::direction);
    }

    {
        auto ray4f = writer<Ray4F>();
        ray4f.property("pt", &Ray4F::point);
        ray4f.property("dir", &Ray4F::direction);
    }

    {
        auto w   = writer<RGB3D>();
        w.property(szRed, &RGB3D::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3D::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3D::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGB3F>();
        w.property(szRed, &RGB3F::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3F::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3F::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGB3U8>();
        w.property(szRed, &RGB3U8::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3U8::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3U8::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGB3U16>();
        w.property(szRed, &RGB3U16::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3U16::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3U16::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGBA4D>();
        w.property(szRed, &RGBA4D::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4D::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4D::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4D::alpha).description(szAlpha_Color).alias(szA);
    }

    {
        auto w   = writer<RGBA4F>();
        w.property(szRed, &RGBA4F::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4F::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4F::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4F::alpha).description(szAlpha_Color).alias(szA);
    }

    {
        auto w   = writer<RGBA4U8>();
        w.property(szRed, &RGBA4U8::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4U8::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4U8::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4U8::alpha).description(szAlpha_Color).alias(szA);
    }

    {
        auto w   = writer<RGBA4U16>();
        w.property(szRed, &RGBA4U16::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4U16::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4U16::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4U16::alpha).description(szAlpha_Color).alias(szA);
    }

    {
        auto rect2d = writer<Rectangle2D>();
        rect2d.property("pos", &Rectangle2D::position);
        rect2d.property("size", &Rectangle2D::size);
    }

    {
        auto rect2f = writer<Rectangle2F>();
        rect2f.property("pos", &Rectangle2F::position);
        rect2f.property("size", &Rectangle2F::size);
    }

    {
        auto rect2i = writer<Rectangle2I>();
        rect2i.property("pos", &Rectangle2I::position);
        rect2i.property("size", &Rectangle2I::size);
    }

    {
        auto rect2u = writer<Rectangle2U>();
        rect2u.property("pos", &Rectangle2U::position);
        rect2u.property("size", &Rectangle2U::size);
    }

    {
        auto seg1d = writer<Segment1D>();
        seg1d.property("a", &Segment1D::a);
        seg1d.property("b", &Segment1D::b);
    }

    {
        auto seg1f = writer<Segment1F>();
        seg1f.property("a", &Segment1F::a);
        seg1f.property("b", &Segment1F::b);
    }

    {
        auto seg1i = writer<Segment1I>();
        seg1i.property("a", &Segment1I::a);
        seg1i.property("b", &Segment1I::b);
    }

    {
        auto seg1u = writer<Segment1U>();
        seg1u.property("a", &Segment1U::a);
        seg1u.property("b", &Segment1U::b);
    }

    {
        auto seg2d = writer<Segment2D>();
        seg2d.property("a", &Segment2D::a);
        seg2d.property("b", &Segment2D::b);
    }

    {
        auto seg2f = writer<Segment2F>();
        seg2f.property("a", &Segment2F::a);
        seg2f.property("b", &Segment2F::b);
    }

    {
        auto seg2i = writer<Segment2I>();
        seg2i.property("a", &Segment2I::a);
        seg2i.property("b", &Segment2I::b);
    }

    {
        auto seg2u = writer<Segment2U>();
        seg2u.property("a", &Segment2U::a);
        seg2u.property("b", &Segment2U::b);
    }

    {
        auto seg3d = writer<Segment3D>();
        seg3d.property("a", &Segment3D::a);
        seg3d.property("b", &Segment3D::b);
    }

    {
        auto seg3f = writer<Segment3F>();
        seg3f.property("a", &Segment3F::a);
        seg3f.property("b", &Segment3F::b);
    }

    {
        auto seg3i = writer<Segment3I>();
        seg3i.property("a", &Segment3I::a);
        seg3i.property("b", &Segment3I::b);
    }

    {
        auto seg3u = writer<Segment3U>();
        seg3u.property("a", &Segment3U::a);
        seg3u.property("b", &Segment3U::b);
    }

    {
        auto seg4d = writer<Segment4D>();
        seg4d.property("a", &Segment4D::a);
        seg4d.property("b", &Segment4D::b);
    }

    {
        auto seg4f = writer<Segment4F>();
        seg4f.property("a", &Segment4F::a);
        seg4f.property("b", &Segment4F::b);
    }

    {
        auto seg4i = writer<Segment4I>();
        seg4i.property("a", &Segment4I::a);
        seg4i.property("b", &Segment4I::b);
    }

    {
        auto seg4u = writer<Segment4U>();
        seg4u.property("a", &Segment4U::a);
        seg4u.property("b", &Segment4U::b);
    }

    {
        auto size2d = writer<Size2D>();
        size2d.property(szX, &Size2D::x);
        size2d.property(szY, &Size2D::y);
        size2d.property(szW, &Size2D::width);
        size2d.property("h", &Size2D::height);
    }

    {
        auto size2f = writer<Size2F>();
        size2f.property(szX, &Size2F::x);
        size2f.property(szY, &Size2F::y);
        size2f.property(szW, &Size2F::width);
        size2f.property("h", &Size2F::height);
    }

    {
        auto size2i = writer<Size2I>();
        size2i.property(szX, &Size2I::x);
        size2i.property(szY, &Size2I::y);
        size2i.property(szW, &Size2I::width);
        size2i.property("h", &Size2I::height);
    }

    {
        auto size2u = writer<Size2U>();
        size2u.property(szX, &Size2U::x);
        size2u.property(szY, &Size2U::y);
        size2u.property(szW, &Size2U::width);
        size2u.property("h", &Size2U::height);
    }

    {
        auto size3d = writer<Size3D>();
        size3d.property(szX, &Size3D::x);
        size3d.property(szY, &Size3D::y);
        size3d.property(szZ, &Size3D::z);
        size3d.property(szW, &Size3D::width);
        size3d.property("h", &Size3D::height);
        size3d.property("d", &Size3D::depth);
    }

    {
        auto size3f = writer<Size3F>();
        size3f.property(szX, &Size3F::x);
        size3f.property(szY, &Size3F::y);
        size3f.property(szZ, &Size3F::z);
        size3f.property(szW, &Size3F::width);
        size3f.property("h", &Size3F::height);
        size3f.property("d", &Size3F::depth);
    }

    {
        auto size3i = writer<Size3I>();
        size3i.property(szX, &Size3I::x);
        size3i.property(szY, &Size3I::y);
        size3i.property(szZ, &Size3I::z);
        size3i.property(szW, &Size3I::width);
        size3i.property("h", &Size3I::height);
        size3i.property("d", &Size3I::depth);
    }

    {
        auto size3u = writer<Size3U>();
        size3u.property(szX, &Size3U::x);
        size3u.property(szY, &Size3U::y);
        size3u.property(szZ, &Size3U::z);
        size3u.property(szW, &Size3U::width);
        size3u.property("h", &Size3U::height);
        size3u.property("d", &Size3U::depth);
    }

    {
        auto sphere3d = writer<Sphere3D>();
        sphere3d.property("pt", &Sphere3D::point);
        sphere3d.property("r", &Sphere3D::radius);
    }

    {
        auto sphere3f = writer<Sphere3F>();
        sphere3f.property("pt", &Sphere3F::point);
        sphere3f.property("r", &Sphere3F::radius);
    }

    {
        auto sphere3i = writer<Sphere3I>();
        sphere3i.property("pt", &Sphere3I::point);
        sphere3i.property("r", &Sphere3I::radius);
    }

    {
        auto sphere3u = writer<Sphere3U>();
        sphere3u.property("pt", &Sphere3U::point);
        sphere3u.property("r", &Sphere3U::radius);
    }

    {
        auto sphere4d = writer<Sphere4D>();
        sphere4d.property("pt", &Sphere4D::point);
        sphere4d.property("r", &Sphere4D::radius);
    }

    {
        auto sphere4f = writer<Sphere4F>();
        sphere4f.property("pt", &Sphere4F::point);
        sphere4f.property("r", &Sphere4F::radius);
    }

    {
        auto sphere4i = writer<Sphere4I>();
        sphere4i.property("pt", &Sphere4I::point);
        sphere4i.property("r", &Sphere4I::radius);
    }

    {
        auto sphere4u = writer<Sphere4U>();
        sphere4u.property("pt", &Sphere4U::point);
        sphere4u.property("r", &Sphere4U::radius);
    }

    {
        auto ten11d = writer<Tensor11D>();
        ten11d.property(szXX, &Tensor11D::xx);
    }

    {
        auto ten11f = writer<Tensor11F>();
        ten11f.property(szXX, &Tensor11F::xx);
    }

    {
        auto ten11i = writer<Tensor11I>();
        ten11i.property(szXX, &Tensor11I::xx).description(szXX_Tensor);
    }

    {
        auto ten11u = writer<Tensor11U>();
        ten11u.property(szXX, &Tensor11U::xx).description(szXX_Tensor);
    }

    {
        auto ten12d = writer<Tensor12D>();
        ten12d.property(szXX, &Tensor12D::xx).description(szXX_Tensor);
        ten12d.property(szXY, &Tensor12D::xy);
    }

    {
        auto ten12f = writer<Tensor12F>();
        ten12f.property(szXX, &Tensor12F::xx).description(szXX_Tensor);
        ten12f.property(szXY, &Tensor12F::xy);
    }

    {
        auto ten12i = writer<Tensor12I>();
        ten12i.property(szXX, &Tensor12I::xx).description(szXX_Tensor);
        ten12i.property(szXY, &Tensor12I::xy);
    }

    {
        auto ten12u = writer<Tensor12U>();
        ten12u.property(szXX, &Tensor12U::xx).description(szXX_Tensor);
        ten12u.property(szXY, &Tensor12U::xy);
    }

    {
        auto ten13d = writer<Tensor13D>();
        ten13d.property(szXX, &Tensor13D::xx).description(szXX_Tensor);
        ten13d.property(szXY, &Tensor13D::xy);
        ten13d.property(szXZ, &Tensor13D::xz);
    }

    {
        auto ten13f = writer<Tensor13F>();
        ten13f.property(szXX, &Tensor13F::xx).description(szXX_Tensor);
        ten13f.property(szXY, &Tensor13F::xy);
        ten13f.property(szXZ, &Tensor13F::xz);
    }

    {
        auto ten13i = writer<Tensor13I>();
        ten13i.property(szXX, &Tensor13I::xx).description(szXX_Tensor);
        ten13i.property(szXY, &Tensor13I::xy);
        ten13i.property(szXZ, &Tensor13I::xz);
    }

    {
        auto ten13u = writer<Tensor13U>();
        ten13u.property(szXX, &Tensor13U::xx).description(szXX_Tensor);
        ten13u.property(szXY, &Tensor13U::xy);
        ten13u.property(szXZ, &Tensor13U::xz);
    }

    {
        auto ten14d = writer<Tensor14D>();
        ten14d.property(szXX, &Tensor14D::xx).description(szXX_Tensor);
        ten14d.property(szXY, &Tensor14D::xy);
        ten14d.property(szXZ, &Tensor14D::xz);
        ten14d.property(szXW, &Tensor14D::xw);
    }

    {
        auto ten14f = writer<Tensor14F>();
        ten14f.property(szXX, &Tensor14F::xx).description(szXX_Tensor);
        ten14f.property(szXY, &Tensor14F::xy);
        ten14f.property(szXZ, &Tensor14F::xz);
        ten14f.property(szXW, &Tensor14F::xw);
    }

    {
        auto ten14i = writer<Tensor14I>();
        ten14i.property(szXX, &Tensor14I::xx).description(szXX_Tensor);
        ten14i.property(szXY, &Tensor14I::xy);
        ten14i.property(szXZ, &Tensor14I::xz);
        ten14i.property(szXW, &Tensor14I::xw);
    }

    {
        auto ten14u = writer<Tensor14U>();
        ten14u.property(szXX, &Tensor14U::xx).description(szXX_Tensor);
        ten14u.property(szXY, &Tensor14U::xy);
        ten14u.property(szXZ, &Tensor14U::xz);
        ten14u.property(szXW, &Tensor14U::xw);
    }

    {
        auto ten21d = writer<Tensor21D>();
        ten21d.property(szXX, &Tensor21D::xx).description(szXX_Tensor);
        ten21d.property(szYX, &Tensor21D::yx);
    }

    {
        auto ten21f = writer<Tensor21F>();
        ten21f.property(szXX, &Tensor21F::xx).description(szXX_Tensor);
        ten21f.property(szYX, &Tensor21F::yx);
    }

    {
        auto ten21i = writer<Tensor21I>();
        ten21i.property(szXX, &Tensor21I::xx).description(szXX_Tensor);
        ten21i.property(szYX, &Tensor21I::yx);
    }

    {
        auto ten21u = writer<Tensor21U>();
        ten21u.property(szXX, &Tensor21U::xx).description(szXX_Tensor);
        ten21u.property(szYX, &Tensor21U::yx);
    }

    {
        auto ten22d = writer<Tensor22D>();
        ten22d.property(szXX, &Tensor22D::xx).description(szXX_Tensor);
        ten22d.property(szXY, &Tensor22D::xy);
        ten22d.property(szYX, &Tensor22D::yx);
        ten22d.property(szYY, &Tensor22D::yy);
    }

    {
        auto ten22f = writer<Tensor22F>();
        ten22f.property(szXX, &Tensor22F::xx).description(szXX_Tensor);
        ten22f.property(szXY, &Tensor22F::xy);
        ten22f.property(szYX, &Tensor22F::yx);
        ten22f.property(szYY, &Tensor22F::yy);
    }

    {
        auto ten22i = writer<Tensor22I>();
        ten22i.property(szXX, &Tensor22I::xx).description(szXX_Tensor);
        ten22i.property(szXY, &Tensor22I::xy);
        ten22i.property(szYX, &Tensor22I::yx);
        ten22i.property(szYY, &Tensor22I::yy);
    }

    {
        auto ten22u = writer<Tensor22U>();
        ten22u.property(szXX, &Tensor22U::xx).description(szXX_Tensor);
        ten22u.property(szXY, &Tensor22U::xy);
        ten22u.property(szYX, &Tensor22U::yx);
        ten22u.property(szYY, &Tensor22U::yy);
    }

    {
        auto ten23d = writer<Tensor23D>();
        ten23d.property(szXX, &Tensor23D::xx).description(szXX_Tensor);
        ten23d.property(szXY, &Tensor23D::xy);
        ten23d.property(szXZ, &Tensor23D::xz);
        ten23d.property(szYX, &Tensor23D::yx);
        ten23d.property(szYY, &Tensor23D::yy);
        ten23d.property(szYZ, &Tensor23D::yz);
    }

    {
        auto ten23f = writer<Tensor23F>();
        ten23f.property(szXX, &Tensor23F::xx).description(szXX_Tensor);
        ten23f.property(szXY, &Tensor23F::xy);
        ten23f.property(szXZ, &Tensor23F::xz);
        ten23f.property(szYX, &Tensor23F::yx);
        ten23f.property(szYY, &Tensor23F::yy);
        ten23f.property(szYZ, &Tensor23F::yz);
    }

    {
        auto ten23i = writer<Tensor23I>();
        ten23i.property(szXX, &Tensor23I::xx).description(szXX_Tensor);
        ten23i.property(szXY, &Tensor23I::xy);
        ten23i.property(szXZ, &Tensor23I::xz);
        ten23i.property(szYX, &Tensor23I::yx);
        ten23i.property(szYY, &Tensor23I::yy);
        ten23i.property(szYZ, &Tensor23I::yz);
    }

    {
        auto ten23u = writer<Tensor23U>();
        ten23u.property(szXX, &Tensor23U::xx).description(szXX_Tensor);
        ten23u.property(szXY, &Tensor23U::xy);
        ten23u.property(szXZ, &Tensor23U::xz);
        ten23u.property(szYX, &Tensor23U::yx);
        ten23u.property(szYY, &Tensor23U::yy);
        ten23u.property(szYZ, &Tensor23U::yz);
    }

    {
        auto ten24d = writer<Tensor24D>();
        ten24d.property(szXX, &Tensor24D::xx).description(szXX_Tensor);
        ten24d.property(szXY, &Tensor24D::xy);
        ten24d.property(szXZ, &Tensor24D::xz);
        ten24d.property(szXW, &Tensor24D::xw);
        ten24d.property(szYX, &Tensor24D::yx);
        ten24d.property(szYY, &Tensor24D::yy);
        ten24d.property(szYZ, &Tensor24D::yz);
        ten24d.property(szYW, &Tensor24D::yw);
    }

    {
        auto ten24f = writer<Tensor24F>();
        ten24f.property(szXX, &Tensor24F::xx).description(szXX_Tensor);
        ten24f.property(szXY, &Tensor24F::xy);
        ten24f.property(szXZ, &Tensor24F::xz);
        ten24f.property(szXW, &Tensor24F::xw);
        ten24f.property(szYX, &Tensor24F::yx);
        ten24f.property(szYY, &Tensor24F::yy);
        ten24f.property(szYZ, &Tensor24F::yz);
        ten24f.property(szYW, &Tensor24F::yw);
    }

    {
        auto ten24i = writer<Tensor24I>();
        ten24i.property(szXX, &Tensor24I::xx).description(szXX_Tensor);
        ten24i.property(szXY, &Tensor24I::xy);
        ten24i.property(szXZ, &Tensor24I::xz);
        ten24i.property(szXW, &Tensor24I::xw);
        ten24i.property(szYX, &Tensor24I::yx);
        ten24i.property(szYY, &Tensor24I::yy);
        ten24i.property(szYZ, &Tensor24I::yz);
        ten24i.property(szYW, &Tensor24I::yw);
    }

    {
        auto ten24u = writer<Tensor24U>();
        ten24u.property(szXX, &Tensor24U::xx).description(szXX_Tensor);
        ten24u.property(szXY, &Tensor24U::xy);
        ten24u.property(szXZ, &Tensor24U::xz);
        ten24u.property(szXW, &Tensor24U::xw);
        ten24u.property(szYX, &Tensor24U::yx);
        ten24u.property(szYY, &Tensor24U::yy);
        ten24u.property(szYZ, &Tensor24U::yz);
        ten24u.property(szYW, &Tensor24U::yw);
    }

    {
        auto ten31d = writer<Tensor31D>();
        ten31d.property(szXX, &Tensor31D::xx).description(szXX_Tensor);
        ten31d.property(szYX, &Tensor31D::yx);
        ten31d.property(szZX, &Tensor31D::zx);
    }

    {
        auto ten31f = writer<Tensor31F>();
        ten31f.property(szXX, &Tensor31F::xx).description(szXX_Tensor);
        ten31f.property(szYX, &Tensor31F::yx);
        ten31f.property(szZX, &Tensor31F::zx);
    }

    {
        auto ten31i = writer<Tensor31I>();
        ten31i.property(szXX, &Tensor31I::xx).description(szXX_Tensor);
        ten31i.property(szYX, &Tensor31I::yx);
        ten31i.property(szZX, &Tensor31I::zx);
    }

    {
        auto ten31u = writer<Tensor31U>();
        ten31u.property(szXX, &Tensor31U::xx).description(szXX_Tensor);
        ten31u.property(szYX, &Tensor31U::yx);
        ten31u.property(szZX, &Tensor31U::zx);
    }

    {
        auto ten32d = writer<Tensor32D>();
        ten32d.property(szXX, &Tensor32D::xx).description(szXX_Tensor);
        ten32d.property(szXY, &Tensor32D::xy);
        ten32d.property(szYX, &Tensor32D::yx);
        ten32d.property(szYY, &Tensor32D::yy);
        ten32d.property(szZX, &Tensor32D::zx);
        ten32d.property(szZY, &Tensor32D::zy);
    }

    {
        auto ten32f = writer<Tensor32F>();
        ten32f.property(szXX, &Tensor32F::xx).description(szXX_Tensor);
        ten32f.property(szXY, &Tensor32F::xy);
        ten32f.property(szYX, &Tensor32F::yx);
        ten32f.property(szYY, &Tensor32F::yy);
        ten32f.property(szZX, &Tensor32F::zx);
        ten32f.property(szZY, &Tensor32F::zy);
    }

    {
        auto ten32i = writer<Tensor32I>();
        ten32i.property(szXX, &Tensor32I::xx).description(szXX_Tensor);
        ten32i.property(szXY, &Tensor32I::xy);
        ten32i.property(szYX, &Tensor32I::yx);
        ten32i.property(szYY, &Tensor32I::yy);
        ten32i.property(szZX, &Tensor32I::zx);
        ten32i.property(szZY, &Tensor32I::zy);
    }

    {
        auto ten32u = writer<Tensor32U>();
        ten32u.property(szXX, &Tensor32U::xx).description(szXX_Tensor);
        ten32u.property(szXY, &Tensor32U::xy);
        ten32u.property(szYX, &Tensor32U::yx);
        ten32u.property(szYY, &Tensor32U::yy);
        ten32u.property(szZX, &Tensor32U::zx);
        ten32u.property(szZY, &Tensor32U::zy);
    }

    {
        auto ten33d = writer<Tensor33D>();
        ten33d.property(szXX, &Tensor33D::xx).description(szXX_Tensor);
        ten33d.property(szXY, &Tensor33D::xy);
        ten33d.property(szXZ, &Tensor33D::xz);
        ten33d.property(szYX, &Tensor33D::yx);
        ten33d.property(szYY, &Tensor33D::yy);
        ten33d.property(szYZ, &Tensor33D::yz);
        ten33d.property(szZX, &Tensor33D::zx);
        ten33d.property(szZY, &Tensor33D::zy);
        ten33d.property(szZZ, &Tensor33D::zz);
    }

    {
        auto ten33f = writer<Tensor33F>();
        ten33f.property(szXX, &Tensor33F::xx).description(szXX_Tensor);
        ten33f.property(szXY, &Tensor33F::xy);
        ten33f.property(szXZ, &Tensor33F::xz);
        ten33f.property(szYX, &Tensor33F::yx);
        ten33f.property(szYY, &Tensor33F::yy);
        ten33f.property(szYZ, &Tensor33F::yz);
        ten33f.property(szZX, &Tensor33F::zx);
        ten33f.property(szZY, &Tensor33F::zy);
        ten33f.property(szZZ, &Tensor33F::zz);
    }

    {
        auto ten33i = writer<Tensor33I>();
        ten33i.property(szXX, &Tensor33I::xx).description(szXX_Tensor);
        ten33i.property(szXY, &Tensor33I::xy);
        ten33i.property(szXZ, &Tensor33I::xz);
        ten33i.property(szYX, &Tensor33I::yx);
        ten33i.property(szYY, &Tensor33I::yy);
        ten33i.property(szYZ, &Tensor33I::yz);
        ten33i.property(szZX, &Tensor33I::zx);
        ten33i.property(szZY, &Tensor33I::zy);
        ten33i.property(szZZ, &Tensor33I::zz);
    }

    {
        auto ten33u = writer<Tensor33U>();
        ten33u.property(szXX, &Tensor33U::xx).description(szXX_Tensor);
        ten33u.property(szXY, &Tensor33U::xy);
        ten33u.property(szXZ, &Tensor33U::xz);
        ten33u.property(szYX, &Tensor33U::yx);
        ten33u.property(szYY, &Tensor33U::yy);
        ten33u.property(szYZ, &Tensor33U::yz);
        ten33u.property(szZX, &Tensor33U::zx);
        ten33u.property(szZY, &Tensor33U::zy);
        ten33u.property(szZZ, &Tensor33U::zz);
    }

    {
        auto ten34d = writer<Tensor34D>();
        ten34d.property(szXX, &Tensor34D::xx).description(szXX_Tensor);
        ten34d.property(szXY, &Tensor34D::xy);
        ten34d.property(szXZ, &Tensor34D::xz);
        ten34d.property(szXW, &Tensor34D::xw);
        ten34d.property(szYX, &Tensor34D::yx);
        ten34d.property(szYY, &Tensor34D::yy);
        ten34d.property(szYZ, &Tensor34D::yz);
        ten34d.property(szYW, &Tensor34D::yw);
        ten34d.property(szZX, &Tensor34D::zx);
        ten34d.property(szZY, &Tensor34D::zy);
        ten34d.property(szZZ, &Tensor34D::zz);
        ten34d.property(szZW, &Tensor34D::zw);
    }

    {
        auto ten34f = writer<Tensor34F>();
        ten34f.property(szXX, &Tensor34F::xx).description(szXX_Tensor);
        ten34f.property(szXY, &Tensor34F::xy);
        ten34f.property(szXZ, &Tensor34F::xz);
        ten34f.property(szXW, &Tensor34F::xw);
        ten34f.property(szYX, &Tensor34F::yx);
        ten34f.property(szYY, &Tensor34F::yy);
        ten34f.property(szYZ, &Tensor34F::yz);
        ten34f.property(szYW, &Tensor34F::yw);
        ten34f.property(szZX, &Tensor34F::zx);
        ten34f.property(szZY, &Tensor34F::zy);
        ten34f.property(szZZ, &Tensor34F::zz);
        ten34f.property(szZW, &Tensor34F::zw);
    }

    {
        auto ten34i = writer<Tensor34I>();
        ten34i.property(szXX, &Tensor34I::xx).description(szXX_Tensor);
        ten34i.property(szXY, &Tensor34I::xy);
        ten34i.property(szXZ, &Tensor34I::xz);
        ten34i.property(szXW, &Tensor34I::xw);
        ten34i.property(szYX, &Tensor34I::yx);
        ten34i.property(szYY, &Tensor34I::yy);
        ten34i.property(szYZ, &Tensor34I::yz);
        ten34i.property(szYW, &Tensor34I::yw);
        ten34i.property(szZX, &Tensor34I::zx);
        ten34i.property(szZY, &Tensor34I::zy);
        ten34i.property(szZZ, &Tensor34I::zz);
        ten34i.property(szZW, &Tensor34I::zw);
    }

    {
        auto ten34u = writer<Tensor34U>();
        ten34u.property(szXX, &Tensor34U::xx).description(szXX_Tensor);
        ten34u.property(szXY, &Tensor34U::xy);
        ten34u.property(szXZ, &Tensor34U::xz);
        ten34u.property(szXW, &Tensor34U::xw);
        ten34u.property(szYX, &Tensor34U::yx);
        ten34u.property(szYY, &Tensor34U::yy);
        ten34u.property(szYZ, &Tensor34U::yz);
        ten34u.property(szYW, &Tensor34U::yw);
        ten34u.property(szZX, &Tensor34U::zx);
        ten34u.property(szZY, &Tensor34U::zy);
        ten34u.property(szZZ, &Tensor34U::zz);
        ten34u.property(szZW, &Tensor34U::zw);
    }

    {
        auto ten41d = writer<Tensor41D>();
        ten41d.property(szXX, &Tensor41D::xx).description(szXX_Tensor);
        ten41d.property(szYX, &Tensor41D::yx);
        ten41d.property(szZX, &Tensor41D::zx);
        ten41d.property(szWX, &Tensor41D::wx);
    }

    {
        auto ten41f = writer<Tensor41F>();
        ten41f.property(szXX, &Tensor41F::xx).description(szXX_Tensor);
        ten41f.property(szYX, &Tensor41F::yx);
        ten41f.property(szZX, &Tensor41F::zx);
        ten41f.property(szWX, &Tensor41F::wx);
    }

    {
        auto ten41i = writer<Tensor41I>();
        ten41i.property(szXX, &Tensor41I::xx).description(szXX_Tensor);
        ten41i.property(szYX, &Tensor41I::yx);
        ten41i.property(szZX, &Tensor41I::zx);
        ten41i.property(szWX, &Tensor41I::wx);
    }

    {
        auto ten41u = writer<Tensor41U>();
        ten41u.property(szXX, &Tensor41U::xx).description(szXX_Tensor);
        ten41u.property(szYX, &Tensor41U::yx);
        ten41u.property(szZX, &Tensor41U::zx);
        ten41u.property(szWX, &Tensor41U::wx);
    }

    {
        auto ten42d = writer<Tensor42D>();
        ten42d.property(szXX, &Tensor42D::xx).description(szXX_Tensor);
        ten42d.property(szXY, &Tensor42D::xy);
        ten42d.property(szYX, &Tensor42D::yx);
        ten42d.property(szYY, &Tensor42D::yy);
        ten42d.property(szZX, &Tensor42D::zx);
        ten42d.property(szZY, &Tensor42D::zy);
        ten42d.property(szWX, &Tensor42D::wx);
        ten42d.property(szWY, &Tensor42D::wy);
    }

    {
        auto ten42f = writer<Tensor42F>();
        ten42f.property(szXX, &Tensor42F::xx).description(szXX_Tensor);
        ten42f.property(szXY, &Tensor42F::xy);
        ten42f.property(szYX, &Tensor42F::yx);
        ten42f.property(szYY, &Tensor42F::yy);
        ten42f.property(szZX, &Tensor42F::zx);
        ten42f.property(szZY, &Tensor42F::zy);
        ten42f.property(szWX, &Tensor42F::wx);
        ten42f.property(szWY, &Tensor42F::wy);
    }

    {
        auto ten42i = writer<Tensor42I>();
        ten42i.property(szXX, &Tensor42I::xx).description(szXX_Tensor);
        ten42i.property(szXY, &Tensor42I::xy);
        ten42i.property(szYX, &Tensor42I::yx);
        ten42i.property(szYY, &Tensor42I::yy);
        ten42i.property(szZX, &Tensor42I::zx);
        ten42i.property(szZY, &Tensor42I::zy);
        ten42i.property(szWX, &Tensor42I::wx);
        ten42i.property(szWY, &Tensor42I::wy);
    }

    {
        auto ten42u = writer<Tensor42U>();
        ten42u.property(szXX, &Tensor42U::xx).description(szXX_Tensor);
        ten42u.property(szXY, &Tensor42U::xy);
        ten42u.property(szYX, &Tensor42U::yx);
        ten42u.property(szYY, &Tensor42U::yy);
        ten42u.property(szZX, &Tensor42U::zx);
        ten42u.property(szZY, &Tensor42U::zy);
        ten42u.property(szWX, &Tensor42U::wx);
        ten42u.property(szWY, &Tensor42U::wy);
    }

    {
        auto ten43d = writer<Tensor43D>();
        ten43d.property(szXX, &Tensor43D::xx).description(szXX_Tensor);
        ten43d.property(szXY, &Tensor43D::xy);
        ten43d.property(szXZ, &Tensor43D::xz);
        ten43d.property(szYX, &Tensor43D::yx);
        ten43d.property(szYY, &Tensor43D::yy);
        ten43d.property(szYZ, &Tensor43D::yz);
        ten43d.property(szZX, &Tensor43D::zx);
        ten43d.property(szZY, &Tensor43D::zy);
        ten43d.property(szZZ, &Tensor43D::zz);
        ten43d.property(szWX, &Tensor43D::wx);
        ten43d.property(szWY, &Tensor43D::wy);
        ten43d.property(szWZ, &Tensor43D::wz);
    }

    {
        auto ten43f = writer<Tensor43F>();
        ten43f.property(szXX, &Tensor43F::xx).description(szXX_Tensor);
        ten43f.property(szXY, &Tensor43F::xy);
        ten43f.property(szXZ, &Tensor43F::xz);
        ten43f.property(szYX, &Tensor43F::yx);
        ten43f.property(szYY, &Tensor43F::yy);
        ten43f.property(szYZ, &Tensor43F::yz);
        ten43f.property(szZX, &Tensor43F::zx);
        ten43f.property(szZY, &Tensor43F::zy);
        ten43f.property(szZZ, &Tensor43F::zz);
        ten43f.property(szWX, &Tensor43F::wx);
        ten43f.property(szWY, &Tensor43F::wy);
        ten43f.property(szWZ, &Tensor43F::wz);
    }

    {
        auto ten43i = writer<Tensor43I>();
        ten43i.property(szXX, &Tensor43I::xx).description(szXX_Tensor);
        ten43i.property(szXY, &Tensor43I::xy);
        ten43i.property(szXZ, &Tensor43I::xz);
        ten43i.property(szYX, &Tensor43I::yx);
        ten43i.property(szYY, &Tensor43I::yy);
        ten43i.property(szYZ, &Tensor43I::yz);
        ten43i.property(szZX, &Tensor43I::zx);
        ten43i.property(szZY, &Tensor43I::zy);
        ten43i.property(szZZ, &Tensor43I::zz);
        ten43i.property(szWX, &Tensor43I::wx);
        ten43i.property(szWY, &Tensor43I::wy);
        ten43i.property(szWZ, &Tensor43I::wz);
    }

    {
        auto ten43u = writer<Tensor43U>();
        ten43u.property(szXX, &Tensor43U::xx).description(szXX_Tensor);
        ten43u.property(szXY, &Tensor43U::xy);
        ten43u.property(szXZ, &Tensor43U::xz);
        ten43u.property(szYX, &Tensor43U::yx);
        ten43u.property(szYY, &Tensor43U::yy);
        ten43u.property(szYZ, &Tensor43U::yz);
        ten43u.property(szZX, &Tensor43U::zx);
        ten43u.property(szZY, &Tensor43U::zy);
        ten43u.property(szZZ, &Tensor43U::zz);
        ten43u.property(szWX, &Tensor43U::wx);
        ten43u.property(szWY, &Tensor43U::wy);
        ten43u.property(szWZ, &Tensor43U::wz);
    }

    {
        auto ten44d = writer<Tensor44D>();
        ten44d.property(szXX, &Tensor44D::xx).description(szXX_Tensor);
        ten44d.property(szXY, &Tensor44D::xy);
        ten44d.property(szXZ, &Tensor44D::xz);
        ten44d.property(szXW, &Tensor44D::xw);
        ten44d.property(szYX, &Tensor44D::yx);
        ten44d.property(szYY, &Tensor44D::yy);
        ten44d.property(szYZ, &Tensor44D::yz);
        ten44d.property(szYW, &Tensor44D::yw);
        ten44d.property(szZX, &Tensor44D::zx);
        ten44d.property(szZY, &Tensor44D::zy);
        ten44d.property(szZZ, &Tensor44D::zz);
        ten44d.property(szZW, &Tensor44D::zw);
        ten44d.property(szWX, &Tensor44D::wx);
        ten44d.property(szWY, &Tensor44D::wy);
        ten44d.property(szWZ, &Tensor44D::wz);
        ten44d.property(szWW, &Tensor44D::ww);
    }

    {
        auto ten44f = writer<Tensor44F>();
        ten44f.property(szXX, &Tensor44F::xx).description(szXX_Tensor);
        ten44f.property(szXY, &Tensor44F::xy);
        ten44f.property(szXZ, &Tensor44F::xz);
        ten44f.property(szXW, &Tensor44F::xw);
        ten44f.property(szYX, &Tensor44F::yx);
        ten44f.property(szYY, &Tensor44F::yy);
        ten44f.property(szYZ, &Tensor44F::yz);
        ten44f.property(szYW, &Tensor44F::yw);
        ten44f.property(szZX, &Tensor44F::zx);
        ten44f.property(szZY, &Tensor44F::zy);
        ten44f.property(szZZ, &Tensor44F::zz);
        ten44f.property(szZW, &Tensor44F::zw);
        ten44f.property(szWX, &Tensor44F::wx);
        ten44f.property(szWY, &Tensor44F::wy);
        ten44f.property(szWZ, &Tensor44F::wz);
        ten44f.property(szWW, &Tensor44F::ww);
    }

    {
        auto ten44i = writer<Tensor44I>();
        ten44i.property(szXX, &Tensor44I::xx).description(szXX_Tensor);
        ten44i.property(szXY, &Tensor44I::xy);
        ten44i.property(szXZ, &Tensor44I::xz);
        ten44i.property(szXW, &Tensor44I::xw);
        ten44i.property(szYX, &Tensor44I::yx);
        ten44i.property(szYY, &Tensor44I::yy);
        ten44i.property(szYZ, &Tensor44I::yz);
        ten44i.property(szYW, &Tensor44I::yw);
        ten44i.property(szZX, &Tensor44I::zx);
        ten44i.property(szZY, &Tensor44I::zy);
        ten44i.property(szZZ, &Tensor44I::zz);
        ten44i.property(szZW, &Tensor44I::zw);
        ten44i.property(szWX, &Tensor44I::wx);
        ten44i.property(szWY, &Tensor44I::wy);
        ten44i.property(szWZ, &Tensor44I::wz);
        ten44i.property(szWW, &Tensor44I::ww);
    }

    {
        auto ten44u = writer<Tensor44U>();
        ten44u.property(szXX, &Tensor44U::xx).description(szXX_Tensor);
        ten44u.property(szXY, &Tensor44U::xy);
        ten44u.property(szXZ, &Tensor44U::xz);
        ten44u.property(szXW, &Tensor44U::xw);
        ten44u.property(szYX, &Tensor44U::yx);
        ten44u.property(szYY, &Tensor44U::yy);
        ten44u.property(szYZ, &Tensor44U::yz);
        ten44u.property(szYW, &Tensor44U::yw);
        ten44u.property(szZX, &Tensor44U::zx);
        ten44u.property(szZY, &Tensor44U::zy);
        ten44u.property(szZZ, &Tensor44U::zz);
        ten44u.property(szZW, &Tensor44U::zw);
        ten44u.property(szWX, &Tensor44U::wx);
        ten44u.property(szWY, &Tensor44U::wy);
        ten44u.property(szWZ, &Tensor44U::wz);
        ten44u.property(szWW, &Tensor44U::ww);
    }

    {
        auto tetrahedron3d = writer<Tetrahedron3D>();
        tetrahedron3d.property("a", &Tetrahedron3D::a);
        tetrahedron3d.property("b", &Tetrahedron3D::b);
        tetrahedron3d.property("c", &Tetrahedron3D::c);
        tetrahedron3d.property("d", &Tetrahedron3D::d);
    }

    {
        auto tetrahedron3f = writer<Tetrahedron3F>();
        tetrahedron3f.property("a", &Tetrahedron3F::a);
        tetrahedron3f.property("b", &Tetrahedron3F::b);
        tetrahedron3f.property("c", &Tetrahedron3F::c);
        tetrahedron3f.property("d", &Tetrahedron3F::d);
    }

    {
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
    }

    {
        auto triangle2d = writer<Triangle2D>();
        triangle2d.property("a", &Triangle2D::a);
        triangle2d.property("b", &Triangle2D::b);
        triangle2d.property("c", &Triangle2D::c);
    }

    {
        auto triangle2f = writer<Triangle2F>();
        triangle2f.property("a", &Triangle2F::a);
        triangle2f.property("b", &Triangle2F::b);
        triangle2f.property("c", &Triangle2F::c);
    }

    {
        auto triangle2i = writer<Triangle2I>();
        triangle2i.property("a", &Triangle2I::a);
        triangle2i.property("b", &Triangle2I::b);
        triangle2i.property("c", &Triangle2I::c);
    }

    {
        auto triangle2u = writer<Triangle2U>();
        triangle2u.property("a", &Triangle2U::a);
        triangle2u.property("b", &Triangle2U::b);
        triangle2u.property("c", &Triangle2U::c);
    }

    {
        auto triangle3d = writer<Triangle3D>();
        triangle3d.property("a", &Triangle3D::a);
        triangle3d.property("b", &Triangle3D::b);
        triangle3d.property("c", &Triangle3D::c);
    }

    {
        auto triangle3f = writer<Triangle3F>();
        triangle3f.property("a", &Triangle3F::a);
        triangle3f.property("b", &Triangle3F::b);
        triangle3f.property("c", &Triangle3F::c);
    }

    {
        auto triangle3i = writer<Triangle3I>();
        triangle3i.property("a", &Triangle3I::a);
        triangle3i.property("b", &Triangle3I::b);
        triangle3i.property("c", &Triangle3I::c);
    }

    {
        auto triangle3u = writer<Triangle3U>();
        triangle3u.property("a", &Triangle3U::a);
        triangle3u.property("b", &Triangle3U::b);
        triangle3u.property("c", &Triangle3U::c);
    }

    {
        auto triangle4d = writer<Triangle4D>();
        triangle4d.property("a", &Triangle4D::a);
        triangle4d.property("b", &Triangle4D::b);
        triangle4d.property("c", &Triangle4D::c);
    }

    {
        auto triangle4f = writer<Triangle4F>();
        triangle4f.property("a", &Triangle4F::a);
        triangle4f.property("b", &Triangle4F::b);
        triangle4f.property("c", &Triangle4F::c);
    }

    {
        auto triangle4i = writer<Triangle4I>();
        triangle4i.property("a", &Triangle4I::a);
        triangle4i.property("b", &Triangle4I::b);
        triangle4i.property("c", &Triangle4I::c);
    }

    {
        auto triangle4u = writer<Triangle4U>();
        triangle4u.property("a", &Triangle4U::a);
        triangle4u.property("b", &Triangle4U::b);
        triangle4u.property("c", &Triangle4U::c);
    }

    {
        auto trivec3d = writer<Trivector3D>();
        trivec3d.property("xyz", &Trivector3D::xyz);
    }

    {
        auto trivec3f = writer<Trivector3F>();
        trivec3f.property("xyz", &Trivector3F::xyz);
    }

    {
        auto trivec4d = writer<Trivector4D>();
        trivec4d.property("xyz", &Trivector4D::xyz);
        trivec4d.property("yzw", &Trivector4D::yzw);
        trivec4d.property("zwx", &Trivector4D::zwx);
        trivec4d.property("wxy", &Trivector4D::wxy);
    }

    {
        auto trivec4f = writer<Trivector4F>();
        trivec4f.property("xyz", &Trivector4F::xyz);
        trivec4f.property("yzw", &Trivector4F::yzw);
        trivec4f.property("zwx", &Trivector4F::zwx);
        trivec4f.property("wxy", &Trivector4F::wxy);
    }

    {
        auto w = writer<Vector1D>();
        w.property(szLength, &Vector1D::length).description(szLength_Vector).alias(szLen);
        w.property(szLength², &Vector1D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1D::x);
    }

    {
        auto w = writer<Vector1F>();
        w.property(szLength, &Vector1F::length).description(szLength_Vector).alias(szLen);
        w.property(szLength², &Vector1F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1F::x);
    }

    {
        auto w = writer<Vector1I>();
        w.property(szLength², &Vector1I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1I::x).description(szX_Vector);
    }

    {
        auto w = writer<Vector1U>();
        w.property(szLength², &Vector1U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1U::x).description(szX_Vector);
    }

    {
        auto w = writer<Vector2D>();
        w.property(szLength², &Vector2D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector2D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector2D::x).description(szX_Vector);
        w.property(szY, &Vector2D::y).description(szY_Vector);
        w.method(szZ, &Vector2D::z).description(szZ_Vector2);
    }

    {
        auto w = writer<Vector2F>();
        w.property(szLength², &Vector2F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector2F::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector2F::x).description(szX_Vector);
        w.property(szY, &Vector2F::y).description(szY_Vector);
        w.method(szZ, &Vector2F::z).description(szZ_Vector2);
    }

    {
        auto w = writer<Vector2I>();
        w.property(szLength², &Vector2I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector2I::x).description(szX_Vector);
        w.property(szY, &Vector2I::y).description(szY_Vector);
        w.method(szZ, &Vector2I::z).description(szZ_Vector2);
    }

    {
        auto w = writer<Vector2U>();
        w.property(szLength², &Vector2U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector2U::x).description(szX_Vector);
        w.property(szY, &Vector2U::y).description(szY_Vector);
        w.method(szZ, &Vector2U::z).description(szZ_Vector2);
    }

    {
        auto w = writer<Vector3D>();
        w.property(szLength², &Vector3D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector3D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector3D::x).description(szX_Vector);
        w.property(szY, &Vector3D::y).description(szY_Vector);
        w.property(szZ, &Vector3D::z).description(szZ_Vector);
    }

    {
        auto w = writer<Vector3F>();
        w.property(szLength², &Vector3F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector3F::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector3F::x).description(szX_Vector);
        w.property(szY, &Vector3F::y).description(szY_Vector);
        w.property(szZ, &Vector3F::z).description(szZ_Vector);
    }

    {
        auto w = writer<Vector3I>();
        w.property(szLength², &Vector3I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector3I::x).description(szX_Vector);
        w.property(szY, &Vector3I::y).description(szY_Vector);
        w.property(szZ, &Vector3I::z).description(szZ_Vector);
    }

    {
        auto w = writer<Vector3U>();
        w.property(szLength², &Vector3U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector3U::x).description(szX_Vector);
        w.property(szY, &Vector3U::y).description(szY_Vector);
        w.property(szZ, &Vector3U::z).description(szZ_Vector);
    }

    {
        auto w = writer<Vector4D>();
        w.property(szLength², &Vector4D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector4D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector4D::x).description(szX_Vector);
        w.property(szY, &Vector4D::y).description(szY_Vector);
        w.property(szZ, &Vector4D::z).description(szZ_Vector);
        w.property(szW, &Vector4D::w).description(szW_Vector);
    }

    {
        auto w = writer<Vector4F>();
        w.property(szLength², &Vector4F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector4F::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector4F::x).description(szX_Vector);
        w.property(szY, &Vector4F::y).description(szY_Vector);
        w.property(szZ, &Vector4F::z).description(szZ_Vector);
        w.property(szW, &Vector4F::w).description(szW_Vector);
    }

    {
        auto w = writer<Vector4I>();
        w.property(szLength², &Vector4I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector4I::x).description(szX_Vector);
        w.property(szY, &Vector4I::y).description(szY_Vector);
        w.property(szZ, &Vector4I::z).description(szZ_Vector);
        w.property(szW, &Vector4I::w).description(szW_Vector);
    }

    {
        auto w = writer<Vector4U>();
        w.property(szLength², &Vector4U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector4U::x).description(szX_Vector);
        w.property(szY, &Vector4U::y).description(szY_Vector);
        w.property(szZ, &Vector4U::z).description(szZ_Vector);
        w.property(szW, &Vector4U::w).description(szW_Vector);
    }
}

YQ_INVOKE(reg_math();)

namespace yq {
    void        initialize_math()
    {
    }
}

#include "AxBox1.hxx"
#include "AxBox2.hxx"
#include "AxBox3.hxx"
#include "AxBox4.hxx"

#include "Bivector2.hxx"
#include "Bivector3.hxx"
#include "Bivector4.hxx"

#include "Circle2.hxx"
#include "Circle3.hxx"

#include "Fraction.hxx"

#include "MKS.hxx"

#include "Multivector1.hxx"
#include "Multivector2.hxx"
#include "Multivector3.hxx"
#include "Multivector4.hxx"

#include "Normal2.hxx"
#include "Normal3.hxx"

#include "Plane3.hxx"

#include "Polygon2.hxx"
#include "Polygon3.hxx"
#include "Polygon4.hxx"

#include "Polyline2.hxx"
#include "Polyline3.hxx"
#include "Polyline4.hxx"

#include "Pose2.hxx"
#include "Pose3.hxx"

#include "Quadrilateral2.hxx"
#include "Quadvector4.hxx"
#include "Quaternion3.hxx"

#include "Range.hxx"
#include "Ray2.hxx"
#include "Ray3.hxx"
#include "Ray4.hxx"
#include "Rectangle2.hxx"

#include "RGB.hxx"
#include "RGBA.hxx"

#include "SCALED.hxx"
#include "Segment1.hxx"
#include "Segment2.hxx"
#include "Segment3.hxx"
#include "Segment4.hxx"

#include "Size1.hxx"
#include "Size2.hxx"
#include "Size3.hxx"
#include "Size4.hxx"

#include "Sphere3.hxx"
#include "Sphere4.hxx"

#include "Tensor11.hxx"
#include "Tensor12.hxx"
#include "Tensor13.hxx"
#include "Tensor14.hxx"

#include "Tensor21.hxx"
#include "Tensor22.hxx"
#include "Tensor23.hxx"
#include "Tensor24.hxx"

#include "Tensor31.hxx"
#include "Tensor32.hxx"
#include "Tensor33.hxx"
#include "Tensor34.hxx"

#include "Tensor41.hxx"
#include "Tensor42.hxx"
#include "Tensor43.hxx"
#include "Tensor44.hxx"

#include "Tetrahedron3.hxx"

#include "Triangle2.hxx"
#include "Triangle3.hxx"
#include "Triangle4.hxx"

#include "Trivector3.hxx"
#include "Trivector4.hxx"

#include "Vector1.hxx"
#include "Vector2.hxx"
#include "Vector3.hxx"
#include "Vector4.hxx"

