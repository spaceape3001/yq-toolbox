////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/preamble.hpp>
#include <yq/basic/CoordFwd.hpp>
#include <0/io/StreamOps.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <yq/trait/always_false.hpp>

#include <yq/trait/has_abs.hpp>
#include <yq/trait/has_copysign.hpp>
#include <yq/trait/has_half.hpp>
#include <yq/trait/has_identity.hpp>
#include <yq/trait/has_is_finite.hpp>
#include <yq/trait/has_nan.hpp>
#include <yq/trait/has_one.hpp>
#include <yq/trait/has_sqrt.hpp>
#include <yq/trait/has_zero.hpp>
#include <yq/trait/ieee754.hpp>
#include <yq/trait/integer.hpp>
#include <yq/trait/is_arithmetic.hpp>
#include <yq/trait/is_floating_point.hpp>
#include <yq/trait/is_integral.hpp>

#include <yq/math/unit/dims.hpp>
#include <yq/math/unit/declare.hpp>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <numbers>
#include <utility>

    /*
        GLM can be a heavy-weight library, so make it OPTIONAL, enabled via 
        cmake configuration *OR* by a consumer that needs it.  Note, if 
        it's being used, make sure the GLM library's include path is part
        of your target's include directories.
    */
#ifndef YQ_USE_GLM
    #ifdef YQ_FEATURE_GLM
        #define YQ_USE_GLM 1
    #endif
#endif

#ifdef YQ_USE_GLM
    #include <glm/glm.hpp>
