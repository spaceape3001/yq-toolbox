////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <0/math/preamble.hpp>
#include <yq/strings.hpp>


#include <0/math/vector/Bivector2.hpp>
#include <0/math/vector/Bivector3.hpp>
#include <0/math/vector/Bivector4.hpp>

#include <0/math/vector/Multivector1.hpp>
#include <0/math/vector/Multivector2.hpp>
#include <0/math/vector/Multivector3.hpp>
#include <0/math/vector/Multivector4.hpp>

#include <0/math/vector/Quadvector4.hpp>
#include <0/math/vector/Quaternion3.hpp>

#include <0/math/vector/Trivector3.hpp>
#include <0/math/vector/Trivector4.hpp>

#include <0/math/vector/Vector1.hpp>
#include <0/math/vector/Vector2.hpp>
#include <0/math/vector/Vector3.hpp>
#include <0/math/vector/Vector4.hpp>

#include <yq/basic/DelayInit.hpp>
#include <yq/io/StreamOps.hpp>
#include <yq/meta/Init.hpp>

#include <yq/unit/literals.hpp>

using namespace yq;

YQ_TYPE_IMPLEMENT(yq::Bivector2D)
YQ_TYPE_IMPLEMENT(yq::Bivector2F)

YQ_TYPE_IMPLEMENT(yq::Bivector3D)
YQ_TYPE_IMPLEMENT(yq::Bivector3F)

YQ_TYPE_IMPLEMENT(yq::Bivector4D)
YQ_TYPE_IMPLEMENT(yq::Bivector4F)

YQ_TYPE_IMPLEMENT(yq::Multivector1D)
YQ_TYPE_IMPLEMENT(yq::Multivector1F)

YQ_TYPE_IMPLEMENT(yq::Multivector2D)
YQ_TYPE_IMPLEMENT(yq::Multivector2F)

YQ_TYPE_IMPLEMENT(yq::Multivector3D)
YQ_TYPE_IMPLEMENT(yq::Multivector3F)

YQ_TYPE_IMPLEMENT(yq::Multivector4D)
YQ_TYPE_IMPLEMENT(yq::Multivector4F)

YQ_TYPE_IMPLEMENT(yq::Quadvector4D)
YQ_TYPE_IMPLEMENT(yq::Quadvector4F)

YQ_TYPE_IMPLEMENT(yq::Quaternion3D)
YQ_TYPE_IMPLEMENT(yq::Quaternion3F)


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



//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//  OTHER HELPERS FOR MATH

namespace {
    template <typename T>
    void    print_quaternion3(Stream& str, const Quaternion3<T>& v)
    {
        str << "(" << v.w << "," << v.x << "," << v.y << "," << v.z << ")";
    }

    template <typename T>
    void    print_vector1(Stream& str, const Vector1<T>& v)
    {
        str << "(" << v.x << ")";
    }

    template <typename T>
    void    print_vector2(Stream& str, const Vector2<T>& v)
    {
        str << "(" << v.x << "," << v.y << ")";
    }

    template <typename T>
    void    print_vector3(Stream& str, const Vector3<T>& v)
    {
        str << "(" << v.x << "," << v.y << "," << v.z << ")";
    }

    template <typename T>
    void    print_vector4(Stream& str, const Vector4<T>& v)
    {
        str << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
    }
}
    
//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

