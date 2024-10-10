////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Bivector4.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/vector/Multivector4.hpp>
#include <yq-toolbox/vector/Quadvector4.hpp>
#include <yq-toolbox/vector/Trivector4.hpp>
#include <yq-toolbox/vector/Vector4.hpp>

#include "Bivector4.hxx"

YQ_TYPE_IMPLEMENT(yq::Bivector4D)
YQ_TYPE_IMPLEMENT(yq::Bivector4F)

using namespace yq;

static void reg_bivector4()
{
    {
        auto w = writer<Bivector4D>();
        w.description("4D Bivector in double");
        w.property(szXY, &Bivector4D::xy).description(szXY_Bivector);
        w.property(szYZ, &Bivector4D::yz).description(szYZ_Bivector);
        w.property(szZW, &Bivector4D::zw).description(szZW_Bivector);
        w.property(szWX, &Bivector4D::wx).description(szWX_Bivector);
        w.property(szXZ, &Bivector4D::xz).description(szXZ_Bivector);
        w.property(szYW, &Bivector4D::yw).description(szYW_Bivector);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Multivector4D>();
        w.operate_with<Quadvector4D>();
        w.operate_with<Trivector4D>();
        w.operate_with<Vector4D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Bivector4D>();
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
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Multivector4F>();
        w.operate_with<Quadvector4F>();
        w.operate_with<Trivector4F>();
        w.operate_with<Vector4F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Bivector4F>();
    }
}

YQ_INVOKE(reg_bivector4();)