#endif

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
#define DOT         ||

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
    
        //  Some types/constants to work the constructors in magical ways :)
    
    
    template <typename> struct PolygonData;
    template <typename> struct PolylineData;
    template <typename> struct QuadrilateralData;
    template <typename> struct SegmentData;
    template <typename> struct TetrahedronData;
    template <typename> struct TriangleData;

    template <typename> struct Absolute;
    template <typename> struct AllComponents;
    template <typename> struct AnyComponents;
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
    template <typename> struct Data1;
    template <typename> struct Data2;
    template <typename> struct Data3;
    template <typename> struct Data4;
    template <typename> struct ElemComponents;
    template <typename> struct Fraction;
    template <typename> struct HSL;
    template <typename> struct HSV;
    template <typename> struct Multivector1;
    template <typename> struct Multivector2;
    template <typename> struct Multivector3;
    template <typename> struct Multivector4;
    template <typename> struct Normal2;
    template <typename> struct Normal3;
    template <typename> struct Plane3;
    template <typename> struct Polygon2;
    template <typename> struct Polygon3;
    template <typename> struct Polygon4;
    template <typename> struct Polyline2;
    template <typename> struct Polyline3;
    template <typename> struct Polyline4;
    template <typename> struct Pose2;
    template <typename> struct Pose3;
    template <typename> struct Quadvector4;
    template <typename> struct Quaternion3;
    template <typename> struct Quadrilateral2;
    template <typename> struct Range;
    template <typename> struct Ray2;
    template <typename> struct Ray3;
    template <typename> struct Ray4;
    template <typename> struct Rectangle2;
    template <typename> struct RGB;
    template <typename> struct RGBA;
    template <typename> struct Segment1;
    template <typename> struct Segment2;
    template <typename> struct Segment3;
    template <typename> struct Segment4;
    template <typename> struct Size1;
    template <typename> struct Size2;
    template <typename> struct Size3;
    template <typename> struct Size4;
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
    template <typename> struct Tetrahedron3;
    template <typename> struct Triangle2;
    template <typename> struct Triangle3;
    template <typename> struct Triangle4;
    template <typename> struct Trivector3;
    template <typename> struct Trivector4;
    template <typename> struct UV;
    template <typename> struct UVW;
    template <typename> struct Vector1;
    template <typename> struct Vector2;
    template <typename> struct Vector3;
    template <typename> struct Vector4;

    //  ------------------------------------------------
    //  COMPLEX NUMBERS


    using ComplexD                  = std::complex<double>;
    using ComplexF                  = std::complex<float>;
    using ComplexI                  = std::complex<int>;
    using ComplexU                  = std::complex<unsigned>;

    
    //  ------------------------------------------------
    //  Coordinates
    

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
    using Vector2M                  = Vector2<Meter>;
    using Vector2U                  = Vector2<unsigned>;

    using Vector3D                  = Vector3<double>;
    using Vector3F                  = Vector3<float>;
    using Vector3I                  = Vector3<int>;
    using Vector3M                  = Vector3<Meter>;
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
    using AxBox2M                   = AxBox2<Meter>;

    using AxBox3D                   = AxBox3<double>;
    using AxBox3F                   = AxBox3<float>;
    using AxBox3I                   = AxBox3<int>;
    using AxBox3U                   = AxBox3<unsigned>;
    using AxBox3M                   = AxBox3<Meter>;

    using AxBox4D                   = AxBox4<double>;
    using AxBox4F                   = AxBox4<float>;
    using AxBox4I                   = AxBox4<int>;
    using AxBox4U                   = AxBox4<unsigned>;

    using Circle2D                  = Circle2<double>;
    using Circle2F                  = Circle2<float>;
    using Circle2I                  = Circle2<int>;
    using Circle2U                  = Circle2<unsigned>;

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
    using Polygon2I                 = Polygon2<int>;
    using Polygon2U                 = Polygon2<unsigned>;

    using Polygon3D                 = Polygon3<double>;
    using Polygon3F                 = Polygon3<float>;
    using Polygon3I                 = Polygon3<int>;
    using Polygon3U                 = Polygon3<unsigned>;
    
    using Polygon4D                 = Polygon4<double>;
    using Polygon4F                 = Polygon4<float>;
    using Polygon4I                 = Polygon4<int>;
    using Polygon4U                 = Polygon4<unsigned>;

    using Polyline2D                = Polyline2<double>;
    using Polyline2F                = Polyline2<float>;
    using Polyline2I                = Polyline2<int>;
    using Polyline2U                = Polyline2<unsigned>;

    using Polyline3D                = Polyline3<double>;
    using Polyline3F                = Polyline3<float>;
    using Polyline3I                = Polyline3<int>;
    using Polyline3U                = Polyline3<unsigned>;
    
    using Polyline4D                = Polyline4<double>;
    using Polyline4F                = Polyline4<float>;
    using Polyline4I                = Polyline4<int>;
    using Polyline4U                = Polyline4<unsigned>;

    using Quadrilateral2D           = Quadrilateral2<double>;
    using Quadrilateral2F           = Quadrilateral2<float>;
    using Quadrilateral2I           = Quadrilateral2<int>;
    using Quadrilateral2U           = Quadrilateral2<unsigned>;
    
    using RangeD                    = Range<double>;
    using RangeF                    = Range<float>;
    using RangeI                    = Range<int>;
    using RangeU                    = Range<unsigned>;
    
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
    
    using Size1D                    = Size1<double>;
    using Size1F                    = Size1<float>;
    using Size1I                    = Size1<int>;
    using Size1I8                   = Size1<int8_t>;
    using Size1I16                  = Size1<int16_t>;
    using Size1I32                  = Size1<int32_t>;
    using Size1I64                  = Size1<int64_t>;
    using Size1U                    = Size1<unsigned>;
    using Size1U8                   = Size1<int8_t>;
    using Size1U16                  = Size1<int16_t>;
    using Size1U32                  = Size1<int32_t>;
    using Size1U64                  = Size1<int64_t>;
    using Size1Z                    = Size1<size_t>;

    using Size2D                    = Size2<double>;
    using Size2F                    = Size2<float>;
    using Size2I                    = Size2<int>;
    using Size2I8                   = Size2<int8_t>;
    using Size2I16                  = Size2<int16_t>;
    using Size2I32                  = Size2<int32_t>;
    using Size2I64                  = Size2<int64_t>;
    using Size2M                    = Size2<Meter>;
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
    using Size3M                    = Size3<Meter>;
    using Size3U                    = Size3<unsigned>;
    using Size3U8                   = Size3<int8_t>;
    using Size3U16                  = Size3<int16_t>;
    using Size3U33                  = Size3<int32_t>;
    using Size3U64                  = Size3<int64_t>;
    using Size3Z                    = Size3<size_t>;

    using Size4D                    = Size4<double>;
    using Size4F                    = Size4<float>;
    using Size4I                    = Size4<int>;
    using Size4I8                   = Size4<int8_t>;
    using Size4I16                  = Size4<int16_t>;
    using Size4I32                  = Size4<int32_t>;
    using Size4I64                  = Size4<int64_t>;
    using Size4U                    = Size4<unsigned>;
    using Size4U8                   = Size4<int8_t>;
    using Size4U16                  = Size4<int16_t>;
    using Size4U32                  = Size4<int32_t>;
    using Size4U64                  = Size4<int64_t>;
    using Size4Z                    = Size4<size_t>;

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

    using HSL3D                     = HSL<double>;
    using HSL3F                     = HSL<float>;
    using HSL3I                     = HSL<int>;
    using HSL3U                     = HSL<unsigned>;
    using HSL3U8                    = HSL<uint8_t>;
    using HSL3U16                   = HSL<uint16_t>;

    using HSV3D                     = HSV<double>;
    using HSV3F                     = HSV<float>;
    using HSV3I                     = HSV<int>;
    using HSV3U                     = HSV<unsigned>;
    using HSV3U8                    = HSV<uint8_t>;
    using HSV3U16                   = HSV<uint16_t>;

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
    
    class UserExpr;
    
    template <typename T, T> struct Counter;
    
    //!  Standard "zero-point" counter
    template <typename T>
    using Count     = Counter<T,T(0)>;

    //!  Counter that resets to numeric-maximum
    template <typename T>
    using HCount    = Counter<T,std::numeric_limits<T>::max()>;

    //!  Counter that resets to numeric-minimum
    template <typename T>
    using LCount    = Counter<T,std::numeric_limits<T>::min()>;
    
    using CountI    = Count<int>;
    using CountI8   = Count<int8_t>;
    using CountI16  = Count<int16_t>;
    using CountI32  = Count<int32_t>;
    using CountI64  = Count<int64_t>;

    using CountU    = Count<unsigned int>;
    using CountU8   = Count<uint8_t>;
    using CountU16  = Count<uint16_t>;
    using CountU32  = Count<uint32_t>;
    using CountU64  = Count<uint64_t>;

    using CountZ    = Count<size_t>;

    using HCountI   = HCount<int>;
    using HCountI8  = HCount<int8_t>;
    using HCountI16 = HCount<int16_t>;
    using HCountI32 = HCount<int32_t>;
    using HCountI64 = HCount<int64_t>;

    using HCountU   = HCount<unsigned int>;
    using HCountU8  = HCount<uint8_t>;
    using HCountU16 = HCount<uint16_t>;
    using HCountU32 = HCount<uint32_t>;
    using HCountU64 = HCount<uint64_t>;

    using HCountZ   = HCount<size_t>;

    using LCountI   = LCount<int>;
    using LCountI8  = LCount<int8_t>;
    using LCountI16 = LCount<int16_t>;
    using LCountI32 = LCount<int32_t>;
    using LCountI64 = LCount<int64_t>;

    using LCountU   = LCount<unsigned int>;
    using LCountU8  = LCount<uint8_t>;
    using LCountU16 = LCount<uint16_t>;
    using LCountU32 = LCount<uint32_t>;
    using LCountU64 = LCount<uint64_t>;

    using LCountZ   = LCount<size_t>;

    using Pose2D        = Pose2<double>;
    using Pose2F        = Pose2<float>;

    using Pose3D        = Pose3<double>;
    using Pose3F        = Pose3<float>;

    //! Call this if math isn't getting startup-initialized 
    void        initialize_math();

    template <typename T> using unity_t = decltype(T()/T());
    template <typename T> using square_t = decltype(T()*T());
    template <typename T> using cube_t   = decltype(T()*T()*T());
    template <typename T> using fourth_t = decltype(T()*T()*T()*T());
    template <typename T> using inverse_t = decltype(T()/square_t<T>());
    template <typename T, typename U>  static constexpr const bool self_mul_v = std::is_same_v<T,product_t<T,U>>;
    template <typename T, typename U>  static constexpr const bool self_div_v = std::is_same_v<T,quotient_t<T,U>>;
    
    using std::max;
    using std::min;
    using std::abs;
    
    
    template <typename T> static constexpr const bool is_basic_v = std::is_floating_point_v<T>;
    
    //! Fast way to what something's sign is
    enum class Sign : signed {
        NEG        = -1,
        ZERO       =  0,
        POS        =  1
    };
    
    struct Side;
}

#ifdef NAN
    // Get RID of the old C macro!
    #undef NAN
#endif


