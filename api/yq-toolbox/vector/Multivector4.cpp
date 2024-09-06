////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Multivector4.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/vector/Bivector4.hpp>
#include <yq-toolbox/vector/Trivector4.hpp>
#include <yq-toolbox/vector/Vector4.hpp>

#include "Multivector4.hxx"

YQ_TYPE_IMPLEMENT(yq::Multivector4D)
YQ_TYPE_IMPLEMENT(yq::Multivector4F)

using namespace yq;

static void reg_multivector4()
{
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
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Bivector4D>();
        w.operate_with<Multivector4D>();
        w.operate_with<Quadvector4D>();
        w.operate_with<Trivector4D>();
        w.operate_with<Vector4D>();
    }

    {
        auto w = writer<double>();
        w.operate_with<Multivector4D>();
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
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Bivector4F>();
        w.operate_with<Multivector4F>();
        w.operate_with<Quadvector4F>();
        w.operate_with<Trivector4F>();
        w.operate_with<Vector4F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Multivector4F>();
    }
}

YQ_INVOKE(reg_multivector4();)
