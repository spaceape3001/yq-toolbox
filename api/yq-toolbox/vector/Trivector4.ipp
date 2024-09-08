////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Trivector4.hpp"

#include <yq-toolbox/strings.hpp>
#include <yq-toolbox/basic/DelayInit.hpp>
#include <yq-toolbox/meta/Init.hpp>
#include <yq-toolbox/vector/Bivector4.hpp>
#include <yq-toolbox/vector/Multivector4.hpp>
#include <yq-toolbox/vector/Quadvector4.hpp>
#include <yq-toolbox/vector/Vector4.hpp>

#include "Trivector4.hxx"

YQ_TYPE_IMPLEMENT(yq::Trivector4D)
YQ_TYPE_IMPLEMENT(yq::Trivector4F)

using namespace yq;

static void reg_trivector4()
{
    {
        auto w = writer<Trivector4D>();
        w.description("4D trivector in double");
        w.property(szXYZ, &Trivector4D::xyz).description(szXYZ_Trivector);
        w.property(szYZW, &Trivector4D::yzw).description(szYZW_Trivector);
        w.property(szZWX, &Trivector4D::zwx).description(szZWX_Trivector);
        w.property(szWXY, &Trivector4D::wxy).description(szWXY_Trivector);
        w.operate_self();
        w.operate_with<double>();
        w.operate_with<Bivector4D>();
        w.operate_with<Multivector4D>();
        w.operate_with<Quadvector4D>();
        w.operate_with<Vector4D>();
    }
    
    {
        auto w = writer<double>();
        w.operate_with<Trivector4D>();
    }

    {
        auto w = writer<Trivector4F>();
        w.description("4D trivector in float");
        w.property(szXYZ, &Trivector4F::xyz).description(szXYZ_Trivector);
        w.property(szYZW, &Trivector4F::yzw).description(szYZW_Trivector);
        w.property(szZWX, &Trivector4F::zwx).description(szZWX_Trivector);
        w.property(szWXY, &Trivector4F::wxy).description(szWXY_Trivector);
        w.operate_self();
        w.operate_with<float>();
        w.operate_with<Bivector4F>();
        w.operate_with<Multivector4F>();
        w.operate_with<Quadvector4F>();
        w.operate_with<Vector4F>();
    }

    {
        auto w = writer<float>();
        w.operate_with<Trivector4F>();
    }

}

YQ_INVOKE(reg_trivector4();)
