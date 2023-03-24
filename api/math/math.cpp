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
static constexpr const std::string_view     szA_Multivector             = "Scalar 'alpha' of the multivector";
static constexpr const std::string_view     szA_Quadrilateral           = "First point 'A' of the quadrilateral";
static constexpr const std::string_view     szA_Segment                 = "First point 'A' of the segment";
static constexpr const std::string_view     szA_Tetrahedron             = "First point 'A' of the tetrahedron";
static constexpr const std::string_view     szA_Triangle                = "First point 'A' of the triangle";
static constexpr const std::string_view     szAlpha                     = "alpha";
static constexpr const std::string_view     szAlpha_Color               = "Alpha channel of the color";
static constexpr const std::string_view     szArea                      = "area";
static constexpr const std::string_view     szArea_Box                  = "Area of the box";
static constexpr const std::string_view     szArea_Circle               = "Area of the box";
static constexpr const std::string_view     szB                         = "b";
static constexpr const std::string_view     szB_Quadrilateral           = "Second point 'B' of the quadrilateral";
static constexpr const std::string_view     szB_Segment                 = "Second point 'B' of the segment";
static constexpr const std::string_view     szB_Tetrahedron             = "Second point 'B' of the tetrahedron";
static constexpr const std::string_view     szB_Triangle                = "Second point 'B' of the triangle";
static constexpr const std::string_view     szBlue                      = "blue";
static constexpr const std::string_view     szBlue_Color                = "Blue channel of the color";
static constexpr const std::string_view     szBox                       = "box";
static constexpr const std::string_view     szBox_Circle                = "Bounding box of the circle";
static constexpr const std::string_view     szC                         = "c";
static constexpr const std::string_view     szC_Quadrilateral           = "Third point 'C' of the quadrilateral";
static constexpr const std::string_view     szC_Tetrahedron             = "Third point 'C' of the tetrahedron";
static constexpr const std::string_view     szC_Triangle                = "Third point 'C' of the triangle";
static constexpr const std::string_view     szCenter                    = "center";
static constexpr const std::string_view     szCenter_Box                = "Center of the box";
static constexpr const std::string_view     szCenter_Circle             = "Center of the circle";
static constexpr const std::string_view     szCenter_Sphere             = "Center of the sphere";
static constexpr const std::string_view     szCir                       = "cir";
static constexpr const std::string_view     szCirc                      = "circ";
static constexpr const std::string_view     szCircumcircle              = "circumcircle";
static constexpr const std::string_view     szCircumcircle_Box          = "Circumcircle of the box";
static constexpr const std::string_view     szCircumference             = "circumference";
static constexpr const std::string_view     szCircumference_Circle      = "Circumference of the circle";
static constexpr const std::string_view     szCnt                       = "cnt";
static constexpr const std::string_view     szCorner                    = "corner";
static constexpr const std::string_view     szCount                     = "count";
static constexpr const std::string_view     szCount_Count               = "Count of the counter";
static constexpr const std::string_view     szContains                  = "contains";
static constexpr const std::string_view     szContains_Box_Box          = "Tests if other box is inside/touching this box";
static constexpr const std::string_view     szContains_Box_Pt           = "Tests if point is inside/touching the box";
static constexpr const std::string_view     szCtr                       = "ctr";
static constexpr const std::string_view     szD                         = "d";
static constexpr const std::string_view     szD_Quadrilateral           = "Fourth point 'D' of the quadrilateral";
static constexpr const std::string_view     szD_Tetrahedron             = "Fourth point 'D' of the tetrahedron";
static constexpr const std::string_view     szDen                       = "den";
static constexpr const std::string_view     szDenominator               = "denominator";
static constexpr const std::string_view     szDenominator_Fraction      = "Denominator of the fraction";
static constexpr const std::string_view     szDepth                     = "depth";
static constexpr const std::string_view     szDia                       = "dia";
static constexpr const std::string_view     szDiameter                  = "diameter";
static constexpr const std::string_view     szDiameter_Circle           = "Diameter of the circle";
static constexpr const std::string_view     szDim                       = "dim";
static constexpr const std::string_view     szDimension                 = "dimensions";
static constexpr const std::string_view     szDimension_Box             = "Dimension(s) of the box";
static constexpr const std::string_view     szDir                       = "dir";
static constexpr const std::string_view     szDirection                 = "direction";
static constexpr const std::string_view     szDirection_Normal          = "Direction of the normal";
static constexpr const std::string_view     szDirection_Ray             = "Direction of the ray";
static constexpr const std::string_view     szEclipses                  = "eclipses";
static constexpr const std::string_view     szEclipses_Box_Box          = "Tests if other box is inside/touching this box";
static constexpr const std::string_view     szEclipses_Box_Circle       = "Tests if circle is inside/touching this box";
static constexpr const std::string_view     szEclipses_Box_Pt           = "Tests if point is inside/touching the box";
static constexpr const std::string_view     szG                         = "g";
static constexpr const std::string_view     szGreen                     = "green";
static constexpr const std::string_view     szGreen_Color               = "Green channel of the color";
static constexpr const std::string_view     szH                         = "h";
static constexpr const std::string_view     szHeight                    = "height";
static constexpr const std::string_view     szHi                        = "hi";
static constexpr const std::string_view     szHigh                      = "high";
static constexpr const std::string_view     szHigh_Box                  = "High-corner of the box";
static constexpr const std::string_view     szHigh_Range                = "High-value of the range";
static constexpr const std::string_view     szHypervolume               = "hypervolume";
static constexpr const std::string_view     szHypervolume_Box4          = "Hypervolume of the box";
static constexpr const std::string_view     szHVol                      = "hvol";
static constexpr const std::string_view     szI                         = "i";
static constexpr const std::string_view     szI_Coord                   = "I-component of the coordinate";
static constexpr const std::string_view     szIm                        = "im";
static constexpr const std::string_view     szImag                      = "imag";
static constexpr const std::string_view     szImaginary                 = "imaginary";
static constexpr const std::string_view     szImaginary_Complex         = "Imaginary component of the complex number";
static constexpr const std::string_view     szIncircle                  = "incircle";
static constexpr const std::string_view     szIncircle_Box              = "Incircle of the box";
static constexpr const std::string_view     szJ                         = "j";
static constexpr const std::string_view     szJ_Coord                   = "J-component of the coordinate";
static constexpr const std::string_view     szK                         = "k";
static constexpr const std::string_view     szL                         = "l";
static constexpr const std::string_view     szLen                       = "len";
static constexpr const std::string_view     szLen²                      = "len2";
static constexpr const std::string_view     szLength                    = "length";
static constexpr const std::string_view     szLength_Vector             = "Length of the vector";
static constexpr const std::string_view     szLength²                   = "length2";
static constexpr const std::string_view     szLength²_Vector            = "Length SQUARED of the vector";
static constexpr const std::string_view     szLo                        = "lo";
static constexpr const std::string_view     szLow                       = "low";
static constexpr const std::string_view     szLow_Box                   = "Low-corner of the box";
static constexpr const std::string_view     szLow_Range                 = "Low-value of the range";
static constexpr const std::string_view     szM                         = "m";
static constexpr const std::string_view     szMag                       = "mag";
static constexpr const std::string_view     szMagnitude                 = "magnitude";
static constexpr const std::string_view     szMagnitude_Complex         = "Magnitude of the complex number";
static constexpr const std::string_view     szN                         = "n";
static constexpr const std::string_view     szNE                        = "ne";
static constexpr const std::string_view     szNortheast                 = "northeast";
static constexpr const std::string_view     szNortheast_Box             = "North-east corner of the box";
static constexpr const std::string_view     szNorthwest                 = "northwest";
static constexpr const std::string_view     szNorthwest_Box             = "North-west corner of the box";
static constexpr const std::string_view     szNum                       = "num";
static constexpr const std::string_view     szNumerator                 = "numerator";
static constexpr const std::string_view     szNumerator_Fraction        = "Numerator of the fraction";
static constexpr const std::string_view     szNW                        = "nw";
static constexpr const std::string_view     szOverlaps                  = "overlaps";
static constexpr const std::string_view     szOverlaps_Box_Box          = "Tests if other box overlaps this box";
static constexpr const std::string_view     szPeri                      = "peri";
static constexpr const std::string_view     szPerimeter                 = "perimeter";
static constexpr const std::string_view     szPerimeter_Box             = "Perimeter of the box";
static constexpr const std::string_view     szPerimeter_Circle          = "Perimeter of the circle";
static constexpr const std::string_view     szPoint                     = "point";
static constexpr const std::string_view     szPoint_Ray                 = "Point of the ray";
static constexpr const std::string_view     szPos                       = "pos";
static constexpr const std::string_view     szPosition                  = "position";
static constexpr const std::string_view     szPosition_Rectangle        = "Corner of the rectangle, it's nominal position";
static constexpr const std::string_view     szProject                   = "global";
static constexpr const std::string_view     szProject_Box               = "Project local point (u/v/w) to real space (x/y/z)";
static constexpr const std::string_view     szPt                        = "pt";
static constexpr const std::string_view     szR                         = "r";
static constexpr const std::string_view     szRad                       = "rad";
static constexpr const std::string_view     szRadius                    = "radius";
static constexpr const std::string_view     szRadius_Circle             = "Radius of the circle";
static constexpr const std::string_view     szRadius_Sphere             = "Radius of the sphere";
static constexpr const std::string_view     szRe                        = "re";
static constexpr const std::string_view     szReal                      = "real";
static constexpr const std::string_view     szReal_Complex              = "Real component of the comolex number";
static constexpr const std::string_view     szRed                       = "red";
static constexpr const std::string_view     szRed_Color                 = "Red channel of the color";
static constexpr const std::string_view     szSE                        = "se";
static constexpr const std::string_view     szSArea                     = "sarea";
static constexpr const std::string_view     szSize                      = "size";
static constexpr const std::string_view     szSize_Box                  = "Size of the box";
static constexpr const std::string_view     szSize_Rectangle            = "Size of the rectangle";
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
static constexpr const std::string_view     szW_Multivector             = "W component of the multivector";
static constexpr const std::string_view     szW_Quaternion              = "W component of the quaternion";
static constexpr const std::string_view     szW_Size                    = "W component of the size, commonly referred to as the duration";
static constexpr const std::string_view     szW_Vector                  = "W component of the vector";
static constexpr const std::string_view     szWidth                     = "width";
static constexpr const std::string_view     szWW                        = "ww";
static constexpr const std::string_view     szWW_Tensor                 = "WW component of the tensor";
static constexpr const std::string_view     szWX                        = "wx";
static constexpr const std::string_view     szWX_Bivector               = "WX component of the bivector";
static constexpr const std::string_view     szWX_Multivector            = "WX component of the multivector";
static constexpr const std::string_view     szWX_Tensor                 = "WX component of the tensor";
static constexpr const std::string_view     szWXY                       = "wxy";
static constexpr const std::string_view     szWXY_Multivector           = "WXY component of the multivector";
static constexpr const std::string_view     szWXY_Trivector             = "WXY component of the trivector";
static constexpr const std::string_view     szWY                        = "wy";
static constexpr const std::string_view     szWY_Tensor                 = "WY component of the tensor";
static constexpr const std::string_view     szWZ                        = "wz";
static constexpr const std::string_view     szWZ_Tensor                 = "WZ component of the tensor";
static constexpr const std::string_view     szX                         = "x";
static constexpr const std::string_view     szX_Box                     = "X range of the box";
static constexpr const std::string_view     szX_Multivector             = "X component of the multivector";
static constexpr const std::string_view     szX_Quaternion              = "X component of the quaternion";
static constexpr const std::string_view     szX_Size                    = "X component of the size, commonly referred to as the width";
static constexpr const std::string_view     szX_Vector                  = "X component of the vector";
static constexpr const std::string_view     szXW                        = "xw";
static constexpr const std::string_view     szXW_Tensor                 = "XW component of the tensor";
static constexpr const std::string_view     szXX                        = "xx";
static constexpr const std::string_view     szXX_Tensor                 = "XX component of the tensor";
static constexpr const std::string_view     szXY                        = "xy";
static constexpr const std::string_view     szXY_Bivector               = "XY component of the bivector";
static constexpr const std::string_view     szXY_Multivector            = "XY component of the multivector";
static constexpr const std::string_view     szXY_Tensor                 = "XY component of the tensor";
static constexpr const std::string_view     szXYZ                       = "xyz";
static constexpr const std::string_view     szXYZ_Multivector           = "XYZ component of the multivector";
static constexpr const std::string_view     szXYZ_Trivector             = "XYZ component of the trivector";
static constexpr const std::string_view     szXYZW                      = "xyzw";
static constexpr const std::string_view     szXYZW_Multivector          = "XYZW component of the multivector";
static constexpr const std::string_view     szXYZW_Quadvector           = "XYZW component of the quadvector";
static constexpr const std::string_view     szXZ                        = "xz";
static constexpr const std::string_view     szXZ_Bivector               = "XZ component of the bivector";
static constexpr const std::string_view     szXZ_Multivector            = "XZ component of the multivector";
static constexpr const std::string_view     szXZ_Tensor                 = "XZ component of the tensor";
static constexpr const std::string_view     szY                         = "y";
static constexpr const std::string_view     szY_Box                     = "Y range of the box";
static constexpr const std::string_view     szY_Multivector             = "Y component of the multivector";
static constexpr const std::string_view     szY_Quaternion              = "Y component of the quaternion";
static constexpr const std::string_view     szY_Size                    = "Y component of the size, commonly referred to as the height";
static constexpr const std::string_view     szY_Vector                  = "Y component of the vector";
static constexpr const std::string_view     szYW                        = "yw";
static constexpr const std::string_view     szYW_Bivector               = "YW component of the bivector";
static constexpr const std::string_view     szYW_Multivector            = "YW component of the Multivector";
static constexpr const std::string_view     szYW_Tensor                 = "YW component of the tensor";
static constexpr const std::string_view     szYX                        = "yx";
static constexpr const std::string_view     szYX_Bivector               = "YX component of the bivector";
static constexpr const std::string_view     szYX_Multivector            = "YX component of the multivector";
static constexpr const std::string_view     szYX_Tensor                 = "YX component of the tensor";
static constexpr const std::string_view     szYY                        = "yy";
static constexpr const std::string_view     szYY_Tensor                 = "YY component of the tensor";
static constexpr const std::string_view     szYZ                        = "yz";
static constexpr const std::string_view     szYZ_Bivector               = "YZ component of the bivector";
static constexpr const std::string_view     szYZ_Multivector            = "YZ component of the multivector";
static constexpr const std::string_view     szYZ_Tensor                 = "YZ component of the tensor";
static constexpr const std::string_view     szYZW                       = "yzw";
static constexpr const std::string_view     szYZW_Multivector           = "YZW component of the multivector";
static constexpr const std::string_view     szYZW_Trivector             = "YZW component of the trivector";
static constexpr const std::string_view     szZ                         = "z";
static constexpr const std::string_view     szZ_Box                     = "Z range of the box";
static constexpr const std::string_view     szZ_Multivector             = "Z component of the multivector";
static constexpr const std::string_view     szZ_Quaternion              = "Z component of the quaternion";
static constexpr const std::string_view     szZ_Size                    = "Z component of the size, commonly referred to as the depth";
static constexpr const std::string_view     szZ_Vector                  = "Z component of the vector";
static constexpr const std::string_view     szZ_Vector2                 = "Promotes to Vector3 with a z-value";
static constexpr const std::string_view     szZW                        = "zw";
static constexpr const std::string_view     szZW_Bivector               = "ZW component of the bivector";
static constexpr const std::string_view     szZW_Multivector            = "ZW component of the multivector";
static constexpr const std::string_view     szZW_Tensor                 = "ZW component of the tensor";
static constexpr const std::string_view     szZWX                       = "zwx";
static constexpr const std::string_view     szZWX_Multivector           = "ZWX component of the multivector";
static constexpr const std::string_view     szZWX_Trivector             = "ZWX component of the trivector";
static constexpr const std::string_view     szZX                        = "zx";
static constexpr const std::string_view     szZX_Bivector               = "ZX component of the bivector";
static constexpr const std::string_view     szZX_Multivector            = "ZX component of the multivector";
static constexpr const std::string_view     szZX_Tensor                 = "ZX component of the tensor";
static constexpr const std::string_view     szZY                        = "zy";
static constexpr const std::string_view     szZY_Tensor                 = "ZY component of the tensor";
static constexpr const std::string_view     szZZ                        = "zz";
static constexpr const std::string_view     szZZ_Tensor                 = "ZZ component of the tensor";

