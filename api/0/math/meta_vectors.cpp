////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <0/math/preamble.hpp>
#include <yq-toolbox/strings.hpp>


#include <yq-toolbox/vector/Bivector2.hpp>
#include <yq-toolbox/vector/Bivector3.hpp>
#include <yq-toolbox/vector/Bivector4.hpp>

#include <yq-toolbox/vector/Multivector1.hpp>
#include <yq-toolbox/vector/Multivector2.hpp>
#include <yq-toolbox/vector/Multivector3.hpp>
#include <yq-toolbox/vector/Multivector4.hpp>

#include <yq-toolbox/vector/Quadvector4.hpp>
#include <yq-toolbox/vector/Quaternion3.hpp>

#include <yq-toolbox/vector/Trivector3.hpp>
#include <yq-toolbox/vector/Trivector4.hpp>

#include <yq-toolbox/vector/Vector1.hpp>
#include <yq-toolbox/vector/Vector2.hpp>
#include <yq-toolbox/vector/Vector3.hpp>
#include <yq-toolbox/vector/Vector4.hpp>

#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/io/StreamOps.hpp>
#include <yq-toolbox/meta/Init.hpp>

#include <yq-toolbox/unit/literals.hpp>

using namespace yq;


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







//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//  OTHER HELPERS FOR MATH

namespace {
    template <typename T>
    void    print_quaternion3(Stream& str, const Quaternion3<T>& v)
    {
        str << "(" << v.w << "," << v.x << "," << v.y << "," << v.z << ")";
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