static void reg_vector_math () {

    // General order ... all alphabetical
    //
    //      1. properties
    //      2. methods
    //
    
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
    //  Quadvector
    
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

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Quaternion

    {
        auto w = writer<Quaternion3D>();
        w.description("3D Quaternion in double");
        w.property(szW, &Quaternion3D::w).description(szW_Quaternion);
        w.property(szX, &Quaternion3D::x).description(szX_Quaternion);
        w.property(szY, &Quaternion3D::y).description(szY_Quaternion);
        w.property(szZ, &Quaternion3D::z).description(szZ_Quaternion);
        w.print<print_quaternion3<double>>();
    }

    {
        auto w = writer<Quaternion3F>();
        w.description("3D Quaternion in float");
        w.property(szW, &Quaternion3F::w).description(szW_Quaternion);
        w.property(szX, &Quaternion3F::x).description(szX_Quaternion);
        w.property(szY, &Quaternion3F::y).description(szY_Quaternion);
        w.property(szZ, &Quaternion3F::z).description(szZ_Quaternion);
        w.print<print_quaternion3<float>>();
    }

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Trivector

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

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  Vector

    {
        auto w = writer<Vector1D>();
        w.description("1D vector in double");
        w.property(szLength, &Vector1D::length).description(szLength_Vector).alias(szLen);
        w.property(szLength², &Vector1D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1D::x).description(szX_Vector);
        w.operate_self({ Operator::Add, Operator::Subtract });
        w.operate_with<double>();
        w.print<print_vector1<double>>();
    }

    {
        auto w = writer<Vector1F>();
        w.description("1D vector in float");
        w.property(szLength, &Vector1F::length).description(szLength_Vector).alias(szLen);
        w.property(szLength², &Vector1F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1F::x).description(szX_Vector);
        w.print<print_vector1<float>>();
    }

    {
        auto w = writer<Vector1I>();
        w.description("1D vector in integer");
        w.property(szLength², &Vector1I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1I::x).description(szX_Vector);
        w.print<print_vector1<int>>();
    }

    {
        auto w = writer<Vector1U>();
        w.description("1D vector in unsigned integer");
        w.property(szLength², &Vector1U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector1U::x).description(szX_Vector);
        w.print<print_vector1<unsigned>>();
    }

    {
        auto w = writer<Vector2D>();
        w.description("2D vector in double");
        w.property(szLength², &Vector2D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector2D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector2D::x).description(szX_Vector);
        w.property(szY, &Vector2D::y).description(szY_Vector);
        w.method(szZ, &Vector2D::z).description(szZ_Vector2);
        w.operate_self({ Operator::Add, Operator::Subtract });
        w.operate_with<double>();
        w.print<print_vector2<double>>();
    }

    {
        auto w = writer<Vector2F>();
        w.description("2D vector in float");
        w.property(szLength², &Vector2F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector2F::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector2F::x).description(szX_Vector);
        w.property(szY, &Vector2F::y).description(szY_Vector);
        w.method(szZ, &Vector2F::z).description(szZ_Vector2);
        w.print<print_vector2<float>>();
    }

    {
        auto w = writer<Vector2I>();
        w.description("2D vector in integer");
        w.property(szLength², &Vector2I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector2I::x).description(szX_Vector);
        w.property(szY, &Vector2I::y).description(szY_Vector);
        w.method(szZ, &Vector2I::z).description(szZ_Vector2);
        w.print<print_vector2<int>>();
    }

    {
        auto w = writer<Vector2U>();
        w.description("2D vector in unsigned integer");
        w.property(szLength², &Vector2U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector2U::x).description(szX_Vector);
        w.property(szY, &Vector2U::y).description(szY_Vector);
        w.method(szZ, &Vector2U::z).description(szZ_Vector2);
        w.print<print_vector2<unsigned>>();
    }

    {
        auto w = writer<Vector3D>();
        w.description("3D vector in double");
        w.property(szLength², &Vector3D::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector3D::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector3D::x).description(szX_Vector);
        w.property(szY, &Vector3D::y).description(szY_Vector);
        w.property(szZ, &Vector3D::z).description(szZ_Vector);
        w.operate_self({ Operator::Add, Operator::Subtract });
        w.operate_with<double>();
        w.print<print_vector3<double>>();
    }

    {
        auto w = writer<Vector3F>();
        w.description("3D vector in float");
        w.property(szLength², &Vector3F::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szLength, &Vector3F::length).description(szLength_Vector).alias(szLen);
        w.property(szX, &Vector3F::x).description(szX_Vector);
        w.property(szY, &Vector3F::y).description(szY_Vector);
        w.property(szZ, &Vector3F::z).description(szZ_Vector);
        w.print<print_vector3<float>>();
    }

    {
        auto w = writer<Vector3I>();
        w.description("3D vector in integer");
        w.property(szLength², &Vector3I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector3I::x).description(szX_Vector);
        w.property(szY, &Vector3I::y).description(szY_Vector);
        w.property(szZ, &Vector3I::z).description(szZ_Vector);
        w.print<print_vector3<int>>();
    }

    {
        auto w = writer<Vector3U>();
        w.description("3D vector in unsigned integer");
        w.property(szLength², &Vector3U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector3U::x).description(szX_Vector);
        w.property(szY, &Vector3U::y).description(szY_Vector);
        w.property(szZ, &Vector3U::z).description(szZ_Vector);
        w.print<print_vector3<unsigned>>();
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
        w.operate_self({ Operator::Add, Operator::Subtract });
        w.operate_with<double>();
        w.print<print_vector4<double>>();
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
        w.print<print_vector4<float>>();
    }

    {
        auto w = writer<Vector4I>();
        w.description("4D vector in integer");
        w.property(szLength², &Vector4I::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector4I::x).description(szX_Vector);
        w.property(szY, &Vector4I::y).description(szY_Vector);
        w.property(szZ, &Vector4I::z).description(szZ_Vector);
        w.property(szW, &Vector4I::w).description(szW_Vector);
        w.print<print_vector4<int>>();
    }

    {
        auto w = writer<Vector4U>();
        w.description("4D vector in unsigned integer");
        w.property(szLength², &Vector4U::length²).description(szLength²_Vector).alias(szLen²);
        w.property(szX, &Vector4U::x).description(szX_Vector);
        w.property(szY, &Vector4U::y).description(szY_Vector);
        w.property(szZ, &Vector4U::z).description(szZ_Vector);
        w.property(szW, &Vector4U::w).description(szW_Vector);
        w.print<print_vector4<unsigned>>();
    }
}

YQ_INVOKE(reg_vector_math();)

#include "vector/Bivector2.hxx"
#include "vector/Bivector3.hxx"
#include "vector/Bivector4.hxx"

#include "vector/Multivector1.hxx"
#include "vector/Multivector2.hxx"
#include "vector/Multivector3.hxx"
#include "vector/Multivector4.hxx"

#include "vector/Quadvector4.hxx"
#include "vector/Quaternion3.hxx"

#include "vector/Tensor33.hxx"

#include "vector/Trivector3.hxx"
#include "vector/Trivector4.hxx"

#include "vector/Vector1.hxx"
#include "vector/Vector2.hxx"
#include "vector/Vector3.hxx"
#include "vector/Vector4.hxx"

