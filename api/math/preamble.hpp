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
#include <math/trait/has_half.hpp>
#include <math/trait/has_identity.hpp>
#include <math/trait/has_is_finite.hpp>
#include <math/trait/has_nan.hpp>
#include <math/trait/has_one.hpp>
#include <math/trait/has_sqrt.hpp>
#include <math/trait/has_zero.hpp>
#include <math/trait/ieee754.hpp>
#include <math/trait/is_arithmetic.hpp>
#include <math/trait/is_floating_point.hpp>

#include <math/dims.hpp>
#include <math/keywords.hpp>
#include <math/units_declare.hpp>

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
    requires trait::is_floating_point_v<T>
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
    template <typename> struct Polygon2;
    template <typename> struct Polygon3;
    template <typename> struct Polygon4;
    //template <typename> struct Pose2;
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
        
        template <typename T> static constexpr const bool is_basic_v = std::is_floating_point_v<T>;
    }
    
    //! Fast way to what something's sign is
    enum class Sign : signed {
        NEG        = -1,
        ZERO       =  0,
        POS        =  1
    };
    
    //! Denote sides of shapes, planes, etc
    enum class Side : unsigned {
    
        // Mind-boggling how this gets defined...we're undoing that!
        #ifdef ERROR
        #undef ERROR
        #endif
        
        //! Error detected
        ERROR       = 1 << 0,
        
        //! Below the threshhold
        BELOW       = 1 << 1,
        
        //! Inside the threshhold (or center)
        MIDDLE      = 1 << 2,
        
        ABOVE       = 1 << 3,
        
        XNEG        = 1 << 4,
        YNEG        = 1 << 5,
        ZNEG        = 1 << 6,
        WNEG        = 1 << 7,

        XMID        = 1 << 8,
        YMID        = 1 << 9,
        ZMID        = 1 << 10,
        WMID        = 1 << 11,

        XPOS        = 1 << 12,
        YPOS        = 1 << 13,
        ZPOS        = 1 << 14,
        WPOS        = 1 << 15,
        
        COPLANAR    = 1 << 16,
        
        CENTER      = MIDDLE,
        INSIDE      = BELOW,
        TOUCH       = MIDDLE,
        OUTSIDE     = ABOVE,

        EAST        = XPOS,
        WEST        = XNEG,
        NORTH       = YPOS,
        SOUTH       = YNEG,
        TOP         = ZPOS,
        BOTTOM      = ZNEG
        
    };
    
    /*! \brief Mid-way divide two numbers
    */
    template <typename T>
    constexpr T     middivide(T a, T b=T{}) noexcept
    {
        if constexpr (has_ieee754_v<T>)
            return ieee754_t<T>(0.5)*(a+b);
        else if constexpr (std::is_integral_v<T>)
            return (a+b) / T(2);
        else
            return {};
    }
}