//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//  OTHER HELPERS FOR MATH

namespace yq {
    namespace {
        double  magnitude_complexD(const ComplexD& v)
        {
            return std::abs(v);
        }

        double  magnitude_complexF(const ComplexF& v)
        {
            return std::abs(v);
        }
    }
}    
    
//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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
        w.description("1D Axially Aligned Bounding Box in double");
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
        w.description("1D Axially Aligned Bounding Box in float");
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
        w.description("1D Axially Aligned Bounding Box in integer");
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
        w.description("1D Axially Aligned Bounding Box in unsigned integers");
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
        w.description("2D Axially Aligned Bounding Box in double");
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
        w.description("2D Axially Aligned Bounding Box in float");
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
        w.description("2D Axially Aligned Bounding Box in integer");
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
        w.description("2D Axially Aligned Bounding Box in unsigned integers");
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
        w.description("3D Axially Aligned Bounding Box in double");
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
        w.description("3D Axially Aligned Bounding Box in float");
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
        w.description("3D Axially Aligned Bounding Box in integer");
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
        w.description("3D Axially Aligned Bounding Box in unsigned integers");
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
        w.description("4D Axially Aligned Bounding Box in double");
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
        w.description("4D Axially Aligned Bounding Box in float");
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
        w.description("4D Axially Aligned Bounding Box in integer");
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
        w.description("4D Axially Aligned Bounding Box in unsigned integers");
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
        w.description("2D Bivector in double");
        w.property(szXY, &Bivector2D::xy).description(szXY_Bivector);
    }

    {
        auto w = writer<Bivector2F>();
        w.description("2D Bivector in float");
        w.property(szXY, &Bivector2F::xy).description(szXY_Bivector);
    }

    {
        auto w = writer<Bivector3D>();
        w.description("3D Bivector in double");
        w.property(szXY, &Bivector3D::xy).description(szXY_Bivector);
        w.property(szYZ, &Bivector3D::yz).description(szYZ_Bivector);
        w.property(szZX, &Bivector3D::zx).description(szZX_Bivector);
    }

    {
        auto w = writer<Bivector3F>();
        w.description("3D Bivector in float");
        w.property(szXY, &Bivector3F::xy).description(szXY_Bivector);
        w.property(szYZ, &Bivector3F::yz).description(szYZ_Bivector);
        w.property(szZX, &Bivector3F::zx).description(szZX_Bivector);
    }

    {
        auto w = writer<Bivector4D>();
        w.description("4D Bivector in double");
        w.property(szXY, &Bivector4D::xy).description(szXY_Bivector);
        w.property(szYZ, &Bivector4D::yz).description(szYZ_Bivector);
        w.property(szZW, &Bivector4D::zw).description(szZW_Bivector);
        w.property(szWX, &Bivector4D::wx).description(szWX_Bivector);
        w.property(szXZ, &Bivector4D::xz).description(szXZ_Bivector);
        w.property(szYW, &Bivector4D::yw).description(szYW_Bivector);
    }

    {
        auto w = writer<Bivector4F>();
        w.description("4D Bivector in float");
        w.property(szXY, &Bivector4F::xy).description(szXY_Bivector);
        w.property(szYZ, &Bivector4F::yz).description(szYZ_Bivector);
        w.property(szZW, &Bivector4F::zw).description(szZW_Bivector);
        w.property(szWX, &Bivector4F::wx).description(szWX_Bivector);
        w.property(szXZ, &Bivector4F::xz).description(szXZ_Bivector);
        w.property(szYW, &Bivector4F::yw).description(szYW_Bivector);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Circle2
    
    {
        auto w = writer<Circle2D>();
        w.description("2D circle in double");
        w.property(szArea, &Circle2D::area).description(szArea_Circle).alias(szA);
        w.property(szBox, &Circle2D::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2D::center).description(szCenter_Circle).alias({szPoint, szPt});
        w.property(szCircumference, &Circle2D::circumference).description(szCircumference).alias({szCirc, szPerimeter, szPeri});
        w.property(szDiameter, &Circle2D::diameter).description(szDiameter_Circle).alias({szDia, szD});
        w.property(szRadius, &Circle2D::radius).description(szRadius_Circle).alias({szRad, szR});
        w.property(szValid, &Circle2D::valid).description(szValid_Circle);
    }
    
    {
        auto w = writer<Circle2F>();
        w.description("2D circle in float");
        w.property(szArea, &Circle2F::area).description(szArea_Circle).alias(szA);
        w.property(szBox, &Circle2F::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2F::center).description(szCenter_Circle).alias({szPoint, szPt});
        w.property(szCircumference, &Circle2F::circumference).description(szCircumference).alias({szCirc, szPerimeter, szPeri});
        w.property(szDiameter, &Circle2F::diameter).description(szDiameter_Circle).alias({szDia, szD});
        w.property(szRadius, &Circle2F::radius).description(szRadius_Circle).alias({szRad, szR});
        w.property(szValid, &Circle2F::valid).description(szValid_Circle);
    }
    
    {
        auto w = writer<Circle2I>();
        w.description("2D circle in integer");
        w.property(szBox, &Circle2I::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2I::center).description(szCenter_Circle).alias({szPoint, szPt});
        w.property(szDiameter, &Circle2I::diameter).description(szDiameter_Circle).alias({szDia, szD});
        w.property(szRadius, &Circle2I::radius).description(szRadius_Circle).alias({szRad, szR});
        w.property(szValid, &Circle2I::valid).description(szValid_Circle);
    }
    
    {
        auto w = writer<Circle2U>();
        w.description("2D circle in unsigned int");
        w.property(szBox, &Circle2U::bounds).description(szBox_Circle);
        w.property(szCenter, &Circle2U::center).description(szCenter_Circle).alias({szPoint, szPt});
        w.property(szDiameter, &Circle2U::diameter).description(szDiameter_Circle).alias({szDia, szD});
        w.property(szRadius, &Circle2U::radius).description(szRadius_Circle).alias({szRad, szR});
        w.property(szValid, &Circle2U::valid).description(szValid_Circle);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Complex Numbers
    
    {
        auto w = writer<ComplexD>();
        w.description("Complex number in double");
        w.property(szReal, &ComplexD::real).setter((void(ComplexD::*)(double)) &ComplexD::real)
            .description(szReal_Complex)
            .alias({szRe, szR});
        w.property(szImaginary, &ComplexD::imag).setter((void(ComplexD::*)(double)) &ComplexD::imag)
            .description(szImaginary_Complex)
            .alias({szImag, szIm, szI});
        w.property(szMagnitude, magnitude_complexD).description(szMagnitude_Complex).alias(szMag);
    }

    {
        auto w = writer<ComplexF>();
        w.description("Complex number in float");
        w.property(szReal, (float (ComplexF::*)() const) &ComplexF::real).setter((void(ComplexF::*)(float)) &ComplexF::real)
            .description(szReal_Complex)
            .alias({ szRe, szR });
        w.property(szImaginary, (float (ComplexF::*)() const) &ComplexF::imag).setter((void(ComplexF::*)(float)) &ComplexF::imag)
            .description(szImaginary_Complex)
            .alias({szImag, szIm, szI});
        w.property(szMagnitude, magnitude_complexF).description(szMagnitude_Complex).alias(szMag);
    }

    {
        auto w = writer<ComplexI>();
        w.description("Complex number in integer");
        w.property(szReal, (int (ComplexI::*)() const) &ComplexI::real).setter((void(ComplexI::*)(int)) &ComplexI::real)
            .description(szReal_Complex)
            .alias({szRe, szR});
        w.property(szImaginary, (int (ComplexI::*)() const) &ComplexI::imag).setter((void(ComplexI::*)(int)) &ComplexI::imag)
            .description(szImaginary_Complex)
            .alias({szImag, szIm, szI});
    }

    {
        auto w = writer<ComplexU>();
        w.description("Complex number in unsigned integer");
        w.property(szReal, (unsigned (ComplexU::*)() const) &ComplexU::real).setter((void(ComplexU::*)(unsigned)) &ComplexU::real)
            .description(szReal_Complex)
            .alias({szRe, szR});
        w.property(szImaginary, (unsigned (ComplexU::*)() const) &ComplexU::imag).setter((void(ComplexU::*)(unsigned)) &ComplexU::imag)
            .description(szImaginary_Complex)
            .alias({szImag, szIm, szI});
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Coordinates

    {
        auto w = writer<Coord2D>();
        w.description("2D coordinate in double");
        w.property(szI, &Coord2D::i).description(szI_Coord);
        w.property(szJ, &Coord2D::j).description(szJ_Coord);
    }

    {
        auto w = writer<Coord2F>();
        w.description("2D coordinate in float");
        w.property(szI, &Coord2F::i).description(szI_Coord);
        w.property(szJ, &Coord2F::j).description(szJ_Coord);
    }

    {
        auto w = writer<Coord2I>();
        w.description("2D coordinate in integer");
        w.property(szI, &Coord2I::i).description(szI_Coord);
        w.property(szJ, &Coord2I::j).description(szJ_Coord);
    }

    {
        auto w = writer<Coord2U>();
        w.description("2D coordinate in unsigned integer");
        w.property(szI, &Coord2U::i).description(szI_Coord);
        w.property(szJ, &Coord2U::j).description(szJ_Coord);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Counters

    {
        auto w   = writer<CountI8>();
        w.description("Counter with 8-bit integer");
        w.property(szCount, &CountI8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountI16>();
        w.description("Counter with 16-bit integer");
        w.property(szCount, &CountI16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountI32>();
        w.description("Counter with 32-bit integer");
        w.property(szCount, &CountI32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountI64>();
        w.description("Counter with 64-bit integer");
        w.property(szCount, &CountI64::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountU8>();
        w.description("Counter with 8-bit unsigned integer");
        w.property(szCount, &CountU8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountU16>();
        w.description("Counter with 16-bit unsigned integer");
        w.property(szCount, &CountU16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountU32>();
        w.description("Counter with 32-bit unsigned integer");
        w.property(szCount, &CountU32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<CountU64>();
        w.description("Counter with 64-bit unsigned integer");
        w.property(szCount, &CountU64::cnt).description(szCount_Count).alias(szCnt);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Fractions

    {
        auto w  = writer<FractionI>();
        w.description("Fraction using integers");
        w.property(szNumerator, &FractionI::num).description(szNumerator_Fraction).alias({szNum, szN});
        w.property(szDenominator, &FractionI::den).description(szDenominator_Fraction).alias({szDen, szD});
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

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Hi-counters (start at max-value)
    {
        auto w   = writer<HCountI8>();
        w.description("8-bit signed integer counter that starts at max value");
        w.property(szCount, &HCountI8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountI16>();
        w.description("16-bit signed integer counter that starts at max value");
        w.property(szCount, &HCountI16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountI32>();
        w.description("32-bit signed integer counter that starts at max value");
        w.property(szCount, &HCountI32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountI64>();
        w.description("64-bit signed integer counter that starts at max value");
        w.property(szCount, &HCountI64::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountU8>();
        w.description("8-bit unsigned integer counter that starts at max value");
        w.property(szCount, &HCountU8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountU16>();
        w.description("16-bit unsigned integer counter that starts at max value");
        w.property(szCount, &HCountU16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountU32>();
        w.description("32-bit unsigned integer counter that starts at max value");
        w.property(szCount, &HCountU32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<HCountU64>();
        w.description("64-bit unsigned integer counter that starts at max value");
        w.property(szCount, &HCountU64::cnt).description(szCount_Count).alias(szCnt);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Lo-counters (start at min-value)
    
    {
        auto w   = writer<LCountI8>();
        w.description("8-bit integer counter that starts at minimum value");
        w.property(szCount, &LCountI8::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<LCountI16>();
        w.description("16-bit integer counter that starts at minimum value");
        w.property(szCount, &LCountI16::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<LCountI32>();
        w.description("32-bit integer counter that starts at minimum value");
        w.property(szCount, &LCountI32::cnt).description(szCount_Count).alias(szCnt);
    }

    {
        auto w   = writer<LCountI64>();
        w.description("64-bit integer counter that starts at minimum value");
        w.property(szCount, &LCountI64::cnt).description(szCount_Count).alias(szCnt);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Multivector

    {
        auto w  = writer<Multivector1D>();
        w.description("1D Multivector in double");
        w.property(szA, &Multivector1D::a).description(szA_Multivector);
        w.property(szX, &Multivector1D::x).description(szX_Multivector);
    }

    {
        auto w  = writer<Multivector1F>();
        w.description("1D Multivector in float");
        w.property(szA, &Multivector1F::a).description(szA_Multivector);
        w.property(szX, &Multivector1F::x).description(szX_Multivector);
    }

    {
        auto w  = writer<Multivector2D>();
        w.description("2D Multivector in double");
        w.property(szA, &Multivector2D::a).description(szA_Multivector);
        w.property(szX, &Multivector2D::x).description(szX_Multivector);
        w.property(szY, &Multivector2D::y).description(szY_Multivector);
        w.property(szXY, &Multivector2D::xy).description(szXY_Multivector);
    }

    {
        auto w  = writer<Multivector2F>();
        w.description("2D Multivector in float");
        w.property(szA, &Multivector2F::a).description(szA_Multivector);
        w.property(szX, &Multivector2F::x).description(szX_Multivector);
        w.property(szY, &Multivector2F::y).description(szY_Multivector);
        w.property(szXY, &Multivector2F::xy).description(szXY_Multivector);
    }

    {
        auto w  = writer<Multivector3D>();
        w.description("3D Multivector in double");
        w.property(szA, &Multivector3D::a).description(szA_Multivector);
        w.property(szX, &Multivector3D::x).description(szX_Multivector);
        w.property(szY, &Multivector3D::y).description(szY_Multivector);
        w.property(szZ, &Multivector3D::z).description(szZ_Multivector);
        w.property(szXY, &Multivector3D::xy).description(szXY_Multivector);
        w.property(szYZ, &Multivector3D::yz).description(szYZ_Multivector);
        w.property(szZX, &Multivector3D::zx).description(szZX_Multivector);
        w.property(szXYZ, &Multivector3D::xyz).description(szXYZ_Multivector);
    }

    {
        auto w  = writer<Multivector3F>();
        w.description("3D Multivector in float");
        w.property(szA, &Multivector3F::a).description(szA_Multivector);
        w.property(szX, &Multivector3F::x).description(szX_Multivector);
        w.property(szY, &Multivector3F::y).description(szY_Multivector);
        w.property(szZ, &Multivector3F::z).description(szZ_Multivector);
        w.property(szXY, &Multivector3F::xy).description(szXY_Multivector);
        w.property(szYZ, &Multivector3F::yz).description(szYZ_Multivector);
        w.property(szZX, &Multivector3F::zx).description(szZX_Multivector);
        w.property(szXYZ, &Multivector3F::xyz).description(szXYZ_Multivector);
    }

    {
        auto w  = writer<Multivector4D>();
        w.description("4D Multivector in double");
        w.property(szA, &Multivector4D::a).description(szA_Multivector);
        w.property(szX, &Multivector4D::x).description(szX_Multivector);
        w.property(szY, &Multivector4D::y).description(szY_Multivector);
        w.property(szZ, &Multivector4D::z).description(szZ_Multivector);
        w.property(szW, &Multivector4D::w).description(szW_Multivector);
        w.property(szXY, &Multivector4D::xy).description(szXY_Multivector);
        w.property(szYZ, &Multivector4D::yz).description(szYZ_Multivector);
        w.property(szZW, &Multivector4D::zw).description(szZW_Multivector);
        w.property(szWX, &Multivector4D::wx).description(szWX_Multivector);
        w.property(szXZ, &Multivector4D::xz).description(szXZ_Multivector);
        w.property(szYW, &Multivector4D::yw).description(szYW_Multivector);
        w.property(szXYZ, &Multivector4D::xyz).description(szXYZ_Multivector);
        w.property(szYZW, &Multivector4D::yzw).description(szYZW_Multivector);
        w.property(szZWX, &Multivector4D::zwx).description(szZWX_Multivector);
        w.property(szWXY, &Multivector4D::wxy).description(szWXY_Multivector);
        w.property(szXYZW, &Multivector4D::xyzw).description(szXYZW_Multivector);
    }

    {
        auto w  = writer<Multivector4F>();
        w.description("4D Multivector in float");
        w.property(szA, &Multivector4F::a).description(szA_Multivector);
        w.property(szX, &Multivector4F::x).description(szX_Multivector);
        w.property(szY, &Multivector4F::y).description(szY_Multivector);
        w.property(szZ, &Multivector4F::z).description(szZ_Multivector);
        w.property(szW, &Multivector4F::w).description(szW_Multivector);
        w.property(szXY, &Multivector4F::xy).description(szXY_Multivector);
        w.property(szYZ, &Multivector4F::yz).description(szYZ_Multivector);
        w.property(szZW, &Multivector4F::zw).description(szZW_Multivector);
        w.property(szWX, &Multivector4F::wx).description(szWX_Multivector);
        w.property(szXZ, &Multivector4F::xz).description(szXZ_Multivector);
        w.property(szYW, &Multivector4F::yw).description(szYW_Multivector);
        w.property(szXYZ, &Multivector4F::xyz).description(szXYZ_Multivector);
        w.property(szYZW, &Multivector4F::yzw).description(szYZW_Multivector);
        w.property(szZWX, &Multivector4F::zwx).description(szZWX_Multivector);
        w.property(szWXY, &Multivector4F::wxy).description(szWXY_Multivector);
        w.property(szXYZW, &Multivector4F::xyzw).description(szXYZW_Multivector);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Normal

    {
        auto w = writer<Normal2D>();
        w.description("2D normal in double");
        w.property(szDirection, &Normal2D::direction).description(szDirection_Normal).alias(szDir);
    }

    {
        auto w = writer<Normal2F>();
        w.description("2D normal in float");
        w.property(szDirection, &Normal2F::direction).description(szDirection_Normal).alias(szDir);
    }

    {
        auto w = writer<Normal3D>();
        w.description("3D normal in double");
        w.property(szDirection, &Normal3D::direction).description(szDirection_Normal).alias(szDir);
    }

    {
        auto w = writer<Normal3F>();
        w.description("3D normal in float");
        w.property(szDirection, &Normal3F::direction).description(szDirection_Normal).alias(szDir);
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    {
        auto w = writer<Pose3D>();
        w.property("ori", &Pose3D::orientation);
        w.property("pos", &Pose3D::position);
    }

    {
        auto w = writer<Pose3F>();
        w.property("ori", &Pose3F::orientation);
        w.property("pos", &Pose3F::position);
    }

    {
        auto w = writer<Quadrilateral2D>();
        w.description("2D Quadrilateral in double");
        w.property(szA, &Quadrilateral2D::a).description(szA_Quadrilateral);
        w.property(szB, &Quadrilateral2D::b).description(szB_Quadrilateral);
        w.property(szC, &Quadrilateral2D::c).description(szC_Quadrilateral);
        w.property(szD, &Quadrilateral2D::d).description(szD_Quadrilateral);
    }

    {
        auto w = writer<Quadrilateral2F>();
        w.description("2D Quadrilateral in float");
        w.property(szA, &Quadrilateral2F::a).description(szA_Quadrilateral);
        w.property(szB, &Quadrilateral2F::b).description(szB_Quadrilateral);
        w.property(szC, &Quadrilateral2F::c).description(szC_Quadrilateral);
        w.property(szD, &Quadrilateral2F::d).description(szD_Quadrilateral);
    }

    {
        auto w = writer<Quadrilateral2I>();
        w.description("2D Quadrilateral in integer");
        w.property(szA, &Quadrilateral2I::a).description(szA_Quadrilateral);
        w.property(szB, &Quadrilateral2I::b).description(szB_Quadrilateral);
        w.property(szC, &Quadrilateral2I::c).description(szC_Quadrilateral);
        w.property(szD, &Quadrilateral2I::d).description(szD_Quadrilateral);
    }

    {
        auto w = writer<Quadrilateral2U>();
        w.description("2D Quadrilateral in unsigned integer");
        w.property(szA, &Quadrilateral2U::a).description(szA_Quadrilateral);
        w.property(szB, &Quadrilateral2U::b).description(szB_Quadrilateral);
        w.property(szC, &Quadrilateral2U::c).description(szC_Quadrilateral);
        w.property(szD, &Quadrilateral2U::d).description(szD_Quadrilateral);
    }

    {
        auto w = writer<Quadvector4D>();
        w.description("4D quadvector in double");
        w.property(szXYZW, &Quadvector4D::xyzw).description(szXYZW_Quadvector);
    }

    {
        auto w = writer<Quadvector4F>();
        w.description("4D quadvector in float");
        w.property(szXYZW, &Quadvector4F::xyzw).description(szXYZW_Quadvector);
    }

    {
        auto w = writer<Quaternion3D>();
        w.description("3D Quaternion in double");
        w.property(szW, &Quaternion3D::w).description(szW_Quaternion);
        w.property(szX, &Quaternion3D::x).description(szX_Quaternion);
        w.property(szY, &Quaternion3D::y).description(szY_Quaternion);
        w.property(szZ, &Quaternion3D::z).description(szZ_Quaternion);
    }

    {
        auto w = writer<Quaternion3F>();
        w.description("3D Quaternion in float");
        w.property(szW, &Quaternion3F::w).description(szW_Quaternion);
        w.property(szX, &Quaternion3F::x).description(szX_Quaternion);
        w.property(szY, &Quaternion3F::y).description(szY_Quaternion);
        w.property(szZ, &Quaternion3F::z).description(szZ_Quaternion);
    }
        
    {
        auto w  = writer<RangeD>();
        w.description("Range in double");
        w.property(szLow, &RangeD::lo).description(szLow_Range).alias({szLo, szL});
        w.property(szHigh, &RangeD::hi).description(szHigh_Range).alias({szHi, szH});
    }
    
    {
        auto w  = writer<RangeF>();
        w.description("Range in float");
        w.property(szLow, &RangeF::lo).description(szLow_Range).alias({szLo, szL});
        w.property(szHigh, &RangeF::hi).description(szHigh_Range).alias({szHi, szH});
    }

    {
        auto w  = writer<RangeI>();
        w.description("Range in integer");
        w.property(szLow, &RangeI::lo).description(szLow_Range).alias({szLo, szL});
        w.property(szHigh, &RangeI::hi).description(szHigh_Range).alias({szHi, szH});
    }

    {
        auto w  = writer<RangeU>();
        w.description("Range in unsigned integer");
        w.property(szLow, &RangeU::lo).description(szLow_Range).alias({szLo, szL});
        w.property(szHigh, &RangeU::hi).description(szHigh_Range).alias({szHi, szH});
    }

    {
        auto w = writer<Ray2D>();
        w.description("2D ray in double");
        w.property(szPoint, &Ray2D::point).description(szPoint_Ray).alias(szPt);
        w.property(szDirection, &Ray2D::direction).description(szDirection_Ray).alias(szDir);
    }

    {
        auto w = writer<Ray2F>();
        w.description("2D ray in float");
        w.property(szPoint, &Ray2F::point).description(szPoint_Ray).alias(szPt);
        w.property(szDirection, &Ray2F::direction).description(szDirection_Ray).alias(szDir);
    }

    {
        auto w = writer<Ray3D>();
        w.description("3D ray in double");
        w.property(szPoint, &Ray3D::point).description(szPoint_Ray).alias(szPt);
        w.property(szDirection, &Ray3D::direction).description(szDirection_Ray).alias(szDir);
    }

    {
        auto w = writer<Ray3F>();
        w.description("3D ray in float");
        w.property(szPoint, &Ray3F::point).description(szPoint_Ray).alias(szPt);
        w.property(szDirection, &Ray3F::direction).description(szDirection_Ray).alias(szDir);
    }

    {
        auto w = writer<Ray4D>();
        w.description("4D ray in double");
        w.property(szPoint, &Ray4D::point).description(szPoint_Ray).alias(szPt);
        w.property(szDirection, &Ray4D::direction).description(szDirection_Ray).alias(szDir);
    }

    {
        auto w = writer<Ray4F>();
        w.description("4D ray in float");
        w.property(szPoint, &Ray4F::point).description(szPoint_Ray).alias(szPt);
        w.property(szDirection, &Ray4F::direction).description(szDirection_Ray).alias(szDir);
    }

    {
        auto w   = writer<RGB3D>();
        w.description("RGB color in double");
        w.property(szRed, &RGB3D::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3D::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3D::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGB3F>();
        w.description("RGB color in float");
        w.property(szRed, &RGB3F::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3F::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3F::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGB3U8>();
        w.description("RGB color in uint8");
        w.property(szRed, &RGB3U8::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3U8::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3U8::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGB3U16>();
        w.description("RGB color in uint16");
        w.property(szRed, &RGB3U16::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGB3U16::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGB3U16::blue).description(szBlue_Color).alias(szB);
    }

    {
        auto w   = writer<RGBA4D>();
        w.description("RGBA color in double");
        w.property(szRed, &RGBA4D::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4D::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4D::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4D::alpha).description(szAlpha_Color).alias(szA);
    }

    {
        auto w   = writer<RGBA4F>();
        w.description("RGBA color in float");
        w.property(szRed, &RGBA4F::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4F::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4F::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4F::alpha).description(szAlpha_Color).alias(szA);
    }

    {
        auto w   = writer<RGBA4U8>();
        w.description("RGBA color in uint8");
        w.property(szRed, &RGBA4U8::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4U8::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4U8::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4U8::alpha).description(szAlpha_Color).alias(szA);
    }

    {
        auto w   = writer<RGBA4U16>();
        w.description("RGBA color in uint16");
        w.property(szRed, &RGBA4U16::red).description(szRed_Color).alias(szR);
        w.property(szGreen, &RGBA4U16::green).description(szGreen_Color).alias(szG);
        w.property(szBlue, &RGBA4U16::blue).description(szBlue_Color).alias(szB);
        w.property(szAlpha, &RGBA4U16::alpha).description(szAlpha_Color).alias(szA);
    }

    {
        auto w = writer<Rectangle2D>();
        w.description("2D rectangle in double");
        w.property(szPosition, &Rectangle2D::position).description(szPosition_Rectangle).alias({szPos, szCorner});
        w.property(szSize, &Rectangle2D::size).description(szSize_Rectangle);
    }

    {
        auto w = writer<Rectangle2F>();
        w.description("2D rectangle in float");
        w.property(szPosition, &Rectangle2F::position).description(szPosition_Rectangle).alias({szPos, szCorner});
        w.property(szSize, &Rectangle2F::size).description(szSize_Rectangle);
    }

    {
        auto w = writer<Rectangle2I>();
        w.description("2D rectangle in integer");
        w.property(szPosition, &Rectangle2I::position).description(szPosition_Rectangle).alias({szPos, szCorner});
        w.property(szSize, &Rectangle2I::size).description(szSize_Rectangle);
    }

    {
        auto w = writer<Rectangle2U>();
        w.description("2D rectangle in unsigned integer");
        w.property(szPosition, &Rectangle2U::position).description(szPosition_Rectangle).alias({szPos, szCorner});
        w.property(szSize, &Rectangle2U::size).description(szSize_Rectangle);
    }

    {
        auto w = writer<Segment1D>();
        w.description("1D Segment in double");
        w.property(szA, &Segment1D::a).description(szA_Segment);
        w.property(szB, &Segment1D::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment1F>();
        w.description("1D Segment in float");
        w.property(szA, &Segment1F::a).description(szA_Segment);
        w.property(szB, &Segment1F::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment1I>();
        w.description("1D Segment in integer");
        w.property(szA, &Segment1I::a).description(szA_Segment);
        w.property(szB, &Segment1I::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment1U>();
        w.description("1D Segment in unsigned integer");
        w.property(szA, &Segment1U::a).description(szA_Segment);
        w.property(szB, &Segment1U::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment2D>();
        w.description("2D Segment in double");
        w.property(szA, &Segment2D::a).description(szA_Segment);
        w.property(szB, &Segment2D::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment2F>();
        w.description("2D Segment in float");
        w.property(szA, &Segment2F::a).description(szA_Segment);
        w.property(szB, &Segment2F::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment2I>();
        w.description("2D Segment in integer");
        w.property(szA, &Segment2I::a).description(szA_Segment);
        w.property(szB, &Segment2I::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment2U>();
        w.description("2D Segment in unsigned integer");
        w.property(szA, &Segment2U::a).description(szA_Segment);
        w.property(szB, &Segment2U::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment3D>();
        w.description("3D Segment in double");
        w.property(szA, &Segment3D::a).description(szA_Segment);
        w.property(szB, &Segment3D::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment3F>();
        w.description("3D Segment in float");
        w.property(szA, &Segment3F::a).description(szA_Segment);
        w.property(szB, &Segment3F::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment3I>();
        w.description("3D Segment in integer");
        w.property(szA, &Segment3I::a).description(szA_Segment);
        w.property(szB, &Segment3I::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment3U>();
        w.description("3D Segment in unsigned integer");
        w.property(szA, &Segment3U::a).description(szA_Segment);
        w.property(szB, &Segment3U::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment4D>();
        w.description("4D Segment in double");
        w.property(szA, &Segment4D::a).description(szA_Segment);
        w.property(szB, &Segment4D::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment4F>();
        w.description("4D Segment in float");
        w.property(szA, &Segment4F::a).description(szA_Segment);
        w.property(szB, &Segment4F::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment4I>();
        w.description("4D Segment in integer");
        w.property(szA, &Segment4I::a).description(szA_Segment);
        w.property(szB, &Segment4I::b).description(szB_Segment);
    }

    {
        auto w = writer<Segment4U>();
        w.description("4D Segment in unsigned integer");
        w.property(szA, &Segment4U::a).description(szA_Segment);
        w.property(szB, &Segment4U::b).description(szB_Segment);
    }

    {
        auto w = writer<Size2D>();
        w.description("2D Size in double");
        w.property(szX, &Size2D::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2D::y).description(szY_Size).alias(szHeight);
    }

    {
        auto w = writer<Size2F>();
        w.description("2D Size in float");
        w.property(szX, &Size2F::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2F::y).description(szY_Size).alias(szHeight);
    }

    {
        auto w = writer<Size2I>();
        w.description("2D Size in integer");
        w.property(szX, &Size2I::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2I::y).description(szY_Size).alias(szHeight);
    }

    {
        auto w = writer<Size2U>();
        w.description("2D Size in unsigned integer");
        w.property(szX, &Size2U::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size2U::y).description(szY_Size).alias(szHeight);
    }

    {
        auto w = writer<Size3D>();
        w.description("3D Size in double");
        w.property(szX, &Size3D::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3D::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3D::z).description(szZ_Size).alias(szDepth);
    }

    {
        auto w = writer<Size3F>();
        w.description("3D Size in float");
        w.property(szX, &Size3F::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3F::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3F::z).description(szZ_Size).alias(szDepth);
    }

    {
        auto w = writer<Size3I>();
        w.description("3D Size in integer");
        w.property(szX, &Size3I::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3I::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3I::z).description(szZ_Size).alias(szDepth);
    }

    {
        auto w = writer<Size3U>();
        w.description("3D Size in unsigned integer");
        w.property(szX, &Size3U::x).description(szX_Size).alias(szWidth);
        w.property(szY, &Size3U::y).description(szY_Size).alias(szHeight);
        w.property(szZ, &Size3U::z).description(szZ_Size).alias(szDepth);
    }

    {
        auto w = writer<Sphere3D>();
        w.description("3D sphere in double");
        w.property(szCenter, &Sphere3D::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere3D::radius).description(szRadius_Sphere).alias({szRad, szR});
    }

    {
        auto w = writer<Sphere3F>();
        w.description("3D sphere in float");
        w.property(szCenter, &Sphere3F::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere3F::radius).description(szRadius_Sphere).alias({szRad, szR});
    }

    {
        auto w = writer<Sphere3I>();
        w.description("3D sphere in integer");
        w.property(szCenter, &Sphere3I::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere3I::radius).description(szRadius_Sphere).alias({szRad, szR});
    }

    {
        auto w = writer<Sphere3U>();
        w.description("3D sphere in unsigned integer");
        w.property(szCenter, &Sphere3U::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere3U::radius).description(szRadius_Sphere).alias({szRad, szR});
    }

    {
        auto w = writer<Sphere4D>();
        w.description("4D sphere in double");
        w.property(szCenter, &Sphere4D::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere4D::radius).description(szRadius_Sphere).alias({szRad, szR});
    }

    {
        auto w = writer<Sphere4F>();
        w.description("4D sphere in float");
        w.property(szCenter, &Sphere4F::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere4F::radius).description(szRadius_Sphere).alias({szRad, szR});
    }

    {
        auto w = writer<Sphere4I>();
        w.description("4D sphere in integer");
        w.property(szCenter, &Sphere4I::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere4I::radius).description(szRadius_Sphere).alias({szRad, szR});
    }

    {
        auto w = writer<Sphere4U>();
        w.description("4D sphere in unsigned integer");
        w.property(szCenter, &Sphere4U::center).description(szCenter_Sphere).alias({szPoint, szPt});
        w.property(szRadius, &Sphere4U::radius).description(szRadius_Sphere).alias({szRad, szR});
    }

    {
        auto w = writer<Tensor11D>();
        w.description("1x1 tensor in double");
        w.property(szXX, &Tensor11D::xx);
    }

    {
        auto w = writer<Tensor11F>();
        w.description("1x1 tensor in float");
        w.property(szXX, &Tensor11F::xx);
    }

    {
        auto w = writer<Tensor11I>();
        w.description("1x1 tensor in integer");
        w.property(szXX, &Tensor11I::xx).description(szXX_Tensor);
    }

    {
        auto w = writer<Tensor11U>();
        w.description("1x1 tensor in unsigned integer");
        w.property(szXX, &Tensor11U::xx).description(szXX_Tensor);
    }

    {
        auto w = writer<Tensor12D>();
        w.description("1x2 tensor in double");
        w.property(szXX, &Tensor12D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor12D::xy).description(szXY_Tensor);
    }

    {
        auto w = writer<Tensor12F>();
        w.description("1x2 tensor in float");
        w.property(szXX, &Tensor12F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor12F::xy).description(szXY_Tensor);
    }

    {
        auto w = writer<Tensor12I>();
        w.description("1x2 tensor in integer");
        w.property(szXX, &Tensor12I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor12I::xy).description(szXY_Tensor);
    }

    {
        auto w = writer<Tensor12U>();
        w.description("1x2 tensor in unsigned integer");
        w.property(szXX, &Tensor12U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor12U::xy).description(szXY_Tensor);
    }

    {
        auto w = writer<Tensor13D>();
        w.description("1x3 tensor in double");
        w.property(szXX, &Tensor13D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13D::xz).description(szXZ_Tensor);
    }

    {
        auto w = writer<Tensor13F>();
        w.description("1x3 tensor in float");
        w.property(szXX, &Tensor13F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13F::xz).description(szXZ_Tensor);
    }

    {
        auto w = writer<Tensor13I>();
        w.description("1x3 tensor in integer");
        w.property(szXX, &Tensor13I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13I::xz).description(szXZ_Tensor);
    }

    {
        auto w = writer<Tensor13U>();
        w.description("1x3 tensor in unsigned integer");
        w.property(szXX, &Tensor13U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor13U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor13U::xz).description(szXZ_Tensor);
    }

    {
        auto w = writer<Tensor14D>();
        w.description("1x4 tensor in double");
        w.property(szXX, &Tensor14D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor14D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor14D::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor14D::xw).description(szXW_Tensor);
    }

    {
        auto w = writer<Tensor14F>();
        w.description("1x4 tensor in float");
        w.property(szXX, &Tensor14F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor14F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor14F::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor14F::xw).description(szXW_Tensor);
    }

    {
        auto w = writer<Tensor14I>();
        w.description("1x4 tensor in integer");
        w.property(szXX, &Tensor14I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor14I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor14I::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor14I::xw).description(szXW_Tensor);
    }

    {
        auto w = writer<Tensor14U>();
        w.description("1x4 tensor in unsigned integer");
        w.property(szXX, &Tensor14U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor14U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor14U::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor14U::xw).description(szXW_Tensor);
    }

    {
        auto w = writer<Tensor21D>();
        w.description("2x1 tensor in double");
        w.property(szXX, &Tensor21D::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21D::yx).description(szYX_Tensor);
    }

    {
        auto w = writer<Tensor21F>();
        w.description("2x1 tensor in float");
        w.property(szXX, &Tensor21F::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21F::yx).description(szYX_Tensor);
    }

    {
        auto w = writer<Tensor21I>();
        w.description("2x1 tensor in integer");
        w.property(szXX, &Tensor21I::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21I::yx).description(szYX_Tensor);
    }

    {
        auto w = writer<Tensor21U>();
        w.description("2x1 tensor in unsigned integer");
        w.property(szXX, &Tensor21U::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor21U::yx).description(szYX_Tensor);
    }

    {
        auto w = writer<Tensor22D>();
        w.description("2x2 tensor in double");
        w.property(szXX, &Tensor22D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22D::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22D::yy).description(szYY_Tensor);
    }

    {
        auto w = writer<Tensor22F>();
        w.description("2x2 tensor in float");
        w.property(szXX, &Tensor22F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22F::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22F::yy).description(szYY_Tensor);
    }

    {
        auto w = writer<Tensor22I>();
        w.description("2x2 tensor in integer");
        w.property(szXX, &Tensor22I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22I::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22I::yy).description(szYY_Tensor);
    }

    {
        auto w = writer<Tensor22U>();
        w.description("2x2 tensor in unsigned integer");
        w.property(szXX, &Tensor22U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor22U::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor22U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor22U::yy).description(szYY_Tensor);
    }

    {
        auto w = writer<Tensor23D>();
        w.description("2x3 tensor in double");
        w.property(szXX, &Tensor23D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor23D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor23D::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor23D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor23D::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor23D::yz).description(szYZ_Tensor);
    }

    {
        auto w = writer<Tensor23F>();
        w.description("2x3 tensor in float");
        w.property(szXX, &Tensor23F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor23F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor23F::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor23F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor23F::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor23F::yz).description(szYZ_Tensor);
    }

    {
        auto w = writer<Tensor23I>();
        w.description("2x3 tensor in integer");
        w.property(szXX, &Tensor23I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor23I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor23I::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor23I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor23I::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor23I::yz).description(szYZ_Tensor);
    }

    {
        auto w = writer<Tensor23U>();
        w.description("2x3 tensor in unsigned integer");
        w.property(szXX, &Tensor23U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor23U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor23U::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor23U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor23U::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor23U::yz).description(szYZ_Tensor);
    }

    {
        auto w = writer<Tensor24D>();
        w.description("2x4 tensor in double");
        w.property(szXX, &Tensor24D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor24D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor24D::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor24D::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor24D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor24D::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor24D::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor24D::yw).description(szYW_Tensor);
    }

    {
        auto w = writer<Tensor24F>();
        w.description("2x4 tensor in float");
        w.property(szXX, &Tensor24F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor24F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor24F::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor24F::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor24F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor24F::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor24F::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor24F::yw).description(szYW_Tensor);
    }

    {
        auto w = writer<Tensor24I>();
        w.description("2x4 tensor in integer");
        w.property(szXX, &Tensor24I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor24I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor24I::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor24I::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor24I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor24I::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor24I::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor24I::yw).description(szYW_Tensor);
    }

    {
        auto w = writer<Tensor24U>();
        w.description("2x4 tensor in unsigned integer");
        w.property(szXX, &Tensor24U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor24U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor24U::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor24U::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor24U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor24U::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor24U::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor24U::yw).description(szYW_Tensor);
    }

    {
        auto w = writer<Tensor31D>();
        w.description("3x1 tensor in double");
        w.property(szXX, &Tensor31D::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor31D::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor31D::zx).description(szZX_Tensor);
    }

    {
        auto w = writer<Tensor31F>();
        w.description("3x1 tensor in float");
        w.property(szXX, &Tensor31F::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor31F::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor31F::zx).description(szZX_Tensor);
    }

    {
        auto w = writer<Tensor31I>();
        w.description("3x1 tensor in integer");
        w.property(szXX, &Tensor31I::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor31I::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor31I::zx).description(szZX_Tensor);
    }

    {
        auto w = writer<Tensor31U>();
        w.description("3x1 tensor in unsigned integer");
        w.property(szXX, &Tensor31U::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor31U::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor31U::zx).description(szZX_Tensor);
    }

    {
        auto w = writer<Tensor32D>();
        w.description("3x2 tensor in double");
        w.property(szXX, &Tensor32D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor32D::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor32D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor32D::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor32D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor32D::zy).description(szZY_Tensor);
    }

    {
        auto w = writer<Tensor32F>();
        w.description("3x2 tensor in float");
        w.property(szXX, &Tensor32F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor32F::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor32F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor32F::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor32F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor32F::zy).description(szZY_Tensor);
    }

    {
        auto w = writer<Tensor32I>();
        w.description("3x2 tensor in integer");
        w.property(szXX, &Tensor32I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor32I::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor32I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor32I::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor32I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor32I::zy).description(szZY_Tensor);
    }

    {
        auto w = writer<Tensor32U>();
        w.description("3x2 tensor in unsigned integer");
        w.property(szXX, &Tensor32U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor32U::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor32U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor32U::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor32U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor32U::zy).description(szZY_Tensor);
    }

    {
        auto w = writer<Tensor33D>();
        w.description("3x3 tensor in double");
        w.property(szXX, &Tensor33D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor33D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor33D::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor33D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor33D::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor33D::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor33D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor33D::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor33D::zz).description(szZZ_Tensor);
    }

    {
        auto w = writer<Tensor33F>();
        w.description("3x3 tensor in float");
        w.property(szXX, &Tensor33F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor33F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor33F::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor33F::yx).description(szYY_Tensor);
        w.property(szYY, &Tensor33F::yy).description(szYZ_Tensor);
        w.property(szYZ, &Tensor33F::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor33F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor33F::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor33F::zz).description(szZZ_Tensor);
    }

    {
        auto w = writer<Tensor33I>();
        w.description("3x3 tensor in integer");
        w.property(szXX, &Tensor33I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor33I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor33I::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor33I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor33I::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor33I::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor33I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor33I::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor33I::zz).description(szZZ_Tensor);
    }

    {
        auto w = writer<Tensor33U>();
        w.description("3x3 tensor in unsigned integer");
        w.property(szXX, &Tensor33U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor33U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor33U::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor33U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor33U::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor33U::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor33U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor33U::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor33U::zz).description(szZZ_Tensor);
    }

    {
        auto w = writer<Tensor34D>();
        w.description("3x4 tensor in double");
        w.property(szXX, &Tensor34D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor34D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor34D::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor34D::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor34D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor34D::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor34D::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor34D::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor34D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor34D::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor34D::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor34D::zw).description(szZW_Tensor);
    }

    {
        auto w = writer<Tensor34F>();
        w.description("3x4 tensor in float");
        w.property(szXX, &Tensor34F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor34F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor34F::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor34F::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor34F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor34F::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor34F::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor34F::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor34F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor34F::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor34F::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor34F::zw).description(szZW_Tensor);
    }

    {
        auto w = writer<Tensor34I>();
        w.description("3x4 tensor in integer");
        w.property(szXX, &Tensor34I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor34I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor34I::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor34I::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor34I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor34I::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor34I::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor34I::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor34I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor34I::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor34I::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor34I::zw).description(szZW_Tensor);
    }

    {
        auto w = writer<Tensor34U>();
        w.description("3x4 tensor in unsigned integer");
        w.property(szXX, &Tensor34U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor34U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor34U::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor34U::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor34U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor34U::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor34U::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor34U::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor34U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor34U::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor34U::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor34U::zw).description(szZW_Tensor);
    }

    {
        auto w = writer<Tensor41D>();
        w.description("4x1 tensor in double");
        w.property(szXX, &Tensor41D::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor41D::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor41D::zx).description(szZX_Tensor);
        w.property(szWX, &Tensor41D::wx).description(szWX_Tensor);
    }

    {
        auto w = writer<Tensor41F>();
        w.description("4x1 tensor in float");
        w.property(szXX, &Tensor41F::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor41F::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor41F::zx).description(szZX_Tensor);
        w.property(szWX, &Tensor41F::wx).description(szWX_Tensor);
    }

    {
        auto w = writer<Tensor41I>();
        w.description("4x1 tensor in integer");
        w.property(szXX, &Tensor41I::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor41I::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor41I::zx).description(szZX_Tensor);
        w.property(szWX, &Tensor41I::wx).description(szWX_Tensor);
    }

    {
        auto w = writer<Tensor41U>();
        w.description("4x1 tensor in unsigned integer");
        w.property(szXX, &Tensor41U::xx).description(szXX_Tensor);
        w.property(szYX, &Tensor41U::yx).description(szYX_Tensor);
        w.property(szZX, &Tensor41U::zx).description(szZX_Tensor);
        w.property(szWX, &Tensor41U::wx).description(szWX_Tensor);
    }

    {
        auto w = writer<Tensor42D>();
        w.description("4x2 tensor in double");
        w.property(szXX, &Tensor42D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor42D::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor42D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor42D::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor42D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor42D::zy).description(szZY_Tensor);
        w.property(szWX, &Tensor42D::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor42D::wy).description(szWY_Tensor);
    }

    {
        auto w = writer<Tensor42F>();
        w.description("4x2 tensor in float");
        w.property(szXX, &Tensor42F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor42F::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor42F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor42F::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor42F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor42F::zy).description(szZY_Tensor);
        w.property(szWX, &Tensor42F::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor42F::wy).description(szWY_Tensor);
    }

    {
        auto w = writer<Tensor42I>();
        w.description("4x2 tensor in integer");
        w.property(szXX, &Tensor42I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor42I::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor42I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor42I::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor42I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor42I::zy).description(szZY_Tensor);
        w.property(szWX, &Tensor42I::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor42I::wy).description(szWY_Tensor);
    }

    {
        auto w = writer<Tensor42U>();
        w.description("4x2 tensor in unsigned integer");
        w.property(szXX, &Tensor42U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor42U::xy).description(szXY_Tensor);
        w.property(szYX, &Tensor42U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor42U::yy).description(szYY_Tensor);
        w.property(szZX, &Tensor42U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor42U::zy).description(szZY_Tensor);
        w.property(szWX, &Tensor42U::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor42U::wy).description(szWY_Tensor);
    }

    {
        auto w = writer<Tensor43D>();
        w.description("4x3 tensor in double");
        w.property(szXX, &Tensor43D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor43D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor43D::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor43D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor43D::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor43D::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor43D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor43D::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor43D::zz).description(szZZ_Tensor);
        w.property(szWX, &Tensor43D::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor43D::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor43D::wz).description(szWZ_Tensor);
    }

    {
        auto w = writer<Tensor43F>();
        w.description("4x3 tensor in float");
        w.property(szXX, &Tensor43F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor43F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor43F::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor43F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor43F::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor43F::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor43F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor43F::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor43F::zz).description(szZZ_Tensor);
        w.property(szWX, &Tensor43F::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor43F::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor43F::wz).description(szWZ_Tensor);
    }

    {
        auto w = writer<Tensor43I>();
        w.description("4x3 tensor in integer");
        w.property(szXX, &Tensor43I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor43I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor43I::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor43I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor43I::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor43I::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor43I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor43I::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor43I::zz).description(szZZ_Tensor);
        w.property(szWX, &Tensor43I::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor43I::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor43I::wz).description(szWZ_Tensor);
    }

    {
        auto w = writer<Tensor43U>();
        w.description("4x3 tensor in unsigned integer");
        w.property(szXX, &Tensor43U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor43U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor43U::xz).description(szXZ_Tensor);
        w.property(szYX, &Tensor43U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor43U::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor43U::yz).description(szYZ_Tensor);
        w.property(szZX, &Tensor43U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor43U::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor43U::zz).description(szZZ_Tensor);
        w.property(szWX, &Tensor43U::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor43U::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor43U::wz).description(szWZ_Tensor);
    }

    {
        auto w = writer<Tensor44D>();
        w.description("4x4 tensor in double");
        w.property(szXX, &Tensor44D::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor44D::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor44D::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor44D::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor44D::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor44D::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor44D::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor44D::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor44D::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor44D::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor44D::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor44D::zw).description(szZW_Tensor);
        w.property(szWX, &Tensor44D::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor44D::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor44D::wz).description(szWZ_Tensor);
        w.property(szWW, &Tensor44D::ww).description(szWW_Tensor);
    }

    {
        auto w = writer<Tensor44F>();
        w.description("4x4 tensor in float");
        w.property(szXX, &Tensor44F::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor44F::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor44F::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor44F::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor44F::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor44F::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor44F::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor44F::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor44F::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor44F::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor44F::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor44F::zw).description(szZW_Tensor);
        w.property(szWX, &Tensor44F::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor44F::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor44F::wz).description(szWZ_Tensor);
        w.property(szWW, &Tensor44F::ww).description(szWW_Tensor);
    }

    {
        auto w = writer<Tensor44I>();
        w.description("4x4 tensor in integer");
        w.property(szXX, &Tensor44I::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor44I::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor44I::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor44I::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor44I::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor44I::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor44I::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor44I::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor44I::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor44I::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor44I::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor44I::zw).description(szZW_Tensor);
        w.property(szWX, &Tensor44I::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor44I::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor44I::wz).description(szWZ_Tensor);
        w.property(szWW, &Tensor44I::ww).description(szWW_Tensor);
    }

    {
        auto w = writer<Tensor44U>();
        w.description("4x4 tensor in unsigned integer");
        w.property(szXX, &Tensor44U::xx).description(szXX_Tensor);
        w.property(szXY, &Tensor44U::xy).description(szXY_Tensor);
        w.property(szXZ, &Tensor44U::xz).description(szXZ_Tensor);
        w.property(szXW, &Tensor44U::xw).description(szXW_Tensor);
        w.property(szYX, &Tensor44U::yx).description(szYX_Tensor);
        w.property(szYY, &Tensor44U::yy).description(szYY_Tensor);
        w.property(szYZ, &Tensor44U::yz).description(szYZ_Tensor);
        w.property(szYW, &Tensor44U::yw).description(szYW_Tensor);
        w.property(szZX, &Tensor44U::zx).description(szZX_Tensor);
        w.property(szZY, &Tensor44U::zy).description(szZY_Tensor);
        w.property(szZZ, &Tensor44U::zz).description(szZZ_Tensor);
        w.property(szZW, &Tensor44U::zw).description(szZW_Tensor);
        w.property(szWX, &Tensor44U::wx).description(szWX_Tensor);
        w.property(szWY, &Tensor44U::wy).description(szWY_Tensor);
        w.property(szWZ, &Tensor44U::wz).description(szWZ_Tensor);
        w.property(szWW, &Tensor44U::ww).description(szWW_Tensor);
    }

    {
        auto w = writer<Tetrahedron3D>();
        w.description("3D Tetrahedron in double");
        w.property(szA, &Tetrahedron3D::a).description(szA_Tetrahedron);
        w.property(szB, &Tetrahedron3D::b).description(szB_Tetrahedron);
        w.property(szC, &Tetrahedron3D::c).description(szC_Tetrahedron);
        w.property(szD, &Tetrahedron3D::d).description(szD_Tetrahedron);
    }

    {
        auto w = writer<Tetrahedron3F>();
        w.description("3D Tetrahedron in float");
        w.property(szA, &Tetrahedron3F::a).description(szA_Tetrahedron);
        w.property(szB, &Tetrahedron3F::b).description(szB_Tetrahedron);
        w.property(szC, &Tetrahedron3F::c).description(szC_Tetrahedron);
        w.property(szD, &Tetrahedron3F::d).description(szD_Tetrahedron);
    }

    {
        auto w = writer<Tetrahedron3I>();
        w.description("3D Tetrahedron in integer");
        w.property(szA, &Tetrahedron3I::a).description(szA_Tetrahedron);
        w.property(szB, &Tetrahedron3I::b).description(szB_Tetrahedron);
        w.property(szC, &Tetrahedron3I::c).description(szC_Tetrahedron);
        w.property(szD, &Tetrahedron3I::d).description(szD_Tetrahedron);
    }
    
    {
        auto w = writer<Tetrahedron3U>();
        w.description("3D Tetrahedron in unsigned integer");
        w.property(szA, &Tetrahedron3U::a).description(szA_Tetrahedron);
        w.property(szB, &Tetrahedron3U::b).description(szB_Tetrahedron);
        w.property(szC, &Tetrahedron3U::c).description(szC_Tetrahedron);
        w.property(szD, &Tetrahedron3U::d).description(szD_Tetrahedron);
    }

    {
        auto w = writer<Triangle2D>();
        w.description("2D Triangle in double");
        w.property(szA, &Triangle2D::a).description(szA_Triangle);
        w.property(szB, &Triangle2D::b).description(szB_Triangle);
        w.property(szC, &Triangle2D::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle2F>();
        w.description("2D Triangle in float");
        w.property(szA, &Triangle2F::a).description(szA_Triangle);
        w.property(szB, &Triangle2F::b).description(szB_Triangle);
        w.property(szC, &Triangle2F::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle2I>();
        w.description("2D Triangle in integer");
        w.property(szA, &Triangle2I::a).description(szA_Triangle);
        w.property(szB, &Triangle2I::b).description(szB_Triangle);
        w.property(szC, &Triangle2I::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle2U>();
        w.description("2D Triangle in unsigned integer");
        w.property(szA, &Triangle2U::a).description(szA_Triangle);
        w.property(szB, &Triangle2U::b).description(szB_Triangle);
        w.property(szC, &Triangle2U::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle3D>();
        w.description("3D Triangle in double");
        w.property(szA, &Triangle3D::a).description(szA_Triangle);
        w.property(szB, &Triangle3D::b).description(szB_Triangle);
        w.property(szC, &Triangle3D::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle3F>();
        w.description("3D Triangle in float");
        w.property(szA, &Triangle3F::a).description(szA_Triangle);
        w.property(szB, &Triangle3F::b).description(szB_Triangle);
        w.property(szC, &Triangle3F::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle3I>();
        w.description("3D Triangle in integer");
        w.property(szA, &Triangle3I::a).description(szA_Triangle);
        w.property(szB, &Triangle3I::b).description(szB_Triangle);
        w.property(szC, &Triangle3I::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle3U>();
        w.description("3D Triangle in unsigned double");
        w.property(szA, &Triangle3U::a).description(szA_Triangle);
        w.property(szB, &Triangle3U::b).description(szB_Triangle);
        w.property(szC, &Triangle3U::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle4D>();
        w.description("4D Triangle in double");
        w.property(szA, &Triangle4D::a).description(szA_Triangle);
        w.property(szB, &Triangle4D::b).description(szB_Triangle);
        w.property(szC, &Triangle4D::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle4F>();
        w.description("4D Triangle in float");
        w.property(szA, &Triangle4F::a).description(szA_Triangle);
        w.property(szB, &Triangle4F::b).description(szB_Triangle);
        w.property(szC, &Triangle4F::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle4I>();
        w.description("4D Triangle in integer");
        w.property(szA, &Triangle4I::a).description(szA_Triangle);
        w.property(szB, &Triangle4I::b).description(szB_Triangle);
        w.property(szC, &Triangle4I::c).description(szC_Triangle);
    }

    {
        auto w = writer<Triangle4U>();
        w.description("4D Triangle in unsigned integer");
        w.property(szA, &Triangle4U::a).description(szA_Triangle);
        w.property(szB, &Triangle4U::b).description(szB_Triangle);
        w.property(szC, &Triangle4U::c).description(szC_Triangle);
    }

    {
        auto w = writer<Trivector3D>();
        w.description("3D trivector in double");
        w.property(szXYZ, &Trivector3D::xyz).description(szXYZ_Trivector);
    }

    {
        auto w = writer<Trivector3F>();
        w.description("3D trivector in float");
        w.property(szXYZ, &Trivector3F::xyz).description(szXYZ_Trivector);
    }

    {
        auto w = writer<Trivector4D>();
        w.description("4D trivector in double");
        w.property(szXYZ, &Trivector4D::xyz).description(szXYZ_Trivector);
        w.property(szYZW, &Trivector4D::yzw).description(szYZW_Trivector);
        w.property(szZWX, &Trivector4D::zwx).description(szZWX_Trivector);
        w.property(szWXY, &Trivector4D::wxy).description(szWXY_Trivector);
    }

    {
        auto w = writer<Trivector4F>();
        w.description("4D trivector in float");
        w.property(szXYZ, &Trivector4F::xyz).description(szXYZ_Trivector);
        w.property(szYZW, &Trivector4F::yzw).description(szYZW_Trivector);
        w.property(szZWX, &Trivector4F::zwx).description(szZWX_Trivector);
        w.property(szWXY, &Trivector4F::wxy).description(szWXY_Trivector);
    }

    {
        auto w = writer<Vector1D>();
        w.description("1D vector in double");
        w.property(szLength, &Vector1D::length).description(szLength_Vector).alias(szLen);
        w.property(szLength², &Vector1D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1D::x).description(szX_Vector);
    }

    {
        auto w = writer<Vector1F>();
        w.description("1D vector in float");
        w.property(szLength, &Vector1F::length).description(szLength_Vector).alias(szLen);
        w.property(szLength², &Vector1F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1F::x).description(szX_Vector);
    }

    {
        auto w = writer<Vector1I>();
        w.description("1D vector in integer");
        w.property(szLength², &Vector1I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1I::x).description(szX_Vector);
    }

    {
        auto w = writer<Vector1U>();
        w.description("1D vector in unsigned integer");
        w.property(szLength², &Vector1U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1U::x).description(szX_Vector);
    }

    {
        auto w = writer<Vector2D>();
        w.description("2D vector in double");
        w.property(szLength², &Vector2D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector2D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector2D::x).description(szX_Vector);
        w.property(szY, &Vector2D::y).description(szY_Vector);
        w.method(szZ, &Vector2D::z).description(szZ_Vector2);
    }

    {
        auto w = writer<Vector2F>();
        w.description("2D vector in float");
        w.property(szLength², &Vector2F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector2F::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector2F::x).description(szX_Vector);
        w.property(szY, &Vector2F::y).description(szY_Vector);
        w.method(szZ, &Vector2F::z).description(szZ_Vector2);
    }

    {
        auto w = writer<Vector2I>();
        w.description("2D vector in integer");
        w.property(szLength², &Vector2I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector2I::x).description(szX_Vector);
        w.property(szY, &Vector2I::y).description(szY_Vector);
        w.method(szZ, &Vector2I::z).description(szZ_Vector2);
    }

    {
        auto w = writer<Vector2U>();
        w.description("2D vector in unsigned integer");
        w.property(szLength², &Vector2U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector2U::x).description(szX_Vector);
        w.property(szY, &Vector2U::y).description(szY_Vector);
        w.method(szZ, &Vector2U::z).description(szZ_Vector2);
    }

    {
        auto w = writer<Vector3D>();
        w.description("3D vector in double");
        w.property(szLength², &Vector3D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector3D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector3D::x).description(szX_Vector);
        w.property(szY, &Vector3D::y).description(szY_Vector);
        w.property(szZ, &Vector3D::z).description(szZ_Vector);
    }

    {
        auto w = writer<Vector3F>();
        w.description("3D vector in float");
        w.property(szLength², &Vector3F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector3F::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector3F::x).description(szX_Vector);
        w.property(szY, &Vector3F::y).description(szY_Vector);
        w.property(szZ, &Vector3F::z).description(szZ_Vector);
    }

    {
        auto w = writer<Vector3I>();
        w.description("3D vector in integer");
        w.property(szLength², &Vector3I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector3I::x).description(szX_Vector);
        w.property(szY, &Vector3I::y).description(szY_Vector);
        w.property(szZ, &Vector3I::z).description(szZ_Vector);
    }

    {
        auto w = writer<Vector3U>();
        w.description("3D vector in unsigned integer");
        w.property(szLength², &Vector3U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector3U::x).description(szX_Vector);
        w.property(szY, &Vector3U::y).description(szY_Vector);
        w.property(szZ, &Vector3U::z).description(szZ_Vector);
    }

    {
        auto w = writer<Vector4D>();
        w.description("4D vector in double");
        w.property(szLength², &Vector4D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector4D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector4D::x).description(szX_Vector);
        w.property(szY, &Vector4D::y).description(szY_Vector);
        w.property(szZ, &Vector4D::z).description(szZ_Vector);
        w.property(szW, &Vector4D::w).description(szW_Vector);
    }

    {
        auto w = writer<Vector4F>();
        w.description("4D vector in float");
        w.property(szLength², &Vector4F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector4F::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector4F::x).description(szX_Vector);
        w.property(szY, &Vector4F::y).description(szY_Vector);
        w.property(szZ, &Vector4F::z).description(szZ_Vector);
        w.property(szW, &Vector4F::w).description(szW_Vector);
    }

    {
        auto w = writer<Vector4I>();
        w.description("4D vector in integer");
        w.property(szLength², &Vector4I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector4I::x).description(szX_Vector);
        w.property(szY, &Vector4I::y).description(szY_Vector);
        w.property(szZ, &Vector4I::z).description(szZ_Vector);
        w.property(szW, &Vector4I::w).description(szW_Vector);
    }

    {
        auto w = writer<Vector4U>();
        w.description("4D vector in unsigned integer");
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

